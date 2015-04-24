#include <iostream>
#include <exception>
#include "Image.hpp"

using namespace std;

int main(){
	//TODO change to image pointer
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
		cout << "\t5) View current image" << endl;
		cout << "\t6) View original image" << endl;
		cout << "\t7) Save image" << endl;
		cout << "\t8) Exit" << endl;
		
		//Get user input
		cout << "INPUT>> ";
		cin >> input;
		choice = atoi(input.c_str());
		
		switch(choice){
			//Borders
			case 1:
				break;
				
			//Filters
			case 2:
				break;
				
			//Color Focus
			case 3:
				break;
				
			//Generate Meme
			case 4:
				break;
				
			//View current image
			case 5:
				cout << "OUTPUT>> Displaying current image preview. Press any key to continue." << endl;
				img.preview();
				break;
				
			//View original
			case 6:
				cout << "OUTPUT>> Displaying original image preview. Press any key to continue." << endl;
				img.previewOriginal();
				break;
				
			//Save image
			case 7:
				{
					//Get file path from user
					cout << "OUTPUT>> Please enter a filepath for the saved image: " << endl;
					string newFilePath;
					cout << "INPUT>> ";
					cin >> newFilePath;
				
					//Save image to provided filepath, if valid
					while(!img.save(newFilePath)){
						cout << "ERROR>> Unable to save file. Please try again." << endl;
						cout << "OUTPUT>> Please enter a filepath for the saved image: " << endl;
						cin >> newFilePath;
					}
					
					//Confirm file save to user
					cout << "OUTPUT>> File saved successfully." << endl;
				
					break;
				}
				
			//Exit Program
			case 8:
				notDone = false;
				break;
			
			//Invalid choice
			default:
				cout << "ERROR>> Invalid input." << endl;
				break;
		}
		
		//Image has been altered. Confirmation UI
		if(1 <= choice && choice <= 4){
			//Display altered image
			cout << "OUTPUT>> Displaying new image preview. Press any key to continue." << endl;
			img.previewCurr();
			
			//Prompt user to commit changes
			cout << "OUTPUT>> Do you want to commit your changes? (y/n)" << endl;
			char c;
			cout << "INPUT>> ";
			cin >> c;
			
			if(c == 'Y' || c == 'y'){
				img.commit();
				cout << "OUPUT>> Changes commited successfully." << endl;
			}
			else{
				img.revert();
				cout << "OUTPUT>> Changes aborted." << endl;
			}
			
		}
	}
		
	return 0;
}
