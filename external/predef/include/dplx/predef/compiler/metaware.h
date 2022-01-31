/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_METAWARE_H
#define DPLX_PREDEF_COMPILER_METAWARE_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_HIGHC`

MetaWare High C/{CPP} compiler.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__HIGHC__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_COMP_HIGHC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__HIGHC__)
#   define DPLX_COMP_HIGHC_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#endif

#ifdef DPLX_COMP_HIGHC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_HIGHC_EMULATED DPLX_COMP_HIGHC_DETECTION
#   else
#       undef DPLX_COMP_HIGHC
#       define DPLX_COMP_HIGHC DPLX_COMP_HIGHC_DETECTION
#   endif
#   define DPLX_COMP_HIGHC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_HIGHC_NAME "MetaWare High C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_HIGHC,DPLX_COMP_HIGHC_NAME)

#ifdef DPLX_COMP_HIGHC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_HIGHC_EMULATED,DPLX_COMP_HIGHC_NAME)
#endif
