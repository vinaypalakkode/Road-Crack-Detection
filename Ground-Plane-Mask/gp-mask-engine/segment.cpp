/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include <image.h>
#include <misc.h>
#include <pnmfile.h>
#include "segment-image.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void usage(char** argv,int argc){

  if (argc != 6) {
  
    fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
    exit(0);
  }

}


cv::Mat imgToMat( image<rgb> *input){


  int width  = input->width();
  int height = input->height();

  cv::Mat imgMat(height,width,CV_8UC3);


  
  for(int i = 0; i < height; i++){
  
    for(int j=0; j < width; j++){
   

     imgMat.at<Vec3b>(i,j)[0] = input->data[i*width + j].b;
     imgMat.at<Vec3b>(i,j)[1] = input->data[i*width + j].g;
     imgMat.at<Vec3b>(i,j)[2] = input->data[i*width + j].r;


    }

  }
    return imgMat;

}


// helper to change the form of the image container
image<rgb>* matToimg(cv::Mat input ){


  int width  = input.cols; 
  int height = input.rows;

  image<rgb> *imPtr = new image<rgb>(input.cols, input.rows);


  for(int i = 0; i < height; i++){
  
    for(int j=0; j < width; j++){
   

       imPtr->data[ i*width + j].b = input.at<Vec3b>(i,j)[0]; 
       imPtr->data[ i*width + j].g = input.at<Vec3b>(i,j)[1]; 
       imPtr->data[ i*width + j].r = input.at<Vec3b>(i,j)[2]; 

    }
  
  }
  
  return imPtr;

}

int main(int argc, char **argv) {


  // sanity check for correct input
  usage(argv,argc);

  float sigma = atof(argv[1]);
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);
	
  printf("loading input image.\n");

  cv::Mat inp = imread(argv[4]);
  
  image<rgb> *input = matToimg(inp); 

  printf("processing\n");
  int num_ccs; 
  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs); 
  
  Mat outImg  = imgToMat(seg);
  Mat grayImg(outImg.rows,outImg.cols, CV_8UC1);
 
 cvtColor(outImg,grayImg,CV_BGR2GRAY);

  imshow("output",outImg);
  waitKey(0);

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");

  return 0;

}

