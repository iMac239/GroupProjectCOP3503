#include "Image.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//Defualt constructor
Image::Image(string filePath){
	cv::Mat tmpMatrix = cv::imread(filePath);
	//Check if image loaded successfully
	if(!tmpMatrix.data){
		std::exception e;
		throw e;
	}
	//Store image, and extract file extension
	else{
		matrix = tmpMatrix;
		commitMatrix = tmpMatrix;
		originalMatrix = tmpMatrix;
		
		//Extract file extension
		string::size_type pos = filePath.find_last_of('.');
		fileType = filePath.substr(pos);
	}
}

//Displays the current manipulated image in a window,
//and waits for a keypress to close the window
void Image::previewCurr(){
	//Prep window
	namedWindow("Image Preview", WINDOW_AUTOSIZE);
	
	//Show image
	imshow("Image Preview", matrix);
	
	//Wait for a keypress to close the window
	waitKey(0);
	
	//Clear any active windows
	destroyAllWindows();
}

//Displays the last commited state of the image in a window,
//and waits for a keypress to close the window
void Image::preview(){
	//Prep window
	namedWindow("Image Preview", WINDOW_AUTOSIZE);

	//Show image
	imshow("Image Preview", commitMatrix);
	
	//Wait for a keypress to close the window
	waitKey(0);
	
	//Clear any active windows
	destroyAllWindows();
}

//Displays original image in a window,
//and waits for a keypress to close the window
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

//Commits manipulations made to the image, prior to saving
void Image::commit(){
	commitMatrix = matrix;
}

//Reverts current image to last commit
void Image::revert(){
	matrix = commitMatrix;
}

//Saves the last commited state of the manipulated image to the specified file path
//Returns true if saved successfully, and false otherwise
bool Image::save(string filePath){
	//File saved successfully
	if(imwrite(filePath + fileType, commitMatrix)){
		return true;
	}
	//Unable to save file
	else{
		return false;
	}
}
