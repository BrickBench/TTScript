
cmake_minimum_required(VERSION 3.1)
project(TTMMScriptInjector)

set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )

set(PYTHON_INCLUDE_DIRS "C:\\Users\\javst\\AppData\\Local\\Programs\\Python\\Python39\\include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
STRING (REGEX REPLACE "/RTC" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.cpp ../api/memaccess.hpp ../api/game.hpp)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:\\local\\boost_1_75_0\\")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:\\local\\boost_1_75_0\\stage\\lib")

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Boost REQUIRED)

include_directories("F:\\PythonForInject\\include" ${Boost_INCLUDE_DIR})

string(REGEX REPLACE "/RTC(su|[1su])" ""
        CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

add_library(TTMMScriptInjector MODULE  ${SOURCE_FILES})

target_link_libraries(TTMMScriptInjector "F:\\PythonForInject\\libs\\python38.lib" "C:\\local\\boost_1_75_0\\stage\\lib\\libboost_filesystem-vc142-mt-s-x32-1_75.lib")
set_target_properties(TTMMScriptInjector PROPERTIES COMPILE_OPTIONS "-m32" LINK_FLAGS "-m32")

