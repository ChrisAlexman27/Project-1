#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>

using namespace std;

//function prototypes
void intro();
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

#endif /* HEADER_H */

