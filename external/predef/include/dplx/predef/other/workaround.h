/*
Copyright Rene Rivera 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_WORKAROUND_H
#define DPLX_PREDEF_WORKAROUND_H

/* tag::reference[]

= `DPLX_PREDEF_WORKAROUND`

[source]
----
DPLX_PREDEF_WORKAROUND(symbol,comp,major,minor,patch)
----

Usage:

[source]
----
#if DPLX_PREDEF_WORKAROUND(DPLX_COMP_CLANG,<,3,0,0)
    // Workaround for old clang compilers..
#endif
----

Defines a comparison against two version numbers that depends on the definion
of `DPLX_STRICT_CONFIG`. When `DPLX_STRICT_CONFIG` is defined this will expand
to a value convertible to `false`. Which has the effect of disabling all code
conditionally guarded by `DPLX_PREDEF_WORKAROUND`. When `DPLX_STRICT_CONFIG`
is undefine this expand to test the given `symbol` version value with the
`comp` comparison against `DPLX_VERSION_NUMBER(major,minor,patch)`.

*/ // end::reference[]
#ifdef DPLX_STRICT_CONFIG
#   define DPLX_PREDEF_WORKAROUND(symbol, comp, major, minor, patch) (0)
#else
#   include <dplx/predef/version_number.h>
#   define DPLX_PREDEF_WORKAROUND(symbol, comp, major, minor, patch) \
        ( (symbol) != (0) ) && \
        ( (symbol) comp (DPLX_VERSION_NUMBER( (major) , (minor) , (patch) )) )
#endif

/* tag::reference[]

= `DPLX_PREDEF_TESTED_AT`

[source]
----
DPLX_PREDEF_TESTED_AT(symbol,major,minor,patch)
----

Usage:

[source]
----
#if DPLX_PREDEF_TESTED_AT(DPLX_COMP_CLANG,3,5,0)
    // Needed for clang, and last checked for 3.5.0.
#endif
----

Defines a comparison against two version numbers that depends on the definion
of `DPLX_STRICT_CONFIG` and `DPLX_DETECT_OUTDATED_WORKAROUNDS`.
When `DPLX_STRICT_CONFIG` is defined this will expand to a value convertible
to `false`. Which has the effect of disabling all code
conditionally guarded by `DPLX_PREDEF_TESTED_AT`. When `DPLX_STRICT_CONFIG`
is undefined this expand to either:

* A value convertible to `true` when `DPLX_DETECT_OUTDATED_WORKAROUNDS` is not
  defined.
* A value convertible `true` when the expansion of
  `DPLX_PREDEF_WORKAROUND(symbol, <=, major, minor, patch)` is `true` and
  `DPLX_DETECT_OUTDATED_WORKAROUNDS` is defined.
* A compile error when the expansion of
  `DPLX_PREDEF_WORKAROUND(symbol, >, major, minor, patch)` is true and
  `DPLX_DETECT_OUTDATED_WORKAROUNDS` is defined.

*/ // end::reference[]
#ifdef DPLX_STRICT_CONFIG
#   define DPLX_PREDEF_TESTED_AT(symbol, major, minor, patch) (0)
#else
#   ifdef DPLX_DETECT_OUTDATED_WORKAROUNDS
#       define DPLX_PREDEF_TESTED_AT(symbol, major, minor, patch) ( \
            DPLX_PREDEF_WORKAROUND(symbol, <=, major, minor, patch) \
            ? 1 \
            : (1%0) )
#   else
#       define DPLX_PREDEF_TESTED_AT(symbol, major, minor, patch) \
            ( (symbol) >= DPLX_VERSION_NUMBER_AVAILABLE )
#   endif
#endif

#endif
