/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LANGUAGE_OBJC_H
#define DPLX_PREDEF_LANGUAGE_OBJC_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LANG_OBJC`

http://en.wikipedia.org/wiki/Objective-C[Objective-C] language.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__OBJC__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_LANG_OBJC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__OBJC__)
#   undef DPLX_LANG_OBJC
#   define DPLX_LANG_OBJC DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_LANG_OBJC
#   define DPLX_LANG_OBJC_AVAILABLE
#endif

#define DPLX_LANG_OBJC_NAME "Objective-C"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LANG_OBJC,DPLX_LANG_OBJC_NAME)
