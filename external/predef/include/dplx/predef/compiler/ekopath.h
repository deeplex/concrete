/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_EKOPATH_H
#define DPLX_PREDEF_COMPILER_EKOPATH_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_PATH`

http://en.wikipedia.org/wiki/PathScale[EKOpath] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__PATHCC__+` | {predef_detection}

| `+__PATHCC__+`, `+__PATHCC_MINOR__+`, `+__PATHCC_PATCHLEVEL__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_PATH DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__PATHCC__)
#   define DPLX_COMP_PATH_DETECTION \
        DPLX_VERSION_NUMBER(__PATHCC__,__PATHCC_MINOR__,__PATHCC_PATCHLEVEL__)
#endif

#ifdef DPLX_COMP_PATH_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_PATH_EMULATED DPLX_COMP_PATH_DETECTION
#   else
#       undef DPLX_COMP_PATH
#       define DPLX_COMP_PATH DPLX_COMP_PATH_DETECTION
#   endif
#   define DPLX_COMP_PATH_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_PATH_NAME "EKOpath"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_PATH,DPLX_COMP_PATH_NAME)

#ifdef DPLX_COMP_PATH_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_PATH_EMULATED,DPLX_COMP_PATH_NAME)
#endif
