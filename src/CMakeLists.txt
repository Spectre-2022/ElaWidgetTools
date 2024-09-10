cmake_minimum_required(VERSION 3.5)
include(${CMAKE_CURRENT_LIST_DIR}/../buildFiles/versionReader.cmake)
project(elawidgettools VERSION ${VERSION_FIRST_NUMBER}.${VERSION_SECOND_NUMBER}.${VERSION_THIRD_NUMBER}.${VERSION_FOURTH_NUMBER} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_definitions(-DELAWIDGETTOOLS_LIBRARY)
option(ELAWIDGETTOOLS_BUILD_STATIC_LIB "Build static library." OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE CPP_FILES *.cpp *.h)
foreach(filepath ${CPP_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND sources_files ${filename})
endforeach(filepath)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/private
    ${CMAKE_CURRENT_SOURCE_DIR}/DeveloperComponents
)

set(PROJECT_SOURCES
    ${sources_files}
)

if(MSVC)
    set(MY_VERSIONINFO_RC "${CMAKE_BINARY_DIR}/elawidgettools.rc")
    configure_file("${CMAKE_CURRENT_LIST_DIR}/Version.rc.in"
                   "${MY_VERSIONINFO_RC}")
endif()


#@NOTE:Release下生成PDB
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

if (ELAWIDGETTOOLS_BUILD_STATIC_LIB)
    set(LIB_TYPE "STATIC")
else()
    set(LIB_TYPE "SHARED")
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
qt_add_library(${PROJECT_NAME} ${LIB_TYPE}
    ${sources_files}
    ${MY_VERSIONINFO_RC}
)
else()
add_library(${PROJECT_NAME} ${LIB_TYPE}
    ${sources_files}
    ${MY_VERSIONINFO_RC}
)
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    #遍历所有资源文件
    file(GLOB_RECURSE RES_PATHS *.png *.jpg *.svg *.ico *.ttf *.webp *.js)
    foreach(filepath ${RES_PATHS})
            string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
            list(APPEND resource_files ${filename})
    endforeach(filepath)
    qt_add_resources(${PROJECT_NAME} "ElaWidgetTools"
        RESOURCES PREFIX "/"
        FILES
        ${resource_files}
    )
endif()

if(MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif()
if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
endif()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        D3D11
        DXGI
    )
else()
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
)
endif()


set(export_headers
    ${CMAKE_CURRENT_LIST_DIR}/include/stdafx.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaDoubleSpinBox.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaApplication.h
    ${CMAKE_CURRENT_LIST_DIR}/include/singleton.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaMessageButton.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaMessageBar.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Def.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaTheme.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaLineEdit.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaSlider.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ElaColorDialog.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${export_headers}")

include(${CMAKE_SOURCE_DIR}/cmakefiles/installDir.cmake)

message(${CMAKE_INSTALL_PREFIX})
