/*
Copyright Rene Ferdinand Rivera Morell 2020-2021
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OTHER_WORD_SIZE_H
#define DPLX_PREDEF_OTHER_WORD_SIZE_H

#include <dplx/predef/architecture.h>
#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_WORD_BITS`

Detects the native word size, in bits, for the current architecture. There are
two types of macros for this detection:

* `DPLX_ARCH_WORD_BITS`, gives the number of word size bits
  (16, 32, 64).
* `DPLX_ARCH_WORD_BITS_16`, `DPLX_ARCH_WORD_BITS_32`, and
  `DPLX_ARCH_WORD_BITS_64`, indicate when the given word size is
  detected.

They allow for both single checks and direct use of the size in code.

NOTE: The word size is determined manually on each architecture. Hence use of
the `wordsize.h` header will also include all the architecture headers.

*/ // end::reference[]

#if !defined(DPLX_ARCH_WORD_BITS_64)
#   define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_NOT_AVAILABLE
#elif !defined(DPLX_ARCH_WORD_BITS)
#   define DPLX_ARCH_WORD_BITS 64
#endif

#if !defined(DPLX_ARCH_WORD_BITS_32)
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_NOT_AVAILABLE
#elif !defined(DPLX_ARCH_WORD_BITS)
#	  define DPLX_ARCH_WORD_BITS 32
#endif

#if !defined(DPLX_ARCH_WORD_BITS_16)
#   define DPLX_ARCH_WORD_BITS_16 DPLX_VERSION_NUMBER_NOT_AVAILABLE
#elif !defined(DPLX_ARCH_WORD_BITS)
#   define DPLX_ARCH_WORD_BITS 16
#endif

#if !defined(DPLX_ARCH_WORD_BITS)
#   define DPLX_ARCH_WORD_BITS 0
#endif

#define DPLX_ARCH_WORD_BITS_NAME "Word Bits"
#define DPLX_ARCH_WORD_BITS_16_NAME "16-bit Word Size"
#define DPLX_ARCH_WORD_BITS_32_NAME "32-bit Word Size"
#define DPLX_ARCH_WORD_BITS_64_NAME "64-bit Word Size"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_WORD_BITS,DPLX_ARCH_WORD_BITS_NAME)

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_WORD_BITS_16,DPLX_ARCH_WORD_BITS_16_NAME)

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_WORD_BITS_32,DPLX_ARCH_WORD_BITS_32_NAME)

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_WORD_BITS_64,DPLX_ARCH_WORD_BITS_64_NAME)
