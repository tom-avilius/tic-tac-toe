
#include <stdio.h>
#include <stdlib.h>

int bestScore;


/**
 * @var inputInfo
 * @type int
 * @description Tells about the status of the input received from the player.
 * If inputInfo is -
 * 0 -> Normal Input
 * 1 -> Input Exceeds or Preceeds the available grid index.
 * 2 -> The input is redundant.
 * 3 -> The input is not of type int.
**/
int inputInfo = -1;

/**
 * @var gameInfo
 * @type int
 * @description Tells about the state of the game.
 * If the the gameInfo is:
 * 1 --> Then the player has won
 * 2 --> Then the computer has won
 * 3 --> Then the game ended in draw
 * 0 --> Still Going On.
**/
int gameInfo = 0;



/**
 * @function isGridFilled
 * @return int
 * @description Checks if the grid has been filled completely.
 * It return the number of empty cells.
 *
 * @params grid
 * @type int[]
 * @description The grid where the input would be stored.
 *
 * @params gridSize
 * @type int
 * @description The size of the grid.
**/
int isGridFilled (int grid[], int gridSize) {

  int count = 0;

  for (int i=0; i<gridSize; i++) {

    if (grid[i] == 0)
      count++;
  }

  return count;
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
 * @function input
 * @return int (no-value)
 * @description Function to take input from the user.
 * Stores in the provided grid and checks for its validity.
 * Also modifies the global variable inputInfo
 *
 * @params grid
 * @type int[]
 * @description The grid where the input would be stored.
 *
 * @params gridSize
 * @type int
 * @description The size of the grid.
**/
int input (int grid[], int gridSize) {

  char buffer[256];
  int input, result; 

  printf("\n\nYour Move: ");

  if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

    result = sscanf(buffer, "%d" ,&input);
    if (result != 1) {

      // input not of type int
      inputInfo = 3;
      return 0;
    }
  }

  if (input > gridSize || input < 1) {

    // input value exceeds or preceeds the space available in the grid.
    inputInfo = 1;
    return 0;
  } else if (grid[input-1] != 0) {

    // input is redundant
    inputInfo = 2;
    return 0;
  } else {

    // normal input was provided and the value can be assigned to the grid.
    inputInfo = 0;
    grid[input-1] = 1;
    return 0;
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

  // checking if there were any errors in the input.
  if (inputInfo == 1)
    printf("Input Exceeds or Preceeds the available grid. Try again..\n");
  else if (inputInfo == 2)
    printf("Input is Redundant. Try again..\n");
  else if (inputInfo == 3) 
    printf("Input is not a number. Try again..\n");

  // displaying the matrix
  for (int i=0; i<gridSize; i++) {

    if (i % 3 == 0)
      printf("\n");

    if (grid[i] == 0)
      printf("\t*");
    else if (grid[i] == 1)
      printf("\tX");
    else
      printf("\tO");
  }

  // if the game ends then the ending msg is printed.
  if (gameInfo == 1) {

    // the player wins
    printf("\nYou win!");
  } else if (gameInfo == 2) {

    // the computer wins
    printf("\nThe Computer wins!");
  } else if (gameInfo == 3) {

    printf("\nDraw");
  }
}


/**
 * @function setGameInfo
 * @return int (used by minimax algo)
 * @description Sets the variable game info according to the state of the game.
 * If the state is:
 * 1 --> Then the player has won
 * 2 --> Then the computer has won
 * 3 --> Then the game ended in draw
 * 0 --> Still Going On.
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
int setGameInfo (int grid[], int gridSize, int move) {

  if (isGridFilled(grid, gridSize) == 0) {

    // the game ends in a draw
    gameInfo = 3;
    // a draw game is a neutral result, so the minimax algo would it treat it as such
    return 0; 
  } else {

    // check the columns
    for (int i=0; i<3; i++) {

      if (grid[i] != 0) {

        if(grid[i] == grid[i+3] && grid[i] == grid[i+6]) {
          
          if (move == 1) {

            gameInfo = 1;
            // loss for the computer
            return -1;
          } else if (move == 2) {
        
            gameInfo = 2;
            return 1;
          }
        }
      }
    }

    //check rows
    for (int i=0; i<gridSize; i=i+3) {

      if (grid[i] != 0) {

        if(grid[i] == grid[i+1] && grid[i] == grid[i+2]) {

          if (move == 1) {

            gameInfo = 1;
            // loss for the computer
            return -1;
          } else if (move == 2) {
        
            gameInfo = 2;
            return 1;
          }
        }
      }
    }

    // check the primary and secondary diagonal
    int i = 0;
    if (grid[i] == grid[i+4] && grid[i] == grid[i+8] && grid[i] != 0) {
     
      if (move == 1) {

        gameInfo = 1;
        // loss for the computer
        return -1;
      } else if (move == 2) {
        
        gameInfo = 2;
        return 1;
      }
    }

    i = 2;
    if (grid[i] == grid[i+2] && grid[i] == grid[i+4] && grid[i] != 0) {
     
      if (move == 1) {

        gameInfo = 1;
        // loss for the computer
        return -1;
      } else if (move == 2) {
        
        gameInfo = 2;
        return 1;
      }
    }
  }

  return -2;
}

// Evaluate the board and return score: +1 (X wins), -1 (O wins), 0 (no winner)
int evaluate(int grid[], int gridSize, int move) {

  
  /*if (isGridFilled(grid, gridSize) != 0) {*/

    // check the columns
    for (int i=0; i<3; i++) {

      if (grid[i] != 0) {

        if(grid[i] == grid[i+3] && grid[i] == grid[i+6]) {
          
          if (move == 1) {

            // loss for the computer
            return -1;
          } else if (move == 2) {
        
            return 1;
          }
        }
      }
    }

    //check rows
    for (int i=0; i<gridSize; i=i+3) {

      if (grid[i] != 0) {

        if(grid[i] == grid[i+1] && grid[i] == grid[i+2]) {

          if (move == 1) {

            // loss for the computer
            return -1;
          } else if (move == 2) {
        
            return 1;
          }
        }
      }
    }

    // check the primary and secondary diagonal
    int i = 0;
    if (grid[i] == grid[i+4] && grid[i] == grid[i+8] && grid[i] != 0) {
     
      if (move == 1) {

        // loss for the computer
        return -1;
      } else if (move == 2) {
        
        return 1;
      }
    }

    i = 2;
    if (grid[i] == grid[i+2] && grid[i] == grid[i+4] && grid[i] != 0) {
     
      if (move == 1) {

        // loss for the computer
        return -1;
      } else if (move == 2) {
        
        return 1;
      }
    }
  /*} else {*/

    // a draw game is a neutral result, so the minimax algo would it treat it as such
    return 0;
  /*}*/

}


/****/
int minimax (int grid[], int gridSize, int move) {

  move = move%2 == 0 ? 2 : 1;
  int score = evaluate(grid, gridSize, move);

  if (score == 0) {

  if (move%2 == 0) {

    bestScore = -1000;

    for (int i=0; i<gridSize; i++) {

      if (grid[i] == 0) {

        grid[i] = 2;
        int score = minimax(grid, gridSize, move+1);
        grid[i] = 0;
        bestScore = (score > bestScore) ? score : bestScore;
      }
    }
  } else {

    bestScore = 1000;

    for (int i=0; i<gridSize; i++) {

      if (grid[i] == 0) {

        grid[i] = 1;
        int score = minimax(grid, gridSize, move+1);
        grid[i] = 0;
        bestScore = (score < bestScore) ? score : bestScore;
      }
    }
  }
  }

  return bestScore;
}


/****/
int computerMove (int grid[], int gridSize) {

  int bestVal = -1000;
  int bestMove = -1;

  for (int i=0; i<gridSize; i++) {

    if (grid[i] == 0) {

      grid[i] = 2;

      int moveVal = minimax(grid, gridSize, 2);
      grid[i] = 0;

      if (moveVal > bestVal) {

        bestMove = i;
        bestVal = moveVal;
      }
    }
  }

  printf("%d best", bestMove);
  grid[bestMove] = 2;
  return bestMove;
}


int main () {

  // A call to clear the screen
  system("clear");

  // the size of the grid for tic tac toe
  int gridSize = 9;
  // the grid to store the tic tac toe game
  int grid[gridSize];

  // initializing the grid with 0s.
  initializeGrid(grid, gridSize, 0);

  while (gameInfo == 0) {

    inputInfo = -1;

    while (inputInfo != 0 || inputInfo == -1) {

      display(grid, gridSize);
      input(grid, gridSize);
      system("clear");
    }

    setGameInfo(grid, gridSize, 1);
    if (gameInfo == 0) {

      computerMove(grid, gridSize);
      setGameInfo(grid, gridSize, 2);
    }
  }

  display(grid, gridSize);
  printf("\n");
}
