cmake_minimum_required(VERSION 3.5)

project(BigPrj VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        storage.cpp
        mainwindow.cpp
        customproxy.cpp
        storage.h
        mainwindow.h
        customproxy.h
        mainwindow.ui
        cereals.csv
        analyticswindow.cpp
        analyticswindow.h
        analyticswindow.ui
        logoclass.cpp
        logoclass.h
        logoclass.ui
        logowindow.cpp
        logowindow.h
        logowindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BigPrj
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BigPrj APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BigPrj SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BigPrj
            ${PROJECT_SOURCES}
        )
    endif()
endif()

find_package(Qt5Charts)
if(Qt5Charts_FOUND)
set( QT_INCLUDE_DIR
${Qt5Charts_INCLUDE_DIRS}
)
include_directories( ${QT_INCLUDE_DIR} )
set (LIBS ${LIBS} ${Qt5Charts_LIBRARIES} )
endif()

target_link_libraries(BigPrj PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(BigPrj PRIVATE Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(BigPrj PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BigPrj)
endif()
