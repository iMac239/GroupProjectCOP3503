//
//  main.cpp
//  ImageFilters
//
//  Created by Ian MacCallum on 3/15/15.
//  Copyright (c) 2015 MacCDevTeam. All rights reserved.
//

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <cairo/cairo.h>

using namespace std;
using namespace cv;

enum Filter { Tint, Grayscale, Other };
enum Color { Red = 0, Blue = 55, Green = 100 };

void addMemeText(Mat &targetImage, string topText, string bottomText, double fontSize) {
    
    string const fontName = "Impact";
    double topFontSize = fontSize;
    double bottomFontSize = fontSize;
    
    
    // Create Cairo
    cairo_surface_t* surface =
    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, targetImage.cols, targetImage.rows);
    cairo_t *cairo = cairo_create(surface);
    
    // Wrap Cairo with a Mat
    Mat cairoTarget(cairo_image_surface_get_height(surface), cairo_image_surface_get_width(surface), CV_8UC4, cairo_image_surface_get_data(surface), cairo_image_surface_get_stride(surface));
    
    // Put image onto Cairo
    cvtColor(targetImage, cairoTarget, COLOR_BGR2BGRA);
    
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
        
    } while (topTextContainer.width >= targetImage.cols - 16);
    
    // Draw top text
    cairo_move_to(cairo, targetImage.cols/2 - topTextContainer.width/2, 16 + topTextContainer.height);
    cairo_text_path(cairo, topText.c_str());
    cairo_set_source_rgb(cairo, 255, 255, 255);
    cairo_fill_preserve (cairo);
    
    
    // Decrease font size until it fits on screen
    do {
        cairo_set_font_size(cairo, bottomFontSize);
        cairo_text_extents(cairo, bottomText.c_str(), &bottomTextContainer);
        bottomFontSize -= 2.0;
        
    } while (bottomTextContainer.width >= targetImage.cols - 16);
    
    // Draw bottom text
    cairo_move_to(cairo, targetImage.cols/2 - bottomTextContainer.width/2, targetImage.rows - 16);
    cairo_text_path(cairo, bottomText.c_str());
    cairo_set_source_rgb(cairo, 255, 255, 255);
    cairo_fill_preserve (cairo);
    
    
    // Strike text
    cairo_set_source_rgb (cairo, 0, 0, 0);
    cairo_set_line_width (cairo, fontSize/20);
    cairo_stroke (cairo);
    
    
    // Copy the data to the output image
    cvtColor(cairoTarget, targetImage, COLOR_BGRA2BGR);
    
    cairo_destroy(cairo);
    cairo_surface_destroy(surface);
}

class Image {
    
private:
    Mat matrix;
    Mat originalMatrix;
    
    
    
public:
    // Initializers
    Image(string path) {
        Mat matrix = imread(path, CV_LOAD_IMAGE_COLOR);
        this->matrix = matrix;
        this->originalMatrix = matrix;
    }
    
    Image(Mat matrix) {
        this->matrix = matrix;
        this->originalMatrix = matrix;
    }
    
    // Setters/Getters
    Mat getMatrix() {
        return this->matrix;
    }
    
    void setMatrix(Mat matrix) {
        this->matrix = matrix;
    }
    
    // Options
    void createMeme(string topText, string bottomText, double fontSize) {
        
        addMemeText(matrix, topText, bottomText, fontSize);
    }
    
    void previewImage() {
        
        // Display image
        imshow("ImageWindow", matrix);
        
        // On key touch close image
        waitKey(0);
        cvDestroyWindow("ImageWindow");
    }
    
    void presetTintColor(Color color) {
        switch (color) {
            case Red:
                break;
            case Blue:
                break;
            case Green:
                break;
            default:
                break;
        }
    }
    
    void customTintColor(int hue) {
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
        
        // Convert HSV to HSV
        cvtColor(hsvMatrix, matrix, CV_HSV2BGR_FULL);
    }
    
    void adjustColor() {
        // RGB filter
        /*  for (int y = 0; y < matrix.rows; y++) {
         for (int x = 0; x < matrix.cols; x++) {
         Vec3b color = matrix.at<Vec3b>(Point(x,y));
         
         color[0] = 0;
         color[2] = 0;
         
         matrix.at<Vec3b>(Point(x,y)) = color;
         
         }
         }
         */
        
        
        
        
    }
    
    void applyBorder(int width, Color color) {
        //TREVOR: NOT COMPILED
        //TOP ROW/BOTTOM ROW
        /*for(int y=0; y<width;y++){
             for(int x=0; x<matrix.cols;x++){
                 Vec3b colorTop=matrix.at<Vec3b>(Point(x,y));  //Color of Top Border
                 Vec3b colorBottom=matrix.at<Vec3b>(Point(x,matrix.rows-y)); //Color of Bottom Border
                    colorTop[0]=255;                  //Sets borders to black
                    colorTop[1]=255;
                    colortTop[2]=255;
                    colorBottom[0]=255;
                    colorBottom[1]=255;
                    colortBottom[2]=255;
                    matrix.at<Vec3b>(Point(x,y))=colorTop;  //Sets Top Border
                    matrix.at<Vec3v>(Point(x,matrix.rows-y))=colorBottom; //Sets Bottom Border
             }
        }*/
        //LEFT COLUMN/ RIGHT COLUMN 
          /*for(int y=0; y<matrix.rows;y++){
             for(int x=0; x<width;x++){
                 Vec3b colorLeft=matrix.at<Vec3b>(Point(x,y));  //Color of Left Border
                 Vec3b colorRight=matrix.at<Vec3b>(Point(matrix.cols-x,y)); //Color of Right Border
                    colorLeft[0]=255;                  //Sets borders to black
                    colorLeft[1]=255;
                    colortLeft[2]=255;
                    colorRight[0]=255;
                    colorRight[1]=255;
                    colorRight[2]=255;
                    matrix.at<Vec3b>(Point(x,y))=colorLeft;  //Sets Left Border
                    matrix.at<Vec3v>(Point(matrix.cols-x,y))=colorRight; //Sets Right Border
                    }
        }*/
        
             
        
    }
    
    void writeToPath(string path) {
        imwrite(path, matrix);
    }
};



void applyFilterToImage(Image *image) {
    int n, hue, color;
    
    
    cout << "Enter 1 to  or 2 for custom hue: ";
    cin >> n;
    cin.ignore();
    
    // Validate input
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please choose an option between 1 and 2." << endl;
    }
    
    
    
    
    // Handle user command
    switch (n) {
        case 1:
            cout << "Enter a color (RED = 1, BLUE = 2, GREEN = 3): ";
            
            // Validate input
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please choose a valid color" << endl;
            } else {
                image->presetTintColor(Color(color));
            }
            
            break;
        case 2:
            cout << "Enter hue value (0-255): ";
            cin >> hue;
            
            // Validate input
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please choose a number" << endl;
            } else {
                image->customTintColor(hue);
            }
            
            
            break;
        default:
            break;
    }
}

void applyBorderToImage(Image *image) {
    cout << "Applying Border" << endl;
}

void createMemeFromImage(Image *image) {
    string topText, bottomText;
    double fontSize;
    
    
    
    cout << "Creating Meme" << endl;
    cout << "Enter top text: ";
    getline(cin, topText);
    cout << "Enter bottom text: ";
    getline(cin, bottomText);
    cout << "Enter font size: ";
    cin >> fontSize;
    
    
    // Validate input
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number for font size." << endl;
    } else {
        image->createMeme(topText, bottomText, fontSize);
    }
}

void writeImage(Image *image) {
    string writePath;
    
    cout << "Writing Image" << endl;
    cout << "Enter full path";
    cin >> writePath;
    image->writeToPath(writePath);
}

void previewImage(Image *image) {
    // Break loop to kill program
    cout << "Preview image" << endl;
    
    image->previewImage();
}




int main(int argc, const char * argv[]) {
    
    // Get input file
    string path;
    cout << "Enter File Path: ";
    cin >> path;
    cin.ignore();
    
    Image *image = new Image(path);
    
    bool b = true;
    
    do {
        
        int n;
        
        cout << "Enter choice: ";
        cin >> n;
        cin.ignore();
        
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
                applyBorderToImage(image);
                break;
            case 2:
                applyFilterToImage(image);
                break;
            case 3:
                createMemeFromImage(image);
                break;
            case 4:
                writeImage(image);
                break;
            case 5:
                previewImage(image);
                break;
            case 6:
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

