cmake_minimum_required(VERSION 3.20)
project(PolarArea VERSION 0.1.0 DESCRIPTION "wxPolarArea sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(PolarArea 
  WIN32 MACOSX_BUNDLE
    src/WxPolarAreaApp.h
    src/WxPolarAreaApp.cpp
    src/WxPolarAreaFrame.h
    src/WxPolarAreaFrame.cpp
)

target_link_libraries(PolarArea
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(PolarArea
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(PolarArea
  PROPERTIES
    OUTPUT_NAME   "polararea" # Can change the output name of the target.
    DEBUG_POSTFIX "d"         # Appends the letter "d" to the target's output name.
    FOLDER        "Samples")  # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)