//Project 1
// 
// Minesweep v2.0
//
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

struct Board
{
    int size;                   //the width and length of the board
    int mines;                  //the number of mines
};

//void rules();
void usrInput(Board&);
void setup(Board&, char grid[], char hdnGrid[]);
void setMine(Board&, char hdnGrid[]);
void display(Board&, char grid[]);

int main()
{
    Board player;               //player is a Board structure variable
    
//get user input for width, length, and bombs
    usrInput(player);
    
    char grid[player.size * player.size];
    char hdnGrid[player.size * player.size];
    
    setup(player, grid, hdnGrid);
    
    setMine(player, hdnGrid);
    
    display(player, grid);
    
    return 0;
}

//******************************************************************************
// Definition of function usrInput
// This function uses a reference variable for the input of the user. The 
// function outputs the string text from the function call to tell the user
// the parameters that should be entered. 
//******************************************************************************
void usrInput(Board &p)
{   
    int choice;
    
    cout << "The options:\n";
    cout << "1. BEGINNER -     8x8   field, 10 mines\n";
    cout << "2. INTERMEDIATE - 16x16 field, 40 mines\n";
    cout << "3. EXPERT -       24x24 field, 99 mines\n";
    cout << "Your choice: ";
    
    cin >> choice;
    
    while((choice > 3) || (choice < 1))
    {
        cout << "ERROR. Enter a valid input : ";
        cin >> choice;
    }
    
    if(choice == 1)
    {
        p.size = 8;
        p.mines = 10;
    }
    else if(choice ==2)
    {
        p.size = 16;
        p.mines = 40;
    }
    else if(choice == 3)
    {
        p.size = 24;
        p.mines = 99;
    }
}

//******************************************************************************
//
//******************************************************************************
void setup(Board &p, char grid[], char hdnGrid[])
{
    int size = p.size * p.size;
    
    for(int count = 0; count < size; count++)
    {
        grid[count] = '-';
        hdnGrid[count] = '-';
    }
}

//******************************************************************************
//
//******************************************************************************
void setMine(Board &p, char hdnGrid[])
{
    int mine;
    int mineCnt;
    
    while (mineCnt < p.mines)
    {
        mine = rand() % (p.size * p.size);
        
        if(hdnGrid[mine] != '*')
        {
            hdnGrid[mine] = '*';
            mineCnt++;
        }
    }   
}

//******************************************************************************
//
//******************************************************************************
void display(Board &p, char grid[])
{
    cout << endl << endl;
    cout << "  ";
    for(int count = 1; count <= p.size; count++)
    {
        cout << "  " << count;
        if(count < 10)
        {
            cout << " ";
        }
    }
    cout << endl;
    
    for(int count = 0; count < p.size; count++)
    {
        cout << setw(2) << count + 1 << "  ";
        
        for(int index = 0; index < p.size; index++)
        {
            cout << grid[index] << "   ";
        } 
        cout << endl;
    }
}

