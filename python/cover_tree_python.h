#include <boost/python.hpp>
#include "../Cover_Tree.h"
#include "PythonPoint.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace boost::python;

template <class T>
boost::python::list toPythonList(std::vector<T> vector) {
	typename std::vector<T>::iterator iter;
	boost::python::list list;
	for (iter = vector.begin(); iter != vector.end(); ++iter) {
		list.append(*iter);
	}
	return list;
}



class CoverTreePython{
	private:
		std::shared_ptr<CoverTree<PythonPoint>> tree;
		CoverTreePython() = delete;
	public:
        CoverTreePython(double maxDist,  boost::python::list points){
		std::vector<PythonPoint> wrapped_points;
		wrapped_points.reserve(len(points));
        	for(int i=0; i < len(points); i++){
			wrapped_points.emplace_back(points[i]);
		}
		tree = std::shared_ptr<CoverTree<PythonPoint>>(new CoverTree<PythonPoint>(maxDist, wrapped_points));
	}
        CoverTreePython(double maxDist): CoverTreePython(maxDist, boost::python::list()) {}
	bool isValidTree() const{ return tree->isValidTree();}
	
	void insert(const object  newPoint){
		tree->insert(PythonPoint(newPoint));
	}
	void remove(const object p){
		tree->remove(PythonPoint(p));
	}
	
	list kNearestNeighbors(const object p, const unsigned int& k) const {
		std::vector<PythonPoint> nearest = tree->kNearestNeighbors(PythonPoint(p), k);
		std::vector<object> result(nearest.size());
		std::transform(nearest.begin(), nearest.end(), result.begin(), [](PythonPoint&p_point){ return p_point.getObject(); });
		
		return toPythonList<object>(result);
	}

	void print() const{ tree->print(); }
				
};



