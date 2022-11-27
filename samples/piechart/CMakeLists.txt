cmake_minimum_required(VERSION 3.20)
project(PieChart VERSION 0.1.0 DESCRIPTION "wxPieChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(PieChart 
  WIN32 MACOSX_BUNDLE
    src/wxpiechartapp.h
    src/wxpiechartapp.cpp
    src/wxpiechartframe.h
    src/wxpiechartframe.cpp
)

target_link_libraries(PieChart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(PieChart
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(PieChart
  PROPERTIES
    OUTPUT_NAME   "piechart" # Can change the output name of the target.
    DEBUG_POSTFIX "d"        # Appends the letter "d" to the target's output name.
    FOLDER        "Samples") # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)