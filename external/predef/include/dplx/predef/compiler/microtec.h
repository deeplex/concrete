/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_MICROTEC_H
#define DPLX_PREDEF_COMPILER_MICROTEC_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_MRI`

http://www.mentor.com/microtec/[Microtec C/{CPP}] compiler.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+_MRI+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_COMP_MRI DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(_MRI)
#   define DPLX_COMP_MRI_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#endif

#ifdef DPLX_COMP_MRI_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_MRI_EMULATED DPLX_COMP_MRI_DETECTION
#   else
#       undef DPLX_COMP_MRI
#       define DPLX_COMP_MRI DPLX_COMP_MRI_DETECTION
#   endif
#   define DPLX_COMP_MRI_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_MRI_NAME "Microtec C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MRI,DPLX_COMP_MRI_NAME)

#ifdef DPLX_COMP_MRI_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MRI_EMULATED,DPLX_COMP_MRI_NAME)
#endif
