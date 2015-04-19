//
//  image.cpp
//  ImageFilters
//
//  Created by Ian MacCallum on 4/12/15.
//  Copyright (c) 2015 MacCDevTeam. All rights reserved.
//

#include "image.hpp"
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <exception>
#include <cairo/cairo.h>

using namespace std;
using namespace cv;

// Initializers
Image::Image(string path) {

    Mat tmpMatrix = imread(path, CV_LOAD_IMAGE_COLOR);
    
    //Check if image loaded successfully
    if(!tmpMatrix.data){
        exception e;
        throw e;
    } else{
        //Store image data
        this->matrix = tmpMatrix;
        this->commitMatrix = tmpMatrix;
        this->originalMatrix = tmpMatrix;
    }
}

// Setters/Getters
Mat Image::getMatrix() {
    return this->matrix;
}
void Image::setMatrix(Mat matrix) {
    this->matrix = matrix;
}
Mat Image::getCommitMatrix() {
    return this->commitMatrix;
}
void Image::setCommitMatrix(Mat matrix) {
    this->commitMatrix = matrix;
}
Mat Image::getOriginalMatrix() {
    return this->originalMatrix;
}


// Manipulations
void Image::applyBorder(int top, int bottom, int left, int right, int type) {
    cv::Mat borderedMatrix = this->getMatrix();
    cv::Scalar value = cv::Scalar(0,0,0);;
    int borderType = 0;
    
    switch (type) {
        case 0:
            
            for (int y = 0; y < borderedMatrix.rows; y++) {
                for (int x = 0; x < borderedMatrix.cols; x++) {
                    // If on
                    if ((y < top) || (y > borderedMatrix.rows - bottom) || (x < left) || (x > borderedMatrix.cols - right)) {
                        borderedMatrix.at<cv::Vec3b>(cv::Point(x,y)) = cv::Vec3b(0,0,0);
                    }
                }
            }
            this->setMatrix(borderedMatrix);
            
            break;
        case 1:
            borderType = cv::BORDER_CONSTANT;
            break;
        case 2:
            borderType = cv::BORDER_REFLECT;
            break;
        default:
            borderType = cv::BORDER_CONSTANT;
            break;
    }
    
    copyMakeBorder(this->matrix, borderedMatrix, top, bottom, left, right, borderType, value);
    setCommitMatrix(borderedMatrix);
}
void Image::createMeme(string topText, string bottomText, double fontSize) {
    cv::Mat tempMatrix = this->getMatrix();
    
    string const fontName = "Impact";
    double topFontSize = fontSize;
    double bottomFontSize = fontSize;
    
    // Create Cairo
    cairo_surface_t* surface =
    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, tempMatrix.cols, tempMatrix.rows);
    cairo_t *cairo = cairo_create(surface);
    
    // Wrap Cairo with a Mat
    Mat cairoTarget(cairo_image_surface_get_height(surface), cairo_image_surface_get_width(surface), CV_8UC4, cairo_image_surface_get_data(surface), cairo_image_surface_get_stride(surface));
    
    // Put image onto Cairo
    cvtColor(tempMatrix, cairoTarget, COLOR_BGR2BGRA);
    
    // Set font
    cairo_select_font_face (cairo, fontName.c_str(), CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    
    // Create text container
    cairo_text_extents_t topTextContainer;
    cairo_text_extents_t bottomTextContainer;
    
    // Decrease font size until it fits on screen
    do {
        cairo_set_font_size(cairo, topFontSize);
        cairo_text_extents(cairo, topText.c_str(), &topTextContainer);
        topFontSize -= 2.0;
        
    } while (topTextContainer.width >= tempMatrix.cols - 16);
    
    // Draw top text
    cairo_move_to(cairo, tempMatrix.cols/2 - topTextContainer.width/2, 16 + topTextContainer.height);
    cairo_text_path(cairo, topText.c_str());
    cairo_set_source_rgb(cairo, 255, 255, 255);
    cairo_fill_preserve (cairo);
    
    
    // Decrease font size until it fits on screen
    do {
        cairo_set_font_size(cairo, bottomFontSize);
        cairo_text_extents(cairo, bottomText.c_str(), &bottomTextContainer);
        bottomFontSize -= 2.0;
        
    } while (bottomTextContainer.width >= tempMatrix.cols - 16);
    
    // Draw bottom text
    cairo_move_to(cairo, tempMatrix.cols/2 - bottomTextContainer.width/2, tempMatrix.rows - 16);
    cairo_text_path(cairo, bottomText.c_str());
    cairo_set_source_rgb(cairo, 255, 255, 255);
    cairo_fill_preserve (cairo);
    
    
    // Strike text
    cairo_set_source_rgb (cairo, 0, 0, 0);
    cairo_set_line_width (cairo, fontSize/20);
    cairo_stroke (cairo);
    
    
    // Copy the data to the output image
    cvtColor(cairoTarget, tempMatrix, COLOR_BGRA2BGR);
    
    cairo_destroy(cairo);
    cairo_surface_destroy(surface);

    setCommitMatrix(tempMatrix);
}
void Image::presetTintColor(Color color) {
    int hue;
    
    switch (color) {
        case Red:
            hue = 0;
            break;
        case Blue:
            hue = 168;
            break;
        case Green:
            hue = 85;
            break;
        case Yellow:
            hue = 42;
            break;
        case Pink:
            hue = 214;
            break;
        case Purple:
            hue = 195;
            break;
        case Cyan:
            hue = 128;
            break;
        case Orange:
            hue = 28;
            break;
        default:
            break;
    }
    
    customTintColor(hue);
}
void Image::customTintColor(int hue) {
    // Convert BGR to HSV
    Mat hsvMatrix;
    cvtColor(matrix, hsvMatrix, CV_BGR2HSV_FULL);
    
    for (int y = 0; y < hsvMatrix.rows; y++) {
        for (int x = 0; x < hsvMatrix.cols; x++) {
            Vec3b color = hsvMatrix.at<Vec3b>(Point(x,y));
            color[0] = hue;
            hsvMatrix.at<Vec3b>(Point(x,y)) = color;
        }
    }
    
    // Convert HSV to BGR
    cvtColor(hsvMatrix, hsvMatrix, CV_HSV2BGR_FULL);

    setCommitMatrix(hsvMatrix);
}

// Color Focus
bool Image::checkColor(cv::Scalar color, int bValue, int gValue, int rValue){
    
    int rDifference = color[2] - rValue;
    int gDifference = color[1] - gValue;
    int bDifference = color[0] - bValue;
    
    int distance = sqrt(pow(rDifference, 2) + pow(gDifference, 2) + pow(bDifference, 2));
    
    int tolerance = 75;
    int maxDistance = sqrt(pow(tolerance, 2) + pow(tolerance, 2) + pow(tolerance, 2));
    
    if(distance <= maxDistance){
        // Checks to see if the distance is within the radius of max length
        return true;
    }
    return false;
}
void Image::focusColor(cv::Scalar color){
    Mat tempMatrix = this->getMatrix();

    for(int y=0; y<tempMatrix.rows;y++){
        for(int x=0; x<tempMatrix.cols;x++){
            
            Vec3b currentPixelColor = tempMatrix.at<Vec3b>(Point(x,y));
                                                                                                                                        
            if (!checkColor(color, currentPixelColor[0], currentPixelColor[1], currentPixelColor[2])) {
                
                
                int grayValue = (currentPixelColor[0] + currentPixelColor[1] + currentPixelColor[2]) / 3.0;
                tempMatrix.at<Vec3b>(Point(x,y)) = Vec3b(grayValue, grayValue, grayValue);
                
            }
        }
    }
    
    setCommitMatrix(tempMatrix);
}

// Stamp Functions
Point Image::destinationPoint(int location){
    
    int width = matrix.cols;
    int height = matrix.rows;
    int mi = min(width, height);
    
    switch(location){
        case 0:
            return Point(width/2, height/2);				//center
            break;
        case 1:
            return Point(width-(mi/5), mi/5);				//top right
            break;
        case 2:
            return Point(mi/5, mi/5);						//top left
            break;
        case 3:
            return Point(mi/5, height-(mi/5));				//bottom left
            break;
        case 4:
            return Point(width-(mi/5), height-(mi/5));		//bottom right
        default:
            return Point(width/2, height/2);
    }
    
}
Mat Image::stampEllipse(Mat mat, double angle, int center){
    
    int thickness = 2;
    int lineType = 8;
    int width = mat.cols;
    int height = mat.rows;
    int avg = (width+height)/2;
    
    ellipse(mat,                       //Mat that will be stamped
            destinationPoint(center),	//center point for stamp
            Size(avg/8, avg/32),		//dimensions of stamp
            angle,						//rotation of stamp, passed as argument
            0, 360,						//indicates full ellipse to be stamped
            Scalar(255, 0, 0),			//will be stamped in blue
            thickness,					//thickness of line
            lineType);                  //line type
    return mat;
}
Mat Image::stampFilledCircle(Mat mat, int center){
    
    int thickness = -1;
    int lineType = 8;
    int width = mat.cols;
    int size = width/64;

    circle(mat,                        //Mat that will be stamped
           destinationPoint(center),	//center point for stamp
           size,						//dimensions of stamp
           Scalar(0, 0, 255),			//color of stamp
           thickness,					//thickness of line
           lineType);					//line type
    return mat;
}
void Image::stampAtom(int location){
    Mat tempMatrix = this->getMatrix();
    
    //The four electron paths
    tempMatrix = stampEllipse(tempMatrix, 90, location);
    tempMatrix = stampEllipse(tempMatrix, 0, location);
    tempMatrix = stampEllipse(tempMatrix, 45, location);
    tempMatrix = stampEllipse(tempMatrix, -45, location);
    
    //Center nucleus
    tempMatrix = stampFilledCircle(tempMatrix, location);
    
    setCommitMatrix(tempMatrix);
    
}

// Filters
void Image::grayscale(){
    Mat tempMatrix = this->getMatrix();
    //filter applied
    cvtColor(tempMatrix, tempMatrix, CV_BGR2GRAY);
    setCommitMatrix(tempMatrix);
}
void Image::sepia(){
    Mat tempMatrix = this->getMatrix();
    Mat_<float> sepia(3, 3);		//to be used in altering pixel values
    
    sepia << .131, .534, .272		//pixel values will be multiplied by these
    ,.168, .686, .349
    ,.189, .769, .393;
    
    //filter applied
    transform(tempMatrix, tempMatrix, sepia);
    setCommitMatrix(tempMatrix);
}
void Image::blur(int a){
    
    Mat tempMatrix = this->getMatrix();
    Mat kernel;                     //kernel used for filter
    Point anchor = Point (-1, -1);	//anchor placed in center of image
    double delta = 0;				//value added to each pixel, for blurring is 0
    int ddepth = -1;				//the depth will be the same, indicated by a negative number
    int kernelSize = a;				//determirnes amount of blur input by user
    
    //kernel defined
    kernel = Mat::ones(kernelSize, kernelSize, CV_32F)/(float)(kernelSize*kernelSize);
    
    //filter applied
    filter2D(tempMatrix, tempMatrix, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
    setCommitMatrix(tempMatrix);
}
void Image::sketch(){
    Mat tempMatrix = this->getMatrix();
    Mat gradient;			//gradient to be used in Sobel (edge detection) filtering
    int scale = 1;			//no scaling is being done
    int delta = 0;			//value added to each pixel, for sketch is 0
    int ddepth = CV_16S;	//value recommended by OpenCV
    
    //image is first blurred
    GaussianBlur(tempMatrix, tempMatrix, Size(3, 3), 0, 0, BORDER_DEFAULT);
    
    //image converted to grayscale
    cvtColor(tempMatrix, tempMatrix, CV_RGB2GRAY);
    
    //Gradients generated for the two dimensions
    Mat gradient_x, gradient_y;
    Mat abs_gradient_x, abs_gradient_y;
    
    //Sobel (edge detection) applied to x
    Sobel(tempMatrix, gradient_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(gradient_x, abs_gradient_x);
    
    //Sobel (edge detection) applied to y
    Sobel(tempMatrix, gradient_y, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(gradient_y, abs_gradient_y);
    
    //Approximate total gradient to complete Sobel affect
    addWeighted(abs_gradient_x, 0.5, abs_gradient_y, 0.5, 0, tempMatrix);
    
    //invert image made by previous steps resulting in fina result
    bitwise_not(tempMatrix, tempMatrix);
    
    setCommitMatrix(tempMatrix);
}
void Image::negative(){
    Mat tempMatrix = this->getMatrix();
    //filter applied
    bitwise_not(tempMatrix, tempMatrix);
    
    setCommitMatrix(tempMatrix);
}
void Image::erosion(int b){
    Mat tempMatrix = this->getMatrix();
    int erosion_size = b; //determines scale of erosion
    
    //creates element to corrode with
    Mat element = getStructuringElement(MORPH_ELLIPSE,		//shape of errosion, MORPH_RECT and MORPH_CROSS also available
                                        Size(erosion_size, erosion_size),		//severity of erosion
                                        Point(-1, -1));							//starting point for erosion
    
    //filter applied
    erode(tempMatrix, tempMatrix, element);
    setCommitMatrix(tempMatrix);
}

// Saving, Previewing, and Reseting
void Image::writeToPath(string path) {
    imwrite(path, matrix);
}
void Image::previewImage(cv::Mat mat) {

    // Display image
    startWindowThread();
    namedWindow("ImageWindow", WINDOW_AUTOSIZE);
    imshow("ImageWindow", mat);
    
    // On key touch close image
    waitKey(0);
    cvDestroyAllWindows();
}
void Image::resetImage() {
    this->setMatrix(this->originalMatrix);
}
