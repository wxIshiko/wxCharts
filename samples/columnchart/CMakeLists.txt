cmake_minimum_required(VERSION 3.20)
project(columnchart VERSION 0.1.0 DESCRIPTION "wxColumnChart sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(wxCharts CONFIG REQUIRED)

add_executable(columnchart 
  WIN32 MACOSX_BUNDLE
    src/WxColumnApp.h
    src/WxColumnApp.cpp
    src/WxColumnFrame.h
    src/WxColumnFrame.cpp
)

target_link_libraries(columnchart
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

set_target_properties(columnchart
  PROPERTIES
    DEBUG_POSTFIX "d"            # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")     # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)