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

  A copy of the structure below will be created inside software.c
  and will be made visible via extern keyword when you include this
  header file.

  Hence, to access functions for operations that involve equations,
  call Equations.

  Example:
    Equation* E = Equationss->new()
    

  The above examples shows how to access a function from the structure.    

  Equation and Equations will be made visible upon inclusion of this file.

*/

typedef struct {

  
  /*
  
    int canStore()

    Returns 1 if there is enough space to store more equations,
    else returns 0

    Access: Equationss->canStore()

  */


  int(*const canStore)();


  /*
  
    Equations* new()

    Creates a copy of Equation (See Line 46), allocates memory for it in heap,
    assigns numerator and denomenator 0, and returns reference to the structure.

    If there was an error, returns null 

    Access: Equationss->new()

  */


  Equation*( *const new)();

  /*
  
    void Store(Equation* e)

    Takes reference to the newly created strucutre,
    and stores it in the data base internally.

    Access: Equationss->Store()

  */


  void(*const Store)(Equation * restrict e);

  /*
  
    Equation* get(int Index)

    Takes in int Index, and returns the Equation that is stored in that index.
    
    Access: Fractions->get()

  */

  Equation*(*const get)(const int Index);

  /*
  
    char* getFormatted(Equation *e)

    Takes reference to the equation structure, and returns the string representation
    of it.

    Format:
      "[F1N]/[F1D] [OP] [F2N]/[F2D] = [RN]/[RD]"
    
    where:
      F1N is fraction1's numerator
      F1D is fraction1's denomenator
      OP  is the operator
      F2N is fraction2's numerator
      F2D is fraction2's denomenator
      RN  is Result's numerator
      RD  is Result's denomenator

    Access: Fractions->get()

  */

  const char *restrict(*const getFormatted)(Equation * restrict e);

  /*
  
    void forEach(void(*f)(int index, Equation *e))

    Takes in a address to the function f, calls function f on each
    Equation instance stored. Passes function f the Index of the Equation,
    and reference to the Equation found in that index. 
    
    Access: Equations->forEach()

  
  */

  void(*const forEach)(void( * f)(const int index, Equation * restrict e));
}

equationsDB;

/*

  Call this, Equations, to access all
  the publicly available functions.

*/

extern
const equationsDB * restrict Equations;


//This is an example of using our equation create structure
// Equations->new()

//This is an example of using a variable declaration of type equationsDB, accesing the member store which can take an equation type argument and stores it in the database
// Equations->Store()

/*

  software

  This struct holds reference to the functions that can be used
  to check if the program can still run, or to stop the program.

  Example:
    Software->CanRun()
  

*/

typedef struct {

  /*

    int CanRun()

    This function is called by main.c to check if the program
    can still run.

    Returns 1 if it can, else returns 0

    Access: Software->CanRun()
  
  */

  int(*const CanRun)();

  
  /*

    int Exit()

    This function can be called to make
    CanRun() return 0, or in other words,
    exit the program. 

    Also triggers the garbage collection
    process to clean up everything before
    ending.

    Access: Software->Exit()
  
  */


  void( *const Exit)();

}
software;

/*

  Call this, Software, to access all
  the publicly available functions.

*/

extern
const software * restrict Software;

/* -- End -- */

#endif