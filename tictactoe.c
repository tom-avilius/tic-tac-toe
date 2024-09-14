
#include <stdio.h>
#include <stdlib.h>

#define User_Input 1
#define Computer_Input 2
#define User_Wins -1
#define Computer_Wins 1
#define Normal_Input 0
#define Invalid_Input 1
#define Redundant_Input 2
#define NaN_Input 3



void initializeGrid (int grid[], int gridSize, int value);
void display (int grid[], int gridSize);
int evaluate (int grid[], int gridSize, int move);
int isDraw (int grid[], int gridSize);
int freeCells (int grid[], int gridSize);
int userInput (int grid[], int gridSize);
int computerInput (int grid[], int gridSize);
void displayStatus (int code);
void displayResult (int code, int grid[], int gridSize);
int minimax (int grid[], int gridSize, int move, int depth);


int main () {

  system("clear");

  int inputStatus = -111;
  int gameStatus = 0;

  // the size of the grid for tic tac toe
  int gridSize = 9;
  // the grid to store the tic tac toe game
  int grid[gridSize];

  // initializing grid
  initializeGrid(grid, gridSize, 0);

  while (gameStatus == 0) {

    inputStatus = -111;

    while (inputStatus != Normal_Input) {
      
      displayStatus(inputStatus);
      display(grid, gridSize);
      inputStatus = userInput(grid, gridSize);
      system("clear");
    }

    gameStatus = evaluate(grid, gridSize, 1);
    displayResult(gameStatus, grid, gridSize);
    // TODO: Merge isDraw function into the evaluate function.
    if (isDraw(grid, gridSize) == 1) {

      display(grid, gridSize);
      printf("\nDraw.");
      exit(0);
    }
    computerInput(grid, gridSize);
    gameStatus = evaluate(grid, gridSize, 2);
    displayResult(gameStatus, grid, gridSize);
    if (isDraw(grid, gridSize) == 1) {

      display(grid, gridSize);
      printf("\nDraw.");
      exit(0);
    }
  }
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


/**
 * @function isDraw
 * @return int
 * @description Checks whether the game is drawn or not. Evaluate funtion
 * should be called prior to calling isDraw function.
 *
 * If the return is:
 * 1 --> Game is drawn
 * 0 --> Game not drawn
 *
 * @params grid
 * @type int[]
 * @description The tic tac toe grid.
 *
 * @params gridSize
 * @type int
 * @description The tictactoe grid size.
**/
// WARN: The function would return an incorrect value if called before
// evaluate function, because it does not check if any player has won yet.
int isDraw (int grid[], int gridSize) {

  // grid is empty, hence game has not drawn yet
  if (freeCells(grid, gridSize) != 0)
    return 0;

  // otherwise the grid is full, and the game has been drawn. 
  return 1;
}


/**
 * @function freeCells
 * @return int
 * @description Returns the number of empty cells.
 *
 * @params grid
 * @type int[]
 * @description The tic tac toe grid.
 *
 * @params gridSize
 * @type int
 * @description The tictactoe grid size.
**/
int freeCells (int grid[], int gridSize) {

  int count = 0;

  // counting free cells
  for (int i=0; i<gridSize; i++) {

    if (grid[i] == 0)
      count += 1;
  }

  return count;
}


/**
 * @function input
 * @return 
 * @description Function to take input from the user.
 * Stores in the provided grid and checks for its validity.
 * Returns the status of input.
 *
 * If the return value is -
 * 0 -> Normal Input
 * 1 -> Input Exceeds or Preceeds the available grid index.
 * 2 -> The input is redundant.
 * 3 -> The input is not of type int.
 *
 * @params grid
 * @type int[]
 * @description The grid where the input would be stored.
 *
 * @params gridSize
 * @type int
 * @description The size of the grid.
**/
int userInput (int grid[], int gridSize) {

  char buffer[256];
  int input, result; 

  printf("\n\nYour Move: ");

  if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

    result = sscanf(buffer, "%d" ,&input);
    if (result != 1) 
      return NaN_Input;       // input not of type int
  }

  if (input > gridSize || input < 1)
    return Invalid_Input;     // input value exceeds or preceeds the space available in the grid.
  else if (grid[input-1] != 0)
    return Redundant_Input;     // input is redundant
   
  // provided input was valid
  grid[input-1] = 1;
  return Normal_Input;
}


/**
 * @function initializeGrid
 * @return void
 * @description Function to fill in the provided grid with
 * initial values.
 *
 * @param value
 * @type int
 * @description Value to be initialized with
 * @param grid
 * @type int[]
 * @description The grid to fill in with the initial values.
 *
 * @param gridSize
 * @type int
 * @description The size of the grid.
**/
void initializeGrid (int grid[], int gridSize, int value) {

  for (int i=0; i<gridSize; i++) {

    // fill in with value to indicate no input
    grid[i] = value;
  }
}


/**
 * @function displayStatus
 * @return void
 * @description Displays the status of the input.
 *
 * @params code
 * @type int
 * @description The input status code.
**/
void displayStatus (int code) {

  if (code == Redundant_Input)
    printf("\nThe input is redundant. Try again..\n");
  else if (code == Invalid_Input) 
    printf("\nThe input is invalid. Try again..\n");
  else if (code == NaN_Input)
    printf("\nThe input is not an integer. Try again..\n");
}


/**
 * @function displayResult
 * @return void
 * @description Displays the result of the game along with the grid,
 * one last time.
 *
 * @params code
 * @type int
 * @description The game status code.
 *
 * @params grid
 * @type int[]
 * @description The tic tac toe grid.
 *
 * @params gridSize
 * @type int
 * @description The tictactoe grid size.
**/
void displayResult (int code, int grid[], int gridSize) {

  if (code == Computer_Wins) {

    display(grid, gridSize);
    printf("\n\nThe Computer Wins!");
    exit(0);
  } else if (code == User_Wins) {

    printf("\n\nThe User Wins!");
    exit(0);
  }
}


/**
 * @function minimax
 * @return int
 * @description Implementation of the minimax algorithm to decide the most 
 * optimal solution for the AI.
 *
 * @params move
 * @type int
 * @description Denotes whose move it is.
 *
 * @params depth
 * @type int
 * @description Denotes the depth at which the minimax algorithm
 * has reached.
 *
 * @params grid
 * @type int[]
 * @description The tic tac toe grid.
 *
 * @params gridSize
 * @type int
 * @description The tictactoe grid size.
**/
int minimax (int grid[], int gridSize, int move, int depth) {

  move = (move%2 == 0) ? Computer_Input : User_Input;

  int score = evaluate(grid, gridSize, move);

  if (score == Computer_Wins) {

    return 10 - depth;
  } else if (score == User_Wins) {

    return depth - 10;
  } else if (isDraw(grid, gridSize) == 1) {

    return 0;
  }

  if (move%2 == 0) {

    int bestScore = -1000;
    for (int i=0; i<gridSize; i++) {

      if (grid[i] == 0) {

        grid[i] = Computer_Input;
        int score = minimax(grid, gridSize, move+1, depth+1);
        grid[i] = 0;
        bestScore = (score > bestScore) ? score : bestScore;
      }
    }
    return bestScore;
  } else {

    int bestScore = 1000;
    for (int i=0; i<gridSize; i++) {

      if (grid[i] == 0) {

        grid[i] = User_Input;
        int score = minimax(grid, gridSize, move+1, depth+1);
        grid[i] = 0;
        bestScore = (score < bestScore) ? score : bestScore;
      }
    }
    return bestScore;
  }
}


/**
 * @function computerInput
 * @return int
 * @description Makes the computer's move, optimally, 
 * using the minimax algorithm.
 *
 * @params grid
 * @type int[]
 * @description The tic tac toe grid.
 *
 * @params gridSize
 * @type int
 * @description The tictactoe grid size.
**/
int computerInput (int grid[], int gridSize) {

  int bestScore = -1000;
  int bestMove = -111;

  for (int i=0; i<gridSize; i++) {

    if (grid[i] == 0) {

      grid[i] = Computer_Input;
      int score = minimax(grid, gridSize, 1, 0);
      grid[i] = 0;

      if (score > bestScore) {

        bestScore = score;
        bestMove = i;
      }
    }
  }

  grid[bestMove] = Computer_Input;
  return bestMove;
}

