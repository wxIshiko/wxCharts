cmake_minimum_required(VERSION 3.20)
project(Math2d VERSION 0.1.0 DESCRIPTION "wxMath2d sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(Math2d 
  WIN32 MACOSX_BUNDLE
    src/WxMath2DApp.h
    src/WxMath2DApp.cpp
    src/WxMath2DFrame.h
    src/WxMath2DFrame.cpp
)

target_link_libraries(Math2d
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(Math2d
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(Math2d
  PROPERTIES
    OUTPUT_NAME   "math2d"   # Can change the output name of the target.
    DEBUG_POSTFIX "d"        # Appends the letter "d" to the target's output name.
    FOLDER        "Samples") # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)