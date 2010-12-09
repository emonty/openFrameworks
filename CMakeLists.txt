# vim:set ft=cmake:syn on
cmake_minimum_required(VERSION 2.6)
project(openFrameworks)
set(OPENFRAMEWORKS_VERSION "0.6")

#### FIND DEPENDENCIES 
include(cmake/OpenFrameworksConfig.cmake)
include(cmake/OpenFrameworks.cmake)

SUBDIRS(libs/openFrameworks)


