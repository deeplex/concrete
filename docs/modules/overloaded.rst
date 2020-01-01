
============
 overloaded
============

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
