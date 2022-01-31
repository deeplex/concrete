/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_X86_32_H
#define DPLX_PREDEF_ARCHITECTURE_X86_32_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_X86_32`

http://en.wikipedia.org/wiki/X86[Intel x86] architecture:
If available versions [3-6] are specifically detected.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `i386` | {predef_detection}
| `+__i386__+` | {predef_detection}
| `+__i486__+` | {predef_detection}
| `+__i586__+` | {predef_detection}
| `+__i686__+` | {predef_detection}
| `+__i386+` | {predef_detection}
| `+_M_IX86+` | {predef_detection}
| `+_X86_+` | {predef_detection}
| `+__THW_INTEL__+` | {predef_detection}
| `+__I86__+` | {predef_detection}
| `+__INTEL__+` | {predef_detection}

| `+__I86__+` | V.0.0
| `+_M_IX86+` | V.0.0
| `+__i686__+` | 6.0.0
| `+__i586__+` | 5.0.0
| `+__i486__+` | 4.0.0
| `+__i386__+` | 3.0.0
|===
*/ // end::reference[]

#define DPLX_ARCH_X86_32 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(i386) || defined(__i386__) || \
    defined(__i486__) || defined(__i586__) || \
    defined(__i686__) || defined(__i386) || \
    defined(_M_IX86) || defined(_X86_) || \
    defined(__THW_INTEL__) || defined(__I86__) || \
    defined(__INTEL__)
#   undef DPLX_ARCH_X86_32
#   if !defined(DPLX_ARCH_X86_32) && defined(__I86__)
#       define DPLX_ARCH_X86_32 DPLX_VERSION_NUMBER(__I86__,0,0)
#   endif
#   if !defined(DPLX_ARCH_X86_32) && defined(_M_IX86)
#       define DPLX_ARCH_X86_32 DPLX_PREDEF_MAKE_10_VV00(_M_IX86)
#   endif
#   if !defined(DPLX_ARCH_X86_32) && defined(__i686__)
#       define DPLX_ARCH_X86_32 DPLX_VERSION_NUMBER(6,0,0)
#   endif
#   if !defined(DPLX_ARCH_X86_32) && defined(__i586__)
#       define DPLX_ARCH_X86_32 DPLX_VERSION_NUMBER(5,0,0)
#   endif
#   if !defined(DPLX_ARCH_X86_32) && defined(__i486__)
#       define DPLX_ARCH_X86_32 DPLX_VERSION_NUMBER(4,0,0)
#   endif
#   if !defined(DPLX_ARCH_X86_32) && defined(__i386__)
#       define DPLX_ARCH_X86_32 DPLX_VERSION_NUMBER(3,0,0)
#   endif
#   if !defined(DPLX_ARCH_X86_32)
#       define DPLX_ARCH_X86_32 DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_ARCH_X86_32
#   define DPLX_ARCH_X86_32_AVAILABLE
#endif

#if DPLX_ARCH_X86_32
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_X86_32_NAME "Intel x86-32"

#include <dplx/predef/architecture/x86.h>

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_X86_32,DPLX_ARCH_X86_32_NAME)
