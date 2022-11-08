
============
 tag_invoke
============

::

    #include <dplx/cncr/tag_invoke.hpp>
    namespace dplx::cncr {}

.. namespace:: dplx::cncr

.. function:: template <typename T, typename... TArgs> \
              constexpr decltype(auto) tag_invoke(T policy, TArgs &&...args)

    A helper niebloid for writing customization point objects (CPO) which share
    the common function name :texpr:`tag_invoke` for the user provided function.
    The different customization points are distinguished by the :texpr:`policy`
    argument which ought to be the invoking CPO.

    The user provided customizations can live in the CPO namespace, the target
    type's namespace or be inline friend functions which is the preferred way
    (see the example below). Constrained default implementations can be either
    embedded within the CPO or the CPO namespace.

    This niebloid invokes the name :texpr:`tag_invoke` via ADL and perfectly
    forwards all arguments, the return value and noexcept specification.

    .. seealso::

        The original proposal `P1895 <https://wg21.link/p1895>`_

    Here is an example definition of a :texpr:`tag_invoke` based CPO:
    ::

        inline constexpr struct write_fn
        {
            template <typename Stream>
                requires tag_invocable<write_fn,
                                    Stream &,
                                    std::byte const *,
                                    std::size_t const>
            auto operator()(Stream &stream,
                            std::byte const *bytes,
                            std::size_t const numBytes) const
                    noexcept(nothrow_tag_invocable<write_fn,
                                                Stream &,
                                                std::byte const *,
                                                std::size_t const>)
                            -> tag_invoke_result_t<write_fn,
                                                Stream &,
                                                std::byte const *,
                                                std::size_t const>
            {
                return cncr::tag_invoke(*this, stream, bytes, numBytes);
            }
        } write{};

    The above CPO could be specialized like so:
    ::

        class some_stream
        {
            /*...*/
            inline friend void tag_invoke(cncr::tag_t<write>,
                                          some_stream &,
                                          std::byte const *bytes,
                                          std::size_t const numBytes)
            {
                /* the customized behavior */
            }
            /*...*/
        };

    As the CPO definition is quite involved, the following snippet might
    be of use:
    ::

        inline constexpr struct __CPO_NAME___fn
        {
            template <typename Stream>
                requires tag_invocable<__CPO_NAME___fn,
                                    __CPO_TYPES__>
            auto operator()(__CPO_ARGS__) const
                    noexcept(nothrow_tag_invocable<__CPO_NAME___fn,
                                                __CPO_TYPES__>)
                            -> tag_invoke_result_t<__CPO_NAME___fn,
                                                __CPO_TYPES__>
            {
                return cncr::tag_invoke(*this, __CPO_ARG_NAMES__);
            }
        } __CPO_NAME__{};

.. type:: template <auto &Tag> \
          tag_t

    Retrieves the underlying type of a CPO usable for implementing a
    :texpr:`tag_invoke` overload for that CPO.

.. concept:: template <typename Tag, typename... TArgs> \
             tag_invocable = std::invocable<decltype(cncr::tag_invoke), Tag, TArgs...>

    The concept is satisfied if and only if the CPO identified by :texpr:`Tag`
    is implemented for the given set of arguments. It should only be used as a
    building block for concepts which (partially) consist of CPO constraints.

.. concept:: template <typename Tag, typename... TArgs> \
             nothrow_tag_invocable

    Satisfied if :expr:`tag_invocable<Tag, TArgs...>` holds and the invoked
    :texpr:`tag_invoke` overload is `noexcept`.

.. type:: template <typename Tag, typename... TArgs> \
          tag_invoke_result_t

    A type meta function computing the return type of the invoked CPO.
