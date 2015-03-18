//
//  main.cpp
//  ImageFilters
//


#include <iostream>
#include <string>

using namespace std;

enum Filter { Tint, Grayscale, Other };
enum Color { Red, Blue, Green };



class Image {
    
private:
    int *data[];
    
public:
    // Initializers
    Image(string path) {
        
    }
    
    Image(int *data[]) {
        
    }
    
    // Setters/Getters
    void setData(int *data[]) {
        data = data;
    }
    
    // Options
    void createMeme(string topText, string bottomText) {
        
    }
    
    void applyFilter() {
        
    }
    
    void applyBorder(int width, Color color) {
        
    }
    
    void writeToPath(string path, string name) {
        
    }
};





int main(int argc, const char * argv[]) {
    
    // Initialize image from argument
    Image *image = new Image("");
    
    
    bool b = true;
    
    do {
        int n;
        
        cout << "Enter choice: ";
        cin >> n;
        
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
                cout << "Applying Border" << endl;
                break;
            case 2:
                cout << "Applying Filter" << endl;
                break;
            case 3:
                cout << "Creating Meme" << endl;
                break;
            case 4:
                cout << "Writing Image" << endl;
                image->writeToPath("", "");
                break;
            case 5:
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

