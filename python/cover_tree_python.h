#include <boost/python.hpp>
using namespace boost::python;




BOOST_PYTHON_MODULE(cover_tree)
{
    class_<Cover_Tree<object>>("CoverTree")
       .def("insert", &::greet)
       .def("set", &World::set)
				        ;
}

