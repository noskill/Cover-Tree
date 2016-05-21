#include <boost/python/stl_iterator.hpp>
#include "../Cover_Tree_Point.h"
#include <vector>



namespace py = boost::python;

template< typename T >
inline std::vector< T > to_std_vector( const py::object& iterable )
{
    return std::vector< T >( py::stl_input_iterator< T >( iterable ),
                             py::stl_input_iterator< T >( ) );
}

class DerivedPoint : public CoverTreePoint
{
    public:
    // hello constructor storing initial self parameter
    DerivedPoint(PyObject *p, const std::vector<double> & x) // 2
        : CoverTreePoint(x, '0'), self(p) {}

    // In case hello is returned by-value from a wrapped function
    DerivedPoint(PyObject *p, const CoverTreePoint& x) // 3
        : CoverTreePoint(x), self(p) {}

    // Override greet to call back into Python
    double distance(const DerivedPoint&p) const{
	   return call<double>(self, p, "distance");
    }

    const std::vector<double> getVec() const {
	   return call<std::vector<double>>(self, "getVec");
    }

    // Supplies the default implementation of greet
    static double default_distance(const DerivedPoint& self, const DerivedPoint & other) // 5
    {
	   return self.CoverTreePoint::distance(other);
    }

    bool operator==(const DerivedPoint& other) const {
         return call<bool>(self, other, "__eq__");
    }

    static bool default_eq(const DerivedPoint& self, const DerivedPoint& other) {
	return self.CoverTreePoint::operator==(other);
    }

 private:
    PyObject* self; // 1
};


