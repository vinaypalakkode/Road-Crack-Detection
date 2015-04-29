#ifndef BOW_SLIC_H
#define BOW_SLIC_H

/* bow_slic.hpp.
 *
 * Written by: Srivatsan Varadharajan.
 *
 * 
 * This file contains the interface to the TEXTURE_SLIC class,
 * which is an implementation of the superpixel algorithm used in
 * "Vision for Road Inspection" - S. Varadharajan et.al. (WACV 2014)
 * The algorithm requires the texton map for the input image to be 
 * given as input along with the image.
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "oversegmentation.hpp"
#include <stack>
#include <queue>
#include "../include/debugging_functions.hpp"

using namespace std;
using namespace cv;

typedef Vec<int, 50> Vec50s;
typedef Vec<double, 50> Vec50d;

class ClusterPoint{
public:
    Point2f pt_;
    Vec3b lab_color_;
    Vec50d visual_word_histogram_;
    ClusterPoint();
    ClusterPoint(Point2f _pt, Vec3b _lab_color, Vec50d _vword_histogram);
    ~ClusterPoint();
    double distance_to(const ClusterPoint& x, int m, int S, int histogram_distance_weight);
};

class BagOfWordsSlic {
private:

    Mat distance_matrix_;
    const int kMaxIter, kMinSuperpixelAreaThreshold, kHistogramDistanceWeight;
    const double kCentroidErrorThreshold;
    int im_height_, im_width_;
    int num_superpixels_, m_, S_;
    Oversegmentation* image_oversegmentation_;

    Mat visual_word_histogram_matrix_;
    Mat input_image_;

    vector<ClusterPoint> cluster_centroids_;

    // vector<bool> discardList;
    void RenumberEachConnectedComponent();
    void RelabelSmallSegmentsToNearestNeighbor(int area_threshold);
    void UpdateClusterCentroids(Mat lab_image);
    void ComputeVisualWordHistograms(int window_height, int window_width, const Mat& visual_word_map);
    void MoveCentroidsToLocalGradientMinima();
public:
    BagOfWordsSlic(int histogram_distance_weight, int area_threshold, int tightness);
    ~BagOfWordsSlic();
    void GenerateSuperpixels(InputArray _input_image, OutputArray _superpixels,
     int _number_of_superpixels, InputArray _visual_word_map = Mat(), InputArray _mask = Mat(), 
     OutputArray _superpixel_centroids = Mat());
    void OverlaySuperpixelBoundaries(InputArray _input_image, InputArray _superpixels, OutputArray _boundaries);
};

inline bool OutOfBounds(Point pt, int x_max, int y_max){
    return (pt.x < 0) || (pt.x >= x_max) || (pt.y < 0) || (pt.y >= y_max);
}

#endif

