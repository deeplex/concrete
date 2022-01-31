/*
  Copyright 2017 James E. King, III
  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_PLAT_CLOUDABI_H
#define DPLX_PREDEF_PLAT_CLOUDABI_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_PLAT_CLOUDABI`

https://github.com/NuxiNL/cloudabi[CloudABI] platform.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__CloudABI__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_PLAT_CLOUDABI DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__CloudABI__)
#   undef DPLX_PLAT_CLOUDABI
#   define DPLX_PLAT_CLOUDABI DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_PLAT_CLOUDABI
#   define DPLX_PLAT_CLOUDABI_AVAILABLE
#   include <dplx/predef/detail/platform_detected.h>
#endif

#define DPLX_PLAT_CLOUDABI_NAME "CloudABI"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_CLOUDABI,DPLX_PLAT_CLOUDABI_NAME)
