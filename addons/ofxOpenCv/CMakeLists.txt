# This is a sample cmake file to add to newly added OF addons
# simply copy this file to addon directory and customize lib
# finding and include finding.
#
# An addon include cmake file *MUST* set the following cmake variables:
# 
# - ADDONS_SOURCES: list of addon source files
# - ADDONS_INCLUDE_DIRS: list of directories to add to addon include path
# - ADDONS_LIBRARIES: list of library the addon depend on and should be linked with
# 

get_filename_component(ADDON_ROOT ${CMAKE_CURRENT_LIST_FILE} PATH)
get_filename_component(ADDON_NAME ${ADDON_ROOT} NAME)

message(STATUS "-------------------------------- Configuring OF Addon '${ADDON_NAME}'")

#########################################################################
# Add here your cmake code to fill-in described variables
# 
# this populate ADDON_SRC with the list of source files in src/
# this should work in most cases

file( GLOB_RECURSE ADDON_SRC ${ADDON_ROOT}/src/*.cpp)
file( GLOB_RECURSE ADDON_HEADERS ${ADDON_ROOT}/src/*.h)
#########################################################################

set(OPENFRAMEWORKS_INCLUDES ${OPENFRAMEWORKS_INCLUDES}
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/events
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/app
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/communication
${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/sound
)
if ( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" ) 
  of_find_pkgconfig_lib(opencv)
endif()
include_directories(${OPENFRAMEWORKS_INCLUDES} ${ADDON_INCLUDES})
add_library(${ADDON_NAME} SHARED ${ADDON_SRC})
set_target_properties (${ADDON_NAME} 
                        PROPERTIES OUTPUT_NAME ${ADDON_NAME} )
target_link_libraries(${ADDON_NAME} ${ADDON_LIBRARIES})

install(FILES ${ADDON_HEADERS}
  DESTINATION include/openFrameworks/addons/${ADDON_NAME})

install(TARGETS ${ADDON_NAME} DESTINATION lib)
