Misc. functions
===============

::

    #include <dplx/cncr/misc.hpp>
    namespace dplx::cncr {}


.. namespace:: dplx::cncr


.. function:: template <typename T, typename U> \
              constexpr std::common_type_t<T, U> div_ceil(T dividend, U divisor) noexcept

    :returns: :math:`\lceil dividend/divisor \rceil`


.. function:: template <typename T, typename U> \
              constexpr std::common_type_t<T, U> mod(T k, U n) noexcept

    Maps k into the quotient ring :math:`Z / nZ`.

    :param U n: must be > 0


.. function:: constexpr std::uint64_t upow(std::uint64_t x, std::uint64_t e) noexcept

    :returns: :math:`x^e`


.. function:: template <typename... Ts> \
              constexpr std::array<std::byte, sizeof...(Ts)> make_byte_array(Ts... ts) noexcept

    :returns: A byte array filled with the provided values.

    Casts every provided value to :texpr:`std::byte` and returns a brace initialized array with the results.


.. function:: template <typename R, std::size_t N, typename Fn, typename... Args> \
              constexpr R sequence_init(Fn &&initFn, Args &&... args)

    The return object is brace initialized by the results of :texpr:`N`
    invocations of :expr:`std::invoke(initFn, args..., n)` where :texpr:`n`
    is the current counter value starting at 0.

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



.. function:: constexpr bool is_null_byte(const std::byte value) noexcept

    :returns: :expr:`value == std::byte{}`

.. function:: constexpr bool is_non_null_byte(const std::byte value) noexcept

    :returns: :expr:`value != std::byte{}`

