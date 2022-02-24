
==================
 Bit Manipulation
==================

::

    #include <dplx/cncr/bit.hpp>
    namespace dplx::cncr {}

.. namespace:: dplx::cncr


.. function:: std::unsigned_integral{T} \
              inline int countl_zero(T x) noexcept

    :returns: The number of consecutive leading/left unset bits of x.

.. function:: std::unsigned_integral{T} \
              inline int countl_one(T x) noexcept

    :returns: The number of consecutive leading/left set bits of x.

.. function:: std::unsigned_integral{T} \
              inline int countr_zero(T x) noexcept

    :returns: The number of consecutive trailing/right unset bits of x.

.. function:: std::unsigned_integral{T} \
              inline int countr_one(T x) noexcept

    :returns: The number of consecutive trailing/right unset bits of x.


.. seealso::

    `cppreference.com | std::countl_zero <https://en.cppreference.com/w/cpp/numeric/countl_zero>`_
        C++20 :expr:`std::countl_zero()` documentation.

    `cppreference.com | std::countl_one <https://en.cppreference.com/w/cpp/numeric/countl_one>`_
        C++20 :expr:`std::countl_one()` documentation.

    `cppreference.com | std::countr_zero <https://en.cppreference.com/w/cpp/numeric/countr_zero>`_
        C++20 :expr:`std::countr_zero()` documentation.

    `cppreference.com | std::countr_one <https://en.cppreference.com/w/cpp/numeric/countr_one>`_
        C++20 :expr:`std::countr_one()` documentation.
