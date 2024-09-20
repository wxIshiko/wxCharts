cmake_minimum_required(VERSION 3.20)
project(combinationchart VERSION 0.1.0 DESCRIPTION "wxCombinationChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(wxCharts CONFIG REQUIRED)

add_executable(combinationchart
  WIN32 MACOSX_BUNDLE
    src/WxCombinationChartApp.h
    src/WxCombinationChartApp.cpp
    src/WxCombinationChartFrame.h
    src/WxCombinationChartFrame.cpp
)

target_link_libraries(combinationchart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

set_target_properties(combinationchart
  PROPERTIES
    DEBUG_POSTFIX "d"                 # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")          # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)