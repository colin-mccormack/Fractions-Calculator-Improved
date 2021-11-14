/*

  DataBase

  This library is responsible for storing and manipulating values 

*/

#ifndef DataBase
#define DataBase


  /*

    Returns 1, if there's space for storing fractiosn in data base, 
    else returns 0.

  */

  int DataBase_canAddFraction();


  /*

    This function adds provided fraction's numerator 
    and denomerator to the data base.

  */

  void DataBase_addToStoredFractions(int numerator, int denomerator);

  /*

    This function takes in function f as an argument and runs it 
    on each and every fraction in the element.

    Parameters of function f should be as follows:
    
    - The first  parameter is the index of the fraction
    - The second parameter is the numerator of the fraction
    - The third  parameter is the denominator of the fraction

  */

  void DataBase_forEachValueInStoredFractions(void(*f)(int,int,int));


  /*

    Returns 1, if there's space for storing equations in history, 
    else returns 0.

  */

  int DataBase_canAddToHistory();


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
    char Operator);

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
    void(*f)(int num1, int den1, int num2, int den2, int rnum, int rden, 
    char Operator));


  /*

    This function returns 1 (true) if program can be ran.


    DataBase_SetFlagToStopProgram() can be called to 
    make DataBase_ProgramCanRun() return 0 (false)

  */
    
  int DataBase_ProgramCanRun();

  int DataBase_SetFlagToStopProgram();

#endif // DataBase