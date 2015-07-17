#include <boost/python.hpp>

class PythonPoint {
    private PyObject * const item;
    
    PythonPoint(PyObject * object) {
	    Py_INCREF(object);
	    item = object;
    }

    double distance(const PythonPoint&p) {
	   PyObject * ret = PyObject_CallMethodObjArgs(item, "distance", p.item);
	   if (!ret) {
		   throw std::runtime_error("Call to distance failed");
	   }
	   double result = PyFloat_AsDouble(ret);
	   Py_DECREF(ret);
	   return result;
    }


    bool operator==(const PythonPoint&p) {
	   PyObject * ret = PyObject_CallMethodObjArgs(item, "__eq__", p.item);
	   if (!ret) {
		   throw std::runtime_error("Call to __eq__ failed");
	   }
	   bool result = ret == Py_True;
	   Py_DECREF(ret);
	   return result;
    }
 
    void print() const {
	   PyObject * ret = PyObject_CallMethodObjArgs(item, "print");
	   if (!ret) {
		   throw std::runtime_error("Call to print failed");
	   }
	   Py_DECREF(ret);
    }


    ~PythonPoint() {
	Py_DECREF(item);
    }
}


