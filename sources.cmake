set(_SOURCES
    cncr/concepts.hpp
    cncr/intrusive_ptr.hpp
    cncr/math_supplement.hpp
    cncr/misc.hpp
    cncr/mp_lite.hpp
    cncr/pack_utils.hpp
    cncr/tag_invoke.hpp
    cncr/type_utils.hpp
    cncr/windows-proper.h
    cncr/workaround.h
    overloaded.hpp
    predef/workaround.h
    scope_guard.hpp
)

target_include_directories(concrete INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/predef/include>)
