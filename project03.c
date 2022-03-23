#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//set default values within tic-tac-toe board
char* position[3][3] = {{"?", "?", "?"}, {"?", "?", "?"}, {"?", "?", "?"}};

//print the board, values vary based on input
void printBoard() {

   printf ("%s | %s | %s\n", position[0][0] , position[0][1] , position[0][2]);
   printf ("--+---+--\n");
   printf ("%s | %s | %s\n", position[1][0] , position[1][1] , position[1][2]);
   printf ("--+---+--\n");
   printf ("%s | %s | %s\n", position[2][0] , position[2][1] , position[2][2]);

}

//fills values of board with given input
void fillValues (char* input[9]) {
   int i = 1;

   for (int row = 0; row < 3; row++) {
      for (int column = 0; column < 3 ; column++) {
         position[row][column] = input[i];
         i++;
      }
   }
}

//check if a spot has "?", indicates whether or not it is filled
bool filledSpot (char* spot) {
   if (*spot == '?') {
      return false; }

   return true;
}

//go through each winning combination, message displayed + program ends if one is found
bool checkWin() {

   //Horizontal Wins
   for (int row = 0; row < 3 ; row++) {
      if (*position[row][0] == *position[row][1] && *position[row][1] == *position[row][2] && *position[row][2] != '?') {
         return true; }
   }

   //Vertical Wins
   for (int column = 0; column < 2 ; column++) {
      if (*position[0][column] == *position[1][column] && *position[1][column] == *position[2][column] && *position[2][column] != '?') {
         return true; }
   }

   //Diagonal Wins
   if (*position[0][0] == *position[1][1] && *position[1][1] == *position[2][2] && *position[2][2] != '?') {
      return true; }

   if (*position[0][2] == *position[1][1] && *position[1][1] == *position[2][0] && *position[2][0] != '?') {
      return true;
   }

   //if no win found
   return false;
}

//used by function computerMove() to determine AI's best move
//assesses which path will lead to a win by iterating through all possible combinations of moves
int minimax (bool maximize) { //false "maximize" value indicates computer just moved, and vice versa

   //indicates that computer has won, returns value to indicate that this path is optimal
   if (checkWin() && maximize == false) {
       return 1; }

   //indicates that player has won, returns value to indicate that this path is not optimal
   if (checkWin() && maximize == true) {
       return -1; }

   int bestScore = 0; //player is looking for score of -1, computer looking for score of 1

   //computer's next move
   if (maximize) {
      //tests moves on each available spot
      for (int row = 0; row < 3; row++) {
         for (int column = 0; column < 3; column++) {

            //check if current spot is available, if not, move on to next one
            if (filledSpot(position[row][column]) == false) {

               //input computer's hypothetical move, pass through minimax function
               position[row][column] = "O";
               int score = minimax(false);

               //reset board afterwards
               position[row][column] = "?";

               //computer looking for score of 1
               if (score > bestScore) {
                  bestScore = score;
               }
            }
         }
      }
   }

   //player's next move
   else {
       //tests moves on each available spot
       for (int row = 0; row < 3; row++) {
         for (int column = 0; column < 3; column++) {

            //check if current spot is available, if not, move on to next one
            if (filledSpot(position[row][column]) == false) {

            //input player's hypothetical move, pass through minimax function
               position[row][column] = "X";
               int score = minimax(true);

               //reset board afterwards
               position[row][column] = "?";

               //player looking for score of -1
               if (score < bestScore) {
                  bestScore = score;
               }
            }
         }
      }
   }
   return bestScore; //pass value up the function
}

//code to run when it's the computer's move
void computerMove() {

   int bestRow = -1;
   int bestColumn = -1;
   int bestScore = -1;

   //test moves on each available spot
   for (int row = 0; row < 3; row++) {
      for (int column = 0; column < 3; column++) {

         //check if current spot is available, if not, move on to next spot
         if (filledSpot(position[row][column]) == false) {

            //input computer's hypothetical move, pass through minimax function 
            position[row][column] = "O";
            int score = minimax(false);

            //reset board afterwards
            position[row][column] = "?";

            //set current spot as most optimal, for now, if minimax spots a path that leads to a win for computer
            if (score > bestScore) {
               bestScore = score;
               bestRow = row;
               bestColumn = column;
            }
         }
      }
   }

   //once optimal move finally determined, put value into chosen spot
   position[bestRow][bestColumn] = "O";
   printf ("O: %d %d\n", bestRow, bestColumn);
}

//code to run when it is player's move
void playerMove() {
   int row;
   int column;

   //get player's input
   printf ("X: ");
   scanf ("%i %i", &row, &column);

   //error if user puts value into a filled spot
   while (filledSpot (position[row][column]) == true) {
      printf ("illegal move \n");
      printf ("X: ");
      scanf ("%i %i", &row, &column);
   }

   //error if user puts incorrect value
   while ( (row > 2 || row < 0) || (column > 2 || column < 0) ) {
      printf ("illegal move \n");
      printf ("X: ");
      scanf ("%d %d", &row, &column);
   }

   //put player's input into chosen spot
   position[row][column] = "X";
   printBoard();
}

int main(int argc, char *argv[]) {

   //if all values input manually, output computer's next move
   if(argc == 10) {
      fillValues(argv);
      printBoard();
      computerMove();
   }

   //if user wants to play full game of tic tac toe
   else if (argc == 1) {
      printBoard();
      for (int turn = 0; turn < 9; turn++) {

         if (turn % 2 == 0) {
            playerMove();
            if (checkWin()) { //assess if player has won after move
               printf ("X wins");
               return 0; }
         }

         else {
            computerMove();
            if (checkWin()) { //assess if computer has won after move
               printf ("X wins");
               return 0; }
         }
      }
   printf ("draw\n"); //if game ends and no wins detected
   }

   //error handling
   else {
      printf ("invalid number of arguments\n");
   }
   return 0;
}
