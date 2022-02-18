
// Copyright Henrik Steffen Gaßmann 2020.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <type_traits>

namespace dplx::cncr
{

template <typename T>
struct remove_cref
{
    using type = typename std::remove_const<
            typename std::remove_reference<T>::type>::type;
};
template <typename T>
using remove_cref_t = typename remove_cref<T>::type;

} // namespace dplx::cncr
