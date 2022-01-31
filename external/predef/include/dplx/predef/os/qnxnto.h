/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_QNXNTO_H
#define DPLX_PREDEF_OS_QNXNTO_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_QNX`

http://en.wikipedia.org/wiki/QNX[QNX] operating system.
Version number available as major, and minor if possible. And
version 4 is specifically detected.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__QNX__+` | {predef_detection}
| `+__QNXNTO__+` | {predef_detection}

| `+_NTO_VERSION+` | V.R.0
| `+__QNX__+` | 4.0.0
|===
*/ // end::reference[]

#define DPLX_OS_QNX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__QNX__) || defined(__QNXNTO__) \
    )
#   undef DPLX_OS_QNX
#   if !defined(DPLX_OS_QNX) && defined(_NTO_VERSION)
#       define DPLX_OS_QNX DPLX_PREDEF_MAKE_10_VVRR(_NTO_VERSION)
#   endif
#   if !defined(DPLX_OS_QNX) && defined(__QNX__)
#       define DPLX_OS_QNX DPLX_VERSION_NUMBER(4,0,0)
#   endif
#   if !defined(DPLX_OS_QNX)
#       define DPLX_OS_QNX DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_OS_QNX
#   define DPLX_OS_QNX_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_QNX_NAME "QNX"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_QNX,DPLX_OS_QNX_NAME)
