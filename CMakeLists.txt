cmake_minimum_required(VERSION 3.5)

project(ElaFramework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(BUILD_ELAWIDGETTOOLS_EXAMPLE TRUE CACHE BOOL "Build Example")

# # 配置install路径
# file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/install)
# set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#在这里配置QT路径 例如 D:/Qt/6.6.2/msvc2019_64
SET(QT_SDK_DIR C:/Code/Qt/6.2.4/msvc2019_64 CACHE PATH "QT SDK DIR" FORCE)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install CACHE PATH "Installation path" FORCE)

option(BUILD_ELAPACKETIO "Build ElaPacketIO" OFF)
list(APPEND CMAKE_PREFIX_PATH ${QT_SDK_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(ElaWidgetTools)
if (WIN32 AND BUILD_ELAPACKETIO)
    add_definitions(-DBUILD_WITH_ELAPACKETIO)
    add_subdirectory(ElaPacketIO)
    add_subdirectory(ElaWidgetToolsExample)
endif ()

#@NOTE:用于本地导入elawidgettools库的cmake
install(FILES ${CMAKE_SOURCE_DIR}/buildFiles/localImportCMakes/elawidgettools.cmake
    DESTINATION ${CMAKE_SOURCE_DIR}/install/elawidgettools/
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ElaWidgetTools)
endif ()
