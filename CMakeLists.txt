cmake_minimum_required(VERSION 3.16)
project(wxCharts)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(CMAKE_CXX_STANDARD 17)

include(build/cmake/main.cmake)
