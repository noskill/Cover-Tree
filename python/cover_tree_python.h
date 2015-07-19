#include <boost/python.hpp>
#include "../Cover_Tree.h"
#include "PythonPoint.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace boost::python;

class CoverTreePython{
	private:
		std::shared_ptr<CoverTree<PythonPoint>> tree;
		CoverTreePython() = delete;
	public:
        CoverTreePython(const double& maxDist, const std::vector<object>& points=std::vector<object>()){
		std::vector<PythonPoint> wrapped_points;
		wrapped_points.reserve(points.size());
        	for(auto it=points.begin(); it!=points.end(); ++it){
			wrapped_points.emplace_back(*it);
		}
		tree = std::shared_ptr<CoverTree<PythonPoint>>(new CoverTree<PythonPoint>(maxDist, wrapped_points));
	}
	bool isValidTree() const{ return tree->isValidTree();}
	
	void insert(const object  newPoint){
		tree->insert(PythonPoint(newPoint));
	}
	void remove(const object p){
		tree->remove(PythonPoint(p));
	}
	
	std::vector<object> kNearestNeighbors(const object p, const unsigned int& k) const {
		std::vector<PythonPoint> nearest = tree->kNearestNeighbors(PythonPoint(p), k);
		std::vector<object> result(nearest.size());
		std::transform(nearest.begin(), nearest.end(), result.begin(), [](PythonPoint&p_point){ return p_point.getObject(); });
		return result;
	}

	void print() const{ tree->print(); }
				
};



