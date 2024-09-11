cmake_minimum_required(VERSION 3.20)
project(timeserieschart VERSION 0.1.0 DESCRIPTION "wxTimeSeriesChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(wxCharts CONFIG REQUIRED)

add_executable(timeserieschart
  WIN32 MACOSX_BUNDLE
    src/wxtimeseriesapp.h
    src/wxtimeseriesapp.cpp
    src/wxtimeseriesframe.h
    src/wxtimeseriesframe.cpp
)

target_link_libraries(timeserieschart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

set_target_properties(timeserieschart
  PROPERTIES
    DEBUG_POSTFIX "d"          # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")   # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)