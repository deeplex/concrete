/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_CYGWIN_H
#define DPLX_PREDEF_OS_CYGWIN_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_CYGWIN`

http://en.wikipedia.org/wiki/Cygwin[Cygwin] evironment.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__CYGWIN__+` | {predef_detection}

| `CYGWIN_VERSION_API_MAJOR`, `CYGWIN_VERSION_API_MINOR` | V.R.0
|===
*/ // end::reference[]

#define DPLX_OS_CYGWIN DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__CYGWIN__) \
    )
#   include <cygwin/version.h>
#   undef DPLX_OS_CYGWIN
#   define DPLX_OS_CYGWIN \
        DPLX_VERSION_NUMBER(CYGWIN_VERSION_API_MAJOR,\
                             CYGWIN_VERSION_API_MINOR, 0)
#endif

#if DPLX_OS_CYGWIN
#   define DPLX_OS_CYGWIN_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_CYGWIN_NAME "Cygwin"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_CYGWIN,DPLX_OS_CYGWIN_NAME)
