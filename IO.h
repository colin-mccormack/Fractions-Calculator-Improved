/*

  IO

  IO also stands for Input/Output, as its name suggests, this library
  contains functions that allow the program to interact with user, and
  vice versa.

  This library forms an interface between user and the computer

*/


#ifndef IO

#define IO

#include <stdio.h>
#include "Software.h"
  /*

    These are some of the limitations set as per the assignment
    These limitations include limitations such as the max number 
    of fractions that can be stored, Max Numberator and Denomenator 
    value, etc...


  */

#define IO_MAX_FRACTIONS 100	
#define IO_MIN_NUMERATOR -99
#define IO_MAX_NUMERATOR 99
#define IO_MIN_DENOMINATOR 0
#define IO_MAX_DENOMINATOR 99
#define OUT_OF_MEMORY_EXCEPTION {printf("OUT OF MEMORY!\n"); Software->Exit();}
#define MAX_INPUT 99
    

  /*
  
    This function is responsible for showing available
    options on the screen.
  
  */
  void showMenu();

  /*
  
    This function is responsible for prompting user to
    choose and option and input it.

    Returns the calling function the option chosen by
    the user.
  
  */


  int getResponse();


  /*
  
    This function is responsible for prompting user to
    enter values for the fraction.

    Prompts user again and again until user enters a 
    valid fraction.
  
  */

  void getUserFraction (Fraction *fraction);

  /*

    Get expression

  */

  Equation* GetExpression (Equation *expression);  

  /*
  
    Clears Console.

  */
  
  void ClearConsole();


#endif //IO.h

