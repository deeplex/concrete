
===============================
 Template Parameter Pack utils
===============================

::

    #include <dplx/cncr/pack_utils.hpp>
    namespace dplx::cncr {}


.. namespace:: dplx::cncr

.. function:: template <std::size_t N, typename... Ts> \
              constexpr decltype(auto) nth_param(Ts &&...vs) noexcept

    :returns: the perfectly forwarded :texpr:`N` th value from :texpr:`vs` (zero indexed)

.. type:: template <std::size_t N, typename... Ts> \
          nth_param_t

    Selects the :texpr:`N` th type from :texpr:`Ts` (zero indexed).

.. var:: template <std::size_t N, decltype(auto)... Vs> \
         constexpr auto nth_param_v

    Selects the :texpr:`N` th value from :texpr:`Vs` (zero indexed).
