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
cmake_minimum_required(VERSION 3.16)

########################################################################
# configure vcpkg from environment vars if possible
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()

if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
endif()

if(NOT DEFINED VCPKG_FEATURE_FLAGS)
    set(VCPKG_FEATURE_FLAGS "registries" CACHE STRING "")
endif()
if(NOT DEFINED VCPKG_OVERLAY_TRIPLETS)
    set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_SOURCE_DIR}/tools/triplets" CACHE STRING "")
endif()

if (BUILD_TESTING OR NOT DEFINED BUILD_TESTING)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

########################################################################
project(concrete
    VERSION 0.0.0.1
    LANGUAGES CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tools/cmake/")
include(EnforceOutOfSourceBuilds)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(FeatureSummary)
include(GNUInstallDirs)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


########################################################################
# options

########################################################################
# dependencies

find_package(Catch2 CONFIG)
cmake_dependent_option(BUILD_TESTING "Build the documentation using sphinx" ON Catch2_FOUND OFF)
set_package_properties(Catch2 PROPERTIES
    TYPE OPTIONAL
    PURPOSE "Allows to build the test suite"
)

find_package(Sphinx)
cmake_dependent_option(BUILD_DOCS "Build the documentation using sphinx" ON Sphinx_FOUND OFF)
set_package_properties(Sphinx PROPERTIES
    TYPE OPTIONAL
    PURPOSE "Allows to build the documentation"
)


########################################################################
# warning configuration
include(CompilerWarnings)


########################################################################
# additional compiler options
set(CMAKE_CXX_EXTENSIONS OFF CACHE STRING "" FORCE)

add_library(compiler_settings INTERFACE)
add_library(Deeplex::concrete_compiler_settings ALIAS compiler_settings)
set_target_properties(compiler_settings PROPERTIES
    EXPORT_NAME concrete_compiler_settings
)

target_compile_features(compiler_settings INTERFACE cxx_std_20)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(compiler_settings INTERFACE
        /utf-8 # all sources are utf-8 encoded
        /Zc:__cplusplus # correctly define the __cplusplus macro
    )
endif()


########################################################################
# library
add_library(concrete INTERFACE)
add_library(Deeplex::concrete ALIAS concrete)

target_link_libraries(concrete INTERFACE Deeplex::concrete_compiler_settings)

target_include_directories(concrete INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

########################################################################
# library test project
if (BUILD_TESTING)
    add_executable(concrete-tests)
    target_sources(concrete-tests PRIVATE
        src/cncr_tests/test_utils.hpp
    )

    target_link_libraries(concrete-tests PRIVATE
        Deeplex::concrete

        Catch2::Catch2 Catch2::Catch2WithMain
    )

    target_include_directories(concrete-tests PRIVATE
        scr/cncr_tests
    )

    add_test(NAME concrete-tests COMMAND concrete-tests)
endif()

########################################################################
# source files
include(sources.cmake)

set(_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/dplx")
foreach (header IN LISTS _SOURCES)
    set(_SRC_PATH ${_INC_DIR}/${header})
    get_filename_component(_SRC_NAME ${_SRC_PATH} NAME_WLE)
    get_filename_component(_SRC_DIR ${_SRC_PATH} DIRECTORY)
    list(APPEND _ALL_SRCS $<BUILD_INTERFACE:${_SRC_PATH}>)
    list(APPEND _TEST_SRCS ${_SRC_DIR}/${_SRC_NAME}.test.cpp)
endforeach()
target_sources(concrete INTERFACE ${_ALL_SRCS})
if (BUILD_TESTING)
    target_sources(concrete-tests PRIVATE ${_TEST_SRCS})
endif()


########################################################################
# docs
if (BUILD_DOCS)
    add_subdirectory(docs)
endif()

########################################################################
# cmake install
install(DIRECTORY src/dplx
    TYPE INCLUDE
    FILES_MATCHING
    REGEX ".*\\.h(pp)?"
)
install(DIRECTORY external/predef/include/ TYPE INCLUDE)

install(TARGETS concrete compiler_settings EXPORT concrete-targets)
install(EXPORT concrete-targets
    NAMESPACE Deeplex::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/concrete"
)

configure_package_config_file(tools/concrete-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/concrete-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/concrete"
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/concrete-config-version.cmake"
    COMPATIBILITY SameMinorVersion
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/concrete-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/concrete-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/concrete"
)


########################################################################
feature_summary(WHAT PACKAGES_FOUND PACKAGES_NOT_FOUND)
