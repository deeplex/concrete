/*
Copyright Charly Chevalier 2015
Copyright Joel Falcou 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_HARDWARE_SIMD_ARM_H
#define DPLX_PREDEF_HARDWARE_SIMD_ARM_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/hardware/simd/arm/versions.h>

/* tag::reference[]
= `DPLX_HW_SIMD_ARM`

The SIMD extension for ARM (*if detected*).
Version number depends on the most recent detected extension.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__ARM_NEON__+` | {predef_detection}
| `+__aarch64__+` | {predef_detection}
| `+_M_ARM+` | {predef_detection}
| `+_M_ARM64+` | {predef_detection}
|===

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__ARM_NEON__+` | DPLX_HW_SIMD_ARM_NEON_VERSION
| `+__aarch64__+` | DPLX_HW_SIMD_ARM_NEON_VERSION
| `+_M_ARM+` | DPLX_HW_SIMD_ARM_NEON_VERSION
| `+_M_ARM64+` | DPLX_HW_SIMD_ARM_NEON_VERSION
|===

*/ // end::reference[]

#define DPLX_HW_SIMD_ARM DPLX_VERSION_NUMBER_NOT_AVAILABLE

#undef DPLX_HW_SIMD_ARM
#if !defined(DPLX_HW_SIMD_ARM) && (defined(__ARM_NEON__) || defined(__aarch64__) || defined (_M_ARM) || defined (_M_ARM64))
#   define DPLX_HW_SIMD_ARM DPLX_HW_SIMD_ARM_NEON_VERSION
#endif

#if !defined(DPLX_HW_SIMD_ARM)
#   define DPLX_HW_SIMD_ARM DPLX_VERSION_NUMBER_NOT_AVAILABLE
#else
#   define DPLX_HW_SIMD_ARM_AVAILABLE
#endif

#define DPLX_HW_SIMD_ARM_NAME "ARM SIMD"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_HW_SIMD_ARM, DPLX_HW_SIMD_ARM_NAME)
