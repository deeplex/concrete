/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_LLVM_H
#define DPLX_PREDEF_COMPILER_LLVM_H

/* Other compilers that emulate this one need to be detected first. */

#include <dplx/predef/compiler/clang.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_LLVM`

http://en.wikipedia.org/wiki/LLVM[LLVM] compiler.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__llvm__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_COMP_LLVM DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__llvm__)
#   define DPLX_COMP_LLVM_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#endif

#ifdef DPLX_COMP_LLVM_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_LLVM_EMULATED DPLX_COMP_LLVM_DETECTION
#   else
#       undef DPLX_COMP_LLVM
#       define DPLX_COMP_LLVM DPLX_COMP_LLVM_DETECTION
#   endif
#   define DPLX_COMP_LLVM_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_LLVM_NAME "LLVM"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_LLVM,DPLX_COMP_LLVM_NAME)

#ifdef DPLX_COMP_LLVM_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_LLVM_EMULATED,DPLX_COMP_LLVM_NAME)
#endif
