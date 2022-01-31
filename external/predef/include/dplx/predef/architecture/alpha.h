/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_ALPHA_H
#define DPLX_PREDEF_ARCHITECTURE_ALPHA_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_ALPHA`

http://en.wikipedia.org/wiki/DEC_Alpha[DEC Alpha] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}
| `+__alpha__+` | {predef_detection}
| `+__alpha+` | {predef_detection}
| `+_M_ALPHA+` | {predef_detection}

| `+__alpha_ev4__+` | 4.0.0
| `+__alpha_ev5__+` | 5.0.0
| `+__alpha_ev6__+` | 6.0.0
|===
*/ // end::reference[]

#define DPLX_ARCH_ALPHA DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__alpha__) || defined(__alpha) || \
    defined(_M_ALPHA)
#   undef DPLX_ARCH_ALPHA
#   if !defined(DPLX_ARCH_ALPHA) && defined(__alpha_ev4__)
#       define DPLX_ARCH_ALPHA DPLX_VERSION_NUMBER(4,0,0)
#   endif
#   if !defined(DPLX_ARCH_ALPHA) && defined(__alpha_ev5__)
#       define DPLX_ARCH_ALPHA DPLX_VERSION_NUMBER(5,0,0)
#   endif
#   if !defined(DPLX_ARCH_ALPHA) && defined(__alpha_ev6__)
#       define DPLX_ARCH_ALPHA DPLX_VERSION_NUMBER(6,0,0)
#   endif
#   if !defined(DPLX_ARCH_ALPHA)
#       define DPLX_ARCH_ALPHA DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_ARCH_ALPHA
#   define DPLX_ARCH_ALPHA_AVAILABLE
#endif

#if DPLX_ARCH_ALPHA
#   undef DPLX_ARCH_WORD_BITS_64
#   define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_ALPHA_NAME "DEC Alpha"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_ALPHA,DPLX_ARCH_ALPHA_NAME)
