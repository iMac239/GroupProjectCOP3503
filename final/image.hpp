//
//  image.h
//  ImageFilters
//
//  Created by Ian MacCallum on 4/12/15.
//  Copyright (c) 2015 MacCDevTeam. All rights reserved.
//

#ifndef ImageFilters_image_h
#define ImageFilters_image_h

#include <opencv2/core/core.hpp>
#include <string>

// Enums
enum Filter { Tint, Grayscale, Other };
enum Color { Red, Blue, Green, Yellow, Pink, Purple, Cyan, Orange };

// Image Class
class Image {
    
private:
    cv::Mat originalMatrix;
    cv::Mat commitMatrix;
    cv::Mat workingMatrix;
    std::string fileType;
public:
    // Initializers
    Image(std::string path);
    
    // Getters/Setters
    cv::Mat getOriginalMatrix();
    cv::Mat getCommitMatrix();
    void setCommitMatrix(cv::Mat tmp);
    
    // Image Manipulations
    void createMeme(std::string topText, std::string bottomText, double fontSize);
    void presetTintColor(Color color);
    void customTintColor(int hue);
    void applyBorder(int top, int bottom, int left, int right, int type);
    bool checkColor(cv::Scalar color, int bValue, int gValue, int rValue);
    void focusColor(cv::Scalar color);
    void resize(int w, int h);
    void collage(int w, int h);
    
    // Stamp Functions
    cv::Point destinationPoint(int location);
    void stampEllipse(double angle, int center);
    void stampFilledCircle(int center);
    void stampAtom(int location);

    // Filters
    void preview();
    void previewOriginal();
    void grayscale();
    void sepia();
    void blur(int a);
    void sketch();
    void negative();
    void erosion(int b);
    
    // Image Output
    void previewOriginalImage();
    void previewCurrentImage();
    void previewCommitImage();
    void applyChanges(bool b);
    void resetImage();
    bool writeToPath(std::string path);
};


#endif
