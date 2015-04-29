/*
 * test_texture_slic.cpp.
 *
 * Written by: Srivatsan Varadharajan.
 *
 * Testing file for texture_slic function, written in texture_slic.cpp and texture_slic.hpp
 * 
 */
 
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
#include "../include/bow_slic.hpp"
#include "../include/debugging_functions.hpp"

int main(int argc, char *argv[]) {
    /* Load the image and convert to Lab colour space. */
    Mat input_image = imread(argv[1]);
    resize(input_image,input_image,Size(0,0),0.5,0.5);
    // Mat texton_map(input_image.rows,input_image.cols,CV_32S);
    cout << "opencv version: " << CV_VERSION << "\n";
    Mat texton_map = imread(argv[2], IMREAD_ANYDEPTH);
    resize(texton_map,texton_map,Size(0,0),0.5,0.5,INTER_NEAREST);
    // cout << texton_map.depth();

    // imshow("texton_map",texton_map);
    // waitKey(0);

    Mat mask(input_image.rows,input_image.cols,CV_8UC1);
    Mat superpixel_image(input_image.rows,input_image.cols,CV_8UC1);
    
    int num_superpixels = atoi(argv[3]);
    // int m = atoi(argv[3]);
    // int num_superpixels = 300;//1071;
    int m = atoi(argv[4]);
    int histogram_distance_weight = atoi(argv[5]);
    int area_threshold = atoi(argv[6]);
    
    // /* Perform the SLIC superpixel algorithm. */
    BagOfWordsSlic superpixel_generator(histogram_distance_weight, area_threshold, m);
    Mat centroids;
    superpixel_generator.GenerateSuperpixels(input_image,superpixel_image,num_superpixels,texton_map,mask,centroids);
    debugPrintMat<int>(centroids, "centroids");

    // DisplaySuperpixelsColorized(superpixel_image,"final");
    // displaySuperpixelBoundaries(input_image,superpixel_image);
    // destroyAllWindows();
}
