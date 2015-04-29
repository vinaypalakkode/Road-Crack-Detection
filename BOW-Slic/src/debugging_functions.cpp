#include "../include/debugging_functions.hpp"

void displaySuperpixelBoundaries(InputArray _image, InputArray _superpixels){
    Mat image = _image.getMat();
    Mat labels = _superpixels.getMat();
    Mat displayImg = image.clone();
    Vec3b* pDispImg;
    int* pLabelAbove;
    int* pLabelBelow;
    int* pLabelThis;
    for(int i = 1; i < labels.rows; ++i){
        pLabelAbove = labels.ptr<int>(i-1);
        // pLabelBelow = labels.ptr<int>(i+1);
        pLabelThis = labels.ptr<int>(i);
        pDispImg = displayImg.ptr<Vec3b>(i);
        for(int j = 1; j < labels.cols; ++j){
            pDispImg[j] = (pLabelAbove[j] == pLabelThis[j] && pLabelThis[j-1] == pLabelThis[j+1]) ? pDispImg[j] : Vec3b(0,0,255);
        }
    }
    namedWindow("imgOverSeg->pixelLabels");
    imshow("imgOverSeg->pixelLabels",displayImg);
    imwrite("histogram_on.png", displayImg);
    waitKey(0);
    destroyWindow("imgOverSeg->pixelLabels");
}

void DisplaySuperpixelsColorized(InputArray _superpixels, const string& window_name){

    Vec3b color_map[50] = {
            Vec3b(50, 16, 54),
            Vec3b(48, 67, 91),
            Vec3b(40, 47, 204),
            Vec3b(80, 91, 239),
            Vec3b(70, 106, 215),
            Vec3b(185, 107, 40),
            Vec3b(236, 90, 148),
            Vec3b(149, 104, 253),
            Vec3b(77, 232, 19),
            Vec3b(126, 232, 135),
            Vec3b(107, 38, 93),
            Vec3b(53, 12, 180),
            Vec3b(29, 150, 206),
            Vec3b(74, 61, 56),
            Vec3b(17, 85, 177),
            Vec3b(59, 163, 6),
            Vec3b(182, 169, 135),
            Vec3b(3, 184, 123),
            Vec3b(172, 223, 207),
            Vec3b(5, 34, 195),
            Vec3b(212, 213, 64),
            Vec3b(118, 86, 117),
            Vec3b(249, 241, 80),
            Vec3b(172, 95, 245),
            Vec3b(215, 200, 30),
            Vec3b(126, 247, 172),
            Vec3b(102, 238, 101),
            Vec3b(113, 157, 212),
            Vec3b(148, 51, 158),
            Vec3b(232, 46, 9),
            Vec3b(246, 176, 7),
            Vec3b(167, 227, 27),
            Vec3b(236, 222, 240),
            Vec3b(141, 216, 72),
            Vec3b(253, 177, 10),
            Vec3b(244, 242, 236),
            Vec3b(247, 182, 214),
            Vec3b(208, 14, 59),
            Vec3b(34, 235, 248),
            Vec3b(182, 15, 132),
            Vec3b(112, 254, 91),
            Vec3b(203, 77, 208),
            Vec3b(4, 131, 177),
            Vec3b(190, 52, 141),
            Vec3b(243, 39, 102),
            Vec3b(55, 118, 96),
            Vec3b(76, 95, 56),
            Vec3b(162, 158, 127),
            Vec3b(4, 232, 232),
            Vec3b(109, 28, 180)
        };
    Mat labels = _superpixels.getMat();
    Mat display_image(labels.size(), CV_8UC3);
    Vec3b* display_image_ptr;
    int* label_above_ptr;
    int* label_below_ptr;
    int* label_this_ptr;
    for(int i = 1; i < labels.rows; ++i){
        label_above_ptr = labels.ptr<int>(i-1);
        // label_below_ptr = labels.ptr<int>(i+1);
        label_this_ptr = labels.ptr<int>(i);
        display_image_ptr = display_image.ptr<Vec3b>(i);
        for(int j = 1; j < labels.cols; ++j){
            if(label_above_ptr[j] == label_this_ptr[j] && label_this_ptr[j-1] == label_this_ptr[j])
                display_image_ptr[j] =  color_map[label_this_ptr[j]%50];
            else
                display_image_ptr[j] =  Vec3b(0,0,0);
        }
    }
    namedWindow(window_name);
    imshow(window_name,display_image);
    imwrite(window_name + ".png", display_image);
} 

void renderTextonMapAsImage(InputArray _textonMap, OutputArray _textonImage){
    Mat textonMap = _textonMap.getMat();
    Mat textonImage = _textonImage.getMat();

    Vec3b colorMap[50] = {
            Vec3b(50, 16, 54),
            Vec3b(48, 67, 91),
            Vec3b(40, 47, 204),
            Vec3b(80, 91, 239),
            Vec3b(70, 106, 215),
            Vec3b(185, 107, 40),
            Vec3b(236, 90, 148),
            Vec3b(149, 104, 253),
            Vec3b(77, 232, 19),
            Vec3b(126, 232, 135),
            Vec3b(107, 38, 93),
            Vec3b(53, 12, 180),
            Vec3b(29, 150, 206),
            Vec3b(74, 61, 56),
            Vec3b(17, 85, 177),
            Vec3b(5, 16, 6),
            Vec3b(182, 169, 135),
            Vec3b(3, 184, 123),
            Vec3b(172, 223, 207),
            Vec3b(5, 34, 95),
            Vec3b(212, 213, 64),
            Vec3b(118, 86, 117),
            Vec3b(249, 241, 80),
            Vec3b(172, 95, 245),
            Vec3b(215, 200, 30),
            Vec3b(126, 247, 172),
            Vec3b(102, 238, 101),
            Vec3b(113, 157, 212),
            Vec3b(148, 51, 158),
            Vec3b(232, 46, 9),
            Vec3b(246, 176, 7),
            Vec3b(167, 227, 27),
            Vec3b(236, 222, 240),
            Vec3b(141, 216, 72),
            Vec3b(253, 177, 10),
            Vec3b(244, 242, 236),
            Vec3b(247, 182, 214),
            Vec3b(208, 14, 59),
            Vec3b(34, 235, 248),
            Vec3b(182, 15, 132),
            Vec3b(112, 254, 91),
            Vec3b(203, 77, 208),
            Vec3b(4, 131, 177),
            Vec3b(190, 52, 141),
            Vec3b(243, 39, 102),
            Vec3b(55, 118, 96),
            Vec3b(76, 95, 56),
            Vec3b(162, 158, 127),
            Vec3b(4, 232, 232),
            Vec3b(109, 28, 180)
        }; 
    unsigned short* tMap; 
    Vec3b* tImg;
    for(int i = 0; i < textonMap.rows; ++i){
        tMap = textonMap.ptr<unsigned short>(i);
        tImg = textonImage.ptr<Vec3b>(i);
        for(int j = 0; j < textonMap.cols; ++j)
            tImg[j] = colorMap[tMap[j]-1];
    }
 
}
