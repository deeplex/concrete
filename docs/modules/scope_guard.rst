Scope Guard
===========

::

    #include <dplx/scope_guard.hpp>
    namespace dplx {}

.. namespace:: dplx

.. struct:: template <typename Fn> \
            scope_guard

    Utility class for executing a function at scope end, the execution order
    is determined by destruction order e.g.::

        {
            scope_guard cleanup1 = [&]() { printf("cleanup1\n"); };
            scope_guard cleanup2 = [&]() { printf("cleanup2\n"); };

            if (condition)
            {
                return; // prints "cleanup2\ncleanup1\n" on early return
            }
            /*...*/

        } // prints "cleanup2\ncleanup1\n" while destructing cleanup on scope end

    .. warning:: If the given function throws, :expr:`std::terminate()` will be invoked.

    .. function:: scope_guard(Fn &&fn)

        :param Fn &&fn: The function to be executed at destruction; usually a lambda


.. struct:: template <typename Fn> \
            exception_scope_guard

    Utility class for executing a function during stack unwinding, e.g.::

        {
            exception_scope_guard cleanup = [&]() { printf("cleanup\n"); };

            if (condition)
            {
                throw std::runtime_error(); // prints "cleanup" during stack unwinding
            }
            /*...*/

        } // nothing is printed

    .. warning:: If the given function throws, :expr:`std::terminate()` will be invoked.

    .. function:: exception_scope_guard(Fn && fn)

        :param Fn &&fn: The function to be executed during stack unwinding
