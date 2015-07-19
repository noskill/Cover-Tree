import math

class CoverTreePoint:
    def __init__(self, coords, name):
        self._vec = coords
        self._name = name

    def distance(self, p):
        timescalled = 0
        timescalled += 1;
        vec=p.getVec();
        dist=0.0;
        lim = len(vec);
        for i in range(lim): 
            d = vec[i] - self._vec[i]
            dist += d * d
       
        dist=math.sqrt(dist)
        return dist

    def getVec(self):
        return self._vec

    def getChar(self):
        return self._name

    def _print(self): 
        print "point ", self._name, ": "
        for it in self._vec:
            print it, " "
        print "\n"

    def __eq__(self, p):
        return self._vec == p.getVec() and self._name == p.getChar()

