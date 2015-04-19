//
//  main.cpp
//  ImageFilters
//
//  Created by Ian MacCallum on 3/15/15.
//  Copyright (c) 2015 MacCDevTeam. All rights reserved.
//


#include "main.hpp"
#include <exception>


using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    Image *image;
    
    // Loop until user enters a valid image
    while(true) {
        string path;
        
        //Ask user to enter file path for image
        cout << "OUTPUT>> Enter a file path for png or jpg image:" << endl;
        cout << "INPUT>> ";
        cin >> path;
        
        try{
            //Initialize image object
            image = new Image(path);
        } catch(exception e) {
            cout << "ERROR>> Unable to load image." << endl;
            continue;
        }
        
        break;
    }

    // Loop to add manipulations
    while (true) {
        int n;
        
        //Help Menu
        cout << endl << "OUTPUT>> Select an option: " << endl;
        cout << "\t0) Apply Border" << endl;
        cout << "\t1) Apply Filter" << endl;
        cout << "\t2) Color Focus" << endl;
        cout << "\t3) Generate Meme" << endl;
        cout << "\t4) Add Stamp" << endl;
        cout << "\t5) Preview Current" << endl;
        cout << "\t6) Preview Original" << endl;
        cout << "\t7) Revert to Original" << endl;
        cout << "\t8) Save Image" << endl;
        cout << "\t9) Exit" << endl;
    
        cout << "INPUT>> ";
        cin >> n;
        
        // Validate input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR>> Invalid input." << endl;
            continue;
        }
        
//        0) Apply Border
//        1) Apply Filter
//        2) Color Focus
//        3) Generate Meme
//        4) Add Stamp
//        5) Preview Current
//        6) Preview Original
//        7) Revert to Original
//        8) Save Image
//        9) Exit

        
        // Handle user command
        switch (n) {
            case 0:
                applyBorderToImage(image);
                break;
            case 1:
                applyFilterToImage(image);
                break;
            case 2:
                applyColorFocusToImage(image);
                break;
            case 3:
                createMemeFromImage(image);
                break;
            case 4:
                addStampToImage(image);
                break;
            case 5:
                previewImage(image);
                break;
            case 6:
                previewOriginal(image);
                break;
            case 7:
                revertToOriginal(image);
                break;
            case 8:
                writeImage(image);
                return 0;
            case 9:
                // Break loop to kill program
                cout << "OUTPUT>> Terminating Program" << endl;
                return 0;
            default:
                cout << "ERROR>> Invalid input." << endl;
                break;
        }
    }
    
    return 0;
}