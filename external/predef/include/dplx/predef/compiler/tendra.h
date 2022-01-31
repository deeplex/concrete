/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_TENDRA_H
#define DPLX_PREDEF_COMPILER_TENDRA_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_TENDRA`

http://en.wikipedia.org/wiki/TenDRA_Compiler[TenDRA C/{CPP}] compiler.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__TenDRA__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_COMP_TENDRA DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__TenDRA__)
#   define DPLX_COMP_TENDRA_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#endif

#ifdef DPLX_COMP_TENDRA_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_TENDRA_EMULATED DPLX_COMP_TENDRA_DETECTION
#   else
#       undef DPLX_COMP_TENDRA
#       define DPLX_COMP_TENDRA DPLX_COMP_TENDRA_DETECTION
#   endif
#   define DPLX_COMP_TENDRA_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_TENDRA_NAME "TenDRA C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_TENDRA,DPLX_COMP_TENDRA_NAME)

#ifdef DPLX_COMP_TENDRA_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_TENDRA_EMULATED,DPLX_COMP_TENDRA_NAME)
#endif
