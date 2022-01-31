/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_HP_ACC_H
#define DPLX_PREDEF_COMPILER_HP_ACC_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_HPACC`

HP a{CPP} compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__HP_aCC+` | {predef_detection}

| `+__HP_aCC+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_HPACC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__HP_aCC)
#   if !defined(DPLX_COMP_HPACC_DETECTION) && (__HP_aCC > 1)
#       define DPLX_COMP_HPACC_DETECTION DPLX_PREDEF_MAKE_10_VVRRPP(__HP_aCC)
#   endif
#   if !defined(DPLX_COMP_HPACC_DETECTION)
#       define DPLX_COMP_HPACC_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_HPACC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_HPACC_EMULATED DPLX_COMP_HPACC_DETECTION
#   else
#       undef DPLX_COMP_HPACC
#       define DPLX_COMP_HPACC DPLX_COMP_HPACC_DETECTION
#   endif
#   define DPLX_COMP_HPACC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_HPACC_NAME "HP aC++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_HPACC,DPLX_COMP_HPACC_NAME)

#ifdef DPLX_COMP_HPACC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_HPACC_EMULATED,DPLX_COMP_HPACC_NAME)
#endif
