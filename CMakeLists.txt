# Written in 2017, 2019 by Henrik Steffen Gaßmann <henrik@gassmann.onl>
#
# To the extent possible under law, the author(s) have dedicated all
# copyright and related and neighboring rights to this software to the
# public domain worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication
# along with this software. If not, see
#
#     http://creativecommons.org/publicdomain/zero/1.0/
#
########################################################################
cmake_minimum_required(VERSION 3.15)
project(concrete VERSION 0.0.0 LANGUAGES CXX)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "in-source builds are not supported!")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tools/cmake/")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
    OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC"))
    set(GXX_COMPATIBLE 1)
endif()

if(MSVC OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC"))
    set(CL_COMPATIBLE 1)
endif()

########################################################################
# options
if (BUILD_TESTING)
    option(BUILD_TESTING "Add test targets" BUILD_TESTING)
endif()

########################################################################
# dependencies

find_package(Boost 1.71 REQUIRED COMPONENTS
    unit_test_framework
)

########################################################################
# additional compiler options
if (CL_COMPATIBLE)
    set(CNCR_ADDITIONAL_OPTIONS
        /utf-8 # all sources are utf-8 encoded
        /permissive- # TPL, disables many MSVC leniencies

        /W4 # warning level 4
        # with the following exceptions
    )
    set(CNCR_ADDITIONAL_DEFINITIONS
        -D_WIN32_WINNT=0x0601 # WinSDK @ Windows 7
        -DUNICODE -D_UNICODE # force Unicode WinAPIs
    )
elseif (GXX_COMPATIBLE)
    set(CNCR_ADDITIONAL_OPTIONS

        -Wall -Wpedantic # enable all recommended warnings
        # with the following exceptions
        # -Wno-c++98-compat # do not warn about code incompatible with previous standards
    )
endif()

########################################################################
# library
add_library(concrete INTERFACE)
add_library(Deeplex::concrete ALIAS concrete)
target_include_directories(concrete INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
set(CNCR_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/dplx")
target_sources(concrete INTERFACE
    $<BUILD_INTERFACE:${CNCR_INC_DIR}/cncr/misc.hpp>
)

target_compile_features(concrete INTERFACE cxx_std_17)

########################################################################
# library test project
if (BUILD_TESTING)
    add_executable(concrete-tests)
    set_target_properties(concrete-tests PROPERTIES
        OUTPUT_NAME concrete-tests-$<CONFIG>
        CXX_EXTENSIONS OFF
    )
    target_sources(concrete-tests PRIVATE
        tests/concrete-tests.main.cpp
        tests/boost-test.hpp

        tests/misc.test.cpp
    )

    if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.16")
        target_precompile_headers(concrete-tests PRIVATE
            tests/boost-test.hpp
        )
        # we need to define the test suite name before including the unit
        # test framework
        set_source_files_properties(tests/concrete-tests.main.cpp PROPERTIES
            SKIP_PRECOMPILE_HEADERS ON
        )
    endif()

    target_link_libraries(concrete-tests PRIVATE
        Deeplex::concrete

        Boost::unit_test_framework
    )
    target_compile_options(concrete-tests PRIVATE ${CNCR_ADDITIONAL_OPTIONS})
    target_compile_definitions(concrete-tests PRIVATE ${CNCR_ADDITIONAL_DEFINITIONS})

    add_test(NAME concrete-tests COMMAND concrete-tests)
endif()

########################################################################
# cmake install
include(GNUInstallDirs)

install(DIRECTORY include/ TYPE INCLUDE)
install(TARGETS concrete EXPORT concrete-targets)
install(EXPORT concrete-targets
    NAMESPACE Deeplex::
    DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/concrete"
)

include(CMakePackageConfigHelpers)
configure_file(tools/concrete-config.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/concrete-config.cmake"
    COPYONLY
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/concrete-config-version.cmake"
    COMPATIBILITY ExactVersion
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/concrete-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/concrete-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/concrete"
)

