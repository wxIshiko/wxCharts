cmake_minimum_required(VERSION 3.20)

project(wxcharts
        VERSION 0.1.0
        LANGUAGES CXX)

################
# config cmake #
################

# This sets a common dir called bin in the wxcharts_BINARY_DIR,
#   all the executables and libraries will be put there inside a subdirectory called Debug or Release according to its build.
SET(LIBRARY_OUTPUT_PATH    ${wxcharts_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries."   FORCE)
SET(EXECUTABLE_OUTPUT_PATH ${wxcharts_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables." FORCE)


set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ Standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "")
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Postfix for debug binaries")
if (NOT WIN32)
    set(wxWidgets_ROOT_DIR "" CACHE PATH "")
    set(wxWidgets_wxrc_EXECUTABLE "" CACHE FILEPATH "")
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
if(BUILD_SHARED_LIBS)
    message(WARNING "Warning for a shared build: API can change in any version!")
endif()

option(wxBUILD_DEBUG_LEVEL "Debug Level" Default)
if(NOT wxBUILD_DEBUG_LEVEL STREQUAL "Default")
    add_compile_options("-DwxDEBUG_LEVEL=${wxBUILD_DEBUG_LEVEL}")
endif()

##############
# sampples   #
##############
option(BUILD_SAMPLES "Build the samples")
if(BUILD_SAMPLES)
  subdirs(samples)
endif(BUILD_SAMPLES)

##############
# dependency #
##############

include(GNUInstallDirs)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

##########
# target #
##########

file(GLOB SOURCE_FILES src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# export macro
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
                           PUBLIC # use PUBLIC instead of PRIVATE because tests use it
                               $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/wx/charts>
                               $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
                           INTERFACE
                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_FULL_INCLUDEDIR}>
                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_FULL_INCLUDEDIR}/${PROJECT_NAME}>)

target_link_libraries(${PROJECT_NAME} PUBLIC ${wxWidgets_LIBRARIES})

###########
# install #
###########

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        NAMESPACE ${PROJECT_NAME}::
        FILE ${PROJECT_NAME}-config.cmake)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" # source directory
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}) # target directory

install(FILES ${PROJECT_BINARY_DIR}/wxcharts_export.h
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/${PROJECT_NAME}/wx/charts)
