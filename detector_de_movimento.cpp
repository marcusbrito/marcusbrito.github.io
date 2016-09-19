#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath> 

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image,image1,hist,hist1, dif;
  VideoCapture cap;
  vector<Mat> planes,planes1;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  double valor;

  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "Deu ruim!";
    return -1;
  }
  cap >> image;
  while(1){
    cap >> image1;
    split (image, planes);
    split (image1, planes1);
    calcHist(&planes[2], 1, 0, Mat(), hist, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes1[2], 1, 0, Mat(), hist1, 1,
             &nbins, &histrange,
             uniform, acummulate);

    valor = norm(hist, hist1, NORM_L2, Mat() );

    imshow("Image", image);

    image1.copyTo(image);

    if(valor>8000)
    printf("MOVIMENTO DETECTADO - %f\n",valor );

    if(waitKey(30) >= 0) break;  
  }
  return 0;
}
