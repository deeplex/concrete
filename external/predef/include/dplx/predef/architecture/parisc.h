/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_PARISC_H
#define DPLX_PREDEF_ARCHITECTURE_PARISC_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_PARISC`

http://en.wikipedia.org/wiki/PA-RISC_family[HP/PA RISC] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__hppa__+` | {predef_detection}
| `+__hppa+` | {predef_detection}
| `+__HPPA__+` | {predef_detection}

| `+_PA_RISC1_0+` | 1.0.0
| `+_PA_RISC1_1+` | 1.1.0
| `+__HPPA11__+` | 1.1.0
| `+__PA7100__+` | 1.1.0
| `+_PA_RISC2_0+` | 2.0.0
| `+__RISC2_0__+` | 2.0.0
| `+__HPPA20__+` | 2.0.0
| `+__PA8000__+` | 2.0.0
|===
*/ // end::reference[]

#define DPLX_ARCH_PARISC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__hppa__) || defined(__hppa) || defined(__HPPA__)
#   undef DPLX_ARCH_PARISC
#   if !defined(DPLX_ARCH_PARISC) && (defined(_PA_RISC1_0))
#       define DPLX_ARCH_PARISC DPLX_VERSION_NUMBER(1,0,0)
#   endif
#   if !defined(DPLX_ARCH_PARISC) && (defined(_PA_RISC1_1) || defined(__HPPA11__) || defined(__PA7100__))
#       define DPLX_ARCH_PARISC DPLX_VERSION_NUMBER(1,1,0)
#   endif
#   if !defined(DPLX_ARCH_PARISC) && (defined(_PA_RISC2_0) || defined(__RISC2_0__) || defined(__HPPA20__) || defined(__PA8000__))
#       define DPLX_ARCH_PARISC DPLX_VERSION_NUMBER(2,0,0)
#   endif
#   if !defined(DPLX_ARCH_PARISC)
#       define DPLX_ARCH_PARISC DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_ARCH_PARISC
#   define DPLX_ARCH_PARISC_AVAILABLE
#endif

#if DPLX_ARCH_PARISC
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_PARISC_NAME "HP/PA RISC"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_PARISC,DPLX_ARCH_PARISC_NAME)
