
=================
 Misc. functions
=================

::

    #include <dplx/cncr/misc.hpp>
    namespace dplx::cncr {}


.. namespace:: dplx::cncr


.. function:: template <typename Enum> \
                  requires std::is_enum_v<Enum> \
              constexpr auto to_underlying(Enum value) noexcept -> \
                      typename std::underlying_type<Enum>::type

    A backport of C++23 `to_underlying(Enum value) <https://en.cppreference.com/w/cpp/utility/to_underlying>`_.

    :returns: The underlying integer value with the deduced underlying type.


.. function:: template <std::size_t N, typename T> \
              consteval auto make_byte_array(std::initializer_list<T> vs, T dv) noexcept \
                      -> std::array<std::byte, N>

    Casts every provided value to :texpr:`std::byte` and returns a brace initialized array with the results.

    :param T dv: a default value which is used in case of :expr:`vs.size() < N`
    :returns: A byte array filled with the provided values.


.. function:: template <typename R, std::size_t N, typename Fn, typename... Args> \
              constexpr auto sequence_init(Fn &&initFn, Args &&... args) -> R

    The return object is brace initialized by the results of :texpr:`N`
    invocations of :expr:`std::invoke(initFn, args..., cncr::mp_size_t<n>{})`
    where :texpr:`n` is the current counter value starting at 0.

    This helper function is mainly useful for constexpr initializing complex
    array class members::

        struct chunk_cfg;
        struct data_chunk
        {
            data_chunk() = delete;
            explicit constexpr data_chunk(const chunk_cfg &cfg);
        };
        template <std::size_t N>
        class data_container
        {
            using chunks_type = std::array<data_chunk, N>;
            chunks_type chunks;
            static constexpr data_chunk init_chunk(const chunk_cfg &cfg, [[maybe_unused]] std::size_t n)
            {
                return data_chunk(cfg);
            }
        public:
            constexpr data_container(const chunk_cfg &cfg)
                : chunks(dplx::cncr::sequence_init<chunks_type, N>(init_chunk, cfg))
            {
            }
        }

.. function:: template <typename R, typename Fx, typename... Args> \
              constexpr auto sequence_init(Fx &&initFn, Args &&... args) -> R

    Invokes :func:`template \<typename R, std::size_t N, typename Fn, typename... Args> sequence_init`
    with :expr:`N = std::size(R{})`.

.. struct:: is_null_byte_fn

    .. function:: constexpr auto operator()(std::byte const value) const noexcept -> bool

        :returns: :expr:`value == std::byte{}`

.. function:: constexpr auto is_null_byte(std::byte const value) noexcept -> bool

    :returns: :expr:`value == std::byte{}`

.. struct:: is_non_null_byte_fn

    .. function:: constexpr auto operator()(std::byte const value) const noexcept -> bool

        :returns: :expr:`value != std::byte{}`

.. function:: constexpr auto is_non_null_byte(std::byte const value) noexcept -> bool

    :returns: :expr:`value != std::byte{}`
