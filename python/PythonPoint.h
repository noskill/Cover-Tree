#include <boost/python.hpp>

using boost::python::object;
using boost::python::call;
using boost::python::call_method;

class PythonPoint {
	private:
	       	object item;
                object dist;
                object eq;
    
    public: 

    PythonPoint(object  obj):
	    item(obj), 
	    dist(obj.attr("distance")),
	    eq(obj.attr("__eq__"))
    {}
    object getObject(){
    	return item;
    }

    double distance(const PythonPoint&p) const{
	   return call<double>(dist.ptr(), p.item);
    }

    bool operator==(const PythonPoint&p) const{
	   return call<double>(eq.ptr(), p.item);
    }

    void print() const {
         if (PyObject_HasAttrString(item.ptr(), "print")) {
	     call_method<void>(item.ptr(), "print");
	}	 
    }
};


