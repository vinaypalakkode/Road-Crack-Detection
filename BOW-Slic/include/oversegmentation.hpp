#ifndef OVERSEGMENTATION_H
#define OVERSEGMENTATION_H

/* oversegmentation.hpp.
 *
 * Written by: Srivatsan Varadharajan.
 *
 * 
 * This file contains the interface to the Oversegmentation class,
 * which will be used in the superpixel algorithm described in
 * "Vision for Road Inspection" - S. Varadharajan et.al. (WACV 2014)
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

class ImageSegment{
public:
    int label_;
    int area_;
    vector<ImageSegment*> neighbors_;
    Point centroid_;
    vector<Point> pixel_list_;
    ImageSegment(int _label);
    ImageSegment(int _label, Point _centroid);
    // ~ImageSegment();
    Point ComputeCentroid();
    void AddPixel(Point pt);
};

class Oversegmentation{
private:
    int im_height_, im_width_;
    int count_;
    vector<ImageSegment*> segments_;
public:
    Mat_<int> pixel_labels_;
    Oversegmentation(InputArray _original_image);
    Oversegmentation();
    ~Oversegmentation();
    bool IsNotSet(Point pt);
    void ResetSegmentation();
    size_t NumberOfSegments();
    void RelabelSegment(int orig_label, int new_label);    
    void ListPixelsForEachSegment();
    vector<int> GetAreasOfAllSegments();
    int SegmentArea(int segment_label);
    int AddNewSegmentAt(Point location);
    void AddPixelToSegment(Point pt, int segment_label);
    vector<Point> ComputeSegmentCentroids();
    vector<int> ComputeSegmentAreas();
    Point SegmentCentroid(int i);
    Point2f SegmentCentroid_f(int i);
    vector<int> DeleteSegments(vector<bool> discard_list);
    vector<Point> GetCentroids();
    void PrintSegmentBorders(InputArray _input_image, OutputArray _segment_borders);
    void PrintClusterCentroids(InputArray _input_image, OutputArray _segment_centroids);
    void RecolorWithCentroids(InputArray _input_image, OutputArray _recolored_image);
};
#endif

