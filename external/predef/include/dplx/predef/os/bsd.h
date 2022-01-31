/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_BSD_H
#define DPLX_PREDEF_OS_BSD_H

/* Special case: OSX will define BSD predefs if the sys/param.h
 * header is included. We can guard against that, but only if we
 * detect OSX first. Hence we will force include OSX detection
 * before doing any BSD detection.
 */
#include <dplx/predef/os/macos.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_BSD`

http://en.wikipedia.org/wiki/Berkeley_Software_Distribution[BSD] operating system.

BSD has various branch operating systems possible and each detected
individually. This detects the following variations and sets a specific
version number macro to match:

* `DPLX_OS_BSD_DRAGONFLY` http://en.wikipedia.org/wiki/DragonFly_BSD[DragonFly BSD]
* `DPLX_OS_BSD_FREE` http://en.wikipedia.org/wiki/Freebsd[FreeBSD]
* `DPLX_OS_BSD_BSDI` http://en.wikipedia.org/wiki/BSD/OS[BSDi BSD/OS]
* `DPLX_OS_BSD_NET` http://en.wikipedia.org/wiki/Netbsd[NetBSD]
* `DPLX_OS_BSD_OPEN` http://en.wikipedia.org/wiki/Openbsd[OpenBSD]

NOTE: The general `DPLX_OS_BSD` is set in all cases to indicate some form
of BSD. If the above variants is detected the corresponding macro is also set.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `BSD` | {predef_detection}
| `+_SYSTYPE_BSD+` | {predef_detection}

| `BSD4_2` | 4.2.0
| `BSD4_3` | 4.3.0
| `BSD4_4` | 4.4.0
| `BSD` | V.R.0
|===
*/ // end::reference[]

#include <dplx/predef/os/bsd/bsdi.h>
#include <dplx/predef/os/bsd/dragonfly.h>
#include <dplx/predef/os/bsd/free.h>
#include <dplx/predef/os/bsd/open.h>
#include <dplx/predef/os/bsd/net.h>

#ifndef DPLX_OS_BSD
#define DPLX_OS_BSD DPLX_VERSION_NUMBER_NOT_AVAILABLE
#endif

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(BSD) || \
    defined(_SYSTYPE_BSD) \
    )
#   undef DPLX_OS_BSD
#   include <sys/param.h>
#   if !defined(DPLX_OS_BSD) && defined(BSD4_4)
#       define DPLX_OS_BSD DPLX_VERSION_NUMBER(4,4,0)
#   endif
#   if !defined(DPLX_OS_BSD) && defined(BSD4_3)
#       define DPLX_OS_BSD DPLX_VERSION_NUMBER(4,3,0)
#   endif
#   if !defined(DPLX_OS_BSD) && defined(BSD4_2)
#       define DPLX_OS_BSD DPLX_VERSION_NUMBER(4,2,0)
#   endif
#   if !defined(DPLX_OS_BSD) && defined(BSD)
#       define DPLX_OS_BSD DPLX_PREDEF_MAKE_10_VVRR(BSD)
#   endif
#   if !defined(DPLX_OS_BSD)
#       define DPLX_OS_BSD DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_OS_BSD
#   define DPLX_OS_BSD_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_BSD_NAME "BSD"

#endif

#include <dplx/predef/os/bsd/bsdi.h>
#include <dplx/predef/os/bsd/dragonfly.h>
#include <dplx/predef/os/bsd/free.h>
#include <dplx/predef/os/bsd/open.h>
#include <dplx/predef/os/bsd/net.h>

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_BSD,DPLX_OS_BSD_NAME)
