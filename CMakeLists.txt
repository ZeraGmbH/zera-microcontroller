cmake_minimum_required(VERSION 3.1)

project(zera-microcontroller LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "2")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

find_package(Qt5 COMPONENTS Core CONFIG REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(ZenuxCore REQUIRED)
find_package(GTest REQUIRED)

include(FeatureSummary)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(FindPkgConfig)

enable_testing()
# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname})
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
            )
        target_link_libraries(${_testname}
            PUBLIC
            Qt5::Test
            Zera::tasks-base-testlib
            Zera::zera-timers-testlib
            zera-i2c-devices-testlib
            )
    endforeach()
endfunction()

add_subdirectory(zera-i2c)
add_subdirectory(zera-intel-hex)

write_basic_package_version_file(
    ZeraMicroControllerConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(ZeraMicroControllerConfig.cmake.in ZeraMicroControllerConfig.cmake @ONLY)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ZeraMicroControllerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ZeraMicroControllerConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZeraMicroController
    )

install(EXPORT ZeraMicroControllerExport
    FILE ZeraMicroControllerTargets.cmake
    NAMESPACE Zera::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZeraMicroController
    )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
