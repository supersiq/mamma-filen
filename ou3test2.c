#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALIVE 'X'
#define DEAD '.'

typedef struct{
    char current;
    char next;
} cell;

void cellReset (const int rows, const int cols, cell field[rows][cols]) {
  for (int r = 0 ; r < rows ; r++) {
    for (int c = 0 ; c < cols ; c++) {
      field[r][c].current = DEAD;
    }
  }
}

void printer (const int rows, const int cols, cell field[rows][cols]) {
  for (int c = 0; c < cols; c++) {
    printf("\n" );
    for (int r = 0; r < rows; r++) {
        printf("%c ", field[c][r].current);
    }
  }
  printf("\n" );
}

void cellChanger (const int rows, const int cols, cell field[rows][cols]) {

  for (int c = 0; c < cols; c++) {
    for (int r = 0; r < rows; r++) {
      if (field[r][c].current == DEAD) {
        field[r][c].next = ALIVE;
      }
      else
      field[r][c].next = DEAD;
    }
  }
}

void cellChangerAdvanced (const int rows,
                          const int cols, cell field[rows][cols]) {
 int livingNeighbor = 0;
      for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {

          if (field[r+1][c-1].current == ALIVE) {
            livingNeighbor++;
          }
          else if (field[r+1][c].current == ALIVE) {
            livingNeighbor++;
          }
          else if (field[r+1][c+1].current == ALIVE) {
            livingNeighbor++;
          }


          printf("field[%d][%d] %d",r ,c, livingNeighbor);
        }
      }
}


void sephamore (const int rows, const int cols, cell field[rows][cols]) {
  field[2][1].current = ALIVE;
  field[2][2].current = ALIVE;
  field[2][3].current = ALIVE;
}

void swapper (const int rows, const int cols, cell field[rows][cols]) {
  for (int c = 0; c < cols; c++) {
    for (int r = 0; r < rows; r++) {
      field[r][c].current = field[r][c].next;
    }
  }
}


int main()
{

  const int rows = 5;
  const int cols = 5;
  cell field[rows][cols];

// Sets status of cell to DEAD.

  cellReset(rows, cols, field);

// This creates a sephamore.

  sephamore(rows, cols, field);

// Prints field of cells.

  printer(rows, cols, field);

// Changes status of cells.

  cellChanger(rows, cols, field);  /* cellChanger -> swapper -> printer works.*/

// Swaps out the current field.

  swapper(rows, cols, field);

// Prints field of cells.

  printer(rows, cols, field);

//  cellChangerAdvanced(rows, cols, field);/* Does not work as intended. */
                                           /* Is supposed to check neighbors. */
  return 0;
}
