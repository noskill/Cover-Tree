from  cover_tree import CoverTree
from cover_tree_point import CoverTreePoint

import random

CoverTree(10.0, [CoverTreePoint([1,2], 'm'),])
CoverTree(10.0)

def testTree():
    a = (1.0,)
    cTree = CoverTree(10)
    cTree.insert(CoverTreePoint(a,'a'))
    cTree.insert(CoverTreePoint(a,'b'))
    cTree.insert(CoverTreePoint(a,'c'))
    cTree.remove(CoverTreePoint(a,'b'))
    cTree.remove(CoverTreePoint(a,'c'))
    
    a = (2.1,);  cTree.insert(CoverTreePoint(a,'a'))
    a = (3.2,);  cTree.insert(CoverTreePoint(a,'a'))
    a = (4.1,);  cTree.insert(CoverTreePoint(a,'a'))
    a = (1.1,);  cTree.insert(CoverTreePoint(a,'a'))
    a = (2.5,);  cTree.insert(CoverTreePoint(a,'a'))
    a = (3.1,);  cTree.insert(CoverTreePoint(a,'a'))

    if(cTree.isValidTree()):
      print  "Insert test: \t\t\t\tPassed\n"
    else:
      print  "Insert test: \t\t\t\tFailed\n"

    a=(2.0,) # the 5 nearest points to this are 2.1, 2.5, 1.1, 1, 3.1
    points = cTree.kNearestNeighbors(CoverTreePoint(a,'a'),5)
    kNNGood=True
    for p in points:
        p._print()
    a = (2.1,)
    if(not (CoverTreePoint(a,'a')==points[0])):
        kNNGood=False
    a = (2.5,)
    if(not (CoverTreePoint(a,'a')==points[1])):
        kNNGood=False
    a = (1.1,)
    if(not (CoverTreePoint(a,'a')==points[2])):
        kNNGood=False
    a = (1.0,)
    if(not (CoverTreePoint(a,'a')==points[3])):
        kNNGood=False
    a = (3.1,)
    if(not (CoverTreePoint(a,'a')==points[4])):
        kNNGood=False
    if(kNNGood):
        print  "KNN test: \t\t\t\tPassed\n"
    else:
        print  "KNN test: \t\t\t\tFailed\n"
    
    cTree.insert(CoverTreePoint(a,'b'))
    cTree.insert(CoverTreePoint(a,'c'))    
    
    points = cTree.kNearestNeighbors(CoverTreePoint(a,'a'), 1)
    #there should be a three-way tie since there are 3 nodes with distance 0
    if len(points) == 3 and points[2].distance(CoverTreePoint(a,'a')) == 0.0:
        print "Multiple 0 distance points test: \tPassed\n"
    else:
        print "Multiple 0 distance points test: \tFailed\n"

    cTree.remove(CoverTreePoint(a,'b'))
    points = cTree.kNearestNeighbors(CoverTreePoint(a,'a'), 1)
    #there should be a two-way tie now since one was removed
    if len(points) == 2 and points[1].distance(CoverTreePoint(a,'a')) == 0.0:
        print "Multiple 0 distance points removal test:Passed\n"
    else:
        print "Multiple 0 distance points removal test:Failed\n"
    
    a = (2.124,)
    cTree.remove(CoverTreePoint(a,'a'))
    a = (4.683,)
    cTree.remove(CoverTreePoint(a,'a'))
    a = (9.123,)
    cTree.remove(CoverTreePoint(a,'a'))
    if(cTree.isValidTree()):
        print "Remove nonexistent point test: \t\tPassed\n"
    else:
        print "Remove nonexistent point test: \t\tFailed\n"

    a = (1.1,)
    cTree.remove(CoverTreePoint(a,'b')) #//this has dist 0 to a
    #node in cTree, but it is a different point, so the removal should not
    #alter the tree at all.
    points = cTree.kNearestNeighbors(CoverTreePoint(a,'c'),1)
    if(points[0]==CoverTreePoint(a,'a') and cTree.isValidTree()):
        print "Remove differently-named point test: \tPassed\n"
    else:
        print "Remove differently-named point test: \tFailed\n"
    
    a = (3.2,);  cTree.remove(CoverTreePoint(a,'a'))
    a = (1.1,);  cTree.remove(CoverTreePoint(a,'a'))
    a = (2.5,);  cTree.remove(CoverTreePoint(a,'a'))
    if(cTree.isValidTree()):
        print "Remove test: \t\t\t\tPassed\n"
    else:
        print "Remove test: \t\t\t\tFailed\n"

    a = (1.0,);  cTree.remove(CoverTreePoint(a,'a'))
    if(cTree.isValidTree()):
        print "Remove root test: \t\t\tPassed\n"
    else:
        print "Remove root test: \t\t\tFailed\n"

    start = []
    for i in range(5):
       start.append(random.random())

    initVec = []
    initVec.append(CoverTreePoint(start, 'a'))
 
    cTree2 = CoverTree(10, initVec) 
    cTree2.remove(CoverTreePoint(start,'a')) #Now the tree has no nodes...
    #make sure it can handle trying to remove a node when
    #it has no nodes to begin with...
    cTree2.remove(CoverTreePoint(start,'a'))
    points = []
    for i in range(500):
        a = [random.random() for j in range(5)]
        cTree2.insert(CoverTreePoint(a, 'a'))
        points.append(a)
    if cTree2.isValidTree():
        print "500 random inserts test: \t\tPassed\n"
    else:
        print "500 random inserts test: \t\tFailed\n"  
    #points = vector<CoverTreePoint>()
    #for(int i=0i<500i++) {
        #vector<double> a
        #for(int j=0j<5j++) {
            #a.push_back((double)rand()/(double)RAND_MAX)
        #}
        #cTree2.insert(CoverTreePoint(a,'a'))
        #points.push_back(CoverTreePoint(a,'a'))
    #}
    #if(cTree2.isValidTree()) print "500 random inserts test: \t\tPassed\n"
    #else print "500 random inserts test: \t\tFailed\n"

    #bool NNGood=true
    #for(int i=0i<100i++) {
        #vector<CoverTreePoint>
            #v = cTree2.kNearestNeighbors(points[i],1)
        #if(v[0].distance(points[i])!=0.0) NNGood=False
    #}
    #if(NNGood) print "Nearest Neighbor test: \t\t\tPassed\n"
    #else print "Nearest Neighbor test: \t\t\tFailed\n"

    #for(int i=0i<490i++) {
        #cTree2.remove(points[i])
    #}
    #if(cTree2.isValidTree()) print "Remove random test: \t\t\tPassed\n"
    #else print "Remove random test: \t\t\tFailed\n"

if __name__ == '__main__':
    testTree()
