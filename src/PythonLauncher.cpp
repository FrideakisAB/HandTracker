#include "PythonLauncher.h"

PythonLauncher::PythonLauncher()
{
    Py_Initialize();

    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyObject* programName = PyUnicode_FromString(".");
    PyList_Append(sysPath, programName);
    Py_DECREF(programName);
    pName = PyUnicode_FromString("tracker");
    pModule = PyImport_Import(pName);
    
    if(pModule)
    {
        pDict = PyModule_GetDict(pModule);
        pFunc = PyDict_GetItemString(pDict, "multiply");
        if(PyCallable_Check(pFunc))
        {
            PyObject* obj = PyObject_CallObject(pFunc, NULL);
        }
        else
            PyErr_Print();
    }
}

PythonLauncher::~PythonLauncher()
{
    Py_DECREF(pModule);
    Py_DECREF(pName);

    Py_Finalize();
}