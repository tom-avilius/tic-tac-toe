
#include <stdio.h>

#define User_Input 1
#define Computer_Input 2
#define User_Wins -1
#define Computer_Wins +1
#define Draw 0



void display (int grid[], int gridSize);
int evaluate (int grid[], int gridSize, int move);
int checkDraw (int grid[], int gridSize);
int freeCells (int grid[], int gridSize);



int main () {

  // the size of the grid for tic tac toe
  int gridSize = 9;
  // the grid to store the tic tac toe game
  int grid[gridSize];

  display(grid, gridSize);  
}


/**
 * @function display
 * @return void
 * @description Prints the grid after formatting it
 * according to the inputs.
 * 0 is formatted as '*' meaning no input.
 * 1 is formatted as 'O' meaning computer input 
 * 2 is formatted as 'X' meaning user input.
 *
 * @params grid
 * @type int[]
 * @description The grid where the input would be stored.
 *
 * @params gridSize
 * @type int
 * @description The size of the grid.
**/
void display (int grid[], int gridSize) {

  // displaying the matrix
  for (int i=0; i<gridSize; i++) {

    // end of row
    if (i % 3 == 0)
      printf("\n");

    if (grid[i] == Computer_Input)
      printf("\tO");
    else if (grid[i] == User_Input)
      printf("\tX");
    else
      printf("\t*");
  }
}


/**
 * @function evaluate
 * @return int 
 * @description Return the information about the game.
 * If the return value is:
 * -1 --> Then the player has won
 * +1 --> Then the computer has won
 * 0 --> The game continues
 *
 * @params grid
 * @type int[]
 * @description The grid where the input would be stored.
 *
 * @params gridSize
 * @type int
 * @description The size of the grid.
 *
 * @params move
 * @type int
 * @description Denotes the current move positions, ie, whose move it is.
 * If it is:
 * 1 --> Player's Move
 * 2 --> Computer's Move
**/
int evaluate (int grid[], int gridSize, int move) {

  // Check rows for a win
  for (int row = 0; row < 3; row++) {
      if (grid[3*row] == grid[3*row + 1] && grid[3*row + 1] == grid[3*row + 2]) {
          if (grid[3*row] == User_Input) return User_Wins;  // Player (O) wins
          else if (grid[3*row] == Computer_Input) return Computer_Wins;  // Computer (X) wins
      }
  }

  // Check columns for a win
  for (int col = 0; col < 3; col++) {
      if (grid[col] == grid[col + 3] && grid[col + 3] == grid[col + 6]) {
          if (grid[col] == User_Input) return User_Wins;  // Player (O) wins
          else if (grid[col] == Computer_Input) return Computer_Wins;  // Computer (X) wins
      }
  }

  // Check primary diagonal (top-left to bottom-right)
  if (grid[0] == grid[4] && grid[4] == grid[8]) {
      if (grid[0] == User_Input) return User_Wins;  // Player (O) wins
      else if (grid[0] == Computer_Input) return Computer_Wins;  // Computer (X) wins
  }

  // Check secondary diagonal (top-right to bottom-left)
  if (grid[2] == grid[4] && grid[4] == grid[6]) {
      if (grid[2] == User_Input) return User_Wins;  // Player (O) wins
      else if (grid[2] == Computer_Input) return Computer_Wins;  // Computer (X) wins
  }

  return 0;
}


// WARN: The function would give an incorrect output if called before
// evaluate function, because it does not check if any player has won yet.
int isDraw (int grid[], int gridSize) {

  // grid is empty, hence game has not drawn yet
  if (freeCells(grid, gridSize) != 0)
    return 0;

  // otherwise the grid is full, and the game has been drawn. 
  return 1;
}


int freeCells (int grid[], int gridSize) {

  int count = 0;

  // counting free cells
  for (int i=0; i<gridSize; i++) {

    if (grid[i] == 0)
      count += 1;
  }

  return count;
}
