/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_GCC_H
#define DPLX_PREDEF_COMPILER_GCC_H

/* Other compilers that emulate this one need to be detected first. */

#include <dplx/predef/compiler/clang.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_GNUC`

http://en.wikipedia.org/wiki/GNU_Compiler_Collection[Gnu GCC C/{CPP}] compiler.
Version number available as major, minor, and patch (if available).

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__GNUC__+` | {predef_detection}

| `+__GNUC__+`, `+__GNUC_MINOR__+`, `+__GNUC_PATCHLEVEL__+` | V.R.P
| `+__GNUC__+`, `+__GNUC_MINOR__+` | V.R.0
|===
*/ // end::reference[]

#define DPLX_COMP_GNUC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__GNUC__)
#   if !defined(DPLX_COMP_GNUC_DETECTION) && defined(__GNUC_PATCHLEVEL__)
#       define DPLX_COMP_GNUC_DETECTION \
            DPLX_VERSION_NUMBER(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)
#   endif
#   if !defined(DPLX_COMP_GNUC_DETECTION)
#       define DPLX_COMP_GNUC_DETECTION \
            DPLX_VERSION_NUMBER(__GNUC__,__GNUC_MINOR__,0)
#   endif
#endif

#ifdef DPLX_COMP_GNUC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_GNUC_EMULATED DPLX_COMP_GNUC_DETECTION
#   else
#       undef DPLX_COMP_GNUC
#       define DPLX_COMP_GNUC DPLX_COMP_GNUC_DETECTION
#   endif
#   define DPLX_COMP_GNUC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_GNUC_NAME "Gnu GCC C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_GNUC,DPLX_COMP_GNUC_NAME)

#ifdef DPLX_COMP_GNUC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_GNUC_EMULATED,DPLX_COMP_GNUC_NAME)
#endif
