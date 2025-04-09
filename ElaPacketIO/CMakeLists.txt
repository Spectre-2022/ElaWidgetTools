cmake_minimum_required(VERSION 3.5)

project(ElaPacketIO VERSION 2.0.0 LANGUAGES CXX)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_definitions(-DELAPACKETIO_LIBRARY)
option(ELAPACKETIO_BUILD_STATIC_LIB "Build static library." OFF)

FILE(GLOB ORIGIN *.h *.cpp)
FILE(GLOB PacketIO PacketIO/*.h PacketIO/*.cpp)
FILE(GLOB Genio Genio/*.h Genio/*.cpp)
FILE(GLOB Util Util/*.h Util/*.cpp)
FILE(GLOB XIO XIO/*.h XIO/*.cpp)

source_group(PacketIO FILES ${PacketIO})
source_group(Genio FILES ${Genio})
source_group(Util FILES ${Util})
source_group(XIO FILES ${XIO})

set(PROJECT_SOURCES
    ${ORIGIN}
    ${PacketIO}
    ${Genio}
    ${Util}
    ${XIO}
)

if (ELAPACKETIO_BUILD_STATIC_LIB)
    set(LIB_TYPE "STATIC")
else ()
    set(LIB_TYPE "SHARED")
endif ()

if(MSVC)
    set(MY_VERSIONINFO_RC "${CMAKE_BINARY_DIR}/ElaPacketIO.rc")
    configure_file("${CMAKE_CURRENT_LIST_DIR}/../buildFiles/Version.rc.in"
                    "${MY_VERSIONINFO_RC}")
endif()

add_library(${PROJECT_NAME} ${LIB_TYPE}
    ${PROJECT_SOURCES}
    ${MY_VERSIONINFO_RC}
)

if (MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif ()
if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

FILE(GLOB ORIGIN_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB XIO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/XIO/*.h)
FILE(GLOB GENIO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/GenIO/*.h)
FILE(GLOB PACKETIO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/PacketIO/*.h)
FILE(GLOB UTIL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Util/*.h)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/GenIO
    ${CMAKE_CURRENT_SOURCE_DIR}/PacketIO
    ${CMAKE_CURRENT_SOURCE_DIR}/Util
    ${CMAKE_CURRENT_SOURCE_DIR}/XIO
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        ws2_32
    )
endif ()

install(FILES ${ORIGIN_HEADERS} DESTINATION ${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/include)
install(FILES ${XIO_HEADERS} DESTINATION ${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/include/XIO)
install(FILES ${GENIO_HEADERS} DESTINATION ${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/include/GenIO)
install(FILES ${PACKETIO_HEADERS} DESTINATION ${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/include/PacketIO)
install(FILES ${UTIL_HEADERS} DESTINATION ${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/include/Util)

include(${CMAKE_CURRENT_LIST_DIR}/../buildFiles/installConfig.cmake)
