#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/python.hpp>
#include "cv2_python_conversion.hpp"
#include "../include/bow_slic.hpp"

class PyBagOfWordsSlic{
    BagOfWordsSlic* bow_slic_generator_;
public:
    PyBagOfWordsSlic(int histogram_distance_weight, int area_threshold, int tightness);
    ~PyBagOfWordsSlic();
    PyObject* GenerateSuperpixels(PyObject* input_image, int num_superpixels, PyObject* word_map);
    PyObject* GenerateSuperpixelsWithoutVisualWords(PyObject* input_image, int num_superpixels);
    PyObject* GenerateSuperpixelsWithCentroids(PyObject* input_image, int num_superpixels);
    PyObject* OverlaySuperpixelBoundaries(PyObject* input_image, PyObject* superpixel_image);
};
