cmake_minimum_required(VERSION 3.20)
project(linechart VERSION 0.1.0 DESCRIPTION "wxLineChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(wxcharts CONFIG REQUIRED)

add_executable(linechart 
  WIN32 MACOSX_BUNDLE
    src/wxlinechartapp.h
    src/wxlinechartapp.cpp
    src/wxlinechartframe.h
    src/wxlinechartframe.cpp
)

target_link_libraries(linechart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

set_target_properties(linechart
  PROPERTIES
    DEBUG_POSTFIX "d"         # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")  # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)
