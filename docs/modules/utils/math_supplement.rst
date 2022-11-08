=============================
 Supplemental Math Functions
=============================

::

    #include <dplx/cncr/math_supplement.hpp>
    namespace dplx::cncr {}

.. namespace:: dplx::cncr

.. concept:: template <typename T> \
             integer

    Identifies the standard and extended integer types.

.. concept:: template <typename T> \
             signed_integer

    Identifies the standard and extended signed integer types.

.. concept:: template <typename T> \
             unsigned_integer

    Identifies the standard and extended unsigned integer types.


.. function:: template <signed_integer T, signed_integer U> \
              constexpr auto div_ceil(T const dividend, U const divisor) noexcept \
                  -> std::common_type_t<T, U>

    :returns: :math:`\left\lceil \frac{dividend}{divisor} \right\rceil`

.. function:: template <unsigned_integer T, unsigned_integer U> \
              constexpr auto div_ceil(T const dividend, U const divisor) noexcept \
                  -> std::common_type_t<T, U>

    :returns: :math:`\left\lceil \frac{dividend}{divisor} \right\rceil`

.. function:: template <integer T, integer U> \
              constexpr auto round_up(T const value, U const multiple) noexcept \
                  -> std::common_type_t<T, U>

    :returns: :math:`multiple \cdot \left\lceil \frac{value}{multiple} \right\rceil`

.. function:: template <unsigned_integer T, unsigned_integer U> \
              constexpr auto round_up_p2(T const value, U const powerOf2) noexcept \
                  -> std::common_type_t<T, U>

    :param: powerOf2 must be of the form :math:`2^n` whereas :math:`n \in \mathbb{N}`
    :returns: :math:`2^n \cdot \left\lceil \frac{value}{2^n} \right\rceil`

.. function:: template <integer T, integer U> \
              constexpr auto round_down(T const value, U const multiple) noexcept \
                  -> std::common_type_t<T, U>

    :returns: :math:`multiple \cdot \left\lfloor \frac{value}{multiple} \right\rfloor`

.. function:: template <unsigned_integer T, unsigned_integer U> \
              constexpr auto round_down_p2(T const value, U const powerOf2) noexcept \
                  -> std::common_type_t<T, U>

    :param: powerOf2 must be of the form :math:`2^n` whereas :math:`n \in \mathbb{N}`
    :returns: :math:`2^n \cdot \left\lfloor \frac{value}{2^n} \right\rfloor`

.. function:: constexpr auto upow(unsigned long long x, unsigned long long e) noexcept \
                  -> unsigned long long

    :returns: :math:`x^e \mod 2^b` whereas :math:`b` is the size of :texpr:`unsigned long long` in bits
