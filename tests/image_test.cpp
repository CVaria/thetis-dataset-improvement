#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
//#include "matplotlibcpp.h"

//g++ image_test.cpp `pkg-config --libs opencv`  -std=c++11 -I/usr/include/python2.7 -lpython2.7 -o image_test


using namespace cv;
using namespace std;
//namespace plt = matplotlibcpp;

int canny_lowThreshold = 0;
const int canny_max_lowThreshold = 100;
const int canny_ratio = 3;
const int canny_kernel_size = 3;
const char* canny_name = "Canny Map";

Mat image, hsvImage, cannyImage, grayImage, thresImage, adaptImage;
Mat dst, detected_edges;
Mat H,S,V; //channels for hue, saturation, value
vector<Mat> channels;
Mat cannyH;

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
char* thres_name = "Threshold Demo";
char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

int const adapt_maxValue = 255;
int const adapt_max_type = 1;
int adapt_threshold_type = 0;
int adapt_c = 0;
int adapt_blocksize = 3;
int adapt_method =0;
char* adapt_name = "Adaptive Threshold Demo";
char* adapt_trackbar_threshold = "Thres: \n 0: Binary \n 1: Binary Inverted";
char* adapt_trackbar_method ="Method: \n 0: Mean \n 1: Gaussian";
char* adapt_trackbar_c = "C";
char* adapt_trackbar_blocksize="Blocksize";

RNG rng(12345);

//------------------------------------------------------------

void findContoursCustom(int, void* )
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( cannyImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
    Mat drawing = Mat::zeros( cannyImage.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color, 2,8, hierarchy, 0 );
    }
    imshow( "Contours", drawing );
}

static void CannyThreshold(int, void*)
{
    blur( grayImage, detected_edges, Size(5,5) );
    Canny( detected_edges, detected_edges, canny_lowThreshold, canny_lowThreshold*canny_ratio, canny_kernel_size );
    dst = Scalar::all(0);
    detected_edges.copyTo(cannyImage);
    imshow( canny_name, detected_edges );
    //findContoursCustom(0,0);

}

static void ThresholdDemo( int, void* )
{
  threshold( grayImage, thresImage, threshold_value, max_BINARY_value,threshold_type );
  imshow( thres_name, thresImage );
}

static void AdaptiveThreshold( int, void* ){
  if(adapt_blocksize < 1) {adapt_blocksize=3;}
  if(adapt_blocksize % 2 != 1 ) {adapt_blocksize++;}
  //cout << adapt_blocksize;
  adaptiveThreshold(grayImage, adaptImage, adapt_maxValue, adapt_method, adapt_threshold_type, adapt_blocksize, adapt_c );
  //adaptiveThreshold(grayImage, adaptImage, adapt_maxValue,1,1, adapt_blocksize, adapt_c );
  imshow(adapt_name, adaptImage);
}

int main( int argc, char** argv )
{


    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay";
     cout << argc <<endl;
     return -1;
    }


//-------Single Image Processing--------------------------------------------------
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    cvtColor(image, hsvImage, CV_BGR2HSV); //convert image to Hue/Saturation/Value
    cvtColor( image, grayImage, COLOR_BGR2GRAY ); //Gray suitablefor Canny detector
    split(hsvImage, channels);
    
    H = channels[0]; //Seperate channels of image
    S = channels[1];
    V = channels[2];


    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

  namedWindow( canny_name, WINDOW_AUTOSIZE );
  createTrackbar( "Min Threshold:", canny_name, &canny_lowThreshold, canny_max_lowThreshold, CannyThreshold );
  CannyThreshold(0, 0);

  namedWindow( thres_name, CV_WINDOW_AUTOSIZE );
  createTrackbar( trackbar_type, thres_name, &threshold_type, max_type, ThresholdDemo );
  createTrackbar( trackbar_value, thres_name, &threshold_value, max_value, ThresholdDemo );
  ThresholdDemo( 0, 0 );

  namedWindow( adapt_name, WINDOW_AUTOSIZE );
  createTrackbar( adapt_trackbar_blocksize, adapt_name, &adapt_blocksize, adapt_maxValue, AdaptiveThreshold );
  createTrackbar( adapt_trackbar_c, adapt_name, &adapt_c, adapt_maxValue, AdaptiveThreshold );
   createTrackbar( adapt_trackbar_method, adapt_name, &adapt_method, adapt_max_type, AdaptiveThreshold );
  createTrackbar( adapt_trackbar_threshold, adapt_name, &adapt_threshold_type, adapt_max_type, AdaptiveThreshold);
  AdaptiveThreshold( 0, 0 );



    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}