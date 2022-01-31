/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_UNIX_H
#define DPLX_PREDEF_OS_UNIX_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_UNIX`

http://en.wikipedia.org/wiki/Unix[Unix Environment] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `unix` | {predef_detection}
| `+__unix+` | {predef_detection}
| `+_XOPEN_SOURCE+` | {predef_detection}
| `+_POSIX_SOURCE+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_UNIX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(unix) || defined(__unix) || \
    defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#   undef DPLX_OS_UNIX
#   define DPLX_OS_UNIX DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_UNIX
#   define DPLX_OS_UNIX_AVAILABLE
#endif

#define DPLX_OS_UNIX_NAME "Unix Environment"

/* tag::reference[]
= `DPLX_OS_SVR4`

http://en.wikipedia.org/wiki/UNIX_System_V[SVR4 Environment] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__sysv__+` | {predef_detection}
| `+__SVR4+` | {predef_detection}
| `+__svr4__+` | {predef_detection}
| `+_SYSTYPE_SVR4+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_SVR4 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__sysv__) || defined(__SVR4) || \
    defined(__svr4__) || defined(_SYSTYPE_SVR4)
#   undef DPLX_OS_SVR4
#   define DPLX_OS_SVR4 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_SVR4
#   define DPLX_OS_SVR4_AVAILABLE
#endif

#define DPLX_OS_SVR4_NAME "SVR4 Environment"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_UNIX,DPLX_OS_UNIX_NAME)
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_SVR4,DPLX_OS_SVR4_NAME)
