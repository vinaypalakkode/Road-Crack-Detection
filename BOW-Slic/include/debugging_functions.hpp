#ifndef __DEBUGGING_FUNCTIONS__
#define __DEBUGGING_FUNCTIONS__
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>

using namespace cv;
using namespace std;

template <typename T>
void debugPrintMat(InputArray _someMat, string label){
    Mat someMat = _someMat.getMat();
    cout << "\n" << label << ":\n";
    int i = 0;
    for(MatIterator_<T>it = someMat.begin<T>(); it != someMat.end<T>(); ++it){
        cout << *it << "\t";
        if (++i % someMat.cols == 0)
            cout << "\n";
    }
}
void DisplaySuperpixelsColorized(InputArray _superpixels, const string& window_name);
void displaySuperpixelBoundaries(InputArray _image, InputArray _superpixels);

void renderTextonMapAsImage(InputArray _textonMap, OutputArray _textonImage);

template <typename T>
void countOccurrencesOfValue(InputArray _someMat, T value){
    Mat someMat = _someMat.getMat();
    cout << "\noccurrences of " << value << ":\t";
    int count = 0;
    for(MatIterator_<T>it = someMat.begin<T>(); it != someMat.end<T>(); ++it){
    	if (*it == value) ++count;
    }
    cout << count << "\n";
}

#endif // __DEBUGGING_FUNCTIONS__