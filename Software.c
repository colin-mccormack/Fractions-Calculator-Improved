/*

  StructureDataBase

  Used for creating,storing, and getting
  Fractions and Equations

*/

#include <stdio.h>
#include <stdlib.h>

#include "Software.h"
#include "IO.h"

/*

  Memory allocated for structure instances

*/

static Fraction *storedFractionsArray[IO_MAX_FRACTIONS];
static Equation *storedEquationsArray[IO_MAX_FRACTIONS];


/*

  Error Handlers

*/

#define DISPLAY_MALLOC_ERROR { /*Print Error Message*/ printf("FATAL ERROR: UNABLE TO ALLOCATE MEMORY IN HEAP"); /*Garbage Collect*/ Software->Exit(); /*Quickly Exit*/ exit(-1);}

/*



  Fractions DB



*/


/*

  To track number of Fractions

*/

int StoredFractionsCount = 0;


/*

  To check if we have enough storage to store fractions

*/

static int canStoreFractions() {
    return StoredFractionsCount < IO_MAX_FRACTIONS;
}

/*

  To create a new fraction

*/

static Fraction* newFraction() {

    // Allocate in Heap
    Fraction *f = (Fraction*) malloc(sizeof(Fraction));

    // If Null, throw error
    if(!f) DISPLAY_MALLOC_ERROR

    // Store Values
    f->numerator   = 0;
    f->denomenator = 0;

    // Return Pointer
    return f;
}


/*

  To store the fraction in the array

*/

static void StoreFraction(Fraction* f) {
    storedFractionsArray[StoredFractionsCount] = f;
    StoredFractionsCount++;
}

/*

 To get a fraction by index

*/

static Fraction* getFraction(const int Index) {
    return storedFractionsArray[Index];
}

/*

  Runs Function F and on each fraction stored in the array

*/

static void forEachFraction(void(*f)(const int,Fraction *restrict)) {
    for(int i = 0; i < StoredFractionsCount; i++)
        f(i, storedFractionsArray[i]);
}



/*



  Equation DB



*/


/* 

  To track number of Equations

*/

int StoredEquationsCount = 0;

/*

  To check if there's enough space to store the equations

*/

static int canStoreEquation() {
    return StoredEquationsCount < IO_MAX_FRACTIONS;
}

/*

  To create a new equation

*/

static Equation* newEquation(){

    Equation* E = (Equation*) malloc(sizeof (Equation));
    char*     C = (char*) malloc(sizeof (char));

    if(!E || !C) {
        if(!E) free(E);
        if(!C) free(C);
        DISPLAY_MALLOC_ERROR
    }

    *C = '\n';

    E->operand1 = newFraction();
    E->operator = C;
    E->operand2 = newFraction();
    E->result   = newFraction();

    if(!E->operand1 || !E->operand2 || !E->result ) {
      return NULL;
    }


    return E;
}

/*

  To store the equation

*/

static void StoreEquation(Equation *restrict e) {
    storedEquationsArray[StoredEquationsCount] = e;
    StoredEquationsCount++;
}

/*

  To get the equation

*/

static Equation* getEquation(const int Index) {
    return storedEquationsArray[Index];
}

/*

  This is a local-yet-global temperary string storage,
  used by getEquationFormatted for storing 
  newly created string.

  It's local to this file, technically global,
  but abstracted, 

  This is will be Garbage collected upon the program
  ends.

*/

char temp[100];

/*

  Takes in the equation, and returns it's string
  representation

*/

static const char *restrict getEquationFormatted(Equation *restrict E){
    snprintf(
            temp,
            sizeof (temp),
            "%i/%i %c %i/%i = %i/%i",
             E->operand1->numerator,
             E->operand1->denomenator,
             *E->operator,
             E->operand2->numerator,
             E->operand2->denomenator,
             E->result->numerator,
             E->result->denomenator
             );

    return temp;
}

/*

  Runs Function F and on each equation stored in the array

*/

static void forEachEquation(void(*f)(const int index, Equation *restrict e)){
    for(int i = 0; i < StoredEquationsCount; i++)
        f(i,storedEquationsArray[i]);
}


/*


  Software


  Software is a structure that holds
  references to functions that take
  care of misc and tedious tasks.

  So that you can focus on the main
  program logic

*/


/*

  To track if the program can still run
  (A callent function will set this to 0 via Exit())

*/
int Running = 1;

/*

  Returns the value of Running

  Basically acts as a getter (if you are familiar with OOP)

*/

static int CanRun() {
    return Running;
}


/*

  freeFractions is used to Garbage Collect all fraction
  instances store in the heap.

  Note: 
  
  Variable attribute __attribute__((unused))
  is used to mark int Index as a variable that 
  will not be used. But it's there, compiler will
  treat this function as if int Index didnt exist.

  Ofcoure, you will ask, why not just exclude it?

  To make my life easier, I am passing reference for
  this function to forEach, which iterates over each 
  fraction stored in the memory and passes reference 
  to it.

  That function passes this function two arguments,
  int Index, Fraction *f.

  We ignore Index, and free fracton. As simple as that.

*/

static void freeFractions(__attribute__((unused)) const int Index, Fraction *restrict f){
    free(f);
}

/*

  Same as the function above, but for equations

*/

static void freeEquations(__attribute__((unused)) const int Index, Equation *restrict E) {
    free(E->operand1);
    free(E->operator);
    free(E->operand2);
    free(E->result);
}

/*

  Sets Running to false,
  Garbage Collects everything.

*/

static void Exit() {
    forEachFraction(&freeFractions);
    forEachEquation(&freeEquations);
    Running = 0;
}




/*


  Now implementing abstraction

  Note: 
  
  All functions static, meaning,
  you cannot access them even if you 
  include this file.

  Back to the point:

  We are basically creating structures
  and assigning them with references 
  to the functions.

  Then, we are creating a pointer 
  variable of the structure type,
  that points to the structure holding
  references to the function.

  The pointer variables is "externed" or 
  made visible.

  So now functions can be accessed via pointer
  variables.

  So this is how it works under the hood:

    Example:
      Fractions->new()


    Background:
      Software.h ->
        Fractions->
          FractionsFunctions->new()

  There won't be any performance impact, because:
    Fractions is a globally visible variable with
    direct reference to memory address where the structure
    with references to the functions is stored.

  So there isn't any performance impacts. As it directly
  accesses it.

  Under the hood:
    [Structure]->[Function]

*/


const static fractionsDB FractionFunctions = {
  &canStoreFractions,
  &newFraction,
  &StoreFraction,
  &getFraction,
  &forEachFraction
};

const static equationsDB EquationFunctions = {
  &canStoreEquation,
  &newEquation,
  &StoreEquation,
  &getEquation,
  &getEquationFormatted,
  &forEachEquation
};

const static software sfw = {&CanRun,&Exit};

/*

  All these will be externed by the header file.

*/

const fractionsDB *restrict Fractions = &FractionFunctions;
const equationsDB *restrict Equations = &EquationFunctions;

const software *restrict Software = &sfw;



