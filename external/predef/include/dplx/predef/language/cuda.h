/*
Copyright Benjamin Worpitz 2018
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LANGUAGE_CUDA_H
#define DPLX_PREDEF_LANGUAGE_CUDA_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LANG_CUDA`

https://en.wikipedia.org/wiki/CUDA[CUDA C/{CPP}] language.
If available, the version is detected as VV.RR.P.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__CUDACC__+` | {predef_detection}
| `+__CUDA__+` | {predef_detection}

| `CUDA_VERSION` | VV.RR.P
|===
*/ // end::reference[]

#define DPLX_LANG_CUDA DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__CUDACC__) || defined(__CUDA__)
#   undef DPLX_LANG_CUDA
#   include <cuda.h>
#   if defined(CUDA_VERSION)
#       define DPLX_LANG_CUDA DPLX_PREDEF_MAKE_10_VVRRP(CUDA_VERSION)
#   else
#       define DPLX_LANG_CUDA DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_LANG_CUDA
#   define DPLX_LANG_CUDA_AVAILABLE
#endif

#define DPLX_LANG_CUDA_NAME "CUDA C/C++"


#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LANG_CUDA,DPLX_LANG_CUDA_NAME)
