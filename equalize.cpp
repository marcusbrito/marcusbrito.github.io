#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image,original, equalizada;
  VideoCapture cap;
  
  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "Deu ruim!";
    return -1;
  }

  while(1){
    cap >> image;
    cvtColor(image, original, CV_BGR2GRAY);
    
    equalizeHist( original, equalizada );
    
    imshow("Original", original);
    imshow("Equalizada", equalizada);
    if(waitKey(30)>=0) break;
  }
  return 0;
}