//Project 1
// 
// Minesweep v3.0
//
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
//#include <stdlib.h>

using namespace std;

struct Board
{
    int size;                   //the width and length of the board
    int mines;                  //the number of mines
};

//void rules();
void usrInput(Board&);
void setup(Board&, char [], char []);
void setMine(Board&, char []);
void fndMine(Board&, char []);
char mineCnt(Board&, char [], int);
bool checkE(Board&, int, int);
void display(Board&, char []);

int main()
{
    Board player;               //player is a Board structure variable
    
//get user input for width, length, and bombs
    usrInput(player);
    
    char grid[player.size * player.size];
    char hdnGrid[player.size * player.size];
    
    setup(player, grid, hdnGrid);
    
    setMine(player, hdnGrid);
    
    fndMine(player, hdnGrid);
    
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
        mine = rand() % (p.size * p.size);    //rand num range 0 to size*size -1
        
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
void fndMine(Board &p, char hdnGrid[])
{
    int mineTtl;     //the total number of mines found surrounding the grid spot
    int eight[8];    //the eight surrounding squares to the reference spot
    
    for(int count = 0; count < p.size*p.size; count++)
    {
        if(hdnGrid[count] != '*')
        {
            eight[0] = count - p.size - 1;
            eight[1] = count - p.size;
            eight[2] = count - p.size + 1;
            eight[3] = count - 1;
            eight[4] = count + 1;
            eight[5] = count + p.size - 1;
            eight[6] = count + p.size ;
            eight[7] = count + p.size + 1;
            
            hdnGrid[count] = mineCnt(p, hdnGrid, count);
        }
    }
}

//******************************************************************************
//
//******************************************************************************
char mineCnt(Board &p, char hdnGrid[], int count)
{
    int mines;
    
    for(int index = 0; count < 8; count++)
    {
        if( checkE(p, index, count) )
        {
            if(hdnGrid[count] == '*')
            {
                mines++;
            }
        }
    }
    
    return mines;
}

//******************************************************************************
//
//******************************************************************************
bool checkE(Board &p, int count, int positn)
{
    bool result;
    
    if(positn < p.size)
    {
        if(count == 0 || count == 1 || count == 2)
        {
            result = false;
        }
    }
    
    else if(p.size*(p.size - 1) <= positn)
    {
        if(count == 5 || count == 6 || count == 7)
        {
            result = false;
        }
    }
    
    else if(positn % p.size == 0)
    {
        if(count == 0 || count == 3 || count == 5)
        {
            result = false;
        }
    }
    
    else if((positn + 1) % p.size == 0)
    {
        if(count == 2 || count == 4 || count == 7)
        {
            result = false;
        }
    }
    else
    {
        result = true;
    }
    
    return result;
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

