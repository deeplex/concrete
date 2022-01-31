/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_SUPERH_H
#define DPLX_PREDEF_ARCHITECTURE_SUPERH_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_SH`

http://en.wikipedia.org/wiki/SuperH[SuperH] architecture:
If available versions [1-5] are specifically detected.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__sh__+` | {predef_detection}

| `+__SH5__+` | 5.0.0
| `+__SH4__+` | 4.0.0
| `+__sh3__+` | 3.0.0
| `+__SH3__+` | 3.0.0
| `+__sh2__+` | 2.0.0
| `+__sh1__+` | 1.0.0
|===
*/ // end::reference[]

#define DPLX_ARCH_SH DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__sh__)
#   undef DPLX_ARCH_SH
#   if !defined(DPLX_ARCH_SH) && (defined(__SH5__))
#       define DPLX_ARCH_SH DPLX_VERSION_NUMBER(5,0,0)
#   endif
#   if !defined(DPLX_ARCH_SH) && (defined(__SH4__))
#       define DPLX_ARCH_SH DPLX_VERSION_NUMBER(4,0,0)
#   endif
#   if !defined(DPLX_ARCH_SH) && (defined(__sh3__) || defined(__SH3__))
#       define DPLX_ARCH_SH DPLX_VERSION_NUMBER(3,0,0)
#   endif
#   if !defined(DPLX_ARCH_SH) && (defined(__sh2__))
#       define DPLX_ARCH_SH DPLX_VERSION_NUMBER(2,0,0)
#   endif
#   if !defined(DPLX_ARCH_SH) && (defined(__sh1__))
#       define DPLX_ARCH_SH DPLX_VERSION_NUMBER(1,0,0)
#   endif
#   if !defined(DPLX_ARCH_SH)
#       define DPLX_ARCH_SH DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_ARCH_SH
#   define DPLX_ARCH_SH_AVAILABLE
#endif

#if DPLX_ARCH_SH
#   if DPLX_ARCH_SH >= DPLX_VERSION_NUMBER(5,0,0)
#       undef DPLX_ARCH_WORD_BITS_64
#       define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_AVAILABLE
#   elif DPLX_ARCH_SH >= DPLX_VERSION_NUMBER(3,0,0)
#       undef DPLX_ARCH_WORD_BITS_32
#       define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#   else
#       undef DPLX_ARCH_WORD_BITS_16
#       define DPLX_ARCH_WORD_BITS_16 DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#define DPLX_ARCH_SH_NAME "SuperH"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_SH,DPLX_ARCH_SH_NAME)
