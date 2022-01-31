/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_CONVEX_H
#define DPLX_PREDEF_ARCHITECTURE_CONVEX_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_CONVEX`

http://en.wikipedia.org/wiki/Convex_Computer[Convex Computer] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__convex__+` | {predef_detection}

| `+__convex_c1__+` | 1.0.0
| `+__convex_c2__+` | 2.0.0
| `+__convex_c32__+` | 3.2.0
| `+__convex_c34__+` | 3.4.0
| `+__convex_c38__+` | 3.8.0
|===
*/ // end::reference[]

#define DPLX_ARCH_CONVEX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__convex__)
#   undef DPLX_ARCH_CONVEX
#   if !defined(DPLX_ARCH_CONVEX) && defined(__convex_c1__)
#       define DPLX_ARCH_CONVEX DPLX_VERSION_NUMBER(1,0,0)
#   endif
#   if !defined(DPLX_ARCH_CONVEX) && defined(__convex_c2__)
#       define DPLX_ARCH_CONVEX DPLX_VERSION_NUMBER(2,0,0)
#   endif
#   if !defined(DPLX_ARCH_CONVEX) && defined(__convex_c32__)
#       define DPLX_ARCH_CONVEX DPLX_VERSION_NUMBER(3,2,0)
#   endif
#   if !defined(DPLX_ARCH_CONVEX) && defined(__convex_c34__)
#       define DPLX_ARCH_CONVEX DPLX_VERSION_NUMBER(3,4,0)
#   endif
#   if !defined(DPLX_ARCH_CONVEX) && defined(__convex_c38__)
#       define DPLX_ARCH_CONVEX DPLX_VERSION_NUMBER(3,8,0)
#   endif
#   if !defined(DPLX_ARCH_CONVEX)
#       define DPLX_ARCH_CONVEX DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_ARCH_CONVEX
#   define DPLX_ARCH_CONVEX_AVAILABLE
#endif

#if DPLX_ARCH_CONVEX
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_CONVEX_NAME "Convex Computer"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_CONVEX,DPLX_ARCH_CONVEX_NAME)
