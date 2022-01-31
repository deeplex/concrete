/*
Copyright Benjamin Worpitz 2018
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_PTX_H
#define DPLX_PREDEF_ARCHITECTURE_PTX_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_PTX`

https://en.wikipedia.org/wiki/Parallel_Thread_Execution[PTX] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__CUDA_ARCH__+` | {predef_detection}

| `+__CUDA_ARCH__+` | V.R.0
|===
*/ // end::reference[]

#define DPLX_ARCH_PTX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__CUDA_ARCH__)
#   undef DPLX_ARCH_PTX
#   define DPLX_ARCH_PTX DPLX_PREDEF_MAKE_10_VR0(__CUDA_ARCH__)
#endif

#if DPLX_ARCH_PTX
#   define DPLX_ARCH_PTX_AVAILABLE
#endif

#if DPLX_ARCH_PTX
#   undef DPLX_ARCH_WORD_BITS_64
#   define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_PTX_NAME "PTX"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_PTX,DPLX_ARCH_PTX_NAME)
