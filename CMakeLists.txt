# vim:set ft=cmake:syn on
cmake_minimum_required(VERSION 2.6)
project(openFrameworks)
set(OPENFRAMEWORKS_VERSION "0.6")

#### FIND DEPENDENCIES 
include(cmake/OpenFrameworksConfig.cmake)
include(cmake/OpenFrameworks.cmake)

SUBDIRS(libs/openFrameworks)

set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 6)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_SOURCE_GENERATOR TGZ)
INCLUDE(CPack)
