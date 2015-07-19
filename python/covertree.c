#include "cover_tree_python.h"



BOOST_PYTHON_MODULE(cover_tree)
{
    
    class_<CoverTreePython>("CoverTreePython", init<double&, std::vector<object>&>())
       .def("insert", &CoverTreePython::insert)
       .def("remove", &CoverTreePython::remove)
       .def("print", &CoverTreePython::print)
       ;
}

