//
// Created by javst on 2/6/2021.
//

#ifndef TTSCRIPTINGLIBRARY_TTLIB_H
#define TTSCRIPTINGLIBRARY_TTLIB_H

#include <boost/python.hpp>
#include "library.h"

using namespace boost::python;

char const* greet()
{
    return "hello, world";
}

BOOST_PYTHON_MODULE(TTMMScriptingLibrary)
        {
                def("hello", &greet)
        }

#endif //TTSCRIPTINGLIBRARY_TTLIB_H
