#include "cover_tree_python.h"
#include "DerivedPoint.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

///http://stackoverflow.com/questions/15842126/feeding-a-python-list-into-a-function-taking-in-a-vector-with-boost-python
/// @brief Type that allows for registration of conversions from
///        python iterable types.
struct iterable_converter
{
  /// @note Registers converter from a python interable type to the
  ///       provided type.
  template <typename Container>
  iterable_converter&
  from_python()
  {
    boost::python::converter::registry::push_back(
      &iterable_converter::convertible,
      &iterable_converter::construct<Container>,
      boost::python::type_id<Container>());

    // Support chaining.
    return *this;
  }

  /// @brief Check if PyObject is iterable.
  static void* convertible(PyObject* object)
  {
    return PyObject_GetIter(object) ? object : NULL;
  }

  /// @brief Convert iterable PyObject to C++ container type.
  ///
  /// Container Concept requirements:
  ///
  ///   * Container::value_type is CopyConstructable.
  ///   * Container can be constructed and populated with two iterators.
  ///     I.e. Container(begin, end)
  template <typename Container>
  static void construct(
    PyObject* object,
    boost::python::converter::rvalue_from_python_stage1_data* data)
  {
    namespace python = boost::python;
    // Object is a borrowed reference, so create a handle indicting it is
    // borrowed for proper reference counting.
    python::handle<> handle(python::borrowed(object));

    // Obtain a handle to the memory block that the converter has allocated
    // for the C++ type.
    typedef python::converter::rvalue_from_python_storage<Container>
                                                                storage_type;
    void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

    typedef python::stl_input_iterator<typename Container::value_type>
                                                                    iterator;

    // Allocate the C++ type into the converter's memory block, and assign
    // its handle to the converter's convertible variable.  The C++
    // container is populated by passing the begin and end iterators of
    // the python object to the container's constructor.
    new (storage) Container(
      iterator(python::object(handle)), // begin
      iterator());                      // end
    data->convertible = storage;
  }
};



template class CoverTree<DerivedPoint>;
#define Cover CoverTree<DerivedPoint>
BOOST_PYTHON_MODULE(cover_tree)
{
    // Register interable conversions.
    iterable_converter()
    // Build-in type.
    .from_python<std::vector<double> >()
    .from_python<std::vector<DerivedPoint> >()
    ;

    class_<CoverTreePython>("CoverTreePython", init<double, boost::python::list >())
       .def(init<double>())
       .def("insert", &CoverTreePython::insert)
       .def("remove", &CoverTreePython::remove)
       .def("kNearestNeighbors", &CoverTreePython::kNearestNeighbors)
       .def("isValidTree", &CoverTreePython::isValidTree)
       .def("print", &CoverTreePython::print)
       ;

    class_<CoverTreePoint, DerivedPoint>("Point", init<std::vector<double>>())
       .def(init<std::vector<double>>())
       .def("getVec", &DerivedPoint::getVec)
       .def("__eq__", &DerivedPoint::default_eq)
       .def("distance", &DerivedPoint::default_distance)
    ;

    class_<CoverTree<DerivedPoint>>("CoverTree", init<double, std::vector<DerivedPoint>>())
       .def(init<double>())
       .def("insert", &Cover::insert)
       .def("remove", &Cover::remove)
       .def("kNearestNeighbors", &Cover::kNearestNeighbors)
       .def("isValidTree", &Cover::isValidTree)
       .def("_print", &Cover::print)
    ;

}

