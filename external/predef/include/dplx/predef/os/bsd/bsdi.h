/*
Copyright Rene Rivera 2012-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_BSD_BSDI_H
#define DPLX_PREDEF_OS_BSD_BSDI_H

#include <dplx/predef/os/bsd.h>

/* tag::reference[]
= `DPLX_OS_BSD_BSDI`

http://en.wikipedia.org/wiki/BSD/OS[BSDi BSD/OS] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__bsdi__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_BSD_BSDI DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__bsdi__) \
    )
#   ifndef DPLX_OS_BSD_AVAILABLE
#       undef DPLX_OS_BSD
#       define DPLX_OS_BSD DPLX_VERSION_NUMBER_AVAILABLE
#       define DPLX_OS_BSD_AVAILABLE
#   endif
#   undef DPLX_OS_BSD_BSDI
#   define DPLX_OS_BSD_BSDI DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_BSD_BSDI
#   define DPLX_OS_BSD_BSDI_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_BSD_BSDI_NAME "BSDi BSD/OS"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_BSD_BSDI,DPLX_OS_BSD_BSDI_NAME)
