/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include <dplx/predef/architecture/x86/32.h>
#include <dplx/predef/architecture/x86/64.h>

#ifndef DPLX_PREDEF_ARCHITECTURE_X86_H
#define DPLX_PREDEF_ARCHITECTURE_X86_H

/* tag::reference[]
= `DPLX_ARCH_X86`

http://en.wikipedia.org/wiki/X86[Intel x86] architecture. This is
a category to indicate that either `DPLX_ARCH_X86_32` or
`DPLX_ARCH_X86_64` is detected.
*/ // end::reference[]

#define DPLX_ARCH_X86 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if DPLX_ARCH_X86_32 || DPLX_ARCH_X86_64
#   undef DPLX_ARCH_X86
#   define DPLX_ARCH_X86 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_X86
#   define DPLX_ARCH_X86_AVAILABLE
#endif

#define DPLX_ARCH_X86_NAME "Intel x86"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_X86,DPLX_ARCH_X86_NAME)
