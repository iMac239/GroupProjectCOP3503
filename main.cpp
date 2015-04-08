//
//  main.cpp
//  ImageFilters
//
//  Created by Ian MacCallum on 3/15/15.
//  Copyright (c) 2015 MacCDevTeam. All rights reserved.
//

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

enum Filter { Tint, Grayscale, Other };
enum Color { Red, Blue, Green };



class Image {
    
private:
    Mat matrix;
    
public:
    // Initializers
    Image(string path) {
        Mat matrix = imread(path, CV_LOAD_IMAGE_COLOR);
        this->matrix = matrix;
    }
    
    Image(Mat matrix) {
        this->matrix = matrix;
    }
    
    // Setters/Getters
    Mat getMatrix() {
        return this->matrix;
    }
    
    void setMatrix(Mat matrix) {
        this->matrix = matrix;
    }
    
    // Options
    void createMeme(string topText, string bottomText) {
        //        void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false )
        Mat newMatrix = matrix;
        
        putText(newMatrix, topText, cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250));
        putText(newMatrix, bottomText, cvPoint(30,150), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250));
        
        matrix = newMatrix;
        
        /// Create Windows
        namedWindow("New Image", 1);
        
        /// Show Image in Window
        imshow("New Image", matrix);
        
        /// Wait until user press some key
        waitKey();
        
    }
    
    void applyFilter() {
        
    }
    
    void applyBorder(int width, Color color) {
        
    }
    
    void writeToPath(string path) {
        imwrite(path, matrix);
    }
};





int main(int argc, const char * argv[]) {
    
    // Get input file
    string path;
    cout << "Enter File Path: ";
    cin >> path;
    
    Image *image = new Image(path);
    
    
    
    string topText, bottomText, writePath;
    
    
    bool b = true;
    
    do {
        int n;
        
        cout << "Enter choice: ";
        cin >> n;
        
        // Validate input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please choose an option between 1 and 5.\n";
            continue;
        }
        
        // Handle user command
        switch (n) {
            case 1:
                cout << "Applying Border" << endl;
                break;
            case 2:
                cout << "Applying Filter" << endl;
                break;
            case 3:
                cout << "Creating Meme" << endl;
                cout << "Enter top text: ";
                getline(cin, topText, '\n');
                cout << "Enter bottom text: ";
                getline(cin, bottomText, '\n');
                
                image->createMeme(topText, bottomText);
                break;
            case 4:
                cout << "Writing Image" << endl;
                cout << "Enter full path";
                cin >> writePath;
                image->writeToPath("");
                break;
            case 5:
                // Break loop to kill program
                cout << "Terminating Program" << endl;
                b = false;
                break;
            default:
                break;
        }
    } while (b == true);
    
    return 0;
}

