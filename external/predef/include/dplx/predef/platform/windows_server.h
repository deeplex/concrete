/*
Copyright James E. King III, 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_PLAT_WINDOWS_SERVER_H
#define DPLX_PREDEF_PLAT_WINDOWS_SERVER_H

#include <dplx/predef/make.h>
#include <dplx/predef/os/windows.h>
#include <dplx/predef/platform/windows_uwp.h>
#include <dplx/predef/version_number.h>

/* tag::reference[]
= `DPLX_PLAT_WINDOWS_SERVER`

https://docs.microsoft.com/en-us/windows/uwp/get-started/universal-application-platform-guide[UWP]
for Windows Server development.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `WINAPI_FAMILY == WINAPI_FAMILY_SERVER` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_PLAT_WINDOWS_SERVER DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if DPLX_OS_WINDOWS && \
    defined(WINAPI_FAMILY_SERVER) && WINAPI_FAMILY == WINAPI_FAMILY_SERVER
#   undef DPLX_PLAT_WINDOWS_SERVER
#   define DPLX_PLAT_WINDOWS_SERVER DPLX_VERSION_NUMBER_AVAILABLE
#endif
 
#if DPLX_PLAT_WINDOWS_SERVER
#   define DPLX_PLAT_WINDOWS_SERVER_AVAILABLE
#   include <dplx/predef/detail/platform_detected.h>
#endif

#define DPLX_PLAT_WINDOWS_SERVER_NAME "Windows Server"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_WINDOWS_SERVER,DPLX_PLAT_WINDOWS_SERVER_NAME)
