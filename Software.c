/*

    StructureDataBase

    Used for creating,storing, and getting
    Fractions and Equations

 */

#include <stdio.h>
#include <stdlib.h>

#include "Software.h"
#include "IO.h"

// Memory allocated for storing pointers to functions
static Fraction *storedFractionsArray[IO_MAX_FRACTIONS];
static Equation *storedEquationsArray[IO_MAX_FRACTIONS];

/*

  Fractions DB

*/

// To track number of Fractions
int StoredFractionsCount = 0;

// To check if we have enough storage to store fractions
static int canStoreFractions() {
    return StoredFractionsCount < IO_MAX_FRACTIONS;
}

// To create a new fraction
static Fraction* newFraction() {

    // Allocate in Heap
    Fraction *f = (Fraction*) malloc(sizeof(Fraction));

    // If Null, throw error
    if(!f) {
        return NULL;
    }

    // Store Values
    f->numerator   = 0;
    f->denomenator = 0;

    // Return Pointer
    return f;
}

// To store the fraction in the array
static void StoreFraction(Fraction* f) {
    storedFractionsArray[StoredFractionsCount] = f;
    StoredFractionsCount++;
}

// To get a fraction by index
static Fraction* getFraction(const int Index) {
    return storedFractionsArray[Index];
}

// Runs Function F and on each fraction stored in the array
static void forEachFraction(void(*f)(const int,Fraction *restrict)) {
    for(int i = 0; i < StoredFractionsCount; i++)
        f(i, storedFractionsArray[i]);
}

/*

    Equation DB

*/

// To count number of Equations
int StoredEquationsCount = 0;

int canStoreEquation() {
    return StoredEquationsCount < IO_MAX_FRACTIONS;
}

Equation* newEquation(){

    Equation* E = (Equation*) malloc(sizeof (Equation));
    char*     C = (char*) malloc(sizeof (char));


    if(!E || !C) {
        return NULL;
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

void StoreEquation(Equation *restrict e) {
    storedEquationsArray[StoredEquationsCount] = e;
    StoredEquationsCount++;
}

Equation* getEquation(const int Index) {
    return storedEquationsArray[Index];
}

char temp[100];

const char *restrict getEquationFormatted(Equation *restrict E){
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

void forEachEquation(void(*f)(const int index, Equation *restrict e)){
    for(int i = 0; i < StoredEquationsCount; i++)
        f(i,storedEquationsArray[i]);
}

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

// To track if the program can still run
// (A callent function will set this to 0)
int Running = 1;

static int CanRun() {
    return Running;
}

static void freeFractions(__attribute__((unused)) const int Index, Fraction *restrict f){
    free(f);
}

static void freeEquations(__attribute__((unused)) const int Index, Equation *restrict E) {
    free(E->operand1);
    free(E->operator);
    free(E->operand2);
    free(E->result);
}

static void Exit() {
    forEachFraction(&freeFractions);
    forEachEquation(&freeEquations);
    Running = 0;
}

// This is getting abstracted
const static software sfw = {&CanRun,&Exit};
// while this will be visible.

const fractionsDB *restrict Fractions = &FractionFunctions;
const equationsDB *restrict Equations = &EquationFunctions;

const software *restrict Software = &sfw;



