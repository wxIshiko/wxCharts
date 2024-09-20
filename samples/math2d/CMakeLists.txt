cmake_minimum_required(VERSION 3.20)
project(math2d VERSION 0.1.0 DESCRIPTION "wxMath2d sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(wxCharts CONFIG REQUIRED)

add_executable(math2d 
  WIN32 MACOSX_BUNDLE
    src/WxMath2DApp.h
    src/WxMath2DApp.cpp
    src/WxMath2DFrame.h
    src/WxMath2DFrame.cpp
)

target_link_libraries(math2d
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

set_target_properties(math2d
  PROPERTIES
    DEBUG_POSTFIX "d"        # Appends the letter "d" to the target's output name.
    FOLDER        "Samples") # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)
