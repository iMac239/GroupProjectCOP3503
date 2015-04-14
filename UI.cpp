#include <iostream>
#include <exception>
#include "Image.hpp"

using namespace std;

int main(){
	Image img; //Image object for manipulations

	/* Initial UI */
	bool fileNotOpen = true;
	while(fileNotOpen){
		string filePath;	//Holds image file path provided by user

		//Ask user to enter file path for image
		cout << "Please enter a file path for the image to be manipulated: " << endl;
		cout << "INPUT>> ";
		cin >> filePath;
	
		try{
			//Initialize image object
			Image tmpImg(filePath);
			img = tmpImg;
			fileNotOpen = false;
		}catch(exception e){
			cout << "ERROR>> Unable to load image." << endl;
		}
	}
	
	/* Main UI */
	bool notDone = true; 	//Exit flag for program
	string input;		//Stores raw user input
	int choice;			//User input converted to an int
	while(notDone){
		//Main Menu
		cout << "OUTPUT>> Select a manipulation to continue: " << endl;
		cout << "\t1) Borders" << endl;
		cout << "\t2) Filters" << endl;
		cout << "\t3) Color focus" << endl;
		cout << "\t4) Generate meme" << endl;
		cout << "\t5) View original" << endl;
		cout << "\t6) Save image" << endl;
		cout << "\t7) Exit" << endl;
		
		//Get user input
		cout << "INPUT>> ";
		cin >> input;
		choice = atoi(input.c_str());
		
		switch(choice){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				cout << "OUTPUT>> Displaying original image preview. Press any key to continue." << endl;
				img.previewOriginal();
				break;
			case 6:
				break;
			case 7:
				notDone = false;
				break;
			default:
				cout << "ERROR>> Invalid input." << endl;
				break;
		}
		
		//Display a preview of the altered image
		if(1 <= choice && choice <= 4){
			cout << "OUTPUT>> Displaying new image preview. Press any key to continue." << endl;
			img.preview();
		}
	}
		
	return 0;
}
