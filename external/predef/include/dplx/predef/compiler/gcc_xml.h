/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_GCC_XML_H
#define DPLX_PREDEF_COMPILER_GCC_XML_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_GCCXML`

http://www.gccxml.org/[GCC XML] compiler.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__GCCXML__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_COMP_GCCXML DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__GCCXML__)
#   define DPLX_COMP_GCCXML_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#endif

#ifdef DPLX_COMP_GCCXML_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_GCCXML_EMULATED DPLX_COMP_GCCXML_DETECTION
#   else
#       undef DPLX_COMP_GCCXML
#       define DPLX_COMP_GCCXML DPLX_COMP_GCCXML_DETECTION
#   endif
#   define DPLX_COMP_GCCXML_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_GCCXML_NAME "GCC XML"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_GCCXML,DPLX_COMP_GCCXML_NAME)

#ifdef DPLX_COMP_GCCXML_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_GCCXML_EMULATED,DPLX_COMP_GCCXML_NAME)
#endif
