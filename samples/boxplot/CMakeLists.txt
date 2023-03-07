cmake_minimum_required(VERSION 3.20)
project(BoxPlot VERSION 0.1.0 DESCRIPTION "wxBoxPlot sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(BoxPlot 
  WIN32 MACOSX_BUNDLE
    src/wxboxplotapp.h
    src/wxboxplotapp.cpp
    src/wxboxplotframe.h
    src/wxboxplotframe.cpp
)

target_link_libraries(BoxPlot
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(BoxPlot
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(BoxPlot
  PROPERTIES
    OUTPUT_NAME   "boxplot" # Can change the output name of the target.
    DEBUG_POSTFIX "d"            # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")     # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)