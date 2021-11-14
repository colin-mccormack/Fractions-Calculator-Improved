/*

  Software.h


*/

#ifndef SOFTWARE
#define SOFTWARE

/*

  A simple structure to
  store fractions

  Type: Fraction

*/

typedef struct {

  // numerator
  int numerator;

  // Denomenator
  int denomenator;

} 
Fraction;

/*

  A simple structure to
  store equations

  Stores:
    operand1 : *Fraction
    operator : *char (allocated in heap), use a store before to access value.
    operand2 : *Fraction
    result   : *Fraction

  Type: Equation

*/

typedef struct {

  // Operand 1
  Fraction * restrict operand1;

  // Operator
  char *restrict operator;

  // Operand 2
  Fraction * restrict operand2;

  // Result
  Fraction * restrict result;
}
Equation;

/*

  Fraction DB

  To Fully Abstract Functions,
  all functions are stored inside Software.c

  You cannot access them because they are static functions.

  Hence, you will have to access them via this structure.

  A copy of the structure below will be created inside software.c
  and will be made visible via extern keyword when you include this
  header file.

  Hence, to access functions for operations that involve fractions,
  call Fractions.

  Example:
    Fraction* F = Fractions->new()
    

  The above examples shows how to access a function from the structure.    

  Fraction and Fractions will be made visible upon inclusion of this file.

*/

typedef struct {
  
  /*
  
    int canStore()

    Returns 1 if there is space left to store fractions.
    Returns 0 if there isnt.

    Access: Fractions->canStore()
  
  */
  
  int(*const canStore)();


  /*
  
    Fraction* new()

    Creates a copy of Fraction (See Line 20), allocates memory for it in heap,
    assigns numerator and denomenator 0, and returns reference to the structure.

    If there was an error, returns null 

    Access: Fractions->new()

  */

  Fraction*(*const new)();

  
  /*
  
    void Store(Fraction* F)

    Takes reference to the newly created strucutre,
    and stores it in the data base internally.

    Access: Fractions->Store()

  */

  void(*const Store)(Fraction * restrict f);

  
  /*
  
    Fraction* get(int Index)

    Takes in int Index, and returns the Fraction that is stored in that index.
    
    Access: Fractions->get()

  */

  Fraction*(*const get)(const int Index);


  /*
  
    void forEach(void(*f)(int index, Fraction *f))

    Takes in a address to the function f, calls function f on each
    Fraction instance stored. Passes function f the Index of the Fraction,
    and reference to the Fraction found in that index. 
    
    Access: Fractions->forEach()

  */

  void( *const forEach)(void( * f)(const int index, Fraction * restrict f));

}
fractionsDB;

/*

  Call this, Fractions, to access all
  the publicly available functions.

*/

extern
const fractionsDB * restrict Fractions;


/*

  Equations DB

  

*/

typedef struct {
  int( *
    const
      canStore
  )();

  Equation*( *
    const new
  )();

  void( *
    const
      Store
  )(Equation * restrict e);

  Equation * ( *
    const
      get
  )(const int Index);

  const char * restrict( *
    const
      getFormatted
  )(Equation * restrict e);

  void( *
    const
      forEach
  )(void( * f)(const int index, Equation * restrict e));
}
equationsDB;

extern
const equationsDB * restrict Equations;


//This is an example of using our equation create structure
// Equations->new()

//This is an example of using a variable declaration of type equationsDB, accesing the member store which can take an equation type argument and stores it in the database
// Equations->Store()

/*



*/

typedef struct {

  // Returns 1 if program can run
  int( *
    const CanRun)();

  // Exits the program
  void( *
    const Exit)();

}
software;

extern
const software * restrict Software;

// #endif

#endif