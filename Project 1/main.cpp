//Project 1
// 
// Minesweep v1.0
//
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

//void rules();
void usrInput(int &, const string);

struct Board
{
    int width;                  //the width of the board
    int length;                 //the length of the board
    int mines;                  //the number of mines
};

int main()
{
    Board player;               //player is a Board structure variable
    
//get user input for width, length, and bombs
    usrInput(player.width, "Width of the board (3-16): ");
    usrInput(player.length, "Length of the board (3-16): ");
    cout << "Amount of mines: ";
    cin >> player.mines;
    
    cout << player.width << endl;
    cout << player.length << endl;
    cout << player.mines;
    
    return 0;
}

//******************************************************************************
// Definition of function usrInput
// This function uses a reference variable for the input of the user. The 
// function outputs the string text from the function call to tell the user
// the parameters that should be entered. 
//******************************************************************************
void usrInput(int& input, const string text)
{
    cout << text;
    cin >> input;
    
    while((input < 3) || (input > 16))
    {
        cout << "\nERROR. " << text;
        cin >> input;
    }
    cout << endl;
}

//******************************************************************************
//
//******************************************************************************
//void rules()
//{
//    
//}

