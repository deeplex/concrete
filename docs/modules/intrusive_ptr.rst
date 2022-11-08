=========================
 Intrusive Smart Pointer
=========================

::

    #include <dplx/cncr/intrusive_ptr.hpp>
    namespace dplx::cncr {}

.. namespace:: dplx::cncr


Concepts
--------

.. concept:: template <typename RC> \
             ref_counted

    A type whose lifetime is managed by an internal reference counter and which
    has a :class:`reference_counted_traits <template<typename RC> reference_counted_traits>` 
    specialization for controlling the reference counter. 
    
    All functions are required to be ``noexcept``.

    **Notation**

    .. var:: RC &obj

        An lvalue reference to a reference counted object.

    **Valid Expressions**

    - :expr:`reference_counted_traits<RC>::counter_type` is the underlying
      integer type or void if unknown.
    - :expr:`reference_counted_traits<RC>::add_reference(obj)` increments 
      :expr:`obj`'s reference count by one.
    - :expr:`reference_counted_traits<RC>::release(obj)` decrements
      :expr:`obj`'s reference count by one and atomically destructs it if the
      reference count reached zero.

.. concept:: template <typename RC> inspectable_ref_counted

    Requires that a :concept:`ref_counted <template<typename RC> ref_counted>` 
    type also provides a way to get an estimate of the current reference count.
    Not requiring the value to be excact allows reference counted objects 
    shared across multiple threads to satisfy this.

    The only value required to be stable is ``1`` in which case our thread
    should be the only pointee. (With the exception of insane software 
    architectures which retain non owning across threads).

    All functions are required to be ``noexcept``.

    **Notation**

    .. var:: RC &obj

        An lvalue reference to a reference counted object.

    **Valid Expressions**

    - :expr:`reference_counted_traits<RC>::counter_type` is the underlying
      integer type.
    - :expr:`reference_counted_traits<RC>::reference_count(obj)` returns an 
      (estimate) of the current counter value of type ``counter_type``.

.. concept:: template <ref_counted RC> detail::dplx_ref_counted

    *Exposition Only*

    Describes the typical deeplex reference counting API.

    All functions are required to be ``noexcept``.

    **Notation**

    .. var:: RC const &obj

        An lvalue reference to a reference counted object.

    **Valid Expressions**

    - :expr:`obj.add_reference()` increments the reference counter.
    - :expr:`obj.release()` decrements the reference counter.
    - :expr:`obj.reference_count()` retrieves the current (approximate) 
      reference count.

Customization Points
--------------------

.. class:: template <typename RC> \
           reference_counted_traits

    This is a customization point i.e. there is no primary template definition.

    The implementation requirements are described by the :concept:`ref_counted`
    and :concept:`inspectable_ref_counted` concepts.

.. class:: template <detail::dplx_ref_counted RC> \
           reference_counted_traits<RC>

    The specialization of :class:`reference_counted_traits <dplx::cncr::reference_counted_traits>`
    for types satisfying :concept:`detail::dplx_ref_counted`.

    The specialization satisfies :concept:`inspectable_ref_counted`.


Factory Functions
-----------------

.. function:: template <ref_counted RC> \
              constexpr auto intrusive_ptr_import(RC *obj) -> intrusive_ptr<RC>

    Creates a :expr:`intrusive_ptr<RC>` tracking :expr:`obj` assuming ownership 
    of an existing reference (i.e. it doesn't call ``add_reference()``)

    It is a type deducing wrapper around :expr:`intrusive_ptr<RC>::import`.

.. function:: template <ref_counted RC> \
              constexpr auto intrusive_ptr_acquire(RC *obj) -> intrusive_ptr<RC>

    Creates a :expr:`intrusive_ptr<RC>` tracking :expr:`obj` assuming ownership 
    by acquiring a new reference (i.e. it calls ``add_reference()``).

    It is a type deducing wrapper around :expr:`intrusive_ptr<RC>::acquire`.


Types
-----

.. class:: template <ref_counted RC> \
           intrusive_ptr<RC, RC>

    The usual intrusive smart pointer which poses as a pointer to the object
    whose lifetime it manages.

    The type satisfies `std::regular <https://en.cppreference.com/w/cpp/concepts/regular>`_,
    i.e. it is default initializable, copyable and equality comparable.
    It is also swappable, totally ordered and contextually convertible to bool.

    Additionally the following members exist:

    .. type:: element_type = RC

        Exposes the type parameter for meta programming purposes.

    .. type:: handle_type = intrusive_ptr<RC>

        Exposes the type which is used for reference counting. It is exposed for
        compatibility with the aliasing variant :class:`intrusive_ptr\<T, RC> <template <typename T, ref_counted RC> dplx::cncr::intrusive_ptr>`
        whose :expr:`element_type` is not equal to :expr:`RC`.

    .. function:: constexpr intrusive_ptr(std::nullptr_t) noexcept

        Constructs an empty instance from a :expr:`nullptr` literal which makes
        the following expressions well formed:

        ::

            intrusive_ptr<T> ptr{nullptr};
            ptr = nullptr;

    .. function:: template<ref_counted U> \
                  constexpr intrusive_ptr(intrusive_ptr<U> &&other) noexcept

        Imports ownership from a compatible :expr:`intrusive_ptr<U>` instance.

        This constructor is only available if 
        :expr:`std::convertible_to<U *, RC *>` holds.

    .. function:: template<ref_counted U> \
                  constexpr intrusive_ptr(intrusive_ptr<U> const &other) noexcept

        Aquires ownership from a compatible :expr:`intrusive_ptr<U>` instance.

        This constructor is only available if 
        :expr:`std::convertible_to<U *, RC *>` holds.

    .. function:: static constexpr auto import(RC *ptr) noexcept -> intrusive_ptr<RC>

        Creates a :expr:`intrusive_ptr<RC>` tracking :expr:`ptr` assuming ownership of
        an existing reference (i.e. it doesn't call ``add_reference()``).

    .. function:: static constexpr auto acquire(RC *ptr) noexcept -> intrusive_ptr<RC>

        Creates a :expr:`intrusive_ptr<RC>` tracking :expr:`ptr` assuming ownership by
        acquiring a new reference (i.e. it calls ``add_reference()``).

    .. function:: constexpr auto get() const noexcept -> RC *

        Retrieves the stored object pointer.

    .. function:: constexpr auto get_handle() const noexcept -> intrusive_ptr<RC>

        Returns a copy of ``this``. It is exposed for compatibility with the
        aliasing variant :class:`intrusive_ptr\<T, RC> <template <typename T, ref_counted RC> dplx::cncr::intrusive_ptr>`
        whose :expr:`element_type` is not equal to :expr:`RC`.

    .. function:: constexpr auto use_count() const noexcept -> reference_counted_traits<RC>::counter_type
    .. function:: constexpr auto reference_count() const noexcept -> reference_counted_traits<RC>::counter_type

        If :expr:`RC` satisfies :concept:`inspectable_ref_counted` it returns the
        (approximate) number of references. The only value guaranteed to be stable
        in multi-threaded environments is ``1``.

        The :func:`use_count` name exists for API compatibility with 
        ``std::shared_ptr``.

    .. function:: constexpr auto release() noexcept -> RC *

        Returns the bound object after unbinding ``this`` without decrementing
        the reference counter.

    .. function::  constexpr void reset(RC *toBeBound) noexcept

        Replaces the managed object with :expr:`toBeBound` and increases its ref
        count.

.. class:: template <> \
           intrusive_ptr<void, void>

    A type erased intrusive pointer. It keeps a pointer to a vtable in addition
    to a `void *` referencing the bound object.

    The type satisfies `std::regular <https://en.cppreference.com/w/cpp/concepts/regular>`_,
    i.e. it is default initializable, copyable and equality comparable.
    It is also swappable, totally ordered and contextually convertible to bool.

    You can either (copy) assign normal intrusive pointer instances or use the
    static class functions :func:`import <template<ref_counted RC> import>` or
    :func:`acquire <template<ref_counted RC> acquire>`

    Additionally the following members exist:

    .. type:: element_type = void

        Exposes the type parameter for meta programming purposes.

    .. type:: handle_type = intrusive_ptr<void, void>

        Exposes the type which is used for reference counting. It is exposed for
        compatibility with the aliasing variant :class:`intrusive_ptr\<T, RC> <template <typename T, ref_counted RC> dplx::cncr::intrusive_ptr>`
        whose :expr:`element_type` is not equal to :expr:`void`.

    .. function:: intrusive_ptr(std::nullptr_t) noexcept

        Constructs an empty instance from a :expr:`nullptr` literal which makes
        the following expressions well formed:

        ::

            intrusive_ptr<void> ptr{nullptr};
            ptr = nullptr;

    .. function:: template <ref_counted U> intrusive_ptr(intrusive_ptr<U> &&other) noexcept

        Imports ownership from an :expr:`intrusive_ptr<U>` instance.

    .. function:: template <ref_counted U> intrusive_ptr(intrusive_ptr<U> const &other) noexcept

        Aquires ownership from an :expr:`intrusive_ptr<U>` instance.

    .. function:: template <ref_counted RC> static auto import(RC *ptr) noexcept -> intrusive_ptr<void, void>

        Creates a :expr:`intrusive_ptr<void, void>` tracking :expr:`ptr` 
        assuming ownership of an existing reference (i.e. it doesn't call 
        ``add_reference()``).

    .. function:: template <ref_counted RC> static auto acquire(RC *ptr) noexcept -> intrusive_ptr<void, void>

        Creates a :expr:`intrusive_ptr<void, void>` tracking :expr:`ptr` 
        assuming ownership by acquiring a new reference (i.e. it calls 
        ``add_reference()``).

    .. function:: auto get() const noexcept -> void *

        Retrieves the stored object pointer.

    .. function:: auto get_handle() const noexcept -> intrusive_ptr<void>

        Returns a copy of ``this``. It is exposed for compatibility with the
        aliasing variant :class:`intrusive_ptr\<T, RC> <template <typename T, ref_counted RC> dplx::cncr::intrusive_ptr>`
        whose :expr:`element_type` is not equal to :expr:`void`.

    .. function:: template <ref_counted U> auto release_as() noexcept -> U *

        Returns the bound object pointer after casting it to :expr:`U` after
        unbinding ``this`` without decrementing the reference counter.

.. class:: template <typename T, ref_counted RC = T> \
           intrusive_ptr

    The main template is an aliasing intrusive pointer which means it poses as
    a pointer to an object of type :expr:`T` while managing the reference count
    of (a potentially different) object of type :expr:`RC`.

    The type satisfies `std::regular <https://en.cppreference.com/w/cpp/concepts/regular>`_,
    i.e. it is default initializable, copyable and equality comparable.
    It is also swappable, totally ordered and contextually convertible to bool.

    Additionally the following members exist:

    .. type:: element_type = T

        Exposes the type parameter for meta programming purposes.

    .. type:: handle_type = intrusive_ptr<RC>

        Exposes the intrusive pointer type which implements reference counting.

    .. function:: constexpr intrusive_ptr(std::nullptr_t) noexcept

        Constructs an empty instance from a :expr:`nullptr` literal which makes
        the following expressions well formed:

        ::

            intrusive_ptr<T, RC> ptr{nullptr};
            ptr = nullptr;

    .. function:: constexpr intrusive_ptr(intrusive_ptr<RC> &&handle, T *ptr) noexcept

        Creates a :expr:`intrusive_ptr<T, RC>` tracking :expr:`handle` assuming ownership of
        an existing reference (i.e. it doesn't call ``add_reference()``).

        The constructed intrusive pointer poses as :expr:`ptr` afterwards.

    .. function:: constexpr intrusive_ptr(intrusive_ptr<RC> const &handle, T *ptr) noexcept

        Creates a :expr:`intrusive_ptr<T, RC>` tracking :expr:`handle` assuming ownership by
        acquiring a new reference (i.e. it calls ``add_reference()``).

        The constructed intrusive pointer poses as :expr:`ptr` afterwards.

    .. function:: constexpr auto get() const noexcept -> T *

        Retrieves the stored aliased object pointer.

    .. function:: constexpr auto get_handle() const noexcept -> intrusive_ptr<RC>

        Returns a copy of the contained object handle.

    .. function:: constexpr auto use_count() const noexcept -> reference_counted_traits<RC>::counter_type
    .. function:: constexpr auto reference_count() const noexcept -> reference_counted_traits<RC>::counter_type

        If :expr:`RC` satisfies :concept:`inspectable_ref_counted` it returns the
        (approximate) number of references. The only value guaranteed to be stable
        in multi-threaded environments is ``1``.

        The :func:`use_count` name exists for API compatibility with 
        ``std::shared_ptr``.

