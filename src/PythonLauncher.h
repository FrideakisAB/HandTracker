#pragma once

#include <Python.h>

class PythonLauncher {
    PyObject *pName, *pModule = nullptr, *pDict, *pFunc, *pValue;

public:
    PythonLauncher();
    ~PythonLauncher();
};
