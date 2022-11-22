cmake_minimum_required(VERSION 3.20)
project(AreaChart VERSION 0.1.0 DESCRIPTION "wxAreaChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

# This is required for GUI applications on Windows.
if(WIN32)
  SET(APP_TYPE WIN32)
else()
  SET(APP_TYPE "")
endif(WIN32)

add_executable(AreaChart 
  ${APP_TYPE} 
    src/wxareachartapp.h
    src/wxareachartapp.cpp
    src/wxareachartframe.h
    src/wxareachartframe.cpp
)

target_link_libraries(AreaChart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(AreaChart
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(AreaChart 
  PROPERTIES
    OUTPUT_NAME   "areachart"   # Can change the output name of the target.
    DEBUG_POSTFIX "d"           # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")    # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)