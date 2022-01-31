/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_PGI_H
#define DPLX_PREDEF_COMPILER_PGI_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_PGI`

http://en.wikipedia.org/wiki/The_Portland_Group[Portland Group C/{CPP}] compiler.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__PGI+` | {predef_detection}

| `+__PGIC__+`, `+__PGIC_MINOR__+`, `+__PGIC_PATCHLEVEL__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_PGI DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__PGI)
#   if !defined(DPLX_COMP_PGI_DETECTION) && (defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__))
#       define DPLX_COMP_PGI_DETECTION DPLX_VERSION_NUMBER(__PGIC__,__PGIC_MINOR__,__PGIC_PATCHLEVEL__)
#   endif
#   if !defined(DPLX_COMP_PGI_DETECTION)
#       define DPLX_COMP_PGI_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_PGI_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_PGI_EMULATED DPLX_COMP_PGI_DETECTION
#   else
#       undef DPLX_COMP_PGI
#       define DPLX_COMP_PGI DPLX_COMP_PGI_DETECTION
#   endif
#   define DPLX_COMP_PGI_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_PGI_NAME "Portland Group C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_PGI,DPLX_COMP_PGI_NAME)

#ifdef DPLX_COMP_PGI_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_PGI_EMULATED,DPLX_COMP_PGI_NAME)
#endif
