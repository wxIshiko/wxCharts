cmake_minimum_required(VERSION 3.20)

project(wxcharts
        VERSION 0.1.0
        LANGUAGES CXX)

################
# config cmake #
################

set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ Standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "")
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Postfix for debug binaries")
set(wxWidgets_ROOT_DIR "" CACHE PATH "")
set(wxWidgets_wxrc_EXECUTABLE "" CACHE FILEPATH "")


option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
if(BUILD_SHARED_LIBS)
    message(WARNING "Warning for a shared build: API can change in any version!")
endif()

option(wxBUILD_DEBUG_LEVEL "Debug Level" Default)
if(NOT wxBUILD_DEBUG_LEVEL STREQUAL "Default")
    add_compile_options("-DwxDEBUG_LEVEL=${wxBUILD_DEBUG_LEVEL}")
endif()

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
