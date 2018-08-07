#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include <valarray>
using namespace std;
using namespace cv;

/*Global variables*/

/*----------------*/

/*Supported functions*/
std::string base_name(std::string const & path) {
    return path.substr(path.find_last_of("/\\") + 1);
}
Mat ROI(Mat src, int vect[]);

/*-------------------*/
int main(int argc, char** argv) {
    Mat src;
    src = imread(argv[1], IMREAD_COLOR);

    //Level of sliding through vertical and horizontal axis
    int sliding_level = 5;
    //Kernel size 
    int kernel_size = 20;
    int offset = kernel_size / 2;

    int count = 0;

    for (int y = offset; y < src.rows; y += sliding_level) {
        for (int x = offset; x < src.cols; x += sliding_level) {
            Mat region;
            int vect[] = {x - offset, y - offset, kernel_size, kernel_size};;
            
            if ((y + offset) >= src.rows) {
                vect[3] = src.rows - (y - offset); 
            } 
            if ((x + offset) >= src.cols){
                vect[2] = src.cols - (x - offset);
            }
            if ((y + sliding_level) >= src.rows) {
                vect[3] = src.rows - (y - offset);
            } 
            if ((x + sliding_level) >= src.cols){
                vect[2] = src.cols - (x - offset);
            }
            
            region = ROI(src, vect);
            Mat dst = Mat::zeros(src.cols,src.rows, CV_8UC3);
            rectangle(src, Rect(vect[0], vect[1], vect[2], vect[3]), Scalar(0,255,0), 1, LINE_8);
            imshow("SRC",src);
            waitKey(0);
            string index = to_string(count);
            string name = "./image/" + index + ".png";

            imwrite(name, region);
            count++;
        }
    }

    return 0;
}

Mat ROI(Mat src, int vect[]) {
    Mat roi;
    roi = src(Rect(vect[0], vect[1], vect[2], vect[3]));
    return roi;
}