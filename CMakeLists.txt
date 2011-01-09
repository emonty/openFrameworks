# vim:set ft=cmake:syn on
cmake_minimum_required(VERSION 2.6)
project(openFrameworks)
set(OPENFRAMEWORKS_VERSION "0.6")

ADD_DEFINITIONS(-DSKIP_FMODEX)
#### FIND DEPENDENCIES 
include(cmake/OpenFrameworksConfig.cmake)
include(cmake/OpenFrameworks.cmake)

SUBDIRS(libs/openFrameworks)

SUBDIRS(addons/ofx3DModelLoader)
SUBDIRS(addons/ofxAccelerometer)
SUBDIRS(addons/ofxDirList)
SUBDIRS(addons/ofxFbo)
SUBDIRS(addons/ofxNetwork)
SUBDIRS(addons/ofxOpenCv)
SUBDIRS(addons/ofxOsc)
SUBDIRS(addons/ofxShader)
SUBDIRS(addons/ofxThread)
SUBDIRS(addons/ofxVectorGraphics)
SUBDIRS(addons/ofxVectorMath)
SUBDIRS(addons/ofxXmlSettings)

set(VERSION 0.6.0)

set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 6)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_SOURCE_GENERATOR TGZ)
set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "openframeworks-${VERSION}"
  CACHE INTERNAL "tarball basename")
set(CPACK_SOURCE_IGNORE_FILES
"~$"
"\\\\.gitignore"
"\\\\.tar\\\\.gz"
"^${PROJECT_SOURCE_DIR}.*/CMakeFiles/"
"^${PROJECT_SOURCE_DIR}.*/CMakeCache.txt"
"^${PROJECT_SOURCE_DIR}.*/_CPack_Packages/"
"^${PROJECT_SOURCE_DIR}.*/apps/myApps/.*"
"^${PROJECT_SOURCE_DIR}.*/obj/"
"^${PROJECT_SOURCE_DIR}.*/libs/"
"^${PROJECT_SOURCE_DIR}.*/export/"
"^${PROJECT_SOURCE_DIR}.*/.git/"
)
INCLUDE(CPack)
