set(WXCHARTS_SOURCES
    ${CMAKE_SOURCE_DIR}/include/wx/charts/wxchart.h
    ${CMAKE_SOURCE_DIR}/src/wxchart.cpp
)

add_library(wxCharts STATIC ${WXCHARTS_SOURCES})
target_include_directories(wxCharts PUBLIC ${CMAKE_SOURCE_DIR}/include/wx/charts)
