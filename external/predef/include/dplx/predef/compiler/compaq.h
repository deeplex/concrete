/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_COMPAQ_H
#define DPLX_PREDEF_COMPILER_COMPAQ_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_DEC`

http://www.openvms.compaq.com/openvms/brochures/deccplus/[Compaq C/{CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__DECCXX+` | {predef_detection}
| `+__DECC+` | {predef_detection}

| `+__DECCXX_VER+` | V.R.P
| `+__DECC_VER+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_DEC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__DECC) || defined(__DECCXX)
#   if !defined(DPLX_COMP_DEC_DETECTION) && defined(__DECCXX_VER)
#       define DPLX_COMP_DEC_DETECTION DPLX_PREDEF_MAKE_10_VVRR0PP00(__DECCXX_VER)
#   endif
#   if !defined(DPLX_COMP_DEC_DETECTION) && defined(__DECC_VER)
#       define DPLX_COMP_DEC_DETECTION DPLX_PREDEF_MAKE_10_VVRR0PP00(__DECC_VER)
#   endif
#   if !defined(DPLX_COMP_DEC_DETECTION)
#       define DPLX_COMP_DEC_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_DEC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_DEC_EMULATED DPLX_COMP_DEC_DETECTION
#   else
#       undef DPLX_COMP_DEC
#       define DPLX_COMP_DEC DPLX_COMP_DEC_DETECTION
#   endif
#   define DPLX_COMP_DEC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_DEC_NAME "Compaq C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_DEC,DPLX_COMP_DEC_NAME)

#ifdef DPLX_COMP_DEC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_DEC_EMULATED,DPLX_COMP_DEC_NAME)
#endif
