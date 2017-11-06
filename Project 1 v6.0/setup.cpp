#include "board.h"
#include "header.h"

//******************************************************************************
// Definition of function usrInput
// This function passes the structure by reference to access the structure 
// members. It uses an int choice to get the choice of the user from one of 
// three preset options. There is input validation for the choice in the while
// loop. Based on the choice of the user, the size and number of mines are set
// to the values in the if/ else if statements.
//******************************************************************************
void usrInput(Board &p)
{   
    int choice;                         //the choice the user enters
    
    cout << "The options:\n";
    cout << "1. BEGINNER -     8x8   field, 10 mines\n";
    cout << "2. INTERMEDIATE - 16x16 field, 40 mines\n";
    cout << "3. EXPERT -       24x24 field, 99 mines\n";
    cout << "Your choice: ";
    
    cin >> choice;                      //get the choice
    
    while(choice > 3 || choice < 1)     //loop while choice is not 1,2, or 3
    {
        cout << "ERROR. Enter a valid input : ";
        cin >> choice;
    }
    
    if(choice == 1)                    //if they chose 1
    {
        p.size = 8;                    //set structure members = to these values
        p.mines = 10;
    }
    else if(choice == 2)               //if they chose 2
    {
        p.size = 16;                   //set structure members = to these values
        p.mines = 40;
    }   
    else if(choice == 3)               //if they chose 3
    {
        p.size = 24;                   //set structure members = to these values
        p.mines = 99;
    }
}

//******************************************************************************
// Definition of function setup
// This function accepts the Board array by reference along with the 2 char 
// arrays.
// This function sets up the two char arrays to have ( - ) in each element of 
// their respective arrays. 
//******************************************************************************
void setup(Board &p, char grid[], char hdnGrid[])
{
    int size = p.size * p.size;         //total size of the char arrays
    
    for(int count = 0; count < size; count++)
    {
        grid[count] = '-';              //initialize with the dash char '-'
        hdnGrid[count] = '-';           //initialize with the dash char '-'
    }
}

//******************************************************************************
// Definition of function setMine
// This function randomly creates an element number for the hidden grid and
// puts a bomb into that spot. It uses an increment operator to make sure the
// number of mines never exceeds the amount of mines selected. It also uses an
// if statement to make sure a bomb is not already there.
//******************************************************************************
void setMine(Board &p, char hdnGrid[])
{
    int mine;             //random number created, the element of the char array
    int mineCnt = 0;      //number of mines, for while loop, start at 0
    
    unsigned seed = time(0);        //get the system time
    srand(seed);                    //seed the random number generator
    
    while (mineCnt < p.mines)       //loops while current mine num less than ttl
    {
        mine = rand() % (p.size * p.size);    //rand num range 0 to size*size -1
        
        if(hdnGrid[mine] != '*')            //if its not already a bomb
        {
            hdnGrid[mine] = '*';            //put a bomb there
            mineCnt++;                      //increment number of mines
        }
    }   
}

//******************************************************************************
// Definition of function fndMine
// This function will ultimately determine how many bombs are surrounding each
// spot on the n*n grid. The int array eight holds the position of the 8 
// spots that surround a center square. The theEght function determines the 
// positions of the 8 spots. The mineCnt function is then called which in turn
// counts the number of mines, setting it equal to the center square in the
// hdnGrid array.
//******************************************************************************
void fndMine(Board &p, char hdnGrid[])
{
    int eight[8];               //for the 8 spots around the center spot
    
    for(int count = 0; count < p.size*p.size; count++)
    {
        if(hdnGrid[count] != '*')           //if center spot not a mine
        {
            theEght(p, eight, count);       //call function
            
            hdnGrid[count] = mineCnt(p, hdnGrid, count, eight);  //call function
        }
    }
}

//******************************************************************************
// Definition of function theEght
// This function determines the element location of the 8 spots surrounding a 
// center spot. Here is a visual:
//  
//    (count - size) - 1    |    (count - size)    |    (count - size) + 1  
//    ----------------------------------------------------------------------
//    (count - 1)           |    CENTER SPOT       |    (count + 1)
//    ----------------------------------------------------------------------
//    (count + size) - 1    |    (count + size)    |    (count + size) + 1
//
// This is a 3x3 grid. The center spot is the spot being looked at currently by
// the hidden grid. This logic of subtracting/adding the size and subtracting
// or adding 1 is to find their respective spots and store them in the eight
// array. The top are 0, 1, 2. The left of center is 3, right is 4. The bottom
// row is 5, 6, and 7.
// This works because the size, adding or subtracting it, lands you above or 
// below the current spot. The +/- 1 is just an adjustment.
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
// Definition of function mineCnt
// This function takes in the positions from the eight array and searches each
// of them to count the number of mines. It also uses the check function to 
// determine if the position is outside of the grid. If it is not it sees if 
// that position spot has a mine and increments the number of mines. Since the
// number of mines needs to be stored in the hdnGrid array and it is a char
// array the int has to be converted to a ' ' space or a char value.
//******************************************************************************
char mineCnt(Board &p, char hdnGrid[], int positn, int eight[])
{
    int mines = 0;              //the number of mines found
    char value;                 //the char value to put into the hdnGrid array
    
    for(int index = 0; index < p.size; index++)
    {
        if( checkE(p, index, positn) )     //call check function, if false stops
        {
            int holder = eight[index];          //holder for position in array
            if(hdnGrid[holder] == '*')          //if theres a mine there
            {
                mines++;                        //increment the mines
            }
        }
    }
    
    if(mines == 0)                              //if no mines found
    {
        value = ' ';                            //no number will be shown
    }   
    else
    {
        value = ( char ) ( ( ( int ) '0' ) + mines );   //int converted to char
    }
    
    return value;               //return either a blank space or a char number
}

//******************************************************************************
// Definition of function checkE
// This function checks the eight positions found by the eight int function and
// determines whether or not they are inside the array. If they are outside of
// the array it will return false and not check for a mine there. The boolean
// result that it return is automatically true, until proven false. It goes
// through conditions to figure out if it is outside the grid.
//******************************************************************************
bool checkE(Board &p, int count, int positn)
{
    bool result = true;                 //returns true if nothing found false
    
    if(positn < p.size)                 //checks NW, N, NE
    {
        if((count == 0) || (count == 1) || (count == 2))
        {
            result = false;
        }
    }
    
    if(p.size * (p.size - 1) <= positn) //checks SW, S, SE
    {
        if((count == 5) || (count == 6) || (count == 7))
        {
            result = false;
        }
    }
    
    if(positn % p.size == 0)            //checks NW, W, SW
    {
        if((count == 0) || (count == 3) || (count == 5))
        {
            result = false;
        }
    }
    
    if((positn + 1) % p.size == 0)      //checks NE, E, SE
    {
        if((count == 2) || (count == 4) || (count == 7))
        {
            result = false;
        }
    }
    
    if(count > 7)                       //for options 2 and 3, makes sure the
    {                                   //bounds of the array are kept, only 0-7
        result = false;
    }
    
    return result;
}