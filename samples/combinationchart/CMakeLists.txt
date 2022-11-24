cmake_minimum_required(VERSION 3.20)
project(CombinationChart VERSION 0.1.0 DESCRIPTION "wxCombinationChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(CombinationChart 
  WIN32 MACOSX_BUNDLE
    src/WxCombinationChartApp.h
    src/WxCombinationChartApp.cpp
    src/WxCombinationChartFrame.h
    src/WxCombinationChartFrame.cpp
)

target_link_libraries(CombinationChart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(CombinationChart
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(CombinationChart
  PROPERTIES
    OUTPUT_NAME   "combinationchart"  # Can change the output name of the target.
    DEBUG_POSTFIX "d"                 # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")          # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)