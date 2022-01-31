/*
Copyright Charly Chevalier 2015
Copyright Joel Falcou 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_HARDWARE_SIMD_X86_H
#define DPLX_PREDEF_HARDWARE_SIMD_X86_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/hardware/simd/x86/versions.h>

/* tag::reference[]
= `DPLX_HW_SIMD_X86`

The SIMD extension for x86 (*if detected*).
Version number depends on the most recent detected extension.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__SSE__+` | {predef_detection}
| `+_M_X64+` | {predef_detection}
| `_M_IX86_FP >= 1` | {predef_detection}

| `+__SSE2__+` | {predef_detection}
| `+_M_X64+` | {predef_detection}
| `_M_IX86_FP >= 2` | {predef_detection}

| `+__SSE3__+` | {predef_detection}

| `+__SSSE3__+` | {predef_detection}

| `+__SSE4_1__+` | {predef_detection}

| `+__SSE4_2__+` | {predef_detection}

| `+__AVX__+` | {predef_detection}

| `+__FMA__+` | {predef_detection}

| `+__AVX2__+` | {predef_detection}
|===

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__SSE__+` | DPLX_HW_SIMD_X86_SSE_VERSION
| `+_M_X64+` | DPLX_HW_SIMD_X86_SSE_VERSION
| `_M_IX86_FP >= 1` | DPLX_HW_SIMD_X86_SSE_VERSION

| `+__SSE2__+` | DPLX_HW_SIMD_X86_SSE2_VERSION
| `+_M_X64+` | DPLX_HW_SIMD_X86_SSE2_VERSION
| `_M_IX86_FP >= 2` | DPLX_HW_SIMD_X86_SSE2_VERSION

| `+__SSE3__+` | DPLX_HW_SIMD_X86_SSE3_VERSION

| `+__SSSE3__+` | DPLX_HW_SIMD_X86_SSSE3_VERSION

| `+__SSE4_1__+` | DPLX_HW_SIMD_X86_SSE4_1_VERSION

| `+__SSE4_2__+` | DPLX_HW_SIMD_X86_SSE4_2_VERSION

| `+__AVX__+` | DPLX_HW_SIMD_X86_AVX_VERSION

| `+__FMA__+` | DPLX_HW_SIMD_X86_FMA3_VERSION

| `+__AVX2__+` | DPLX_HW_SIMD_X86_AVX2_VERSION
|===

*/ // end::reference[]

#define DPLX_HW_SIMD_X86 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#undef DPLX_HW_SIMD_X86
#if !defined(DPLX_HW_SIMD_X86) && defined(__MIC__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_MIC_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__AVX2__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_AVX2_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__AVX__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_AVX_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__FMA__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_FMA_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__SSE4_2__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_SSE4_2_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__SSE4_1__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_SSE4_1_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__SSSE3__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_SSSE3_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__SSE3__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_SSE3_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && (defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_SSE2_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && (defined(__SSE__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_SSE_VERSION
#endif
#if !defined(DPLX_HW_SIMD_X86) && defined(__MMX__)
#   define DPLX_HW_SIMD_X86 DPLX_HW_SIMD_X86_MMX_VERSION
#endif

#if !defined(DPLX_HW_SIMD_X86)
#   define DPLX_HW_SIMD_X86 DPLX_VERSION_NUMBER_NOT_AVAILABLE
#else
#   define DPLX_HW_SIMD_X86_AVAILABLE
#endif

#define DPLX_HW_SIMD_X86_NAME "x86 SIMD"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_HW_SIMD_X86, DPLX_HW_SIMD_X86_NAME)
