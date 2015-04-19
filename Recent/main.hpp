//
//  main.h
//  ImageFilters
//
//  Created by Ian MacCallum on 4/12/15.
//  Copyright (c) 2015 MacCDevTeam. All rights reserved.
//

#ifndef ImageFilters_main_h
#define ImageFilters_main_h

#include <opencv2/opencv.hpp>
#include "image.hpp"
#include <cmath>


void applyBorderToImage(Image *image) {
    int top, bottom, left, right;
    
    std::cout << "OUTPUT>> Enter top border:" << std::endl;
    std::cout << "INPUT>> ";
    std::cin >> top;
    std::cout << "OUTPUT>> Enter bottom border:" << std::endl;
    std::cout << "INPUT>> ";
    std::cin >> bottom;
    std::cout << "OUTPUT>> Enter left border:" << std::endl;
    std::cout << "INPUT>> ";
    std::cin >> left;
    std::cout << "OUTPUT>> Enter right border:" << std::endl;
    std::cout << "INPUT>> ";
    std::cin >> right;
    
    while(true) {
        int n;
        
        std::cout << "OUTPUT>>Enter border style:" << std::endl;
        std::cout << "\t0) Internal" << std::endl;
        std::cout << "\t1) External" << std::endl;
        std::cout << "\t2) Reflective" << std::endl;

        std::cout << "INPUT>> ";
        std::cin >> n;
        
        // Validate input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR>> Invalid border style." << std::endl;
            continue;
        } else {
            if ((n == 0) || (n == 1) || (n == 2)) {
                image->applyBorder(top, bottom, left, right, n);
            } else {
                std::cout << "ERROR>> Invalid border style." << std::endl;
            }
        }
        
        break;
    }
}

void applyHueAdjustmentToImage(Image *image) {
    int n, hue, color;
    
    while(true) {
        
        std::cout << "OUTPUT>> Enter hue option:" << std::endl;
        std::cout << "\t0) Preset Tint Color" << std::endl;
        std::cout << "\t1) Custom Tint Color" << std::endl;

        std::cout << "INPUT>> ";
        std::cin >> n;
        std::cin.ignore();
        
        // Validate input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR>> Invalid input." << std::endl;
        } else {
            break;
        }
    }

    
    
    
    // Handle user command
    switch (n) {
        case 0:
            
            while(true) {
                
                std::cout << "OUTPUT>> Enter a color:" << std::endl;
                std::cout << "\t0) Red" << std::endl;
                std::cout << "\t1) Blue" << std::endl;
                std::cout << "\t2) Green" << std::endl;
                std::cout << "\t3) Yellow" << std::endl;
                std::cout << "\t4) Pink" << std::endl;
                std::cout << "\t5) Purple" << std::endl;
                std::cout << "\t6) Cyan" << std::endl;
                std::cout << "\t7) Orange" << std::endl;
                
                std::cout << "INPUT>> ";
                std::cin >> color;

                std::cin.ignore();
                
                // Validate input
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "ERROR>> Invalid color." << std::endl;
                } else {
                    if (color < 0 || color > 7) {
                        std::cout << "ERROR>> Invalid color." << std::endl;
                    } else {
                        image->presetTintColor(Color(color));
                        break;
                    }
                }
            }
            
            break;
        case 1:
            
            while(true) {
                
                std::cout << "OUTPUT>> Enter hue value (0-255): ";
                std::cin >> hue;
                
                std::cin.ignore();
                
                // Validate input
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "ERROR>> Invalid color." << std::endl;
                } else {
                    if (hue < 0 || hue > 255) {
                        std::cout << "ERROR>> Invalid color." << std::endl;
                    } else {
                        image->customTintColor(hue);
                        break;
                    }
                }
            }

            break;
        default:
            break;
    }
}

void applyFilterToImage(Image *image) {
    int n;
    int blurChoice;     //User input converted to an int
    int erodeChoice;    //User input converted to an int
    
    while(true) {
        
        //Main filter menu
        std::cout << "OUTPUT>> Select a filter to apply: " << std::endl;
        std::cout << "\t0) Hue Adjustment" << std::endl;
        std::cout << "\t1) Grayscale" << std::endl;
        std::cout << "\t2) Sepia" << std::endl;
        std::cout << "\t3) Blur" << std::endl;
        std::cout << "\t4) Sketch" << std::endl;
        std::cout << "\t5) Negative" << std::endl;
        std::cout << "\t6) Erosion" << std::endl;
        std::cout << "\t7) Go Back" << std::endl;
        
        //Get user input
        std::cout << "INPUT>> ";
        std::cin >> n;
        
        // Validate input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR>> Invalid input." << std::endl;
        } else {
            if (n < 0 || n > 7) {
                std::cout << "ERROR>> Invalid color." << std::endl;
                continue;
            } else {
                break;
            }
        }
    }
    
    while(true){
        
        switch(n){
            case 0:
                applyHueAdjustmentToImage(image);
                break;
            case 1://Grayscale
                image->grayscale();
                break;
                
            case 2://Sepia
                image->sepia();
                break;
                
            case 3://Blur
                //Asks for user input and checks if it is within range
                while (true) {
                    std::cout << "OUTPUT>> Input an integer from 1 to 10" << std::endl;
                    std::cout << "INPUT>> ";
                    std::cin >> blurChoice;
                    
                    // Validate input
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "ERROR>> Invalid input." << std::endl;
                    } else {
                        if (blurChoice < 1 || blurChoice > 10) {
                            std::cout << "ERROR>> Invalid input." << std::endl;
                            continue;
                        } else {
                            break;
                        }
                    }
                }
                
                image->blur(blurChoice);
                break;
                
            case 4://Sketch
                image->sketch();
                break;
                
            case 5://Negative
                image->negative();
                break;
                
            case 6://Erosion
                //Asks for user input and checks if it is within range
                
                while (true) {
                    std::cout << "OUTPUT>> How much erosion would you like?" << std::endl;
                    std::cout << "INPUT>> ";
                    std::cin >> erodeChoice;
                    
                    // Validate input
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "ERROR>> Invalid input." << std::endl;
                    } else {
                        if (erodeChoice < 1 || erodeChoice > 10) {
                            std::cout << "ERROR>> Invalid input." << std::endl;
                            continue;
                        } else {
                            break;
                        }
                    }
                }
                
                
                image->erosion(erodeChoice);
                break;
                
            case 7://Go Back
                break;
                
            default://Invalid input
                std::cout << "ERROR>> Invalid input." << std::endl;
                break;
        }
        break;
    }
    
}

void applyColorFocusToImage(Image *image) {
    
    
    int n = 2;
    cv::Scalar color;
    
    switch (n) {
        case 0:
            // Red
            color = cv::Scalar(32,0,255);
            break;
        case 1:
            // Blue
            color = cv::Scalar(200,120,0);
            break;
        case 2:
            // Green
            color = cv::Scalar(0,200,60);
            break;
        case 3:
            // Cyan
            color = cv::Scalar(255,255,0);
            break;
        case 4:
            // Yellow
            color = cv::Scalar(50,255,255);
            break;
        case 5:
            // Magenta
            color = cv::Scalar(255,50,255);
            break;
        case 6:
            // Orange
            color = cv::Scalar(0,130,255);
            
            break;
            
        default:
            break;
    }
    
    image->focusColor(color);
    

}

void addStampToImage(Image *image) {
    std::string stampInput;		//Stores raw user input for stamp choice
    int stampChoice;		//User input converted to an int
    std::string locationInput;	//Stores raw user input for stamp location
    int locationChoice = 0;		//User input converted to an int
    
    while(true){
        
        std::cout << "What stamp would you like?" << std::endl;
        std::cout << "\t1) Atom" << std::endl;
        std::cout << "\t2) Go Back" << std::endl;
        
        std::cout << "INPUT>> ";
        std::cin >> stampInput;
        stampChoice = atoi(stampInput.c_str());
        
        if(1 <= stampChoice && stampChoice <= 1){
            std::cout << "Where would you like the stamp?" << std::endl;
            std::cout << "\t0) Center" << std::endl;
            std::cout << "\t1) Top Right" << std::endl;
            std::cout << "\t2) Top Left" << std::endl;
            std::cout << "\t3) Bottom Left" << std::endl;
            std::cout << "\t4) Bottom Right" << std::endl;
            
            std::cout << "INPUT>> ";
            std::cin >> locationInput;
            locationChoice = atoi(locationInput.c_str());
        }
        
        switch(stampChoice){
            case 1:
                image->stampAtom(locationChoice);
                break;
            case 2:
                break;
            default:
                std::cout << "ERROR>> Invalid input" << std::endl;
                continue;
        }
        
        break;
    }
}

void createMemeFromImage(Image *image) {
    std::cin.ignore();
    std::string topText, bottomText;
    double fontSize;
    
    std::cout << "OUTPUT>> Enter top text:" << std::endl;
    std::cout << "INPUT>> ";
    std::getline(std::cin, topText);
    std::cout << "OUTPUT>> Enter bottom text:" << std::endl;
    std::cout << "INPUT>> ";
    std::getline(std::cin, bottomText);
    std::cout << "OUTPUT>> Enter font size:" << std::endl;
    std::cout << "INPUT>> ";
    std::cin >> fontSize;
    
    // Validate input
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "ERROR>> Invalid input." << std::endl;
    } else {
        if (fontSize > 500) {
            fontSize = 500;
        }
        image->createMeme(topText, bottomText, fontSize);
    }
}

void writeImage(Image *image) {
    std::string writePath;
    
    std::cout << "OUTPUT>> Enter full path:" << std::endl;
    std::cout << "INPUT>> ";
    std::cin >> writePath;
    image->writeToPath(writePath);
}

void previewImage(Image *image) {
    // Break loop to kill program
    std::cout << "OUTPUT>> Displaying image preview. Press any key to continue." << std::endl;
    
    image->previewImage(image->getMatrix());
}

void previewOriginal(Image *image) {
    // Break loop to kill program
    std::cout << "OUTPUT>> Displaying image preview. Press any key to continue." << std::endl;
    image->previewImage(image->getOriginalMatrix());
}

void revertToOriginal(Image *image) {
    std::cout << "OUTPUT>> Reverting to original image." << std::endl;
    image->setMatrix(image->getOriginalMatrix());
}



#endif
