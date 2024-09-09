
#include <stdlib.h>
#include <stdio.h>

// the tic tac matrix.
int grid[3][3];
int cols=2, rows=2;

/**
 *  Variable to denote the state of the game.
 *
 *  0 -> means the game is going on.
 *  1 -> means the player has won.
 *  2 -> means the computer has won.
**/
int gameState = 0;

/**
 * Displays information about the game, example errors.
 * 0 -> Invalid Input.
 * 1 -> Redundant Input.
 * 2 -> Garbage Input.
**/
int gameInfo = -1;

/**
 * Displays the state of the game, that is,
 * if it is ongoing
 * computer wins
 * or the user wins.
 * This done using the gameState Variable
 * whose value is set by other functions particularly by 
 * the setGameState function.
**/
void displayGameState() {

  if (gameState == 0) {

    /*printf("On Going\n");*/
  } else if (gameState == 1) {

    printf("Player wins!\n");
  } else 
    printf("Computer wins!\n");
}

/**
 * Function to set the set of the game.
 * It is set according to the specifications of the gameState variable.
 *
 * @var turn 
 * if turn is -
 * 0 -> denotes game state check after player input.
 * 1 -> denotes game state check after computer input.
**/
int setGameState(int turn) {

  if (gameState != 0) {

    return -1;
  }

  int diagonalMatch = 0, colAMatch = 0, colBMatch = 0, colCMatch = 0;
  int rowAMatch = 0, rowBMatch = 0, rowCMatch = 0;
  
  // diagonal condition
  if (grid[0][0] == grid[1][1] && grid[1][1] != 0) 
    if (grid[1][1] == grid[2][2])
      diagonalMatch = 1;

  // colA condition
  if (grid[0][0] == grid[1][0] && grid[1][0] != 0)
    if (grid[1][0] == grid[2][0])
      colAMatch = 1;

  // colB condition
  if (grid[0][1] == grid[1][1] && grid[1][1] != 0)
    if (grid[1][1] == grid[2][1])
      colBMatch = 1;

  // colC condition
  if (grid[0][2] == grid[1][2] && grid[1][2] != 0)
    if (grid[1][2] == grid[2][2])
      colCMatch = 1;

  // rowA condition
  if (grid[0][0] == grid[0][1] && grid[0][1] != 0)
    if (grid[0][1] == grid[0][2])
      rowAMatch = 1;

  // rowC condition
  if (grid[1][0] == grid[1][1] && grid[1][1] != 0)
    if (grid[1][1] == grid[1][2])
      rowBMatch = 1;

  // colA condition
  if (grid[2][0] == grid[2][1] && grid[2][1] != 0)
    if (grid[2][1] == grid[2][2])
      rowCMatch = 1;

  // secondary diagonal condition
  if (grid[0][2] == grid[2][0] && grid[0][2] != 0) 
    if(grid[1][1] == grid[2][0]) 
      diagonalMatch = 1;

  /*printf("colA %d", colAMatch);*/
  /*printf("colB %d", colBMatch);*/
  /*printf("colC %d", colCMatch);*/
  /*printf("rowA %d", rowAMatch);*/
  /*printf("rowB %d", rowBMatch);*/
  /*printf("rowC %d", rowCMatch);*/
  /*printf("diagonal %d", diagonalMatch);*/

  if (diagonalMatch == 1 || rowBMatch == 1 || rowCMatch == 1 || rowAMatch == 1 || colBMatch == 1 || colCMatch == 1 || colAMatch == 1) {

    if (turn == 0) {
      gameState = 1;
    } else if (turn == 1) 
      gameState = 2;
  }

  return 0;
}

/**
 * A function to display the grid in tic tac readable
 * format for the player.
**/
void displayGrid() {

  if (gameInfo == 0)
    printf("Illegal Move. Try Again..\n\n");
  else if (gameInfo == 1) 
    printf("Cell Already Filled. Try Again..\n\n");
  else if (gameInfo == 2) 
    printf("Not a digit. Try Again..\n\n");

  for (int i=0; i<3; i++) {

    for (int j=0; j<3; j++) {
      
      if (grid[i][j] == 1) {

        printf("\tX");
      } else if (grid[i][j] == 2) {

        printf("\tO");
      } else {

        printf("\t*");
      }
    }

    printf("\n\n");
  }
}

/**
 * A function that initializes the grid with 
 * 0s, pertaining no input. An input 2 would pertain 
 * computer's input.
**/
void initializeGrid() {

  for (int i=0; i<3; i++) {

    for (int j=0; j<3; j++) {

      grid[i][j] = 0;
    }
  }
}

/**
 * Function that fills in the matrix according to user
 * input.
 * If the user selects a cell then the value in it is replaced by 1.
 * Otherwise the value remains 0.
**/
void fillGrid (int x, int y, int move) {

  if (grid[x][y] != 0) {

    gameInfo = 1;
    // TODO: Implement a waiting mechanism
  } else {

    grid[x][y] = 1;
    gameInfo = -1;
  }
}

int takeInput() {

  if (gameState != 0) {

    return -2;
  }

  char buffer[256];
  int input, result;

  printf("Your Move: ");
  if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

    result = sscanf(buffer, "%d", &input);
    if (result != 1) {
     
      gameInfo = 2;
      system("clear");
      return -1;
    }
  }
  /*scanf("%d", &input);*/

  switch (input) {

    case 1: 
      fillGrid(0, 0, 1); 
      break;
    case 2:
      fillGrid(0, 1, 1);
      break;
    case 3:
      fillGrid(0, 2, 1);
      break;
    case 4:
      fillGrid(1, 0, 1);
      break;
    case 5:
      fillGrid(1, 1, 1);
      break;
    case 6:
      fillGrid(1, 2, 1);
      break;
    case 7:
      fillGrid(2, 0, 1);
      break;
    case 8:
      fillGrid(2, 1, 1);
      break;
    case 9: 
      fillGrid(2, 2, 1);
      break;
    default :
      gameInfo = 0;
      // TODO: implement a waiting mechanism to show the error and then redraw on canvas the grid.
      break;
  }

  system("clear");
  return 0;
}

int computerPlayer () {
  
  if (gameState != 0) {
    
    return -2;
  }

  if (gameInfo != -1) {

    return -2;
  }

  //check for 2s for a win 
  for (int i=0; i<2; i++) {

    for (int j=0; j<2; j++) {

      // successive column check
      if (grid[i][j] == grid[i][j+1] && grid[i][j] != 0) {

        if (grid[i][j+2] != 1 && grid[i][j+2] != 2) {

          grid[i][j+2] = 2;
          return 1;
        }
      }

      // successive row check
      if (grid[i][j] == grid[i+1][j] && grid[i][j] != 0) {

        if (grid[i+2][j] != 1 && grid[i+2][j] != 2) {

          grid[i+2][j] = 2;
          return 1;
        }
      }

      // start end check
      if (i==0 && grid[i][j] == grid[i+2][j] && grid[i][j] != 0) {
        
        if (grid[i+1][j] != 1 && grid[i+1][j] != 2 ) {
          
          grid[i+1][j] = 2;
          return 1;
        }
      }

      // start end check contd.
      if (j==0 && grid[i][j] == grid[i][j+2] && grid[i][j] != 0) {

        if (grid[i][j+1] != 1 && grid[i][j+1] != 2) {

          grid[i][j+1] = 2;
          return 1;
        }
      }

      //offensive
      if (i==0 && grid[i+2][j] != 1 && grid[i+2][j] != 2) {

        grid[i+2][j] = 2;
        return 2;
      }

      if (j==0 && grid[i][j+2] != 1 && grid[i][j+2] != 2) {

        grid[i][j+2] = 2;
        return 2;
      }

      if (i==j && grid[i][j] == grid[rows][cols] && grid[i][j] != 0) {

        if (grid[rows-1][cols-1] != 1 && grid[rows-1][cols-1] != 2) {

          grid[rows-1][cols-1] = 2;
          return -1;
        }
      }

      if (grid[i][j] == grid[j][i] && grid[i][j] != 0) {

        if (i==0 && grid[j][j] == 0) {

          grid[j][j] = 2;
          return -1;
        }

        if (j==0 && grid[i][i] == 0) {

          grid[i][i] = 2;
          return -1;
        }
      }

    }
  }

  return -1;
}

int isGridFilled() {

  int flag = 0;

  for (int i=0; i<3; i++) {

    for (int j=0; j<3; j++) {

      if (grid[i][j] == 0) {
        flag++;
      }
    }
  }

  if (flag > 0) {

    return 1; //the grid is not filled;
  } else {
    return 0;
  }
}

int minimax (int move) {


  // computer's move
  if (move % 2 == 0) {

    fillGrid()
  } 

  return 0;
}

int main () {

  system("clear");

  /*initializeGrid();    */
  /*displayGrid();*/
  /**/
  /*while (gameState == 0) {*/
  /**/
  /*  takeInput();*/
  /*  setGameState(0);*/
  /*  computerPlayer();*/
  /*  setGameState(1);*/
  /*  displayGrid();*/
  /*  displayGameState();*/
  /*}*/
}
