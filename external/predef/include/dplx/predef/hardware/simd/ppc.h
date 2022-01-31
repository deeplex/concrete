/*
Copyright Charly Chevalier 2015
Copyright Joel Falcou 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_HARDWARE_SIMD_PPC_H
#define DPLX_PREDEF_HARDWARE_SIMD_PPC_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/hardware/simd/ppc/versions.h>

/* tag::reference[]
= `DPLX_HW_SIMD_PPC`

The SIMD extension for PowerPC (*if detected*).
Version number depends on the most recent detected extension.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__VECTOR4DOUBLE__+` | {predef_detection}

| `+__ALTIVEC__+` | {predef_detection}
| `+__VEC__+` | {predef_detection}

| `+__VSX__+` | {predef_detection}
|===

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__VECTOR4DOUBLE__+` | DPLX_HW_SIMD_PPC_QPX_VERSION

| `+__ALTIVEC__+` | DPLX_HW_SIMD_PPC_VMX_VERSION
| `+__VEC__+` | DPLX_HW_SIMD_PPC_VMX_VERSION

| `+__VSX__+` | DPLX_HW_SIMD_PPC_VSX_VERSION
|===

*/ // end::reference[]

#define DPLX_HW_SIMD_PPC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#undef DPLX_HW_SIMD_PPC
#if !defined(DPLX_HW_SIMD_PPC) && defined(__VECTOR4DOUBLE__)
#   define DPLX_HW_SIMD_PPC DPLX_HW_SIMD_PPC_QPX_VERSION
#endif
#if !defined(DPLX_HW_SIMD_PPC) && defined(__VSX__)
#   define DPLX_HW_SIMD_PPC DPLX_HW_SIMD_PPC_VSX_VERSION
#endif
#if !defined(DPLX_HW_SIMD_PPC) && (defined(__ALTIVEC__) || defined(__VEC__))
#   define DPLX_HW_SIMD_PPC DPLX_HW_SIMD_PPC_VMX_VERSION
#endif

#if !defined(DPLX_HW_SIMD_PPC)
#   define DPLX_HW_SIMD_PPC DPLX_VERSION_NUMBER_NOT_AVAILABLE
#else
#   define DPLX_HW_SIMD_PPC_AVAILABLE
#endif

#define DPLX_HW_SIMD_PPC_NAME "PPC SIMD"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_HW_SIMD_PPC, DPLX_HW_SIMD_PPC_NAME)
