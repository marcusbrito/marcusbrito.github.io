#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

double alfa;
int alfa_slider = 0;
int alfa_slider_max = 100;

int top_slider = 0;
int top_slider_max = 100;

Mat original, borrada, final ;
Mat imageTop; 

void blend(int, void*){
  for (int i = 0; i < count; ++i)
  {
    /* code */
  }
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted( image1, alfa, imageTop, 1-alfa, 0.0, blended);
 imshow("addweighted", blended);
}

double alpha(double x, double l1, double l2, double d){
  return 0.5*(tanh((x-l1)/d) - tanh((xl2)/d));
}
void soma()

int main(int argc, char** argv){
  Mat image, borrada;
  double l1,l2,d;
  float media[] = {1,1,1,
           1,1,1,
           1,1,1};
  mask = Mat(3, 3, CV_32F, media);
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;

  image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  //Borrando a borrada
  borrada = image.clone();
  for (int i = 0; i < 20; ++i)
  {
    filter2D(borrada, borrada, borrada.depth(), mask, Point(1,1), 0);
  }

  
  imshow("image", trocada);
  waitKey();
  return 0;
}