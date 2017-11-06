#include "board.h"
#include "header.h"

//******************************************************************************
// Definition of function control
// This function controls the game in determining that the board is displayed
// after every turn and in checking for a potential win/loss. It achieves this
// with a do while loop, allowing it to loop until the spot searched by the user
// it not a mine and the number of mines uncovered is less that the amount of
// free spots available. It leaves when one of these are met and uses some if
// statements to determine if the user hit a bomb or uncovered all of the 
// squares on the grid.
//******************************************************************************
void control(Board &p, char grid[], char hdnGrid[])
{
    int row;                                    //user input of row
    int column;                                 //user input of column
    int positn;                                 //position of array element
    char grdSpot;                               //holds the char in hdnGrid arry
    int continu = p.size * p.size - p.mines;    //number of spots without a mine
    int holder = 0;                 //holds number of spots without a mine found
    
    do{
        display(p, grid);               //call function, displays board

        cout << "Enter row [space] column: ";
        cin >> row >> column;                       //get input for row, column

//input validation for row and column amount
        while(row > p.size || row < 1 || column > p.size || column < 1)
        {
            cout << "ERROR. Invalid input.\n";
            cout << "Enter row [space] column: ";
            cin >> row >> column;
        }

//position in the array
        positn = (p.size * (row - 1)) + (column - 1);

        if(grid[positn] == '-')             //if it is a dash ( - )
        {
            grdSpot = hdnGrid[positn];      //take the hidden grid char
            grid[positn] = grdSpot;         //put it in the regular grid spot
            
            if(grdSpot == ' ')              //if no mines around it
            {
                clear(p, grid, hdnGrid, positn, holder);   //call clear function
            }
        }
        
        if(grdSpot != '*')                  //it not a mine
        {
            holder++;                       //increment holder
        }
    
    }while(holder < continu && grdSpot != '*');     //while not mine, and
                                                    //not all spots uncovered
    if(holder == continu)       //if all spots possible uncovered
    {
        display(p, grid);                       //display grid
        cout << "\nYOU HAVE WON MINESWEEP";     //cout win message
    }
    
    if (grdSpot == '*')         //if a mine was found
    {
        for(int count = 0; count < p.size*p.size; count++)
        {
            if(hdnGrid[count] == '*')               //put all from hidden grid
            {
                grid[count] = '*';                  //into the regular grid
            }       
        }
        display(p, grid);                           //display the grid
        cout << "\n\nYOU HAVE LOST MINESWEEP";      //cout lose message
    }
}

//******************************************************************************
// Definition of function clear
// This function determines if a whole section of squares on the grid are 
// empty. If they are it opens up the section with spaces.
//******************************************************************************
void clear(Board& p, char grid[], char hdnGrid[], int positn, int &cntr)
{
    int eight[8];                   //for the 8 surrounding spots
    
    theEght(p, eight, positn);
    
    for(int count = 0; count < 8; count++)
    {
        if( checkE(p, count, positn) )          //check if outside the grid
        {
            if(grid[eight[count]] == '-')       //if its a dash ( - )
            {
//move space from hidden grid to regular grid, increment counter
                grid[eight[count]] = hdnGrid[eight[count]];
                cntr++;
                
                if(hdnGrid[eight[count]] == ' ')    //if theres a space
                {
//checks surrounding squares of the original 8 surrounding squares, recursive
                    clear(p, grid, hdnGrid, eight[count], cntr);
                }
            }
        }
    }
}