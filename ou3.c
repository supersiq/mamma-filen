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
 * Date: 2021-10-22
 * Limitations:  No validation of input.
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
/* Following functions are added by me. */
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
char iterationOrExit(void);
void printField(const int rows, const int cols, cell field[rows][cols]);
void calculateField(const int rows, const int cols, cell field[rows][cols]);
void checkNeighbor(int *ptLivingNeighbor, int *ptC, int *ptR,
                  const int rows, const int cols, cell field[rows][cols]);
void fieldStateChange(const int rows, const int cols, cell field[rows][cols]);
void clearNextField(const int rows, const int cols, cell field[rows][cols]);
/* Function:    main
 * Description: Start and run simulations, interact with the user.
 *              Lets the user choose initial structure and whether to step
 *              or exit. Writes information to the user, and the game field
 *              in each step.
 */
int main(void) {

    srand(time(NULL));
    const int rows = 20;
    const int cols = 20;
    cell field[rows][cols];

    initField(rows, cols, field);

    do {
        printField(rows, cols, field);
        clearNextField(rows, cols, field);
        calculateField(rows, cols, field);
        fieldStateChange(rows, cols, field);
    } while(iterationOrExit() == '\n');

  return 0;
}
/* Function:    printField
 * Description: Renders a visualization of the cell state with chars 'X' and '.'
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The fun part of the whole program.
 */
void printField(const int rows, const int cols, cell field[rows][cols]) {
    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            printf("%c ", field[c][r].current);
        }
    printf("\n" );
    }
}
/* Function:    iterationOrExit
 * Description: This function asks for the procession when field is rendered.
 * Output:      A char that either continues or terminates(exits) the program.
 */
char iterationOrExit(void) {
    int ch;
    printf("Select one of the following options:\n(enter) Step\n(any) Exit\n");
    ch = getchar();
    if (ch != '\n') {
        getchar();
    }
    return ch;
}
/* Function:    calculateField
 * Description: This function traverses through every cell within the field.
 *              It's main purpose is to enforce the game rules - how new
 *              generations of cells live and die.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The next field array is updated.
 */
void calculateField(const int rows, const int cols, cell field[rows][cols]) {
    int livingNeighbor;

    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            if (field[r][c].current == ALIVE) {
                livingNeighbor = -1;         /* -1 Because cell counts itself.*/
                checkNeighbor(&livingNeighbor, &c, &r, rows, cols, field);

                if (livingNeighbor <= 1) {            /* Following rows are   */
                      field[r][c].next = DEAD;        /* based on game rules. */
                }
                else if ( livingNeighbor <= 3) {
                      field[r][c].next = ALIVE;
                }
                else if ( livingNeighbor >= 4) {
                      field[r][c].next = DEAD;
                }
            }
            else {
                livingNeighbor = 0;
                checkNeighbor(&livingNeighbor, &c, &r, rows, cols, field);

                if (livingNeighbor == 3) {
                    field[r][c].next = ALIVE;
                }
            }
        }
    }
}
/* Function:    checkNeighbor
 * Description: This function traverses through every cell within the field
 *              and counts the number of living neighbors adjacent to (r, c).
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 *              *ptC - pointer to current position in column
 *              *p - pointer to current position in row
 *              &livingNeighbor - the initial count of neighbors
 * Output:      The sum of living neighbors.
 */
void checkNeighbor(int *ptLivingNeighbor, int *ptC, int *ptR,
                  const int rows, const int cols, cell field[rows][cols]) {
    for(int colInGrid = -1; colInGrid < 2; colInGrid++) {
        for(int rowInGrid = -1; rowInGrid < 2; rowInGrid++) {
            if ((field[*ptR+rowInGrid][*ptC+colInGrid].current == ALIVE)
            && (*ptR+rowInGrid >= 0 && *ptR+rowInGrid < rows)
            && ((*ptC+colInGrid >= 0) && *ptC+colInGrid < cols)) {
                 *ptLivingNeighbor += 1;
            }
        }
    }
}
/* Funtction:   fieldStateChange
 * Description: This function "moves" the field state one step forward.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */
void fieldStateChange(const int rows, const int cols, cell field[rows][cols]) {
    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = field[r][c].next;
        }
    }
}
/* Function:    clearNextField
 * Description: This function gives a clean "next" state.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      A clean slate for the next iteration to put new values in.
 */
void clearNextField(const int rows, const int cols, cell field[rows][cols]) {
    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].next = DEAD;
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

    /* Ignore following newline */
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
      field[r][c].current = rand()% 2;
      if (field[r][c].current >= 1 ) {
        field[r][c].current = ALIVE;
      }
    }
  }
}
