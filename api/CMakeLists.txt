cmake_minimum_required(VERSION 3.1)

set(PYTHON_EXECUTABLE "F:\\PythonForInject")
set(PYTHON_INCLUDE_DIRS "F:\\PythonForInject\\include")
set(PYTHON_LIBRARIES "F:\\PythonForInject\\libs\\python38.lib")
set(PYTHONLIBS_FOUND "TRUE")

project(TTMMScriptingLibrary)
add_subdirectory(../extern/pybind11 build)
pybind11_add_module(TTMMScriptingLibrary library.cpp log.hpp memaccess.hpp)

