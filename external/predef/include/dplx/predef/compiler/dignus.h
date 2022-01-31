/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_DIGNUS_H
#define DPLX_PREDEF_COMPILER_DIGNUS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_SYSC`

http://www.dignus.com/dcxx/[Dignus Systems/{CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__SYSC__+` | {predef_detection}

| `+__SYSC_VER__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_SYSC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__SYSC__)
#   define DPLX_COMP_SYSC_DETECTION DPLX_PREDEF_MAKE_10_VRRPP(__SYSC_VER__)
#endif

#ifdef DPLX_COMP_SYSC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_SYSC_EMULATED DPLX_COMP_SYSC_DETECTION
#   else
#       undef DPLX_COMP_SYSC
#       define DPLX_COMP_SYSC DPLX_COMP_SYSC_DETECTION
#   endif
#   define DPLX_COMP_SYSC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_SYSC_NAME "Dignus Systems/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_SYSC,DPLX_COMP_SYSC_NAME)

#ifdef DPLX_COMP_SYSC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_SYSC_EMULATED,DPLX_COMP_SYSC_NAME)
#endif
