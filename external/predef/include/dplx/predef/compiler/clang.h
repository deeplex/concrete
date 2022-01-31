/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_CLANG_H
#define DPLX_PREDEF_COMPILER_CLANG_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_CLANG`

http://en.wikipedia.org/wiki/Clang[Clang] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__clang__+` | {predef_detection}

| `+__clang_major__+`, `+__clang_minor__+`, `+__clang_patchlevel__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_CLANG DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__clang__)
#   define DPLX_COMP_CLANG_DETECTION DPLX_VERSION_NUMBER(__clang_major__,__clang_minor__,__clang_patchlevel__)
#endif

#ifdef DPLX_COMP_CLANG_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_CLANG_EMULATED DPLX_COMP_CLANG_DETECTION
#   else
#       undef DPLX_COMP_CLANG
#       define DPLX_COMP_CLANG DPLX_COMP_CLANG_DETECTION
#   endif
#   define DPLX_COMP_CLANG_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_CLANG_NAME "Clang"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_CLANG,DPLX_COMP_CLANG_NAME)

#ifdef DPLX_COMP_CLANG_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_CLANG_EMULATED,DPLX_COMP_CLANG_NAME)
#endif
