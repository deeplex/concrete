# Written in 2017, 2019, 2022-2023 by Henrik Steffen Gaßmann <henrik@gassmann.onl>
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
cmake_minimum_required(VERSION 3.23...4.0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/tools/cmake/")

########################################################################
# configure vcpkg from environment vars if possible
include(VcpkgDefaults)

if (BUILD_TESTING OR NOT DEFINED BUILD_TESTING)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

########################################################################
project(concrete
    VERSION 0.0.0.12
    LANGUAGES CXX
)

include(EnforceOutOfSourceBuilds)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(FeatureSummary)
include(GNUInstallDirs)

include(SourceHelpers)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if (BUILD_TESTING)
    enable_testing()
endif()


########################################################################
# options
option(DPLX_CNCR_USE_STD_BYTESWAP "Use std::byteswap() instead of the polyfill; requires C++23." OFF)

option(DPLX_CNCR_DISABLE_WORKAROUNDS "Disable all workarounds" OFF)
option(DPLX_CNCR_FLAG_OUTDATED_WORKAROUNDS "Emit compiler errors for workarounds which are active, but haven't been validated for this version" OFF)

########################################################################
# dependencies

find_package(status-code CONFIG)
find_package(outcome CONFIG)

find_package(Catch2 CONFIG)
set_package_properties(Catch2 PROPERTIES
    TYPE OPTIONAL
    PURPOSE "Allows to build the test suite"
)
cmake_dependent_option(BUILD_TESTING "Build the documentation using sphinx" ON Catch2_FOUND OFF)
if (BUILD_TESTING)
    find_package(fmt CONFIG)
    set_package_properties(fmt PROPERTIES
        TYPE OPTIONAL
        PURPOSE "Allows to build fmt stringification test cases"
    )
endif()

find_package(Sphinx)
set_package_properties(Sphinx PROPERTIES
    TYPE OPTIONAL
    PURPOSE "Allows to build the documentation"
)
cmake_dependent_option(BUILD_DOCS "Build the documentation using sphinx" ON Sphinx_FOUND OFF)


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
if (DPLX_CNCR_USE_STD_BYTESWAP)
    target_compile_features(compiler_settings INTERFACE cxx_std_23)
endif()
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
if (status-code_FOUND)
    target_link_libraries(concrete INTERFACE status-code::hl)
endif()
if (outcome_FOUND)
    target_link_libraries(concrete INTERFACE outcome::hl)
endif()

target_include_directories(concrete INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/src>
    $<INSTALL_INTERFACE:include>
)

########################################################################
# library test project
if (BUILD_TESTING)
    add_executable(concrete-tests)
    source_group(TREE cncr_tests PREFIX test_utils)

    target_link_libraries(concrete-tests PRIVATE
        Deeplex::concrete

        fmt::fmt
        Catch2::Catch2 Catch2::Catch2WithMain
    )

    target_include_directories(concrete-tests PRIVATE
        src/cncr_tests
    )

    add_test(NAME concrete-tests COMMAND concrete-tests)
endif()

########################################################################
# source files
include(sources.cmake)
source_group(vcpkg REGULAR_EXPRESSION .*/vcpkg_installed/.*)


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
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated/src/dplx
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

export(EXPORT concrete-targets NAMESPACE Deeplex::)
# note that you need to configure with -DCMAKE_EXPORT_PACKAGE_REGISTRY=ON
# for this to have any effect at all
export(PACKAGE concrete)

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
