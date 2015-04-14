#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/highgui/highgui.hpp>
#include <exception>
#include <string>

class Image{
	public:
		Image(){};							//Empty constructor
		Image(std::string filePath){				//Default constructor
			cv::Mat tmpMatrix = cv::imread(filePath);
			//Check if image loaded successfully
			if(!tmpMatrix.data){
				std::exception e;
				throw e;
			}
			//Store image
			else{
				matrix = tmpMatrix;
				originalMatrix = tmpMatrix;
			}
		}
		
		void preview();		//Display manipulated image
		void previewOriginal();	//Display original image
		
	private:
		cv::Mat matrix;			//Stores the current state of the image
		cv::Mat originalMatrix;		//Stores the original image for user reference
};

#endif
