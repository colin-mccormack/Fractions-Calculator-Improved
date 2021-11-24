/*

  Operations

  This file is responsible for performing all types of calculations
  in our program, including Addition, Subtraction, Multiplication etc.

  How it works:

    caller function will provide getFunctionToRun() the option user has chosen,
    getFunctionToRun() will return pointer to the function based on userchoice to
    the main function. callent function will run that respective function.


  All functions follow a pattern, they return void (Nothing), and take in 0 
  arguments. To access data, they use functions from DataBase.h. To manipulate
  the data, even for that they use functions from DataBase.h

  ONLY getFunctionToRun() is visible outside of this file.

*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include "IO.h"
#include "Software.h"
#include "Operations.h"

/*

  Error Messages

*/

#define DISPLAY_FRACTION_LIMIT_REACHED_ERROR printf("Fractions Limit Reached\n");
#define DISPLAY_INVALID_OPTION_ERROR printf("No working case. Retry.\n");

/*

  Data type of our function, this is the data type
  to store the returned function used by the main function.

*/

typedef void
function ();

/*

  These are the function that perform all sorts of calculations.
  These are abstracted, and only the pointer to these are returned
  to the main function, and main function can indirectly use the pointer
  to run this function.

*/

void CreateRandomFraction();
void GetFractionFromUser();
void DisplayFractions();
void EvaluateFractions();

void AddFractions();
void SubtractFractions();
void MultiplyFractions();
void DivideFractions();

void DisplayAllEquations();

void QuitProgram();

void invalidCase();

/*

  function *getFunctionToRun(int Choice);

  This function takes in user choice, and returns
  reference to the function that completes the task
  that user wants the program to do. 


*/

function* getFunctionToRun(int Choice) {

  switch (Choice) {

    // If users wants to generat random fraction
  case OP_GENERATE_RANDOM_FRACTION:
    return &CreateRandomFraction;

    // If users wants the program to store a fraction
  case OP_GET_FRACTIONS:
    return &GetFractionFromUser;

    // If users wants to display stored fractions
  case OP_DISPLAY_FRACTIONS:
    return &DisplayFractions;

    // If user wants to display all equations stored in
  case OP_GET_EXPRESSION:
    return &EvaluateFractions;

    // If user wants to display all equations stored in
  case OP_DISPLAY_ALL_EQUATIONS:
    return &DisplayAllEquations;

    // If user wants to close the program
  case OP_QUIT_PROGRAM:
    return &QuitProgram;

    // This is an easter egg hidden, this clears the console,
    // this was added by us to see if you would suffer through this much code reading.
  case 256:
    return &ClearConsole;

    // If users gives us an invalid input.
  default:
    return &invalidCase;

  }

}

/*

    Helper functions which will be eventually used.

    static functions because we are abstracting these.

*/

/*

  static int getGCD(int numRe, int denRe)

  GCD is an acronym for Greatest Common Factor

  Using eulicd's algorithm we efficently check for the gcd.
  This algorithm swaps the location of (a,b) each time,
  reducing the first term by the remainder from division of the second term each time.

*/

static int getGCD(int numRe, int denRe) {

  if (numRe == 0) return denRe;

  /*

    Using recursion this function will call itself until it gets to a return value,
    but will never 'unfold' recursivly since we are also returning the next function call.

  */

  return getGCD(denRe % numRe, numRe);
}

/*

    Used for Simplifying Fractions

*/

static void simplifyFractions(int *numerator, int *denominator) {

  int GCD = getGCD(*numerator, *denominator);

  *numerator   = *numerator / GCD;
  *denominator = *denominator / GCD;

  if (*denominator < 0) {
    *denominator *= -1; 
    *numerator *= -1; 
  }
  
}

/*

  Used for Displaying Values in the form of Equation

  Print the fraction out in the format -> Fraction 1: 2/2 = 1/1

  Arguments in order are : 
    numerator 1,
    denomenator 1,
    numerator 2,
    denomenator 2,
    resulting numerator,
    resulting denominator.

*/

static void formatAndDisplayInEquation(int num1, int den1, int num2, int den2, int num, int den, char operator) {

  printf(
    "%i/%i %c %i/%i = %i/%i\n",
    num1, den1, operator, num2, den2, num, den
  );
}

/*

  Code for All the operation functions starts from here

*/

/*

  Option 1

  Create RandomFraction

*/

void CreateRandomFraction() {

  /*
  
    Checking if we have not reached the limit
    to add fractions.

    if we can add the fraction, then generate
    and add the fraction.

  */

  if (Fractions->canStore()) {

    /*
    
      Setting a random seed, so that everytime 
      this function is called, it generates numbers 
      randomly, since the seed is being changed evertime.

      If you didn't understand what this does,
      then read it hear:
      https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
    
    */

    srand((unsigned int) rand());

    /*
    
      Generating random numerator and Denomerator
    
    */

   int num,den = 0;

    // Generator Numerator
    num = rand() % IO_MAX_NUMERATOR;

    // Generate Denominator
    //While loop checks if denominator is zero and if so regenerate until you get a valid one
    while (!den)
      den = rand() % IO_MAX_DENOMINATOR;

    /* 

      Its boring to have only positive fractions,
      so we flip coin to decide wether to make it negetive
      or positive.
    
    */
    if (rand() % 2)
      num = -num;

    /*
  
      Storing the generated fraction in our DataBase.
  
    */

    Fraction *f = Fractions->new();
    f->numerator = num;
    f->denomenator = den;

    Fractions->Store(f);

  }

  /*
  
    If we cannot add fraction (if limit is reached),
    then tell user we cannot add the fraction.
  
  */
  else
    DISPLAY_FRACTION_LIMIT_REACHED_ERROR

}

/*

  Option 2

  Get Fraction From User

*/

void GetFractionFromUser() {


  if(!Fractions->canStore()) {  
   
    DISPLAY_FRACTION_LIMIT_REACHED_ERROR
   
    return;
  }


  /*
  
    Initialize a new Fraction


  */
  
  Fraction *fraction = Fractions->new();


  /*
    
    Prompt user to provide us with a fraction
    and store in it *fraction
    
    (This function is from IO.h)

  */

  getUserFraction(fraction);

  /*
      
    Store our *fraction in data base.
      
    (This function is from DataBase.h)

  */

  Fractions->Store(fraction);

}

/*

  Option 3

  Display Elements

*/

/*

  void displayFraction(int index, int num, int den);

*/

static void displayFraction(int index, Fraction *f) {

  int
  simplifiednum = f->numerator,
    simplifiedden = f->denomenator;

  /*
  
    Simplifying Fractions.
  
  */

  simplifyFractions( & simplifiednum, & simplifiedden);

  /*
  
    Print fraction in the format :
      Fraction #: original numerator/original denominator = reduced numerator/reduced denominator
  
  */

  printf("Fraction %i: %i/%i = %i/%i\n", index + 1, f->numerator, f->denomenator, simplifiednum, simplifiedden);

}

/*

  Display Fractions

  This function is the state of the art of Abstraction.

  This function calls DataBase_forEachValueInStoredFractions()
  from DataBase.h and passes reference of displayElements() to it,
  so that it can run that function on each fraction stored in the 
  data base in order. 

*/

void DisplayFractions() {

  // For everything stored in Fractions Array in database file array excecute displayFraction

  Fractions->forEach(&displayFraction);
}

/*

  Evaluate Expression

*/

void EvaluateFractions() {

  //Call io.c


  //Call operation

  

  if(!Equations->canStore()) {  
   
    DISPLAY_FRACTION_LIMIT_REACHED_ERROR
   
    return;
  }


  /*
  
    Initialize a new expression


  */
  
  Equation *expression = Equations->new();


  /*
    
    Prompt user to provide us with an expression
    and store in it *expression
    
    (This function is from IO.h)

  */

  GetExpression(expression);

  /*

    Calculate result

  */

  Operation(expression);

  /*
      
    Store our *expression in data base.
      
    (This function is from DataBase.h)

  */

  Equations->Store(expression);

}

/*

  Calculations

*/

void Operation(Equation * expression) {

  Fraction * f1 = expression -> operand1;
  Fraction * f2 = expression -> operand2;

  int * rn = & expression -> result -> numerator;
  int * rd = & expression -> result -> denomenator;

  char operator = *(expression->operator);

  //printf ("In operator switching on %c", operator);

  //Compute results
  switch (operator) {

  case OP_ADD:

    *rn = (f1 -> numerator * f2 -> denomenator) + (f2 -> numerator * f1 -> denomenator);
    *rd = (f1 -> denomenator * f2 -> denomenator);

    break;

  case OP_SUB:

    *rn = (f1 -> numerator * f2 -> denomenator) - (f2 -> numerator * f1 -> denomenator);
    *rd = (f1 -> denomenator * f2 -> denomenator);

    break;

  case OP_MUL:

    *rn = (f1 -> numerator) * (f2 -> numerator);
    *rd = (f1 -> denomenator) * (f2 -> denomenator);
    
    break;

  case OP_DIV:

    *rn = (f1 -> numerator) * (f2 -> denomenator);
    *rd = (f1 -> denomenator) * (f2 -> numerator);
    
    break;

  default:
    invalidCase();
    break;

  }

  simplifyFractions(rn, rd);

}


/*

  Option 8

  Display All Fractions

*/

static void displayEquation(int Index, Equation *equation) {
  printf("Equation %i : %s", Index+1, Equations->getFormatted(equation));
}


void DisplayAllEquations() {

  /*

    Display All Fractions by passing adress of our format and display function
    to a handler function in Database.c which willl run the function on all stored equations.

  */

  printf("Here are all equations stored in history:\n");

  Equations -> forEach(&displayEquation);

}

/*

  Option 9

  To Quit Program 

*/

void QuitProgram() {

  printf("\nGood bye!\n");

  /*

    This calls DataBase_SetFlagToStopProgram()
    which will set flag for Main function to 
    stop running program.

  */

  Software -> Exit();
}

/*

  Invalid Option
  
*/

void invalidCase() {

  /*

    Ask them to retry with error prompt
  
  */

  DISPLAY_INVALID_OPTION_ERROR
}