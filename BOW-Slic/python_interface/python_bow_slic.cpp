/*
 * python_texture_slic.cpp.
 *
 * Written by: Srivatsan Varadharajan.
 *
 * Python interface file for texture_slic function, written in texture_slic.cpp and texture_slic.hpp
 * 
 */

#include "python_bow_slic.hpp"

using namespace cv;
using namespace std;

PyBagOfWordsSlic::PyBagOfWordsSlic(int histogram_distance_weight, int area_threshold, int tightness){
    import_array(); // This is a function from NumPy that MUST be called.
    bow_slic_generator_ = new BagOfWordsSlic(histogram_distance_weight, area_threshold, tightness);
}

PyBagOfWordsSlic::~PyBagOfWordsSlic(){
    delete bow_slic_generator_;
}

PyObject* PyBagOfWordsSlic::GenerateSuperpixels(PyObject* input_image, int num_superpixels, PyObject* word_map){
    Mat cv_input_image_, cv_superpixel_image_, cv_word_map_;
    pyopencv_to(input_image, cv_input_image_);
    pyopencv_to(word_map, cv_word_map_);
    bow_slic_generator_->GenerateSuperpixels(cv_input_image_, cv_superpixel_image_, num_superpixels, cv_word_map_);
    return pyopencv_from(cv_superpixel_image_);
}

PyObject* PyBagOfWordsSlic::GenerateSuperpixelsWithCentroids(PyObject* input_image, int num_superpixels){
    Mat cv_input_image_, cv_superpixel_image_, cv_centroids_;
    pyopencv_to(input_image, cv_input_image_);
    bow_slic_generator_->GenerateSuperpixels(cv_input_image_, cv_superpixel_image_, num_superpixels, Mat(), Mat(), cv_centroids_);
    return Py_BuildValue("(OO)", pyopencv_from(cv_superpixel_image_), pyopencv_from(cv_centroids_));
}

PyObject* PyBagOfWordsSlic::GenerateSuperpixelsWithoutVisualWords(PyObject* input_image, int num_superpixels){
    Mat cv_input_image_, cv_superpixel_image_, cv_word_map_;
    pyopencv_to(input_image, cv_input_image_);
    bow_slic_generator_->GenerateSuperpixels(cv_input_image_, cv_superpixel_image_, num_superpixels);
    return pyopencv_from(cv_superpixel_image_);
}

PyObject* PyBagOfWordsSlic::OverlaySuperpixelBoundaries(PyObject* input_image, PyObject* superpixel_image){
    Mat cv_input_image_, cv_superpixel_image_, cv_overlay_;
    pyopencv_to(input_image, cv_input_image_);
    pyopencv_to(superpixel_image, cv_superpixel_image_);
    // resize(cv_input_image_,cv_input_image_,Size(0,0),0.5,0.5);
    bow_slic_generator_->OverlaySuperpixelBoundaries(cv_input_image_, cv_superpixel_image_, cv_overlay_);
    return pyopencv_from(cv_overlay_);
}

using namespace boost::python;
BOOST_PYTHON_MODULE(python_bow_slic){
	class_<PyBagOfWordsSlic>("PyBagOfWordsSlic", init<int, int, int>())
		.def("overlay_superpixel_boundaries", &PyBagOfWordsSlic::OverlaySuperpixelBoundaries)
        .def("generate_superpixels", &PyBagOfWordsSlic::GenerateSuperpixels)
        .def("generate_superpixels_and_centroids", &PyBagOfWordsSlic::GenerateSuperpixelsWithCentroids)
        .def("generate_superpixels", &PyBagOfWordsSlic::GenerateSuperpixelsWithoutVisualWords)
	;
}