===================
 General Utilities
===================

.. toctree::

    misc    
    math_supplement
    scope_guard


Generic Helpers
---------------

::

    #include <dplx/cncr/utils.hpp>
    namespace dplx::cncr {}

.. namespace:: dplx::cncr


.. function:: template <typename Enum> \
                  requires std::is_enum_v<Enum> \
              constexpr auto to_underlying(Enum value) noexcept -> \
                      std::underlying_type_t<Enum>

    A backport of C++23 `to_underlying(Enum value) <https://en.cppreference.com/w/cpp/utility/to_underlying>`_.

    :returns: The underlying integer value with the deduced underlying type.


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


.. function:: [[noreturn]] inline void unreachable() noexcept

    Calling this function explicitly invokes Undefined Behaviour. Therefore it
    can be used to inform the compiler about code invariants by calling it in
    places unreachable by the execution flow.

    .. warning::        
        Only ever use this as a last resort in performance critical code *after*
        benchmarking the possible gains.


.. c:macro:: DPLX_ATTR_FORCE_INLINE

    Expands to something equivalent to ``inline`` with compiler specific hints
    to encourage inlining. It's main use case are transparent forwarding wrapper
    functions.

    .. warning:: Needs to be used sparingly in order to prevent machine code 
        bloat.

.. c:macro:: DPLX_ATTR_NO_UNIQUE_ADDRESS

    Expands to ``[[no_unique_address]]``, a compiler specific equivalent or
    nothing if not supported by the current compiler.

    .. seealso:: C++ Reference: `no_unique_address <https://en.cppreference.com/w/cpp/language/attributes/no_unique_address>`_


Lambda Overloading
------------------

::

    #include <dplx/overladed.hpp>
    namespace dplx {}

.. namespace:: dplx


.. struct:: template <typename... Ts> \
            overloaded : Ts...

    Utility class for merging multiple lambdas into one functor::

        auto overloadSet = overloaded{
            [](int) { printf("int"); },
            [](bool) { printf("bool"); }
        };
        overloadSet(true); // prints bool
        overloadSet(0); // prints int
