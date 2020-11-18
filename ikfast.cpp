#define IKFAST_HAS_LIBRARY

#include <Python.h>
#include <vector>
#include "ikfast.h"

using namespace ikfast;

static PyObject *inverse(PyObject *self, PyObject *args);
bool ComputeIk(const IkReal *eetrans, const IkReal *eerot, const IkReal *pfree, IkSolutionListBase<IkReal> &solutions);

static PyMethodDef PyIkFastMethods[] = {
    {"inverse", inverse, METH_VARARGS, "Calculate inverse kinematics"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef pyikfastmodule = {
    PyModuleDef_HEAD_INIT,
    "pyikfast",
    "ikfast wrapper",
    -1,
    PyIkFastMethods};

PyMODINIT_FUNC PyInit_pyikfast(void)
{
  PyObject *module = PyModule_Create(&pyikfastmodule);
  return module;
}

static PyObject *inverse(PyObject *self, PyObject *args)
{
  // Reference: https://docs.python.org/3/c-api/arg.html#c.PyArg_ParseTuple

  PyObject *argTranslation;
  PyObject *argRotation;
  double rotation[9];
  double translation[3];

  // Parse arguments
  if (!PyArg_ParseTuple(args, "OO", &argTranslation, &argRotation))
  {
    return NULL;
  }
  for (int i = 0; i < 3; i++)
  {
    translation[i] = PyFloat_AsDouble(PyList_GetItem(argTranslation, i));
  }
  for (int i = 0; i < 9; i++)
  {
    rotation[i] = PyFloat_AsDouble(PyList_GetItem(argRotation, i));
  }

  // Compute inverse kinematics
  IkSolutionList<IkReal> solutions;
  ComputeIk(rotation, rotation, NULL, solutions);

  // Return the solution
  PyObject *pySolutionCollection = PyList_New((int)solutions.GetNumSolutions());
  std::vector<IkReal> solvalues(GetNumJoints());
  for (int i = 0; i < solutions.GetNumSolutions(); i++)
  {
    const IkSolutionBase<IkReal> &sol = solutions.GetSolution(i);
    std::vector<IkReal> vsolfree(sol.GetFree().size());
    sol.GetSolution(&solvalues[0], vsolfree.size() > 0 ? &vsolfree[0] : NULL);

    PyObject *pySolution = PyList_New(solvalues.size());
    for (int j = 0; j < solvalues.size(); j++)
    {
      PyList_SetItem(pySolution, j, PyFloat_FromDouble(solvalues[j]));
    }
    PyList_SetItem(pySolutionCollection, i, pySolution);
  }

  return pySolutionCollection;
}
