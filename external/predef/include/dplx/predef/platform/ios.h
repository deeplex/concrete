/*
Copyright Ruslan Baratov 2017
Copyright Rene Rivera 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_PLAT_IOS_H
#define DPLX_PREDEF_PLAT_IOS_H

#include <dplx/predef/os/ios.h> // DPLX_OS_IOS
#include <dplx/predef/version_number.h> // DPLX_VERSION_NUMBER_NOT_AVAILABLE

/* tag::reference[]
= `DPLX_PLAT_IOS_DEVICE`
= `DPLX_PLAT_IOS_SIMULATOR`

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `TARGET_IPHONE_SIMULATOR` | {predef_detection}
| `TARGET_OS_SIMULATOR` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_PLAT_IOS_DEVICE DPLX_VERSION_NUMBER_NOT_AVAILABLE
#define DPLX_PLAT_IOS_SIMULATOR DPLX_VERSION_NUMBER_NOT_AVAILABLE

// https://opensource.apple.com/source/CarbonHeaders/CarbonHeaders-18.1/TargetConditionals.h
#if DPLX_OS_IOS
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_SIMULATOR) && (TARGET_OS_SIMULATOR == 1)
#        undef DPLX_PLAT_IOS_SIMULATOR
#        define DPLX_PLAT_IOS_SIMULATOR DPLX_VERSION_NUMBER_AVAILABLE
#    elif defined(TARGET_IPHONE_SIMULATOR) && (TARGET_IPHONE_SIMULATOR == 1)
#        undef DPLX_PLAT_IOS_SIMULATOR
#        define DPLX_PLAT_IOS_SIMULATOR DPLX_VERSION_NUMBER_AVAILABLE
#    else
#        undef DPLX_PLAT_IOS_DEVICE
#        define DPLX_PLAT_IOS_DEVICE DPLX_VERSION_NUMBER_AVAILABLE
#    endif
#endif

#if DPLX_PLAT_IOS_SIMULATOR
#    define DPLX_PLAT_IOS_SIMULATOR_AVAILABLE
#    include <dplx/predef/detail/platform_detected.h>
#endif

#if DPLX_PLAT_IOS_DEVICE
#    define DPLX_PLAT_IOS_DEVICE_AVAILABLE
#    include <dplx/predef/detail/platform_detected.h>
#endif

#define DPLX_PLAT_IOS_SIMULATOR_NAME "iOS Simulator"
#define DPLX_PLAT_IOS_DEVICE_NAME "iOS Device"

#endif // DPLX_PREDEF_PLAT_IOS_H

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_IOS_SIMULATOR,DPLX_PLAT_IOS_SIMULATOR_NAME)
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_IOS_DEVICE,DPLX_PLAT_IOS_DEVICE_NAME)
