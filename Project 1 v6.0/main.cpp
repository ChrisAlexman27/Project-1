////////////////////////////////////////////////////////////////////////////////
// Christopher Alexman                CSC 17A                       Project 1 //
//                                                                            //
//                                  MINESWEEPER                               //
// 11/5/2017                                                             v1.0 //          
////////////////////////////////////////////////////////////////////////////////
#include "board.h"
#include "header.h"

int main()
{
    Board player;               //player is a Board structure variable

//get user input for width, length, and bombs
    usrInput(player);
    
//dynamically allocate memory for the character arrays that hold the board
    char *grid = nullptr;               //to point to grid
    char *hdnGrid = nullptr;            //to point to hdnGrid, the hidden grid
    
//dynamically allocate a char array large enough to hold the size*size
    grid = new char[player.size*player.size];
    hdnGrid= new char[player.size*player.size];
    
//to set up the board, initialize char arrays with '-'
    setup(player, grid, hdnGrid);
    
//to place the mines in random spots in the hidden grid
    setMine(player, hdnGrid);
    
//to calculate for each spot on the hidden grid, how many of the 8 surrounding
//squares are mines
    fndMine(player, hdnGrid);
    
//to loop displaying the game, determine if win/loss
    control(player, grid, hdnGrid);
    
//free dynamically allocated memory for grid and hdnGrid
    delete [] grid;
    grid = nullptr;                     //make grid a null pointer
    delete [] hdnGrid;
    hdnGrid = nullptr;                  //make hdnGrid a null pointer
    
    return 0;
}