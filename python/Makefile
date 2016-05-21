
BOOST_LIB = /usr/lib

PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)

CC=g++
CFLAGS=-c -Wall --std=c++11 -I /usr/include/python2.7/ -fPIC  -ftemplate-backtrace-limit=64

all: cover_tree.so

cover_tree.so: covertree.o Cover_Tree_Point.o
	$(CC) -shared -Wl,--export-dynamic covertree.o Cover_Tree_Point.o -L$(BOOST_LIB) -lboost_python -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o cover_tree.so

Cover_Tree_Point.o: ../Cover_Tree_Point.h ../Cover_Tree_Point.cc
	        g++ -c $(CFLAGS) ../Cover_Tree_Point.cc -shared -o Cover_Tree_Point.o

covertree.o: covertree.c
	$(CC) $(CFLAGS) covertree.c -shared -o covertree.o

clean:
	rm -rf *.o *.so
