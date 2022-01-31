/*
Copyright Rene Rivera 2012-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_BSD_FREE_H
#define DPLX_PREDEF_OS_BSD_FREE_H

#include <dplx/predef/os/bsd.h>

/* tag::reference[]
= `DPLX_OS_BSD_FREE`

http://en.wikipedia.org/wiki/Freebsd[FreeBSD] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__FreeBSD__+` | {predef_detection}

| `+__FreeBSD_version+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_OS_BSD_FREE DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__FreeBSD__) \
    )
#   ifndef DPLX_OS_BSD_AVAILABLE
#       undef DPLX_OS_BSD
#       define DPLX_OS_BSD DPLX_VERSION_NUMBER_AVAILABLE
#       define DPLX_OS_BSD_AVAILABLE
#   endif
#   undef DPLX_OS_BSD_FREE
#   include <sys/param.h>
#   if defined(__FreeBSD_version)
#       if __FreeBSD_version == 491000
#           define DPLX_OS_BSD_FREE \
                DPLX_VERSION_NUMBER(4, 10, 0)
#       elif __FreeBSD_version == 492000
#           define DPLX_OS_BSD_FREE \
                DPLX_VERSION_NUMBER(4, 11, 0)
#       elif __FreeBSD_version < 500000
#           define DPLX_OS_BSD_FREE \
                DPLX_PREDEF_MAKE_10_VRPPPP(__FreeBSD_version)
#       else
#           define DPLX_OS_BSD_FREE \
                DPLX_PREDEF_MAKE_10_VVRRPPP(__FreeBSD_version)
#       endif
#   else
#       define DPLX_OS_BSD_FREE DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_OS_BSD_FREE
#   define DPLX_OS_BSD_FREE_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_BSD_FREE_NAME "Free BSD"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_BSD_FREE,DPLX_OS_BSD_FREE_NAME)
