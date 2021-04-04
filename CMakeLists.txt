#cmake.exe  -G "Visual Studio 14 2015" -D CMAKE_PREFIX_sceneitem="C:\Qt\Qt-5.15.2\lib\cmake" ..
cmake_minimum_required(VERSION 3.18)
project(sceneitem VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS
        Core
        Widgets
        Qml
        Svg
        Quick
        QuickControls2
        Charts
        Multimedia
        LinguistTools
        QmlImportScanner
		PrintSupport 
        Xml
    REQUIRED QUIET
)

add_executable(sceneitem main.cpp scene.h scene.cpp item.h item.cpp)

target_include_directories(sceneitem PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(sceneitem
    PRIVATE
        Qt5::Widgets
        Qt5::Qml
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::Svg
        Qt5::Xml
        Qt5::Gui
		Qt5::PrintSupport
)
