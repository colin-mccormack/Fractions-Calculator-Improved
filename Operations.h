/*

  Operations

  This file is responsible for performing all types of calculations
  in our program, including Addition, Subtraction, Multiplication etc.

  How it works:

    callent function will provide getFunctionToRun() the option user has chosen,
    getFunctionToRun() will return pointer to the function based on userchoice to
    the callent function. Main function will run that respective function.

*/


#ifndef Operations
#define Operations 

  // Data Type of the function that will be returned
  typedef void function();

  /* 
  
    Takes an argument of int that represents user choice,
    and returns the function that will fullfill the task
    the user has requested.

  */ 
  
  function *getFunctionToRun(int Choice);
  
  Fraction *sort(Fraction operand1, Fraction operand2, char operator);

  void Operation(Equation * expression);

#endif //Operations.h

/*

  User Choices

*/

#define OP_GENERATE_RANDOM_FRACTION 1
#define OP_GET_FRACTIONS 2
#define OP_DISPLAY_FRACTIONS 3
#define OP_GET_EXPRESSION 4

#define OP_DISPLAY_ALL_EQUATIONS 5

#define OP_QUIT_PROGRAM 6

#define OP_ADD '+'
#define OP_SUB '-'
#define OP_MUL '*'
#define OP_DIV '/'
