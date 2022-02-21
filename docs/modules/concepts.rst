
===============
 Concept utils
===============

::

    #include <dplx/cncr/concepts.hpp>
    namespace dplx::cncr {}

.. namespace:: dplx::cncr

.. concept:: template <typename T, typename... Ts> \
             any_of

    Fullfilled if :math:`\exists U \in Ts .\; T = U` holds.

.. concept:: template <typename T, typename... Ts> \
             none_of

    Fullfilled if :math:`\forall U \in Ts .\; T \neq U` holds.
