/*

  IO

  IO also stands for Input/Output, as its name suggests, this library
  contains functions that allow the program to interact with user, and
  vice versa.

  This library forms an interface between user and the computer.

*/

#include <stdio.h>
#include <stdlib.h>

#include "IO.h"
#include "Software.h"
#include "Operations.h"

/*

  void showMenu(int *choice);

  This function is responsible for showing available
  options on the screen.

  It takes in an pointer to a variable local to the 
  callent function and assigns the value (or option)
  given by the user.
  
*/

void showMenu() {

  //Clearing Console of everything in it.
  //To read more about this check out : https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
  printf("\e[1;1H\e[2J");

  // Printing the options.
  printf("Options:\n");
  printf ("1. Create Random Fraction\n");
  printf ("2. Get Fraction From User\n");
  printf ("3. Display Fractions\n");
  printf ("4. Evaluate Expression\n");
  printf ("5. Display All Equations\n");
  printf ("6. Quit\n");

}

/*

  int getResponse();


  This function is responsible for prompting user to
  enter values for the fraction.

  Prompts user again and again until user enters a 
  valid fraction.

*/

int getResponse() {


  int choice;

  // Displaying Question
  printf ("\nPlease choose an option:\n>");

  // Getting Input
  scanf ("%i", &choice);
  
  // Clearing Buffer  
  fflush(stdin);

  // Returing the option.
  return choice;
}

/*

  void ClearConsole();

  This function clears the entire console.

  And displays the menu options again.

*/

void ClearConsole() {

  fflush(stdin);

  showMenu();
}


/*

  Function for validating fraction

*/


static int ValidateFraction(int numerator, int denominator) {
  return 
    numerator   > IO_MIN_NUMERATOR   && // These symbolic constatns are in IO.h
    numerator   < IO_MAX_NUMERATOR   &&
    denominator > IO_MIN_DENOMINATOR &&
    denominator < IO_MAX_DENOMINATOR ;

}

/*

  Remove spaces from user input

*/

static void removeAllSpaces (char *s) {

  char remove = ' ';
  int i = 0;
  int j = 0;

  while (s[i]) {
    if (s[i] == remove) {
      j = i;
      i++;
      while(s[i]) {
        if (s[i] != remove) {
          s[j] = s[i];
          j++;
        }
        i++;
      }
      s[j] = 0;
    }
    i++;
  }

}

/*

  Split fraction into numerator and denominator

*/

static int split(char *userInput, int *index) {
  
  int j = 0;
  char fractionPart[MAX_INPUT];

  while (userInput[*index] >= '0' && userInput[*index] <= '9') {
      //Error in this line
      //For character array declared as char * it is not letting the values be assigned
      //printf ("Assinging %c \n", fractionPart[j]);
      fractionPart[j] = userInput[*index];
      //printf ("In split loop\n");
      (*index)++;
      j++;
  }

  return atoi(fractionPart);
}


/*

  Invalid input error message
    Returns flag value to keep loop running
  
*/

static int invalidInput () {

    printf("Invalid Fraction. Please Retry. \n");
    //We know the fraction is invalid so the return
    return 0;
}

/*

  Check if the entered values for the fractions are within base parameteres
  
*/

static int NotValid(Fraction *f1, Fraction *f2) {
  
  if (
    ValidateFraction(f1->numerator, f1->denomenator) && 
    ValidateFraction(f2->numerator, f2->denomenator)) 
    return 0;
  
  
  printf("Invalid Fraction. Please Retry. \n");
  return 1;
}

/*

  Return one if input is a valid operator

*/

static int validOperator(char operator) {

  return 
    operator == OP_ADD ||
    operator == OP_SUB ||
    operator == OP_MUL ||
    operator == OP_DIV;
}

/*

  Identify fraction parts from user input

*/

static int setExpressionParts (Equation *equation, char *userInput) {

  //Initiate valid input flag
  int validInput = 1;

  Fraction *f1 = equation->operand1;
  Fraction *f2 = equation->operand2;
  char *operator = equation->operator;

  //Remove front spaces
  removeAllSpaces(userInput);

  int index = 0;

  /*

    First fraction

  */

  f1->numerator = split(userInput, &index);

  //This increment skips over the invalid character
  if (userInput[index] == '/') 
    index++;
  else 
    validInput = invalidInput();

  f1->denomenator = split(userInput, &index);

  if(!(ValidateFraction(f1->numerator,f1->denomenator)))
    validInput = invalidInput();


  /*

    Operator

  */

  *operator = userInput[index];

  if (!validOperator(*operator)) {
    validInput = invalidInput();
  }

  index++;

  /*

    Second fraction

  */

  f2->numerator = split(userInput, &index);

  //This increment skips over the invalid character
  if (userInput[index] == '/') 
    index++;
  else 
    validInput = invalidInput();

  f2->denomenator = split(userInput, &index);

  if(!(ValidateFraction(f2->numerator,f2->denomenator)))
    validInput = invalidInput();

  return validInput;

}

/*

  Get valid expression from the user

*/

Equation* GetExpression (Equation *expression) {

  //Initalize empty string
  char userInput[MAX_INPUT];
  char operator;
  
  Fraction *f1 = expression->operand1;
  Fraction *f2 = expression->operand2;


  //Initiate valid input flag
  int validInput = 1;

  //While input is invalid run loop
  do {
    
    /*
      
      Prompt user and store results
    
    */

    printf ("Please enter an expression to evaluate : ");
    //Error : Running without prompting
    //Solution : Add space before scanf and use regex code to take in spaces
    scanf (" %99[^\n]", userInput);
    
    
    /*
    
      Clear Buffer
    
    */

    fflush(stdin);

    //Remove front spaces
    removeAllSpaces(userInput);
    
  } while (! (setExpressionParts(expression, userInput)) );

  return expression;
}

/*

  Identify fraction parts from user input

*/

static int setFractionParts (Fraction *fraction, char *userInput) {

  //Initiate valid input flag
  int validInput = 1;

  //Remove front spaces
  removeAllSpaces(userInput);

  int index = 0;

  fraction->numerator = split(userInput, &index);

  //This increment skips over the invalid character
  if (userInput[index] == '/') 
    index++;
  else 
    validInput = invalidInput();

  fraction->denomenator = split(userInput, &index);

  if(!(ValidateFraction(fraction->numerator,fraction->denomenator)))
    validInput = invalidInput();

  return validInput;

}

/*

  Get fraction from user until they enter valid input

*/

void getUserFraction (Fraction *fraction) {
  
  /*

    Get a valid fraction from the user
    by prompting for valid input until valid input is found.

    If no valid input then print error and run loop again.

  */

  //Initalize empty string
  char userInput[MAX_INPUT];

  //While input is invalid run loop
  do {
    
    /*
      
      Prompt user and store results
    
    */

    printf ("Please enter a fraction : ");
    scanf (" %99[^\n]", userInput);

    /*
    
      Clear Buffer
    
    */

    fflush(stdin);

    /*

      Parse user input to remove spaces from front and end of of fraction.

    */

    /*
    
      Check if the fraction is valid.

      If valid, break out. 
      (Values are already passed to callent function, Pointers Remember!)
    
    */ 

  } while (!(setFractionParts (fraction, userInput)));

}
