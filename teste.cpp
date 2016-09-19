#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  	Mat image;
  	image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	for(int i=200;i<210;i++){
		for(int j=10;j<200;j++){
      	image.at<uchar>(i,j)=0;
    	}
	}
  	imshow("image", image);
  	waitKey();
  	return 0;
}