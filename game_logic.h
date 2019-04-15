/*  Prints the board
    Input: the board to be printed. */
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

void print_board(square board[NUM_ROWS][NUM_COLUMNS]);

/*  Place tokens in the first column of the board
    Input: board - a 6x9 array of squares that represents the board
    players - the array of the players
    numPlayers - the number of players  */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers,token *top);

/* Manages the logic of the game 
    Input: board - a 6x9 array of squares that represents the board
    players - the array of the players
    numPlayers - the number of players */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers, token *top);



#endif	// GAMELOGIC_H

