#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;
  int p1[2], p2[2],flag;

  image= imread("dead.png",CV_LOAD_IMAGE_COLOR);
  if(!image.data)
    cout << "Deu ruim" << endl;


  namedWindow("janela",WINDOW_AUTOSIZE);

    cout << "O tamanho da imagem eh:" << image.size().height << "/"<< image.size().width<< endl;
  do{
    cout << "Digite a coordenada X do ponto inicial:" << endl;
    cin>> p1[0];
    cout << "Digite a coordenada Y do ponto inicial:" << endl;
    cin>> p1[1];
    cout << "Digite a coordenada X do ponto final:" << endl;
    cin>> p2[0];
    cout << "Digite a coordenada Y do ponto final:" << endl;
    cin>> p2[1];
    flag = 0;
    if(p1[0]<0 || p1[1]<0 || p2[0]<0 || p2[1]<0 || p1[0]> image.size().height || p1[1]> image.size().width || p2[0]> image.size().height || p2[1]> image.size().width){
      flag = 1;
      cout << "Coodenadas invalidas. Digite novamente:" << endl;
    }
      
  }while(flag==1);

  for(int i= p1[0];i<=p2[0];i++){
    for(int j=p1[1];j<=p2[1];j++){
      image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
    }
  }

  imshow("janela", image);
  waitKey();

  
  return 0;
}