cmake_minimum_required(VERSION 3.5)

# Package name (without the "rtmaps_" prefix)
set(PCK sbg_systems_2)
project("${PCK}.u")

##################################
# General project configuration
##################################

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD          17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS        OFF)
endif()

##################################
# Dependencies
##################################

# RTMaps
if (NOT DEFINED RTMAPS_SDKDIR)
    if (DEFINED ENV{RTMAPS_SDKDIR})
        set(RTMAPS_SDKDIR "$ENV{RTMAPS_SDKDIR}" CACHE PATH "")
    else()
        message(FATAL_ERROR "RTMAPS_SDKDIR not defined")
    endif()
endif()
include("${RTMAPS_SDKDIR}/templates.u/rtmaps.cmake")

# SBG Systems
add_compile_definitions(SBG_COMMON_STATIC_USE)
if (MSVC)
    list(APPEND CMAKE_PREFIX_PATH "C:/Program Files/sbgECom/lib/cmake/sbgECom")
    list(APPEND CMAKE_PREFIX_PATH "C:/Program Files (x86)/sbgECom/lib/cmake/sbgECom")
else ()
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/sbgECom")
    list(APPEND CMAKE_PREFIX_PATH "/usr/lib/cmake/sbgECom")
endif ()
find_package(sbgECom CONFIG REQUIRED)
set(sbgEComLib sbgECom::sbgEcom)

# Find include directory and binary library for SBG (not set by sbgEComConfig)
set(sbgECom_ROOT "${sbgECom_DIR}")
get_filename_component(sbgECom_ROOT "${sbgECom_ROOT}" DIRECTORY)
get_filename_component(sbgECom_ROOT "${sbgECom_ROOT}" DIRECTORY)
get_filename_component(sbgECom_ROOT "${sbgECom_ROOT}" DIRECTORY)
set(sbgECom_INCLUDE_DIRS "${sbgECom_ROOT}/include")
if (MSVC)
    set(sbgECom_LIBRARIES "${sbgECom_ROOT}/lib/sbgECom.lib")
else ()
    set(sbgECom_LIBRARIES "${sbgECom_ROOT}/lib/libsbgECom.a")
endif ()

##################################
# Package configuration
##################################

add_library(${PCK} SHARED "${CMAKE_CURRENT_LIST_DIR}/src/maps_ellipse_decoder.cpp"
                          "${CMAKE_CURRENT_LIST_DIR}/src/maps_ellipse_device.cpp"
                          )
target_include_directories(${PCK} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include")
configure_target_as_rtmaps_package(${PCK} PCKINFO "${CMAKE_CURRENT_LIST_DIR}/rtmaps_package.pckinfo")
target_include_directories(${PCK} PRIVATE ${sbgECom_INCLUDE_DIRS})
target_link_libraries(${PCK} ${sbgECom_LIBRARIES})

# Link to Windows libraries
if (MSVC)
    target_compile_definitions(${PCK} PUBLIC _CRT_SECURE_NO_WARNINGS)
    target_link_libraries(${PCK} Ws2_32)
endif()

# Set installation directory for the PCK file
install(TARGETS ${PCK} DESTINATION "${RTMAPS_SDKDIR}/packages")