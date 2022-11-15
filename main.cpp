#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main(){
    cout<<"Welcome to the airport information and game center"<<endl;
    cout<<"Would you like to play the Runway Landing Game or just receive information on a desired runway?"<<endl;
    int validate = 0;
    string choice;
    while (validate < 1){
        cout << "If you would like to play the game press 'p' then enter, "
                "if you would like to view runway information press 'i' then enter:  " << endl;
        cin >> choice;
        if ((choice == "p") or (choice == 'i')){
            validate = 1;
        }
        else{
            cout << "Invalid input please try again... \n" << endl;
        }
    }
    if choice
};

