cmake_minimum_required(VERSION 3.5)

include(${CMAKE_CURRENT_LIST_DIR}/buildFiles/versionReader.cmake)
project(ElaFramework VERSION ${VERSION_FIRST_NUMBER}.${VERSION_SECOND_NUMBER}.${VERSION_THIRD_NUMBER}.${VERSION_FOURTH_NUMBER} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 确保启用调试符号生成
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Zi")

# 确保链接器生成 PDB 文件
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

# 显式指定 PDB 输出目录
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/pdb)


# # 配置install路径
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/install)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#在这里配置QT路径 例如 D:/Qt/6.6.2/msvc2019_64
SET(QT_SDK_DIR C:/Qt/6.2.4/msvc2019_64 CACHE PATH "QT SDK DIR" FORCE)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "Installation path" FORCE)

option(BUILD_ELAPACKETIO "Build ElaPacketIO" OFF)
option(BUILD_ELAWIDGETTOOLS_EXAMPLE "Build ElaWidgetToolsExample" ON)

list(APPEND CMAKE_PREFIX_PATH ${QT_SDK_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if (${QT_VERSION} VERSION_GREATER 6.7.0 OR ${QT_VERSION} VERSION_LESS 5.12.0)
    message("你当前使用的QT版本不在维护范围内！可能出现编译失败或使用时崩溃问题，推荐QT版本为QT5.15.2 QT6.6.2 QT6.6.3！请知悉~")
    message("The QT version you are currently using is no longer under maintenance! There may be issues such as compilation failures or crashes during use. The recommended QT versions are QT5.15.2, QT6.6.2, and QT6.6.3! Please be advised")
endif ()

if (${QT_VERSION} VERSION_GREATER_EQUAL 6.5.3 AND ${QT_VERSION} VERSION_LESS_EQUAL 6.6.1)
    message("你当前使用的QT版本为不推荐版本！可能出现使用时异常或崩溃问题，推荐QT版本为QT5.15.2 QT6.6.2 QT6.6.3！请知悉~")
    message("The QT version you are currently using is not recommended! It may cause exceptions or crashes during operation. The recommended QT versions are QT5.15.2, QT6.6.2, and QT6.6.3! Please be advised")
endif ()

if (NOT WIN32)
    add_link_options(-Wl,--disable-new-dtags)
    set(CMAKE_SKIP_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "${QT_SDK_DIR}/lib:${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib")
endif ()

add_subdirectory(ElaWidgetTools)
if (WIN32 AND BUILD_ELAPACKETIO)
    add_definitions(-DBUILD_WITH_ELAPACKETIO)
    add_subdirectory(ElaPacketIO)
endif ()

if(BUILD_ELAWIDGETTOOLS_EXAMPLE)
    add_subdirectory(ElaWidgetToolsExample)
endif()

#@NOTE:用于本地导入elawidgettools库的cmake
install(FILES ${CMAKE_SOURCE_DIR}/buildFiles/localImportCMakes/elawidgettools.cmake
    DESTINATION ${CMAKE_SOURCE_DIR}/install/Elawidgettools/
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ElaWidgetTools)
endif ()
