/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_VISUALC_H
#define DPLX_PREDEF_COMPILER_VISUALC_H

/* Other compilers that emulate this one need to be detected first. */

#include <dplx/predef/compiler/clang.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_MSVC`

http://en.wikipedia.org/wiki/Visual_studio[Microsoft Visual C/{CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+_MSC_VER+` | {predef_detection}

| `+_MSC_FULL_VER+` | V.R.P
| `+_MSC_VER+` | V.R.0
|===

NOTE: Release of Visual Studio after 2015 will no longer be identified
by Boost Predef as the marketing version number. Instead we use the
compiler version number directly, i.e. the _MSC_VER number.
*/ // end::reference[]

#define DPLX_COMP_MSVC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(_MSC_VER)
#   if !defined (_MSC_FULL_VER)
#       define DPLX_COMP_MSVC_BUILD 0
#   else
        /* how many digits does the build number have? */
#       if _MSC_FULL_VER / 10000 == _MSC_VER
            /* four digits */
#           define DPLX_COMP_MSVC_BUILD (_MSC_FULL_VER % 10000)
#       elif _MSC_FULL_VER / 100000 == _MSC_VER
            /* five digits */
#           define DPLX_COMP_MSVC_BUILD (_MSC_FULL_VER % 100000)
#       else
#           error "Cannot determine build number from _MSC_FULL_VER"
#       endif
#   endif
    /*
    VS2014 was skipped in the release sequence for MS. Which
    means that the compiler and VS product versions are no longer
    in sync. Hence we need to use different formulas for
    mapping from MSC version to VS product version.

    VS2017 is a total nightmare when it comes to version numbers.
    Hence to avoid arguments relating to that both present and
    future.. Any version after VS2015 will use solely the compiler
    version, i.e. cl.exe, as the version number here.
    */
#   if (_MSC_VER > 1900)
#       define DPLX_COMP_MSVC_DETECTION DPLX_VERSION_NUMBER(\
            _MSC_VER/100,\
            _MSC_VER%100,\
            DPLX_COMP_MSVC_BUILD)
#   elif (_MSC_VER >= 1900)
#       define DPLX_COMP_MSVC_DETECTION DPLX_VERSION_NUMBER(\
            _MSC_VER/100-5,\
            _MSC_VER%100,\
            DPLX_COMP_MSVC_BUILD)
#   else
#       define DPLX_COMP_MSVC_DETECTION DPLX_VERSION_NUMBER(\
            _MSC_VER/100-6,\
            _MSC_VER%100,\
            DPLX_COMP_MSVC_BUILD)
#   endif
#endif

#ifdef DPLX_COMP_MSVC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_MSVC_EMULATED DPLX_COMP_MSVC_DETECTION
#   else
#       undef DPLX_COMP_MSVC
#       define DPLX_COMP_MSVC DPLX_COMP_MSVC_DETECTION
#   endif
#   define DPLX_COMP_MSVC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_MSVC_NAME "Microsoft Visual C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MSVC,DPLX_COMP_MSVC_NAME)

#ifdef DPLX_COMP_MSVC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MSVC_EMULATED,DPLX_COMP_MSVC_NAME)
#endif
