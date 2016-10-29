#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>


using namespace cv;
using namespace std;

int d0 = 20;
int d0_max = 100;

int gamaL = 20;
int gamaL_max = 100;

int gamaH = 20;
int gamaH_max = 100;

char TrackbarName[50];

Mat imaginaryInput, complexImage, multsp;
  Mat padded, filter, mag;
  Mat original,image, tmp,final;
  Mat_<float> realInput, zeros;
  vector<Mat> planos;
  double d;

void deslocaDFT(Mat& image ){
  Mat tmp, A, B, C, D;

  image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
  int cx = image.cols/2;
  int cy = image.rows/2;

  A = image(Rect(0, 0, cx, cy));
  B = image(Rect(cx, 0, cx, cy));
  C = image(Rect(0, cy, cx, cy));
  D = image(Rect(cx, cy, cx, cy));

  A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);
  C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
}

void homo(int, void*){
  int dft_M, dft_N;
  dft_M = getOptimalDFTSize(original.rows);
  dft_N = getOptimalDFTSize(original.cols);
  image += Scalar::all(1);
  log(image,image);
  normalize(image, image, 0, 1, CV_MINMAX);
  imshow("Original", original);
  imshow("log", image);
  copyMakeBorder(image, padded, 0,
                 dft_M - image.rows, 0,
                 dft_N - image.cols,
                 BORDER_CONSTANT, Scalar::all(0));

  zeros = Mat_<float>::zeros(padded.size());
  complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));
  filter = complexImage.clone();
  tmp = Mat(dft_M, dft_N, CV_32F);

  for(int i=0; i<dft_M; i++){
    for(int j=0; j<dft_N; j++){
      d = (i-dft_M/2)*(i-dft_M/2)+(j-dft_N/2)*(j-dft_N/2);
      tmp.at<float> (i,j) = (gamaH - gamaL)*(1 - exp(-d/(d0*d0))) + gamaL;
    }
  }
  Mat comps[]= {tmp, tmp};
  merge(comps, 2, filter);
  copyMakeBorder(image, padded, 0,
                   dft_M - image.rows, 0,
                   dft_N - image.cols,
                   BORDER_CONSTANT, Scalar::all(0));
  planos.clear();
  realInput = Mat_<float>(padded);
  planos.push_back(realInput);
  planos.push_back(zeros);
  merge(planos, complexImage);
  dft(complexImage, complexImage);
  deslocaDFT(complexImage);
  mulSpectrums(complexImage,filter,complexImage,0);
  planos.clear();
  deslocaDFT(complexImage);
  idft(complexImage, complexImage);
  planos.clear();
  split(complexImage, planos);
  imshow("antes da exp", planos[0]);
  //normalize(planos[0], planos[0], 0, 1, CV_MINMAX);
  exp(planos[0],final);
  normalize(final, final, 0, 1, CV_MINMAX);
  imshow("resultado", final);
}

int main(int argc, char** argv){
  original = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  image = Mat_<float>(original);
  final = Mat_<float>(original);
  

  sprintf( TrackbarName, "Frequência de Corte", d0_max );
  createTrackbar( TrackbarName, "resultado",
          &d0,
          d0_max,
          homo);
  homo(d0, 0 );
  
  sprintf( TrackbarName, "gamaL", gamaL_max );
  createTrackbar( TrackbarName, "resultado",
          &gamaL,
          gamaL_max,
          homo);
  homo(gamaL, 0 );

  sprintf( TrackbarName, "gamaH", gamaH_max );
  createTrackbar( TrackbarName, "resultado",
          &gamaH,
          gamaH_max,
          homo );
  homo(gamaH, 0 );
  waitKey();
  return 0;
}
