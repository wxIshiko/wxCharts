# Author: YWiyogo
# CMake build for wxcharts
#-------------------------------------
# How to build and run the piechartapp:
# 1. Goto wxCharts repo directory
# 2. mkdir cmakebuild && cd cmakebuild
# 3. cmake ..
# 4. make piechartapp
#-------------------------------------

cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(wxcharts)

# Install the wxwidgets library first in your system
# For Fedora30+: sudo dnf install wxGTK3-devel
# For Ubuntu18+: sudo apt install libwxbase3.1-dev libwxgtk3.1-dev
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# include the header directories
include_directories(./include/wx/charts)

# Extract the common parts in a (internal) static library
file(GLOB LIBRARY_SRCS src/*.cpp)
add_library(wxcharts STATIC ${LIBRARY_SRCS})
target_include_directories(wxcharts PUBLIC include )

# Add `samples` targets that enables building the sample programs
# Not built by default. Run `make piechartapp` to build the wxpiechartapp
# piechartapp
file(GLOB SAMPLE_SRCS samples/piechart/src/*.cpp)
add_executable(piechartapp EXCLUDE_FROM_ALL ${SAMPLE_SRCS})
target_link_libraries(piechartapp wxcharts ${wxWidgets_LIBRARIES})

# linechartapp
file(GLOB SAMPLE_SRCS samples/linechart/src/*.cpp)
add_executable(linechartapp EXCLUDE_FROM_ALL ${SAMPLE_SRCS})
target_link_libraries(linechartapp wxcharts ${wxWidgets_LIBRARIES})

# histogramapp
file(GLOB SAMPLE_SRCS samples/histogram/src/*.cpp)
add_executable(histogramapp EXCLUDE_FROM_ALL ${SAMPLE_SRCS})
target_link_libraries(histogramapp wxcharts ${wxWidgets_LIBRARIES})