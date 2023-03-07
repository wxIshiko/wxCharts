cmake_minimum_required(VERSION 3.20)
project(Radar VERSION 0.1.0 DESCRIPTION "wxRadar sample")

# Allows to use virtual folders in visual studio, 
#  it helps to organize larger projects.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(Radar 
  WIN32 MACOSX_BUNDLE
    src/WxRadarApp.h
    src/WxRadarApp.cpp
    src/WxRadarFrame.h
    src/WxRadarFrame.cpp
)

target_link_libraries(Radar
  PRIVATE
    ${wxWidgets_LIBRARIES}
    wxcharts::wxcharts)

target_include_directories(Radar
  PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${wxcharts_SOURCE_DIR}/include
)

set_target_properties(Radar
  PROPERTIES
    OUTPUT_NAME   "radar"    # Can change the output name of the target.
    DEBUG_POSTFIX "d"        # Appends the letter "d" to the target's output name.
    FOLDER        "Samples") # In visual studio puts this target's project inside a virtual folder (requires setting USE_FOLDERS = ON)