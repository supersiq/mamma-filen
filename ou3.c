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
void initField(const int rows, const int cols, cell field[rows][cols]);
void clearField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);
char getStartStateChoice(void);
/*Functions that I have made*/
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void aliveNeighbourCount (const int rows, const int cols, cell field[rows][cols]);

/* Function:    main
 * Description: Start and run simulations, interact with the user.
 *              Lets the user choose initial structure and whether to step
 *              or exit. Writes information to the user, and the game field
 *              in each step.
 */

int main(void) {

                                  /*
                                  To-do list:
                                  * Loop this? How do I "transfer" choice
                                  from menu back to main function?
                                  Something something while thing != '\n'
                                  * Make the CURRENT -> NEXT work....
                                  * Make use of ALIVE, DEAD instead of printfs.
                                  * Write out field in separate function?
                                  * Tidy up the random-function.
                                  */


  srand(time(NULL));
  const int rows = 20;
  const int cols = 20;
  cell field[rows][cols];

  do {
    initField(rows, cols, field);

    for (int c = 0; c < cols; c++) {        /* This belongs in a separate  */
      printf("\n" );                        /* function "worldInit" or smt.*/
      for (int r = 0; r < rows; r++) {
          printf("%c ", field[c][r].current);
      }
    }


    printf("\n");
  } while(getStartStateChoice() != '\n');

    return 0;
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



/* Stupid pseudocode. */
/* ATT: make sure it only counts inside the given field and not outside. */
void aliveNeighbourCount (const int rows, const int cols, cell field[rows][cols]) {

  int aliveNeighbor;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
        
      /*
      only read the neighbor if r+1 < rows (-1?) && c+1 < cols (-1?)
                                r-1 > rows   (?) && c-1 > cols   (?)

      
      */
      /* aliveNeighbor = field[r][c].current ???*/

      if (aliveNeighbor == (0 || 1)) {
        field[r][c].next = DEAD;
      }

      else if (aliveNeighbor == (2 || 3)) {
        field[r][c].next = ALIVE;
      }

      else if (aliveNeighbor >= 4 ) {
        field[r][c].next = DEAD;
      }

      else if (aliveNeighbor == 3) {
        field[r][c].next = ALIVE;
      }
    }
  }
}
