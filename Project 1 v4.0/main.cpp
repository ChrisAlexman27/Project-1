//Project 1
// 
// Minesweep v4.0
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
void setup(Board&, char [], char []);
void setMine(Board&, char []);
void fndMine(Board&, char []);
char mineCnt(Board&, char [], int, int []);
bool checkE(Board&, int, int);
void theEght(Board&, int[], int);
void display(Board&, char []);
void control(Board&, char[], char[]);
void clear(Board&, char[], char[], int, int&);

int main()
{
    Board player;               //player is a Board structure variable

//get user input for width, length, and bombs
    usrInput(player);
    
    char grid[player.size*player.size];
    char hdnGrid[player.size*player.size];
    
    setup(player, grid, hdnGrid);
    
    setMine(player, hdnGrid);
    
    fndMine(player, hdnGrid);
    
    control(player, grid, hdnGrid);
    
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
    int mineCnt = 0;
    
    unsigned seed = time(0);
    srand(seed);
    
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
//  int mineTtl;     //the total number of mines found surrounding the grid spot
    int eight[8];    //the eight surrounding squares to the reference spot
    
    for(int count = 0; count < p.size*p.size; count++)
    {
        if(hdnGrid[count] != '*')
        {
            theEght(p, eight, count);
            
            hdnGrid[count] = mineCnt(p, hdnGrid, count, eight);
        }
    }
}

//******************************************************************************
//
//******************************************************************************
void theEght(Board &p, int eight[], int count)
{
    eight[0] = (count - p.size) - 1;
    eight[1] = (count - p.size);
    eight[2] = (count - p.size) + 1;
    eight[3] = (count - 1);
    eight[4] = (count + 1);
    eight[5] = (count + p.size) - 1;
    eight[6] = (count + p.size);
    eight[7] = (count + p.size) + 1;
}

//******************************************************************************
//
//******************************************************************************
char mineCnt(Board &p, char hdnGrid[], int pos, int eight[])
{
    int mines = 0;
    char value;
    
    for(int index = 0; index < p.size; index++)
    {
        if( checkE(p, index, pos) )
        {
            if(hdnGrid[eight[index]] == '*')
            {
                mines++;
            }
        }
    }
    
    if(mines == 0)
    {
        value = ' ';
    }
    else
    {
        value = static_cast <char> (mines);
    }
    
    return value;
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
    
    else if(p.size * (p.size - 1) <= positn)
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
            cout << grid[p.size*count + index] << "   ";
        } 
        cout << endl;
    }
}

//******************************************************************************
//
//******************************************************************************
void control(Board &p, char grid[], char hdnGrid[])
{
    int row;
    int column;
    int positn;
    char grdSpot;
    int continu = p.size * p.size - p.mines;
    int holder;
    int counter = 0;
    
    do{
        display(p, grid);

        cout << "Enter row [space] column: ";
        cin >> row >> column;

        while(row > p.size || row < 1 || column > p.size || column < 1)
        {
            cout << "ERROR. Invalid input.\n";
            cout << "Enter row [space] column: ";
            cin >> row >> column;
        }

    //position in the array is the 
        positn = (p.size * (row - 1)) + (column - 1);
        

        if(grid[positn] == '-')
        {
            grdSpot = hdnGrid[positn];
            grid[positn] = grdSpot;
            
            if(grdSpot == ' ')
            {
                clear(p, grid, hdnGrid, positn, counter);
            }
        }
        
        if(grdSpot != '*')
        {
            holder++;
        }
    
    }while(counter < continu && grdSpot != '*');
    
    if(counter == continu)
    {
        display(p, grid);
        cout << "\nYOU HAVE WON MINESWEEP";
    }
    
    if (grdSpot == '*')
    {
        for(int count = 0; count < p.size*p.size; count++)
        {
            if(hdnGrid[count] == '*')
            {
                grid[count] = '*';
            }
        }
        display(p, grid);
        cout << "\n\nYOU HAVE LOST MINESWEEP";
    }
    
    
}

//******************************************************************************
//
//******************************************************************************
void clear(Board& p, char grid[], char hdnGrid[], int positn, int &cntr)
{
    int eight[8];
    
    theEght(p, eight, positn);
    
    for(int count = 0; count < 8; count++)
    {
        if( checkE(p, count, positn) )
        {
            if(grid[eight[count]] == '-')
            {
                grid[eight[count]] = hdnGrid[eight[count]];
                cntr++;
                
                if(hdnGrid[eight[count]] == ' ')
                {
                    clear(p, grid, hdnGrid, eight[count], cntr);
                }
            }
        }
    }
}