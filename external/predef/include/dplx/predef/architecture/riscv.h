/*
Copyright Andreas Schwab 2019
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_RISCV_H
#define DPLX_PREDEF_ARCHITECTURE_RISCV_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_RISCV`

http://en.wikipedia.org/wiki/RISC-V[RISC-V] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__riscv+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_RISCV DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__riscv)
#   undef DPLX_ARCH_RISCV
#   define DPLX_ARCH_RISCV DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_RISCV
#   define DPLX_ARCH_RISCV_AVAILABLE
#endif

#if DPLX_ARCH_RISCV
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_RISCV_NAME "RISC-V"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_RISCV,DPLX_ARCH_RISCV_NAME)
