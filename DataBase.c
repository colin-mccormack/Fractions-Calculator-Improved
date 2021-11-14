/*

  DataBase

  This library is responsible for storing and manipulating values 

*/

#include "IO.h"

/*

  Array for storing Stractions

*/

int StoredFractions[IO_MAX_FRACTIONS][2];

/*

  For keeping track of how many values are stored
  in the StoredFractions array.

*/

unsigned int NumStoredFractions = 0;

/*

  Returns 1 (true) if fractions can be added.
  Else returns 0 (false).

  So in other words, checks if array limit is reached. 

*/

int DataBase_canAddFraction() {
  return (NumStoredFractions + 1) < IO_MAX_FRACTIONS;
}

/*

  Adds a fraction to the data base.


*/

void DataBase_addToStoredFractions(int numerator, int denomerator) {
  
  StoredFractions[NumStoredFractions][0] = numerator;
  StoredFractions[NumStoredFractions][1] = denomerator;
  NumStoredFractions++;
  
}

/*

  This function takes in function f as an argument and runs it 
  on each and every fraction in the element.

  Parameters of function f should be as follows:
  
  - The first  parameter is the index of the fraction
  - The second parameter is the numerator of the fraction
  - The third  parameter is the denominator of the fraction


*/

void DataBase_forEachValueInStoredFractions(void(*f)(int,int,int)) {

  for (int i = 0; i < NumStoredFractions; i++) {
  
    // Caching Reference to our array for speed
    int *myArray = StoredFractions[i];
    
    // Pass the values to the function and run it
    f(i,myArray[0],myArray[1]);

  }
  
}

/*

  Arrays for storing equations.

*/

int  History_Operand1[IO_MAX_FRACTIONS][2]; // Fraction 1
int  History_Operand2[IO_MAX_FRACTIONS][2]; // Fraction 2
int  History_Results [IO_MAX_FRACTIONS][2]; // Their result after operation
char History_Operator[IO_MAX_FRACTIONS];    // The operator. Can be + , - , * , /  

/*

  To keep track of number of equations

*/

unsigned int Num_History = 0;

/*

  Returns 1 (true) if equations can be added.
  Else returns 0 (false).

  So in other words, checks if array limit is reached. 

*/

int DataBase_canAddToHistory() {
  return (Num_History + 1) < IO_MAX_FRACTIONS;
}

 /*

  This function stores history .

  Requires 4 different Values.
  - Operand 1's Numerator and Denominator
  - Operand 2's Numerator and Denominator
  - Result's Numerator and Denominator
  - 
*/

void DataBase_addToHistory(
  int num1, int den1, 
  int num2, int den2, 
  int rnum, int rden, 
  char Operator) {

  int *myArray;

  myArray = History_Operand1[Num_History];
  myArray[0] = num1;
  myArray[1] = den1;

  myArray = History_Operand2[Num_History];
  myArray[0] = num2;
  myArray[1] = den2;

  myArray = History_Results[Num_History];
  myArray[0] = rnum;
  myArray[1] = rden;

  History_Operator[Num_History] = Operator;
  
  Num_History++;
}

/*

  This function takes in function f as an argument and runs it 
  on each and every fraction in the element.

  Parameters of function f should be as follows:
  (Note: P stands for Parameter)

  - P1 and P2 are Operand 1's Numerator and Denominator respectively
  - P3 and P4 are Operand 2's Numerator and Denominator respectively
  - P5 and P6 are Operand 3's Numerator and Denominator respectively
  - P7 is the operator.
*/

void DataBase_forEachValueStoredInHistory(
  void(*f)(
    int num1, int den1, 
    int num2, int den2, 
    int rnum, int rden, 
    char Operator)) {


  for (unsigned int i = 0; i < Num_History; i++) {
  
      // Caching references to arrays for performance
      int *myArray  = History_Operand1[i];
      int *myArray2 = History_Operand1[i];
      int *myArray3 = History_Results[i]; 

      //Pass the values, and run the function
    f(
      myArray [0],myArray[1],
      myArray2[0],myArray2[1],
      myArray3[0],myArray3[1],
      History_Operator[i]
      );
   
  }
}

/*

  This function returns 1 (true) if program can be ran.


  DataBase_SetFlagToStopProgram() can be called to 
  make DataBase_ProgramCanRun() return 0 (false)

*/

// This is the variable that DataBase_SetFlagToStopProgram() updates.
unsigned int DataBase_ProgramShouldRun = 1;

int DataBase_ProgramCanRun() {
  return DataBase_ProgramShouldRun;
}

void DataBase_SetFlagToStopProgram() {
  DataBase_ProgramShouldRun = 0;
}

