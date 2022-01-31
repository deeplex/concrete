/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_VACPP_H
#define DPLX_PREDEF_LIBRARY_STD_VACPP_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_IBM`

http://www.ibm.com/software/awdtools/xlcpp/[IBM VACPP Standard {CPP}] library.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__IBMCPP__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_LIB_STD_IBM DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__IBMCPP__)
#   undef DPLX_LIB_STD_IBM
#   define DPLX_LIB_STD_IBM DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_LIB_STD_IBM
#   define DPLX_LIB_STD_IBM_AVAILABLE
#endif

#define DPLX_LIB_STD_IBM_NAME "IBM VACPP"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_IBM,DPLX_LIB_STD_IBM_NAME)
