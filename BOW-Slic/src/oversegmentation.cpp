#include "../include/oversegmentation.hpp"

/*------------------------------------------------------------*/
/*---------------------   ImageSegment   ---------------------*/
/*------------------------------------------------------------*/

/*-----------  Constructor - 1  -----------*/
ImageSegment::ImageSegment(int _label, Point _centroid){
    label_ = _label;
    centroid_ = _centroid;
    area_ = 1;
}

/*-----------  Constructor - 2  -----------*/
ImageSegment::ImageSegment(int _label){
    area_ = 0;
    label_ = _label;
    centroid_ = Point(-1,-1);
}

void ImageSegment::AddPixel(Point pt){
    pixel_list_.push_back(pt);
}

/*------------------------------------------------------------*/
/*-------------------   Oversegmentation   -------------------*/
/*------------------------------------------------------------*/

/*-----------  Constructor  -----------*/
Oversegmentation::Oversegmentation(){
}

Oversegmentation::Oversegmentation(InputArray _original_image){
	Mat original_image_ = _original_image.getMat();
	im_height_ = original_image_.rows;
	im_width_ = original_image_.cols;
    pixel_labels_ = Mat(Size(im_width_,im_height_),CV_32S, -1);
}

Oversegmentation::~Oversegmentation(){
    // cout << segments_.size();
    for (int i = 0; i < segments_.size();++i){
        delete segments_[i];
    }
}

bool Oversegmentation::IsNotSet(Point pt){
    return pixel_labels_.at<int>(pt) == -1;
}

void Oversegmentation::ResetSegmentation(){
    for (int i = 0; i < segments_.size();++i)
        delete segments_[i];
    segments_.clear();
    pixel_labels_.setTo(-1);
}

size_t Oversegmentation::NumberOfSegments(){
    return segments_.size();
}

// /*-----------  Get Pixel Labels - returns Mat  -----------*/
// Mat Oversegmentation::getPixelLabelMat(){
//     return pixel_labels_;
// }

/*-----------  Add new superpixel at point  -----------*/
int Oversegmentation::AddNewSegmentAt(Point pt){
    int segment_label = segments_.size();
    segments_.push_back(new ImageSegment(segment_label, Point2f(pt.x,pt.y)));
    pixel_labels_.at<int>(pt) = segment_label;
    return segment_label;
}

void Oversegmentation::AddPixelToSegment(Point pt, int segment_label){
    if (segment_label >= 0){
        pixel_labels_.at<int>(pt) = segment_label;
        segments_[segment_label]->AddPixel(pt);
    }
}

/*-----------  Recompute superpixel centroids  -----------*/
vector<Point> Oversegmentation::ComputeSegmentCentroids(){
    vector<Point> mean_centroids(segments_.size(), Point(0,0));
    int* ptr_pix_labels;

    for (int i = 0; i < im_height_; ++i){
        ptr_pix_labels = pixel_labels_.ptr<int>(i);
        for (int j = 0; j < im_width_; ++j){
            if(ptr_pix_labels[j] >= 0){
                mean_centroids[ptr_pix_labels[j]].x += j;
                mean_centroids[ptr_pix_labels[j]].y += i;
            }
        }
    }

    for (int i = 0; i < segments_.size(); ++i) {
        mean_centroids[i] *= 1.0/segments_[i]->area_;
        segments_[i]->centroid_ = mean_centroids[i];
    }

    return mean_centroids;
}

/*-----------  Recompute superpixel areas  -----------*/
vector<int> Oversegmentation::ComputeSegmentAreas(){
    vector<int> segment_areas(segments_.size(),0);
    int* ptr_pix_labels;

    for (int i = 0; i < im_height_; ++i){
        ptr_pix_labels = pixel_labels_.ptr<int>(i);

        for (int j = 0; j < im_width_; ++j)
            if(ptr_pix_labels[j] >= 0)
                segment_areas[ptr_pix_labels[j]]++;
    }

    for (int i = 0; i < segments_.size(); ++i) {
        segments_[i]->area_ = segment_areas[i];
    }

    return segment_areas;
}

/*----------- Return superpixel centroids -----------*/
vector<Point> Oversegmentation::GetCentroids(){
    vector<Point> vector_of_centroids;

    for (int i = 0; i < segments_.size(); ++i)
        vector_of_centroids.push_back(segments_[i]->centroid_); 

    return vector_of_centroids;
}

/*----------- Get centroid for superpixel[i] (int) -----------*/
Point Oversegmentation::SegmentCentroid(int i){
    Point pt = segments_[i]->centroid_;
    return pt;
}

/*-----------  Get centroid for superpixel[i] (float)  -----------*/
Point2f Oversegmentation::SegmentCentroid_f(int i){
    return segments_[i]->centroid_;
}

/*-----------  Get Pixel Areas - returns vector of areas -----------*/
vector<int> Oversegmentation::GetAreasOfAllSegments(){
    vector<int> pixel_areas;
    for(int i=0; i < segments_.size(); ++i) pixel_areas.push_back(segments_[i]->area_);
    return pixel_areas;
}

/*----------- Get area of a single segment -----------*/
int Oversegmentation::SegmentArea(int segment_label){
    return segments_[segment_label]->area_;
}

/*-----------  Delete and renumber segments -----------*/
// Pass a boolean vector containing True for segments to be deleted

vector<int> Oversegmentation::DeleteSegments(vector<bool> discard_list){
    vector<int> new_indices(segments_.size(),0);
    vector<ImageSegment*> new_segments;
    
    for (int i = 0; i < discard_list.size(); ++i){
        if(discard_list[i]){
            new_indices[i] = -1;
            delete segments_[i];
        }
        else{
            new_segments.push_back(segments_[i]);
            new_indices[i] = new_segments.size()-1;
        }
    }
    segments_.clear();
    segments_ = new_segments;

    MatIterator_<int> itr_pixel_labels = pixel_labels_.begin();
    while(itr_pixel_labels != pixel_labels_.end()){
        if (*itr_pixel_labels >= 0)
            *itr_pixel_labels = new_indices[*itr_pixel_labels];
        itr_pixel_labels++;
    }
    return new_indices;
}

/*-------- Construct list of pixels for each segment --------*/
// Creates explicit list of points in each segment

void Oversegmentation::ListPixelsForEachSegment(){
    for(int i = 0; i < segments_.size(); ++i){
        segments_[i]->area_ = 0;
        segments_[i]->pixel_list_.clear();
        segments_[i]->label_ = i;
    }

    int* ptr_pix_labels;
    for(int i = 0; i < im_height_; ++i){
        ptr_pix_labels = pixel_labels_.ptr<int>(i);
        for(int j = 0; j < im_width_; ++j){ 
            if (ptr_pix_labels[j] >= 0){
                AddPixelToSegment(Point(j,i), ptr_pix_labels[j]);
            }
        }
    }
    ComputeSegmentAreas();
    ComputeSegmentCentroids();
}

/*---------- Change label of segment ----------*/
// Works only if pixel_list_ has been populated for each segment

// pixel_list_ can be populated by using AddPixelToSegment to assign
// pixels to segments instead of directly modifying the Mat pixel_labels_

// If segments have been created using Mat pixel_labels_, 
// call ListPixelsForEachSegment to populate the pixel_list_ for each segment

void Oversegmentation::RelabelSegment(int orig_label, int new_label){
    vector<Point> pixels_to_relabel = segments_[orig_label]->pixel_list_;

    for (int i = 0; i < pixels_to_relabel.size(); ++i)
        AddPixelToSegment(pixels_to_relabel[i], new_label);

    segments_[orig_label]->pixel_list_.clear();
}

/*-----------  Visualize superpixel borders  -----------*/
void Oversegmentation::PrintSegmentBorders(InputArray _input_image, OutputArray _segment_borders){
    Mat image = _input_image.getMat();
    Mat display_img = _segment_borders.getMat();
    display_img = image.clone();
    Vec3b* p_disp_img;
    int* p_label_above;
    int* p_label_below;
    int* p_label_this;
    for(int i = 1; i < pixel_labels_.rows - 1; ++i){
        p_label_above = pixel_labels_.ptr<int>(i-1);
        p_label_below = pixel_labels_.ptr<int>(i+1);
        p_label_this = pixel_labels_.ptr<int>(i);
        p_disp_img = display_img.ptr<Vec3b>(i);
        for(int j = 1; j < pixel_labels_.cols - 1; ++j){
            p_disp_img[j] = (p_label_above[j] == p_label_below[j] && p_label_this[j-1] == p_label_this[j+1]) ? p_disp_img[j] : Vec3b(0,0,255);
        }
    }
}

void Oversegmentation::PrintClusterCentroids(InputArray _input_image, OutputArray _segment_centroids){

}
void Oversegmentation::RecolorWithCentroids(InputArray _input_image, OutputArray _recolored_image){

}