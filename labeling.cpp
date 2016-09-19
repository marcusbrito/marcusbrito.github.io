#include <iostream>
#include <opencv2/opencv.hpp>
#include <stack>

using namespace cv;
using namespace std;


void seedfill(Mat image, CvPoint p, unsigned char cor){
  unsigned char cor_atual;
  CvPoint aux1,aux2,aux3,aux4,aux5,aux6,aux7,aux8;

  cor_atual= image.at<uchar>(p.y,p.x) ;
  
  if(image.at<uchar>(p.y + 1,p.x) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux1.x = p.x;
    aux1.y = p.y + 1;
    
    seedfill(image,aux1,cor);
  }
  if(image.at<uchar>(p.y - 1,p.x) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux2.x = p.x;
    aux2.y = p.y - 1;
    
    seedfill(image,aux2,cor);
  }
  if(image.at<uchar>(p.y,p.x + 1) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux3.x = p.x + 1;
    aux3.y = p.y;
    
    seedfill(image,aux3,cor);
  }
  if(image.at<uchar>(p.y,p.x - 1) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux4.x = p.x - 1;
    aux4.y = p.y;
    
    seedfill(image,aux4,cor);
  }
  if(image.at<uchar>(p.y + 1,p.x + 1) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux5.x = p.x + 1;
    aux5.y = p.y + 1;
    
    seedfill(image,aux5,cor);
  }
  if(image.at<uchar>(p.y + 1,p.x - 1) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux6.x = p.x - 1;
    aux6.y = p.y + 1;
    
    seedfill(image,aux6,cor);
  }
  if(image.at<uchar>(p.y - 1,p.x + 1) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux7.x = p.x + 1;
    aux7.y = p.y - 1;
    
    seedfill(image,aux7,cor);
  }
  if(image.at<uchar>(p.y - 1,p.x - 1) == cor_atual){
    image.at<uchar>(p.y,p.x) = cor;

    aux8.x = p.x - 1;
    aux8.y = p.y - 1;
    
    seedfill(image,aux8,cor);
  }
  
  
}

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int comf = 0, semf = 0;
  
  CvPoint p,p1;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

  //Limpar as bordas
  for(int i=0; i<height; i++) 
  {
    if(image.at<uchar>(i,0) == 255)
    {
      p.x=0;
      p.y=i;
      floodFill(image,p,0);
    }
    if(image.at<uchar>(i,width-1) == 255)
    {
      p.x=width-1;
      p.y=i;
      floodFill(image,p,0);
    }
  }
  for(int j=0; j<width; j++) 
  {
    if(image.at<uchar>(0,j) == 255)
    {
      p.x=j;
      p.y=0;
      floodFill(image,p,0);
    }
    if(image.at<uchar>(height -1,j) == 255)
    {
      p.x=j;
      p.y=height-1;
      floodFill(image,p,0);
    }
  }

  p.x=0;
  p.y=0;
  floodFill(image,p,0);

  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(image.at<uchar>(i,j) == 0 && image.at<uchar>(i,j-1) == 255 )
      {
        // achou um objeto
        comf++;
        p.x=j;
        p.y=i;
       floodFill(image,p,comf);

        p1.x=j-1;
        p1.y=i;
        floodFill(image,p1,1);
      }
    }
  }
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
    // achou um objeto
    semf++;
    p.x=j;
    p.y=i;
    floodFill(image,p,semf);
    }
  }
  }
  printf("Bolhas com furos: %i\n",comf);
  printf("Bolhas sem furos: %i\n",semf);

  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}