#include "cover_tree_python.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>



BOOST_PYTHON_MODULE(cover_tree)
{


    class_<CoverTreePython>("CoverTree", init<double, boost::python::list >())
       .def(init<double>())
       .def("insert", &CoverTreePython::insert)
       .def("remove", &CoverTreePython::remove)
       .def("kNearestNeighbors", &CoverTreePython::kNearestNeighbors)
       .def("isValidTree", &CoverTreePython::isValidTree)
       .def("print", &CoverTreePython::print)
       ;

}


