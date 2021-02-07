cmake_minimum_required(VERSION 3.1)

project(TTMMScriptingLibrary)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories("F:\\PythonForInject\\include")

add_library(TTMMScriptingLibrary SHARED library.cpp library.h ttlib.h )
target_link_libraries(TTMMScriptingLibrary "F:\\PythonForInject\\libs\\python38.lib")
set_target_properties(TTMMScriptingLibrary PROPERTIES COMPILE_OPTIONS "-m32" LINK_FLAGS "-m32")

set_target_properties(TTMMScriptingLibrary PROPERTIES SUFFIX .pyd)
set_target_properties(TTMMScriptingLibrary PROPERTIES PREFIX "")
