//
// stamps.hpp
// stamp user interface
// 
// Created by Thomas Headley

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void stampMenu(Image* target){

	bool option = false;	//exit flag for stamps
	string stampInput;		//Stores raw user input for stamp choice
	int stampChoice;		//User input converted to an int
	string locationInput;	//Stores raw user input for stamp location
	int locationChoice;		//User input converted to an int

	do{
		option = false;

		cout << "What stamp would you like?" << endl;
		cout << "\t1) Atom" << endl;
		cout << "\t2) Go Back" << endl;

		cout << "INPUT>> ";
		cin >> stampInput;
		stampChoice = atoi(stampInput.c_str());

		if(1 <= stampChoice && stampChoice <= 1){
			cout << "Where would you like the stamp?" << endl;
			cout << "\t0) Center" << endl;
			cout << "\t1) Top Right" << endl;
			cout << "\t2) Top Left" << endl;
			cout << "\t3) Bottom Left" << endl;
			cout << "\t4) Bottom Right" << endl;

			cout << "INPUT>> ";
			cin >> locationInput;
			locationChoice = atoi(locationInput.c_str());
		}

		switch(stampChoice){
			case 1:
				target->stampAtom(locationChoice);
				break;
			case 2:
				break;
			default:
				cout << "ERROR>> Invalid input" << endl;
				option = true;
				break;
		}
	}while(option);
}
