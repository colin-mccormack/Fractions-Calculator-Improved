/*

  A01 Fraction Program

  Program Structure:

    - This file:
      Runs fnctions from various header files.
    
    - IO.h
      Header file containing IO functions, 
      Interface between User and Program 

    - Operations.h
      Header file containing all functions created for specific operations,
      Including Addition, Subtraction, Multiplication, and so on...
      All those functions are abstracted away.
      The only visible function visible is getFunctionToRun()

    - DataBase.h
      Contains MultiDimensional Arrays that can be used to store data.
      Syntax Sugar: Just include this header file to access these arrays instead
      of passing them by reference each time.


  @author Abdul Mannan Syed, asyed24@ocdsb.ca
  @author Collin McMcormack, cmcco3@ocdsb.ca

  @date  11/23/2021

*/

// Header files
#include "IO.h"
#include "Operations.h"
#include "Software.h"


// Entry Point of Program
int main() {
  
  /*
  
    Showing the user menu.

  */

  showMenu();

  /*
  
    WHAT IS THIS CODE??
    IS THIS EVEN C?
    REALLY? 

    Yes this is C, we just copied
    the style used in Dynamically Typed 
    Languages like Lua, Java Script, etc.

    DataBase_ProgramCanRun() is from DataBase.h, which we call A for now.
    getResponse() is from IO.h, which we call B for now.
    getFunctionToRun() is from Operations.h, which we call C for now.

    A returns true if the program can still run,
    because a function interally called makes A return false
    so that when A is called next time this loop can stop.
    
    B gets response from the user, basically user input that
    tells the user what program should do next.

    C takes the user response, and returns the address
    to the function that can execute the task.

    We take that function and directly run it.

    This process is repeated until A returns false.


  */

  while(Software->CanRun()) 
    getFunctionToRun(getResponse())();
  
  return 0;
}