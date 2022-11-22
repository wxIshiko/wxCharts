cmake_minimum_required(VERSION 3.20)
project(LineChart VERSION 0.1.0 DESCRIPTION "wxLineChart sample")

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

add_executable(LineChart 
  ${APP_TYPE} 
    src/wxlinechartapp.h
    src/wxlinechartapp.cpp
    src/wxlinechartframe.h
    src/wxlinechartframe.cpp
)

target_link_libraries(LineChart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(LineChart
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(LineChart
  PROPERTIES
    OUTPUT_NAME   "lineChart" # Can change the output name of the target.
    DEBUG_POSTFIX "d"         # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")  # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)