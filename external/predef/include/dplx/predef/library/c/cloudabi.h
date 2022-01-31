/*
 * Copyright (C) 2017 James E. King III
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef DPLX_PREDEF_LIBRARY_C_CLOUDABI_H
#define DPLX_PREDEF_LIBRARY_C_CLOUDABI_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

#include <dplx/predef/library/c/_prefix.h>

#if defined(__CloudABI__)
#include <stddef.h>
#endif

/* tag::reference[]
= `DPLX_LIB_C_CLOUDABI`

https://github.com/NuxiNL/cloudlibc[cloudlibc] - CloudABI's standard C library.
Version number available as major, and minor.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__cloudlibc__+` | {predef_detection}

| `+__cloudlibc_major__+`, `+__cloudlibc_minor__+` | V.R.0
|===
*/ // end::reference[]

#define DPLX_LIB_C_CLOUDABI DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__cloudlibc__)
#   undef DPLX_LIB_C_CLOUDABI
#   define DPLX_LIB_C_CLOUDABI \
            DPLX_VERSION_NUMBER(__cloudlibc_major__,__cloudlibc_minor__,0)
#endif

#if DPLX_LIB_C_CLOUDABI
#   define DPLX_LIB_C_CLOUDABI_AVAILABLE
#endif

#define DPLX_LIB_C_CLOUDABI_NAME "cloudlibc"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_C_CLOUDABI,DPLX_LIB_C_CLOUDABI_NAME)
