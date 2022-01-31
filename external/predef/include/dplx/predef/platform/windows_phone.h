/*
Copyright (c) Microsoft Corporation 2014
Copyright Rene Rivera 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_PLAT_WINDOWS_PHONE_H
#define DPLX_PREDEF_PLAT_WINDOWS_PHONE_H

#include <dplx/predef/make.h>
#include <dplx/predef/os/windows.h>
#include <dplx/predef/platform/windows_uwp.h>
#include <dplx/predef/version_number.h>

/* tag::reference[]
= `DPLX_PLAT_WINDOWS_PHONE`

https://docs.microsoft.com/en-us/windows/uwp/get-started/universal-application-platform-guide[UWP]
for Windows Phone development.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_PLAT_WINDOWS_PHONE DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if DPLX_OS_WINDOWS && \
    defined(WINAPI_FAMILY_PHONE_APP) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#   undef DPLX_PLAT_WINDOWS_PHONE
#   define DPLX_PLAT_WINDOWS_PHONE DPLX_VERSION_NUMBER_AVAILABLE
#endif
 
#if DPLX_PLAT_WINDOWS_PHONE
#   define DPLX_PLAT_WINDOWS_PHONE_AVAILABLE
#   include <dplx/predef/detail/platform_detected.h>
#endif

#define DPLX_PLAT_WINDOWS_PHONE_NAME "Windows Phone"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_WINDOWS_PHONE,DPLX_PLAT_WINDOWS_PHONE_NAME)
