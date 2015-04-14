#include "Image.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//Displays the current manipulated image in a window,
//and waits for a keypress to close the window
//TODO BUG: Preview window becomes unresponsive
void Image::preview(){
	//Prep window
	namedWindow("Image Preview", WINDOW_AUTOSIZE);

	//Show image
	imshow("Image Preview", matrix);
	
	//Wait for a keypress to close the window
	waitKey(0);
	
	//Clear any active windows
	destroyAllWindows();
}

void Image::previewOriginal(){
	//Prep window
	namedWindow("Image Preview", WINDOW_AUTOSIZE);
	
	//Show image
	imshow("Image Preview", originalMatrix);
	
	//Wait for a keypress to close the window
	waitKey(0);
	
	//Clear any active windows
	destroyAllWindows();
}
