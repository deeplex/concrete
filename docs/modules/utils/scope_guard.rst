=============
 Scope Guard
=============

::

    #include <dplx/scope_guard.hpp>
    namespace dplx {}

.. namespace:: dplx

.. struct:: template <typename EF> \
            scope_exit

    .. seealso:: This class matches the ``scope_exit`` specified by the `Library Fundamentals TS v3 <https://cplusplus.github.io/fundamentals-ts/v3.html#scopeguard.exit>`_.

    Utility class for executing a function at scope end, the execution order
    is determined by destruction order e.g.::

        {
            scope_exit cleanup1 = [&] { printf("cleanup1\n"); };
            scope_exit cleanup2 = [&] { printf("cleanup2\n"); };

            if (condition)
            {
                return; // prints "cleanup2\ncleanup1\n" on early return
            }
            /*...*/

        } // prints "cleanup2\ncleanup1\n" while destructing cleanup on scope end

    In contrast to :expr:`scope_guard<Fn>` it is possible to move "ownership" 
    of the finalization or outright cancel it.

    .. warning:: The given functor will be executed during object destruction.
        If an exception escapes, :expr:`std::terminate()` will be invoked.

    .. function:: scope_exit(scope_exit &&other) noexcept(__see_below__)

        Imports the finalization task from :expr:`other`.

        This constructor is noexcept if :expr:`is_nothrow_move_constructible_v<EF> || is_nothrow_copy_constructible_v<EF>` holds.

        :param scope_exit &&other: The instance to be moved into :expr:`this`.

    .. function:: template <typename Fn> \
                  scope_exit(Fn &&fn) noexcept(__see_below__)

        This constructor is noexcept if :expr:`is_nothrow_constructible_v<EF, Fn> || is_nothrow_constructible_v<EF, Fn&>` holds.

        :param Fn &&fn: The function to be executed at destruction; usually a lambda.

    .. function:: void release() noexcept

        Cancels execution of the attached finalization logic.

.. struct:: template <typename Fn> \
            scope_guard

    Utility class for executing a function at scope end, the execution order
    is determined by destruction order e.g.::

        {
            scope_guard cleanup1 = [&] { printf("cleanup1\n"); };
            scope_guard cleanup2 = [&] { printf("cleanup2\n"); };

            if (condition)
            {
                return; // prints "cleanup2\ncleanup1\n" on early return
            }
            /*...*/

        } // prints "cleanup2\ncleanup1\n" while destructing cleanup on scope end

    .. warning:: The given functor will be executed during object destruction.
        If an exception escapes, :expr:`std::terminate()` will be invoked.

    .. function:: scope_guard(Fn &&fn)

        :param Fn &&fn: The function to be executed at destruction; usually a lambda.


.. struct:: template <typename Fn> \
            [[deprecated]] exception_scope_guard

    Utility class for executing a function during stack unwinding, e.g.::

        {
            exception_scope_guard cleanup = [&]() { printf("cleanup\n"); };

            if (condition)
            {
                throw std::runtime_error(); // prints "cleanup" during stack unwinding
            }
            /*...*/

        } // nothing is printed

    .. warning:: The given functor will be executed during object destruction.
        If an exception escapes, :expr:`std::terminate()` will be invoked.

    .. function:: exception_scope_guard(Fn && fn)

        :param Fn &&fn: The function to be executed during stack unwinding
