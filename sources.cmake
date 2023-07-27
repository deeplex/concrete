dplx_target_sources(concrete
    TEST_TARGET concrete-tests
    MODE SMART_HEADER_ONLY MERGED_LAYOUT
    BASE_DIR dplx

    PUBLIC
        cncr/bit
        cncr/concepts
        cncr/config
        cncr/data_defined_status_domain
        cncr/detail/workaround
        cncr/intrusive_ptr
        cncr/math_supplement
        cncr/misc
        cncr/mp_lite
        cncr/pack_utils
        cncr/tag_invoke
        cncr/type_utils
        cncr/utils
        cncr/uuid
        overloaded
        scope_guard
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated/src/dplx/cncr/detail)
configure_file(tools/config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/generated/src/dplx/cncr/detail/config.hpp @ONLY)
target_sources(concrete PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/src/dplx/cncr/detail/config.hpp>)

dplx_target_sources(concrete
    MODE VERBATIM
    BASE_DIR dplx

    PRIVATE
        cncr/uuid.fmt.hpp
        cncr/uuid.rng.hpp
        cncr/windows-proper.h
        cncr/workaround.h
        predef/workaround.h
)

target_include_directories(concrete INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/predef/include>)


if (BUILD_TESTING)
    dplx_target_sources(concrete-tests
        MODE VERBATIM
        BASE_DIR cncr_tests

        PRIVATE
            range_generator.hpp
            test_utils.hpp
    )

    dplx_target_sources(concrete-tests
        MODE VERBATIM
        BASE_DIR dplx

        PRIVATE
            cncr/windows-proper.test.cpp
            cncr/workaround.test.cpp
            predef/workaround.test.cpp
    )
endif ()
