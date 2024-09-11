cmake_minimum_required(VERSION 3.20)
project(boxplot VERSION 0.1.0 DESCRIPTION "wxBoxPlot sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(wxCharts CONFIG REQUIRED)

add_executable(boxplot 
  WIN32 MACOSX_BUNDLE
    src/wxboxplotapp.h
    src/wxboxplotapp.cpp
    src/wxboxplotframe.h
    src/wxboxplotframe.cpp
)

target_link_libraries(boxplot
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

set_target_properties(boxplot
  PROPERTIES
    DEBUG_POSTFIX "d"            # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")     # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)
