#include <iostream>
#include <opencv2/opencv.hpp>
#include <stack>

using namespace cv;
using namespace std;


void seedfill(Mat image, CvPoint p, unsigned char cor){
  stack<CvPoint> pilha;
  unsigned char cor_atual;
  CvPoint aux1,aux2,aux3,aux4,atual;

  pilha.push(p);
  cor_atual = image.at<uchar>(p.y,p.x);
  while(!pilha.empty()){
    atual = pilha.top();
    pilha.pop();
    
    if(image.at<uchar>(atual.y + 1,atual.x) == cor_atual && atual.y < image.cols - 1 ){

    aux1.x = atual.x;
    aux1.y = atual.y + 1;
    pilha.push(aux1);
    
    }
    if(image.at<uchar>(atual.y - 1,atual.x) == cor_atual && atual.y > 0){

    aux2.x = atual.x;
    aux2.y = atual.y - 1;
    pilha.push(aux2);

    
    }
    if(image.at<uchar>(atual.y,atual.x + 1) == cor_atual && atual.x < image.rows - 1 ){

    aux3.x = atual.x + 1;
    aux3.y = atual.y;
    pilha.push(aux3);

    
    }
    if(image.at<uchar>(atual.y,atual.x - 1) == cor_atual && atual.x > 0){

    aux4.x = atual.x - 1;
    aux4.y = atual.y;
    pilha.push(aux4);
    }
  image.at<uchar>(atual.y,atual.x) = cor;  
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
      seedfill(image,p,0);
    }
    if(image.at<uchar>(i,width-1) == 255)
    {
      p.x=width-1;
      p.y=i;
      seedfill(image,p,0);
    }
  }
  for(int j=0; j<width; j++) 
  {
    if(image.at<uchar>(0,j) == 255)
    {
      p.x=j;
      p.y=0;
      seedfill(image,p,0);
    }
    if(image.at<uchar>(height -1,j) == 255)
    {
      p.x=j;
      p.y=height-1;
      seedfill(image,p,0);
    }
  }

  p.x=0;
  p.y=0;
  seedfill(image,p,0);

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
       seedfill(image,p,comf);

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