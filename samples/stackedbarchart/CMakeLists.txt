cmake_minimum_required(VERSION 3.20)
project(StackedBarChart VERSION 0.1.0 DESCRIPTION "wxStackedBarChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(StackedBarChart 
  WIN32 MACOSX_BUNDLE
    src/WxStackedBarApp.h
    src/WxStackedBarApp.cpp
    src/WxStackedBarFrame.h
    src/WxStackedBarFrame.cpp
)

target_link_libraries(StackedBarChart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(StackedBarChart
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(StackedBarChart
  PROPERTIES
    OUTPUT_NAME   "stackedbarchart" # Can change the output name of the target.
    DEBUG_POSTFIX "d"               # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")        # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)