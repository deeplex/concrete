/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_SPARC_H
#define DPLX_PREDEF_ARCHITECTURE_SPARC_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_SPARC`

http://en.wikipedia.org/wiki/SPARC[SPARC] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__sparc__+` | {predef_detection}
| `+__sparc+` | {predef_detection}

| `+__sparcv9+` | 9.0.0
| `+__sparc_v9__+` | 9.0.0
| `+__sparcv8+` | 8.0.0
| `+__sparc_v8__+` | 8.0.0
|===
*/ // end::reference[]

#define DPLX_ARCH_SPARC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__sparc__) || defined(__sparc)
#   undef DPLX_ARCH_SPARC
#   if !defined(DPLX_ARCH_SPARC) && (defined(__sparcv9) || defined(__sparc_v9__))
#       define DPLX_ARCH_SPARC DPLX_VERSION_NUMBER(9,0,0)
#   endif
#   if !defined(DPLX_ARCH_SPARC) && (defined(__sparcv8) || defined(__sparc_v8__))
#       define DPLX_ARCH_SPARC DPLX_VERSION_NUMBER(8,0,0)
#   endif
#   if !defined(DPLX_ARCH_SPARC)
#       define DPLX_ARCH_SPARC DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_ARCH_SPARC
#   define DPLX_ARCH_SPARC_AVAILABLE
#endif

#if DPLX_ARCH_SPARC
#   if DPLX_ARCH_SPARC >= DPLX_VERSION_NUMBER(9,0,0)
#       undef DPLX_ARCH_WORD_BITS_64
#       define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_AVAILABLE
#   else
#       undef DPLX_ARCH_WORD_BITS_32
#       define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#define DPLX_ARCH_SPARC_NAME "SPARC"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_SPARC,DPLX_ARCH_SPARC_NAME)
