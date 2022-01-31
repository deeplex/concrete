/*
Copyright Rene Rivera 2013-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ENDIAN_H
#define DPLX_PREDEF_ENDIAN_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>
#include <dplx/predef/library/c/gnu.h>
#include <dplx/predef/os/macos.h>
#include <dplx/predef/os/bsd.h>
#include <dplx/predef/platform/android.h>

/* tag::reference[]
= `DPLX_ENDIAN_*`

Detection of endian memory ordering. There are four defined macros
in this header that define the various generally possible endian
memory orderings:

* `DPLX_ENDIAN_BIG_BYTE`, byte-swapped big-endian.
* `DPLX_ENDIAN_BIG_WORD`, word-swapped big-endian.
* `DPLX_ENDIAN_LITTLE_BYTE`, byte-swapped little-endian.
* `DPLX_ENDIAN_LITTLE_WORD`, word-swapped little-endian.

The detection is conservative in that it only identifies endianness
that it knows for certain. In particular bi-endianness is not
indicated as is it not practically possible to determine the
endianness from anything but an operating system provided
header. And the currently known headers do not define that
programatic bi-endianness is available.

This implementation is a compilation of various publicly available
information and acquired knowledge:

. The indispensable documentation of "Pre-defined Compiler Macros"
  http://sourceforge.net/p/predef/wiki/Endianness[Endianness].
. The various endian specifications available in the
  http://wikipedia.org/[Wikipedia] computer architecture pages.
. Generally available searches for headers that define endianness.
*/ // end::reference[]

#define DPLX_ENDIAN_BIG_BYTE DPLX_VERSION_NUMBER_NOT_AVAILABLE
#define DPLX_ENDIAN_BIG_WORD DPLX_VERSION_NUMBER_NOT_AVAILABLE
#define DPLX_ENDIAN_LITTLE_BYTE DPLX_VERSION_NUMBER_NOT_AVAILABLE
#define DPLX_ENDIAN_LITTLE_WORD DPLX_VERSION_NUMBER_NOT_AVAILABLE

/* GNU libc provides a header defining __BYTE_ORDER, or _BYTE_ORDER.
 * And some OSs provide some for of endian header also.
 */
#if !DPLX_ENDIAN_BIG_BYTE && !DPLX_ENDIAN_BIG_WORD && \
    !DPLX_ENDIAN_LITTLE_BYTE && !DPLX_ENDIAN_LITTLE_WORD
#   if DPLX_LIB_C_GNU || DPLX_PLAT_ANDROID || DPLX_OS_BSD_OPEN
#       include <endian.h>
#   else
#       if DPLX_OS_MACOS
#           include <machine/endian.h>
#       else
#           if DPLX_OS_BSD
#               include <sys/endian.h>
#           endif
#       endif
#   endif
#   if defined(__BYTE_ORDER)
#       if defined(__BIG_ENDIAN) && (__BYTE_ORDER == __BIG_ENDIAN)
#           undef DPLX_ENDIAN_BIG_BYTE
#           define DPLX_ENDIAN_BIG_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#       endif
#       if defined(__LITTLE_ENDIAN) && (__BYTE_ORDER == __LITTLE_ENDIAN)
#           undef DPLX_ENDIAN_LITTLE_BYTE
#           define DPLX_ENDIAN_LITTLE_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#       endif
#       if defined(__PDP_ENDIAN) && (__BYTE_ORDER == __PDP_ENDIAN)
#           undef DPLX_ENDIAN_LITTLE_WORD
#           define DPLX_ENDIAN_LITTLE_WORD DPLX_VERSION_NUMBER_AVAILABLE
#       endif
#   endif
#   if !defined(__BYTE_ORDER) && defined(_BYTE_ORDER)
#       if defined(_BIG_ENDIAN) && (_BYTE_ORDER == _BIG_ENDIAN)
#           undef DPLX_ENDIAN_BIG_BYTE
#           define DPLX_ENDIAN_BIG_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#       endif
#       if defined(_LITTLE_ENDIAN) && (_BYTE_ORDER == _LITTLE_ENDIAN)
#           undef DPLX_ENDIAN_LITTLE_BYTE
#           define DPLX_ENDIAN_LITTLE_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#       endif
#       if defined(_PDP_ENDIAN) && (_BYTE_ORDER == _PDP_ENDIAN)
#           undef DPLX_ENDIAN_LITTLE_WORD
#           define DPLX_ENDIAN_LITTLE_WORD DPLX_VERSION_NUMBER_AVAILABLE
#       endif
#   endif
#endif

/* Built-in byte-swapped big-endian macros.
 */
#if !DPLX_ENDIAN_BIG_BYTE && !DPLX_ENDIAN_BIG_WORD && \
    !DPLX_ENDIAN_LITTLE_BYTE && !DPLX_ENDIAN_LITTLE_WORD
#   if (defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)) || \
       (defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)) || \
        defined(__ARMEB__) || \
        defined(__THUMBEB__) || \
        defined(__AARCH64EB__) || \
        defined(_MIPSEB) || \
        defined(__MIPSEB) || \
        defined(__MIPSEB__)
#       undef DPLX_ENDIAN_BIG_BYTE
#       define DPLX_ENDIAN_BIG_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

/* Built-in byte-swapped little-endian macros.
 */
#if !DPLX_ENDIAN_BIG_BYTE && !DPLX_ENDIAN_BIG_WORD && \
    !DPLX_ENDIAN_LITTLE_BYTE && !DPLX_ENDIAN_LITTLE_WORD
#   if (defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) || \
       (defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)) || \
        defined(__ARMEL__) || \
        defined(__THUMBEL__) || \
        defined(__AARCH64EL__) || \
        defined(_MIPSEL) || \
        defined(__MIPSEL) || \
        defined(__MIPSEL__) || \
        defined(__riscv) || \
        defined(__e2k__)
#       undef DPLX_ENDIAN_LITTLE_BYTE
#       define DPLX_ENDIAN_LITTLE_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

/* Some architectures are strictly one endianess (as opposed
 * the current common bi-endianess).
 */
#if !DPLX_ENDIAN_BIG_BYTE && !DPLX_ENDIAN_BIG_WORD && \
    !DPLX_ENDIAN_LITTLE_BYTE && !DPLX_ENDIAN_LITTLE_WORD
#   include <dplx/predef/architecture.h>
#   if DPLX_ARCH_M68K || \
        DPLX_ARCH_PARISC || \
        DPLX_ARCH_SPARC || \
        DPLX_ARCH_SYS370 || \
        DPLX_ARCH_SYS390 || \
        DPLX_ARCH_Z
#       undef DPLX_ENDIAN_BIG_BYTE
#       define DPLX_ENDIAN_BIG_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#   if DPLX_ARCH_IA64 || \
        DPLX_ARCH_X86 || \
        DPLX_ARCH_BLACKFIN
#       undef DPLX_ENDIAN_LITTLE_BYTE
#       define DPLX_ENDIAN_LITTLE_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

/* Windows on ARM, if not otherwise detected/specified, is always
 * byte-swapped little-endian.
 */
#if !DPLX_ENDIAN_BIG_BYTE && !DPLX_ENDIAN_BIG_WORD && \
    !DPLX_ENDIAN_LITTLE_BYTE && !DPLX_ENDIAN_LITTLE_WORD
#   if DPLX_ARCH_ARM
#       include <dplx/predef/os/windows.h>
#       if DPLX_OS_WINDOWS
#           undef DPLX_ENDIAN_LITTLE_BYTE
#           define DPLX_ENDIAN_LITTLE_BYTE DPLX_VERSION_NUMBER_AVAILABLE
#       endif
#   endif
#endif

#if DPLX_ENDIAN_BIG_BYTE
#   define DPLX_ENDIAN_BIG_BYTE_AVAILABLE
#endif
#if DPLX_ENDIAN_BIG_WORD
#   define DPLX_ENDIAN_BIG_WORD_BYTE_AVAILABLE
#endif
#if DPLX_ENDIAN_LITTLE_BYTE
#   define DPLX_ENDIAN_LITTLE_BYTE_AVAILABLE
#endif
#if DPLX_ENDIAN_LITTLE_WORD
#   define DPLX_ENDIAN_LITTLE_WORD_BYTE_AVAILABLE
#endif

#define DPLX_ENDIAN_BIG_BYTE_NAME "Byte-Swapped Big-Endian"
#define DPLX_ENDIAN_BIG_WORD_NAME "Word-Swapped Big-Endian"
#define DPLX_ENDIAN_LITTLE_BYTE_NAME "Byte-Swapped Little-Endian"
#define DPLX_ENDIAN_LITTLE_WORD_NAME "Word-Swapped Little-Endian"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ENDIAN_BIG_BYTE,DPLX_ENDIAN_BIG_BYTE_NAME)

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ENDIAN_BIG_WORD,DPLX_ENDIAN_BIG_WORD_NAME)

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ENDIAN_LITTLE_BYTE,DPLX_ENDIAN_LITTLE_BYTE_NAME)

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ENDIAN_LITTLE_WORD,DPLX_ENDIAN_LITTLE_WORD_NAME)
