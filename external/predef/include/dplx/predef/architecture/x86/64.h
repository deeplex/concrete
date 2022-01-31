/*
Copyright Rene Rivera 2008-2021
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_X86_64_H
#define DPLX_PREDEF_ARCHITECTURE_X86_64_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_X86_64`

https://en.wikipedia.org/wiki/X86-64[X86-64] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__x86_64+` | {predef_detection}
| `+__x86_64__+` | {predef_detection}
| `+__amd64__+` | {predef_detection}
| `+__amd64+` | {predef_detection}
| `+_M_X64+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_X86_64 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__x86_64) || defined(__x86_64__) || \
    defined(__amd64__) || defined(__amd64) || \
    defined(_M_X64)
#   undef DPLX_ARCH_X86_64
#   define DPLX_ARCH_X86_64 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_X86_64
#   define DPLX_ARCH_X86_64_AVAILABLE
#endif

#if DPLX_ARCH_X86_64
#   undef DPLX_ARCH_WORD_BITS_64
#   define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_X86_64_NAME "Intel x86-64"

#include <dplx/predef/architecture/x86.h>

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_X86_64,DPLX_ARCH_X86_64_NAME)
