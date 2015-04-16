#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/highgui/highgui.hpp>
#include <exception>
#include <string>

class Image{
	public:
		Image(){};				//Empty constructor
		Image(std::string);		//Default constructor
		
		void previewCurr();		//Display current state of image
		void preview();			//Display last accepted state of image
		void previewOriginal();		//Display original image
		void commit();			//Commits changes to the image
		void revert();			//Reverts current image to last commit
		bool save(std::string);		//Saves image to file system
		
	private:
		cv::Mat matrix;			//Stores the current manipulation of the image
		cv::Mat commitMatrix;		//Stores the last accepted state of the image
		cv::Mat originalMatrix;		//Stores the original image for user reference
		std::string fileType; 		//Stores the file type for the loaded image
};

#endif
