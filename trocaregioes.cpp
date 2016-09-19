#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  Mat trocada(height, width, image.type());

  image(Rect(0, 0, width/2, height/2)).copyTo(trocada(Rect(width/2, height/2, width/2, height/2)));
  

  image(Rect(0, height/2, width/2, height/2)).copyTo(trocada(Rect(width/2,0, width/2, height/2)));

  image(Rect(width/2,0,width/2,height/2)).copyTo(trocada(Rect(0,height/2, width/2, height/2)));

  image(Rect(width/2,height/2,width/2,height/2)).copyTo(trocada(Rect(0,0, width/2, height/2)));

  

  imshow("image", trocada);
  waitKey();
  return 0;
}