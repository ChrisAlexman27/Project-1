#include "board.h"
#include "header.h"

//******************************************************************************
// Definition of function display
// This function outputs the one dimensional array into the shape of an n by n
// minesweeper board. It achieves this by first outputting a top line of
// numbers which is equal to n (the width or height). It then checks if the 
// value is under 10 so it can add another space, making the dashes ( - ) be 
//able to line up with the later 2 digit numbers if there are any. The next
// for loop outputs the row numbers and the entire row itself.
//This function is also called after every move, it changes based on the move.
//******************************************************************************
void display(Board &p, char grid[])
{
    cout << endl << endl;                           //initial formatting
    cout << "  ";                                   //initial formatting
    for(int count = 1; count <= p.size; count++)    //1 to row length
    {
        cout << "  " << count;                      //space between numbers
        if(count < 10)                              //more space, only 1 digit
        {                                             //versus the 2 digits
            cout << " ";
        }
    }
    cout << endl;                                   //to start the rows
    
    for(int count = 0; count < p.size; count++)     //0 to row length - 1
    {
        cout << setw(2) << count + 1 << "  ";       //to output row number
        
        for(int index = 0; index < p.size; index++) //outputs the dashes in each
        {                                                                  //row
            cout << grid[p.size*count + index] << "   ";   //[here] for the dash
        } 
        cout << endl;
    }
}