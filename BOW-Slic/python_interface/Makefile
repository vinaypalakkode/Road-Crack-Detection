PYTHON_VERSION = 2.7

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
PYTHON_INCLUDE = /usr/include/python2.7
PYTHON_LIBRARY = /usr/lib/python2.7

NUMPY_INCLUDE = $(PYTHON_INCLUDE)/numpy
# location of the Boost Python include files and library

BOOST_INCLUDE = /usr/include
BOOST_LIB = /usr/lib
BOOST_PYTHON_LIB = -lboost_python

OPENCV_INCLUDE = /usr/local/include
OPENCV_LIB = /usr/local/lib
endif

ifeq ($(UNAME), Darwin)
PYTHON_INCLUDE = /opt/local/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
PYTHON_LIBRARY = /opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib

NUMPY_INCLUDE = /opt/local/Library/Frameworks/Python.framework/Versions/Current/lib/python2.7/site-packages/numpy/core/include
# location of the Boost Python include files and library

BOOST_INCLUDE = /opt/local/include
BOOST_LIB = /opt/local/lib
BOOST_PYTHON_LIB = -lboost_python-mt

OPENCV_INCLUDE = /opt/local/include
OPENCV_LIB = /opt/local/lib
endif

TARGET = python_bow_slic

SOURCE_FILES = $(TARGET).cpp ../src/bow_slic.cpp ../src/oversegmentation.cpp

$(TARGET).so: $(TARGET).o bow_slic.o oversegmentation.o
ifeq ($(UNAME), Darwin)
	g++ -shared $(TARGET).o bow_slic.o oversegmentation.o -L$(BOOST_LIB) $(BOOST_PYTHON_LIB) -L$(PYTHON_LIBRARY) -lpython$(PYTHON_VERSION) -L$(OPENCV_LIB) `pkg-config --libs opencv` -o $(TARGET).so -lc++
endif
ifeq ($(UNAME), Linux)
	g++ -shared $(TARGET).o bow_slic.o oversegmentation.o -L$(BOOST_LIB) $(BOOST_PYTHON_LIB) -L$(PYTHON_LIBRARY) -lpython$(PYTHON_VERSION) -L$(OPENCV_LIB) `pkg-config --libs opencv` -o $(TARGET).so
endif

$(TARGET).o: $(TARGET).cpp
	clang -O3 -I$(PYTHON_INCLUDE) -I$(BOOST_INCLUDE) -I$(OPENCV_INCLUDE) -I$(NUMPY_INCLUDE) -c $(SOURCE_FILES) -fpic

