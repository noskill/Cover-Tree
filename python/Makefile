
BOOST_LIB = /usr/lib

PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)

CC=g++
CFLAGS=-c -Wall --std=c++11 -I /usr/include/python2.7/ -fPIC

all: covertree.so

cover_tree.so: covertree.o
	$(CC) -shared -Wl,--export-dynamic covertree.o -L$(BOOST_LIB) -lboost_python-$(PYTHON_VERSION) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o cover_tree.so

covertree.o: covertree.c
	$(CC) $(CFLAGS) covertree.c -shared -o covertree.o

clean:
	rm -rf *.o *.so