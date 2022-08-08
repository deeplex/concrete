
// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <concepts>
#include <utility>

namespace dplx::cncr
{

template <typename T, typename = void>
struct reference_counted_traits;

// clang-format off
template <typename RC>
concept ref_counted = requires(RC &v)
{
    typename reference_counted_traits<RC>;
    typename reference_counted_traits<RC>::counter_type;
    { reference_counted_traits<RC>::add_reference(v) } noexcept;
    { reference_counted_traits<RC>::release(v) } noexcept;
};
// clang-format on

// clang-format off
template <typename RC>
concept inspectable_ref_counted = ref_counted<RC> && requires(RC &v)
{
    typename reference_counted_traits<RC>::counter_type;
    { reference_counted_traits<RC>::reference_count(v) } noexcept
        -> std::same_as<typename reference_counted_traits<RC>::counter_type>;
};
// clang-format on

namespace detail
{

// clang-format off
template <typename RC>
concept dplx_ref_counted = requires(RC const &obj)
{
    { obj.add_reference() } noexcept;
    { obj.release() } noexcept;
    { obj.reference_count() } noexcept;
};
// clang-format on

} // namespace detail

template <detail::dplx_ref_counted RC>
struct reference_counted_traits<RC>
{
    using counter_type = decltype(std::declval<RC &>().reference_count());

    static constexpr void add_reference(RC &v) noexcept
    {
        v.add_reference();
    }
    static constexpr void release(RC &v) noexcept
    {
        v.release();
    }

    static constexpr auto reference_count(RC &v) noexcept
    {
        return v.reference_count();
    }
};

namespace detail
{

template <ref_counted RC>
struct erased_ref_ops final
{
    using traits = reference_counted_traits<RC>;

    static void add_reference(void *h) noexcept
    {
        traits::add_reference(*static_cast<RC *>(h));
    }
    static void release(void *h) noexcept
    {
        traits::release(*static_cast<RC *>(h));
    }
};

struct ref_ops_vtable final
{
    using op_fn = void (*)(void *) noexcept;

    op_fn add_reference;
    op_fn release;
};

template <typename RC>
inline constexpr ref_ops_vtable ref_ops_vtable_of{
        &erased_ref_ops<RC>::add_reference,
        &erased_ref_ops<RC>::release,
};

} // namespace detail

template <typename RC>
concept erased_or_ref_counted = std::same_as<RC, void> || ref_counted<RC>;

template <typename T, erased_or_ref_counted RC = T>
class intrusive_ptr;

constexpr inline struct intrusive_ptr_import_fn
{
    template <ref_counted RC>
    auto operator()(RC *referenceCounted) const noexcept -> intrusive_ptr<RC>
    {
        return intrusive_ptr<RC>::import(referenceCounted);
    }
} intrusive_ptr_import{};

constexpr inline struct intrusive_ptr_acquire_fn
{
    template <ref_counted RC>
    auto operator()(RC *referenceCounted) const noexcept -> intrusive_ptr<RC>
    {
        return intrusive_ptr<RC>::acquire(referenceCounted);
    }
} intrusive_ptr_acquire;

///
/// @brief A smart pointer managing objects whose lifetime is governed by an
///        internal reference counter accessible via
///        @ref reference_counted_traits.
///
/// The API is drop-in compatible with std::shared_ptr except weak references.
///
template <erased_or_ref_counted RC>
class intrusive_ptr<RC, RC> final
{
    using traits = reference_counted_traits<RC>;

    RC *mPtr;

public:
    constexpr ~intrusive_ptr() noexcept
    {
        if (mPtr)
        {
            traits::release(*mPtr);
        }
    }
    constexpr intrusive_ptr() noexcept
        : mPtr{}
    {
    }

    constexpr intrusive_ptr(intrusive_ptr const &other) noexcept
        : mPtr{other.mPtr}
    {
        if (mPtr)
        {
            traits::add_reference(*mPtr);
        }
    }
    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment): we took care
    constexpr auto operator=(intrusive_ptr const &other) noexcept
            -> intrusive_ptr &
    {
        if (other.mPtr)
        {
            traits::add_reference(*other.mPtr);
        }
        if (mPtr)
        {
            traits::release(*mPtr);
        }
        mPtr = other.mPtr;
        return *this;
    }

    constexpr intrusive_ptr(intrusive_ptr &&other) noexcept
        : mPtr{std::exchange(other.mPtr, nullptr)}
    {
    }
    constexpr auto operator=(intrusive_ptr &&other) noexcept -> intrusive_ptr &
    {
        if (mPtr)
        {
            traits::release(*mPtr);
        }
        mPtr = std::exchange(other.mPtr, nullptr);
        return *this;
    }

    friend inline constexpr void swap(intrusive_ptr &lhs,
                                      intrusive_ptr &rhs) noexcept
    {
        using std::swap;
        swap(lhs.mPtr, rhs.mPtr);
    }

    constexpr intrusive_ptr(std::nullptr_t) noexcept
        : mPtr{}
    {
    }

    template <ref_counted U>
        requires std::convertible_to<U *, RC *>
    constexpr intrusive_ptr(intrusive_ptr<U> const &other) noexcept
        : mPtr(other.get())
    {
        if (mPtr)
        {
            traits::add_reference(*mPtr);
        }
    }
    template <ref_counted U>
        requires std::convertible_to<U *, RC *>
    constexpr intrusive_ptr(intrusive_ptr<U> &&other) noexcept
        : mPtr(other.release())
    {
    }

private:
    explicit constexpr intrusive_ptr(RC *referenceCounted) noexcept
        : mPtr{referenceCounted}
    {
    }

public:
    /// @brief Creates a intrusive_ptr tracking ptr assuming ownership of an
    ///        existing reference (i.e. it doesn't call add_reference)
    /// @param ptr the object to be tracked (may be a nullptr)
    /// @return the created intrusive_ptr
    static constexpr auto import(RC *ptr) noexcept -> intrusive_ptr
    {
        return intrusive_ptr(ptr);
    }
    /// @brief Creates a intrusive_ptr tracking ptr assuming ownership by
    /// acquiring a
    ///        new reference (i.e. it calls add_reference)
    /// @param ptr the object to be tracked (may be a nullptr)
    /// @return the created intrusive_ptr
    static constexpr auto acquire(RC *ptr) noexcept -> intrusive_ptr
    {
        if (ptr)
        {
            traits::add_reference(*ptr);
        }
        return intrusive_ptr(ptr);
    }

    using element_type = RC;
    using handle_type = intrusive_ptr;

    /// @brief Returns true if an object is bound false otherwise
    constexpr explicit operator bool() const noexcept
    {
        return mPtr != nullptr;
    }

    /// @brief Returns a pointer to the bound object or nullptr if empty.
    constexpr auto get() const noexcept -> RC *
    {
        return mPtr;
    }
    constexpr auto get_handle() const noexcept -> intrusive_ptr<RC>
    {
        return *this;
    }
    constexpr auto operator*() const noexcept -> RC &
    {
        return *mPtr;
    }
    constexpr auto operator->() const noexcept -> RC *
    {
        return mPtr;
    }

    /// @brief If T satisfies inspectable_ref_counted it returns the
    ///        (approximate) number of references. The only value guaranteed to
    ///        be stable in multi-threaded environments is ``1``. This API
    ///        behaves the same as @ref reference_count and exists for
    ///        std::shared_ptr compatibility.
    constexpr auto use_count() const noexcept ->
            typename traits::counter_type requires inspectable_ref_counted<RC>

    {
        return traits::reference_count(*mPtr);
    }
    /// @brief If T satisfies inspectable_ref_counted it returns the
    ///        (approximate) number of references. The only value guaranteed to
    ///        be stable in multi-threaded environments is ``1``.
    constexpr auto reference_count() const noexcept ->
            typename traits::counter_type requires inspectable_ref_counted<RC>

    {
        return traits::reference_count(*mPtr);
    }

    /// @brief Returns the bound object after unbinding this without
    ///        decrementing the reference counter.
    constexpr auto release() noexcept -> RC *
    {
        return std::exchange(mPtr, nullptr);
    }
    /// @brief Replaces the managed object and binds the new
    /// @param toBeBound will be pointed to and its reference count increased
    constexpr void reset(RC *toBeBound) noexcept
    {
        *this = acquire(toBeBound);
    }

    friend inline auto operator==(intrusive_ptr const &,
                                  intrusive_ptr const &) noexcept -> bool
            = default;
    friend inline auto operator<=>(intrusive_ptr const &,
                                   intrusive_ptr const &) noexcept
            -> std::strong_ordering = default;
};

template <>
class intrusive_ptr<void, void> final
{
    detail::ref_ops_vtable const *mVTable;
    void *mPtr;

public:
    ~intrusive_ptr() noexcept
    {
        if (mPtr != nullptr)
        {
            mVTable->release(mPtr);
        }
    }
    intrusive_ptr() noexcept
        : mVTable{nullptr}
        , mPtr{nullptr}
    {
    }

    intrusive_ptr(intrusive_ptr const &other) noexcept
        : mVTable{other.mVTable}
        , mPtr{other.mPtr}
    {
        if (mPtr != nullptr)
        {
            mVTable->add_reference(mPtr);
        }
    }

    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment): we took care
    auto operator=(intrusive_ptr const &other) noexcept -> intrusive_ptr &
    {
        if (other.mPtr != nullptr)
        {
            other.mVTable->add_reference(other.mPtr);
        }
        if (mPtr != nullptr)
        {
            mVTable->release(mPtr);
        }
        mVTable = other.mVTable;
        mPtr = other.mPtr;

        return *this;
    }

    intrusive_ptr(intrusive_ptr &&other) noexcept
        : mVTable{std::exchange(other.mVTable, nullptr)}
        , mPtr{std::exchange(other.mPtr, nullptr)}
    {
    }
    auto operator=(intrusive_ptr &&other) noexcept -> intrusive_ptr &
    {
        if (mPtr != nullptr)
        {
            mVTable->release(mPtr);
        }
        mVTable = std::exchange(other.mVTable, nullptr);
        mPtr = std::exchange(other.mPtr, nullptr);

        return *this;
    }

    friend inline void swap(intrusive_ptr &lhs, intrusive_ptr &rhs) noexcept
    {
        using std::swap;
        swap(lhs.mVTable, rhs.mVTable);
        swap(lhs.mPtr, rhs.mPtr);
    }

private:
    explicit intrusive_ptr(detail::ref_ops_vtable const *vTable, void *handle)
        : mVTable{vTable}
        , mPtr{handle}
    {
    }

public:
    template <ref_counted U>
    static auto import(U *toBeBound) noexcept -> intrusive_ptr
    {
        if (toBeBound == nullptr)
        {
            return {};
        }
        return intrusive_ptr(&detail::ref_ops_vtable_of<U>, toBeBound);
    }
    template <ref_counted U>
    static auto acquire(U *toBeBound) noexcept -> intrusive_ptr
    {
        if (toBeBound == nullptr)
        {
            return {};
        }
        reference_counted_traits<U>::add_reference(*toBeBound);
        return intrusive_ptr(&detail::ref_ops_vtable_of<U>, toBeBound);
    }

    intrusive_ptr(std::nullptr_t) noexcept
        : intrusive_ptr{}
    {
    }

    template <ref_counted U>
    intrusive_ptr(intrusive_ptr<U> const &other) noexcept
        : mVTable(other ? &detail::ref_ops_vtable_of<U> : nullptr)
        , mPtr(other.get())
    {
        if (other)
        {
            reference_counted_traits<U>::add_reference(*other);
        }
    }
    template <ref_counted U>
    intrusive_ptr(intrusive_ptr<U> &&other) noexcept
        : mVTable(other ? &detail::ref_ops_vtable_of<U> : nullptr)
        , mPtr(other.release())
    {
    }

    using element_type = void;
    using handle_type = intrusive_ptr;

    /// @brief Returns true if an object is bound false otherwise
    explicit operator bool() const noexcept
    {
        return mPtr != nullptr;
    }

    /// @brief Returns a pointer to the bound object or nullptr if empty.
    [[nodiscard]] auto get() const noexcept -> void *
    {
        return mPtr;
    }
    [[nodiscard]] auto get_handle() const noexcept -> intrusive_ptr<void>
    {
        return *this;
    }
    template <ref_counted U>
    auto release_as() noexcept -> U *
    {
        mVTable = nullptr;
        return static_cast<U *>(std::exchange(mPtr, nullptr));
    }

    friend inline auto operator==(intrusive_ptr const &lhs,
                                  intrusive_ptr const &rhs) noexcept -> bool
    {
        return lhs.mPtr == rhs.mPtr;
    }
    friend inline auto operator<=>(intrusive_ptr const &lhs,
                                   intrusive_ptr const &rhs) noexcept
            -> std::strong_ordering
    {
        return lhs.mPtr <=> rhs.mPtr;
    }
};

template <typename T, erased_or_ref_counted RC>
class intrusive_ptr
{
    T *mPtr;
    intrusive_ptr<RC> mHandle;

public:
    constexpr intrusive_ptr() noexcept
        : mPtr{}
        , mHandle{}
    {
    }

    constexpr intrusive_ptr(intrusive_ptr const &) noexcept = default;
    constexpr auto operator=(intrusive_ptr const &) noexcept
            -> intrusive_ptr & = default;

    constexpr intrusive_ptr(intrusive_ptr &&other) noexcept
        : mPtr{std::exchange(other.mPtr, nullptr)}
        , mHandle{static_cast<intrusive_ptr<RC> &&>(other.mHandle)}
    {
    }
    constexpr auto operator=(intrusive_ptr &&other) noexcept -> intrusive_ptr &
    {
        mPtr = std::exchange(other.mPtr, nullptr);
        mHandle = static_cast<intrusive_ptr<RC> &&>(other.mHandle);
        return *this;
    }

    friend inline void swap(intrusive_ptr &lhs, intrusive_ptr &rhs) noexcept
    {
        using std::swap;
        swap(lhs.mPtr, rhs.mPtr);
        swap(lhs.mHandle, rhs.mHandle);
    }

    constexpr intrusive_ptr(std::nullptr_t) noexcept
        : intrusive_ptr{}
    {
    }

    constexpr intrusive_ptr(intrusive_ptr<RC> const &handle, T *ptr) noexcept
        : mPtr{handle && ptr ? ptr : nullptr}
        , mHandle{handle && ptr ? handle : nullptr}
    {
    }
    template <erased_or_ref_counted U>
        requires std::constructible_from<intrusive_ptr<RC>, intrusive_ptr<U>>
    constexpr intrusive_ptr(intrusive_ptr<U> const &handle, T *ptr) noexcept
        : mPtr{handle && ptr ? ptr : nullptr}
        , mHandle{handle && ptr ? handle : nullptr}
    {
    }
    constexpr intrusive_ptr(intrusive_ptr<RC> &&handle, T *ptr) noexcept
        : mPtr{handle && ptr ? ptr : nullptr}
        , mHandle{handle && ptr ? static_cast<intrusive_ptr<RC> &&>(handle)
                                : intrusive_ptr<RC>{}}
    {
    }
    template <erased_or_ref_counted U>
        requires std::constructible_from<intrusive_ptr<RC>, intrusive_ptr<U>>
    constexpr intrusive_ptr(intrusive_ptr<U> &&handle, T *ptr) noexcept
        : mPtr{handle && ptr ? ptr : nullptr}
        , mHandle{handle && ptr ? static_cast<intrusive_ptr<U> &&>(handle)
                                : intrusive_ptr<U>{}}
    {
    }

    using element_type = T;
    using handle_type = intrusive_ptr<RC>;

    explicit operator bool() const noexcept
    {
        return mPtr != nullptr;
    }

    constexpr auto operator*() const noexcept -> T &
    {
        return *mPtr;
    }
    constexpr auto operator->() const noexcept -> T *
    {
        return mPtr;
    }

    friend constexpr auto operator==(intrusive_ptr const &,
                                     intrusive_ptr const &) noexcept -> bool
            = default;

    constexpr auto get() const noexcept -> T *
    {
        return mPtr;
    }
    constexpr auto get_handle() &&noexcept -> intrusive_ptr<RC>
    {
        mPtr = nullptr;
        return std::move(mHandle);
    }
    constexpr auto get_handle() const &noexcept -> intrusive_ptr<RC> const &
    {
        return mHandle;
    }

    /// @brief If T satisfies inspectable_ref_counted it returns the
    ///        (approximate) number of references. Only the value 1 is
    ///        guaranteed to be stable even in multi-threaded environments. This
    ///        API behaves the same as @ref reference_count and exists for
    ///        std::shared_ptr compatibility.
    constexpr auto use_count() const noexcept ->
            typename reference_counted_traits<RC>::counter_type requires
            inspectable_ref_counted<RC>

    {
        return mHandle.use_count();
    }
    /// @brief If T satisfies inspectable_ref_counted it returns the
    ///        (approximate) number of references. Only the value 1 is
    ///        guaranteed to be stable even in multi-threaded environments.
    constexpr auto reference_count() const noexcept ->
            typename reference_counted_traits<RC>::counter_type requires
            inspectable_ref_counted<RC>

    {
        return mHandle.reference_count();
    }
};

template <erased_or_ref_counted T, erased_or_ref_counted U>
inline auto static_pointer_cast(intrusive_ptr<U> const &ptr) noexcept
        -> intrusive_ptr<T>
{
    return intrusive_ptr<T>::acquire(static_cast<T *>(ptr.get()));
}
template <erased_or_ref_counted T, ref_counted U>
inline auto static_pointer_cast(intrusive_ptr<U> &&ptr) noexcept
        -> intrusive_ptr<T>
{
    return intrusive_ptr<T>::import(static_cast<T *>(ptr.release()));
}
template <erased_or_ref_counted T>
inline auto static_pointer_cast(intrusive_ptr<void> &&ptr) noexcept
        -> intrusive_ptr<T>
{
    return intrusive_ptr<T>::import(ptr.template release_as<T>());
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto static_pointer_cast(intrusive_ptr<From, RC> const &ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    return intrusive_ptr<To, RC>{ptr.get_handle(),
                                 static_cast<To *>(ptr.get())};
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto static_pointer_cast(intrusive_ptr<From, RC> &&ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    auto *const alias = static_cast<To *>(ptr.get());
    return intrusive_ptr<To, RC>{
            static_cast<intrusive_ptr<From, RC> &&>(ptr).get_handle(), alias};
}

template <ref_counted T, ref_counted U>
inline auto dynamic_pointer_cast(intrusive_ptr<U> const &ptr) noexcept
        -> intrusive_ptr<T>
{
    return intrusive_ptr<T>::acquire(dynamic_cast<T *>(ptr.get()));
}
template <ref_counted T, ref_counted U>
inline auto dynamic_pointer_cast(intrusive_ptr<U> &&ptr) noexcept
        -> intrusive_ptr<T>
{
    return intrusive_ptr<T>::import(dynamic_cast<T *>(ptr.release()));
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto dynamic_pointer_cast(intrusive_ptr<From, RC> const &ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    return intrusive_ptr<To, RC>{ptr.get_handle(),
                                 dynamic_cast<To *>(ptr.get())};
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto dynamic_pointer_cast(intrusive_ptr<From, RC> &&ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    auto *const alias = dynamic_cast<To *>(ptr.get());
    return intrusive_ptr<To, RC>{
            static_cast<intrusive_ptr<From, RC> &&>(ptr).get_handle(), alias};
}

template <ref_counted T, ref_counted U>
inline auto const_pointer_cast(intrusive_ptr<U> const &ptr) noexcept
        -> intrusive_ptr<T>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return intrusive_ptr<T>::acquire(const_cast<T *>(ptr.get()));
}
template <ref_counted T, ref_counted U>
inline auto const_pointer_cast(intrusive_ptr<U> &&ptr) noexcept
        -> intrusive_ptr<T>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return intrusive_ptr<T>::import(const_cast<T *>(ptr.release()));
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto const_pointer_cast(intrusive_ptr<From, RC> const &ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return intrusive_ptr<To, RC>{ptr.get_handle(), const_cast<To *>(ptr.get())};
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto const_pointer_cast(intrusive_ptr<From, RC> &&ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    auto *const alias = const_cast<To *>(ptr.get());
    return intrusive_ptr<To, RC>{
            static_cast<intrusive_ptr<From, RC> &&>(ptr).get_handle(), alias};
}

template <typename T, erased_or_ref_counted U>
inline auto reinterpret_pointer_cast(intrusive_ptr<U> const &ptr) noexcept
        -> intrusive_ptr<T>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return intrusive_ptr<T>::acquire(reinterpret_cast<T *>(ptr.get()));
}
template <typename T, ref_counted U>
inline auto reinterpret_pointer_cast(intrusive_ptr<U> &&ptr) noexcept
        -> intrusive_ptr<T>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return intrusive_ptr<T>::import(reinterpret_cast<T *>(ptr.release()));
}
template <typename T>
inline auto reinterpret_pointer_cast(intrusive_ptr<void> &&ptr) noexcept
        -> intrusive_ptr<T>
{
    return intrusive_ptr<T>::import(ptr.template release_as<T>());
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto
reinterpret_pointer_cast(intrusive_ptr<From, RC> const &ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    return intrusive_ptr<To, RC>{
            ptr.get_handle(),
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            reinterpret_cast<To *>(ptr.get())};
}
template <typename To, typename From, erased_or_ref_counted RC>
inline auto reinterpret_pointer_cast(intrusive_ptr<From, RC> &&ptr) noexcept
        -> intrusive_ptr<To, RC>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    auto *const alias = reinterpret_cast<To *>(ptr.get());
    return intrusive_ptr<To, RC>{
            static_cast<intrusive_ptr<From, RC> &&>(ptr).get_handle(), alias};
}

} // namespace dplx::cncr
