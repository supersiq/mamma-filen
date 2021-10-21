/*
 * Programmeringsteknik med C och Matlab
 * Fall 21
 * Assignment 3

 * File:         ou3.c
 * Description:  A simple implementation of Conway's Game of Life. Lets the user
 *               choose initial configuration. Then let them step or exit.
 *               Prints the game field in each step.
 * Author: Jonathan Broms
 * CS username: oi21jbs
 * Date: 2021-10-18
 * Limitations:  No validation of input. Is trash...
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'



/* Declaration of data structure */
typedef struct{
    char current;
    char next;
} cell;

/* Declaration of functions */
/* initField - poor variable name? */
void initField(const int rows, const int cols, cell field[rows][cols]);
void clearField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);
char getStartStateChoice(void);
/*Functions that I have made*/
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void aliveNeighbourCount (const int rows, const int cols,
                                cell field[rows][cols]);
char iterationOrExit(void);
void printField(const int rows, const int cols, cell field[rows][cols]);
void calculateField(const int rows, const int cols, cell field[rows][cols]);


/* Function:    main
 * Description: Start and run simulations, interact with the user.
 *              Lets the user choose initial structure and whether to step
 *              or exit. Writes information to the user, and the game field
 *              in each step.
 */


/******************************************************************************/
int main(void) {

                              /*
                              To-do list:
                            X * Loop this? How do I "transfer" choice
                                from menu back to main function?
                                Something something while thing != '\n'
            Is this needed?   * Make the CURRENT -> NEXT work....
                            X * Make use of ALIVE, DEAD instead of printfs.
                              * Write out field in separate function?
                              * Tidy up the random-function.
                              * Swap function for current and next?
                              * Include "Select one of the following options:
                                          (enter) Step
                                          (any) Exit"
                              */


  srand(time(NULL));
  const int rows = 20;
  const int cols = 20;
  cell field[rows][cols];

  initField(rows, cols, field);


  do {
    printField(rows, cols, field);
    calculateField(rows, cols, field);

    printf("\n");
  } while(iterationOrExit() == '\n');

    return 0;
}


/******************************************************************************/


void printField(const int rows, const int cols, cell field[rows][cols]) {

    for (int c = 0; c < cols; c++) {
      printf("\n" );
      for (int r = 0; r < rows; r++) {
        printf("%c ", field[c][r].current);
      }
    }
    printf("\n");
}



char iterationOrExit(void) {
    int ch;

    printf("Press enter to iterate new generation.\nAny other key to exit.");

    ch = getchar();

    /* Ignore following newline */ /* What does this mean? */
    if (ch != '\n') {
        getchar();
    }
    return ch;
}

void calculateField(const int rows, const int cols, cell field[rows][cols]) {

  int livingNeighbor;
  for (int c = 0; c < cols; c++) {
    for (int r = 0; r < rows; r++) {
      if (field[r][c].current == ALIVE) {
        livingNeighbor = -1; /* This resets the value for each cell check. */
                             /* -1 To negate it's own status.              */

        for(int colInGrid = -1; colInGrid < 2; colInGrid++) {
          for(int rowInGrid = -1; rowInGrid < 2; rowInGrid++) {
            if (field[r+rowInGrid][c+colInGrid].current == ALIVE) {
              if ((rowInGrid >= 0 && rowInGrid < rows)
              && ((colInGrid >= 0) && colInGrid < cols)) {
              livingNeighbor++;
              }
            }
          }
        }

        /* Debugging line. */
        printf("(%d,%d)neighbors=%d  ",r , c,  livingNeighbor);

        if (livingNeighbor <= 1) {    /* This kills the current cell, and when*/
          field[r][c].current = DEAD; /* the next one is counted it sees dead.*/
        }                             /* Causing a calculation error.         */
        else if ( livingNeighbor <= 3) {
          field[r][c].current = ALIVE;
        }
        else if ( livingNeighbor >= 4) {
          field[r][c].current = DEAD;
        }
      }
      else {
        livingNeighbor = 0;
        for(int rowInGrid = -1; rowInGrid < 2; rowInGrid++) {
          for(int colInGrid = -1; colInGrid < 2; colInGrid++) {
            if (field[r+rowInGrid][c+colInGrid].current == ALIVE) {
              livingNeighbor++;
            }
          }
        }
        if (livingNeighbor == 3) {
          field[r][c].current = ALIVE;
        }
      }
    }
  }
}


/* Function:    initField
 * Description: Loads a structure that the user selects
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols]) {
    char choice;

    clearField(rows,cols,field);

    choice=getStartStateChoice();

    switch (choice) {
        case 'g':
        case 'G':
            loadGlider(rows, cols, field);
            break;
        case 's':
        case 'S':
            loadSemaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            loadRandom(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            loadCustom(rows, cols, field);
            break;
    }
}

/* Function:    getStartStateChoice
 * Description: Lets the user choose starting state
 * Input:
 * Output:      The users choice. Should be one of the letters G,S,R or C.
 */
char getStartStateChoice(void) {
    int ch;

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    ch = getchar();

    /* Ignore following newline */ /* What does this mean? */
    if (ch != '\n') {
        getchar();
    }
    return ch;
}

/* Function:    clearField
 * Description: Initialize all the cells in the field to dead
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */
void clearField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = DEAD;
        }
    }
}

/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols]) {

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}


/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols]) {

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}


/* Function:    loadRandom
 * Description: Inserts a random structure into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        field[r][c].current = rand()% 2;     /* Maybe a bad idea to not use */
        if (field[r][c].current >= 1 ) {     /* a designated variable? */
          field[r][c].current = ALIVE;
        }
      }
    }
}


/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadCustom(const int rows, const int cols, cell field[rows][cols]) {
    int r, c;

    printf("Give custom format string: ");
    do {
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}



/* Stupid pseudocode of what is probably more than one functions. */

/* ATT: make sure it only counts inside the given field and not outside. */

//void aliveNeighbourCount (const int rows, const int cols, cell field[rows][cols]) {
//
//  int aliveNeighbor;
//
//  for (int r = 0; r < rows; r++) {
//    for (int c = 0; c < cols; c++) {
//
//      /*
//      only read in aliveNeighbor if r+1 < rows (-1?) && c+1 < cols (-1?)
//                                    r-1 > rows   (?) && c-1 > cols   (?)
//
//
//      */
//      /* aliveNeighbor = field[r][c].current ???*/
//
//      if (aliveNeighbor == (0 || 1)) {
//        field[r][c].next = DEAD;
//      }
//
//      else if (aliveNeighbor == (2 || 3)) {
//        field[r][c].next = ALIVE;
//      }
//
//      else if (aliveNeighbor >= 4 ) {
//        field[r][c].next = DEAD;
//      }
//
//      else if (aliveNeighbor == 3) {
//        field[r][c].next = ALIVE;
//      }
//    }
//  }
//}
