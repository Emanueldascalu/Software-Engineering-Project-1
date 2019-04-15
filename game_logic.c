#include "game_init.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printLine();

/* Returns the first letter associated with the color of the token 
 * Input: t - pointer to a token
 * Output: initial of the color of the token.*/
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLUE) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*Prints the board
 * Input: the board to be printed.*/
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    // TO BE IMPLEMENTED
    int minimumTokens=0;
    int selectedSquare=0;
    token * top_token=NULL;
    
    //board[NUM_ROWS][NUM_COLUMNS].numTokens={0};
    int i, j;
    
    for(i=0;i<4;i++)
    {
        for(j=0;j<numPlayers;j++)
        {
            printf("Player %d, please select a square\n", (j+1));
            scanf("%d", &selectedSquare);

            if(board[selectedSquare][0].numoftokens==minimumTokens && board[selectedSquare][0].stack == NULL)
            {
                board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
                board[selectedSquare][0].stack->col = players[j].col;
                board[selectedSquare][0].stack->next = top_token;
                board[selectedSquare][0].numoftokens++;
                print_board(board);

                if(((numPlayers*i) + j + 1)%NUM_ROWS == 0)
                {
                    minimumTokens++;
                }
            }     

            else if(board[selectedSquare][0].numoftokens!=minimumTokens || board[selectedSquare][0].stack->col == players[j].col)// && board[selectedSquare][0].stack != NULL)
            {
                //if(board[selectedSquare][0].stack->col == players[j].col)
                //{
                    printf("Error\n");
                    j--;
                //} 
            }       
            
            else if(board[selectedSquare][0].numoftokens==minimumTokens && board[selectedSquare][0].stack != NULL)
            {
                top_token = board[selectedSquare][0].stack;
                board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
                board[selectedSquare][0].stack->col = players[j].col;
                board[selectedSquare][0].stack->next = top_token;
                board[selectedSquare][0].numoftokens++;
                print_board(board);

                if(((numPlayers*i) + j + 1)%NUM_ROWS == 0)
                {
                    minimumTokens++;
                }

            }
              
        }
    }
}
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
    srand(time(NULL));

    int choice, i;
    int dice;

    for(i=1;i<=numPlayers;i++)
    {

        printf("Rolling the dice for Player %d !\n", i);
        dice = 1+rand()%6;

        printf("Input 1 if you want to move your token, otherwise input 2\n");
        scanf("%d",&choice);

        if(choice==1)
        {
          
           //removeTokens(board, dice, players, numPlayers);
           //updateTokens(board, dice, players, numPlayers);
           //moveTokens(board, dice, players, numPlayers);
        }

    }

}
/*void removeTokens(square board[NUM_ROWS][NUM_COLUMNS], int dice, player players[],int numPlayers)
{
    int choice;
    square *current;
    
    printf("Input 1 to move up and 2 to move down");
    scanf("%d", &choice);
    
    if(choice==1)
    {
        board[dice][0].stack->next;
        current->next = NULL;
     
        
    }
    else
    {
        
        
    }
    
    
    
}


void updateTokens(square board[NUM_ROWS][NUM_COLUMNS], int dice, player players[], int numPlayers)
{
    
    
}
void moveTokens(square board[NUM_ROWS][NUM_COLUMNS], int dice, player players[], int numPlayers)
{
    int i;
    
    for(i=0;i<6;i++)
    {
        if(i==dice)
        {
            board[dice][0].stack;
            
            
            
        }
    }
    
    
    
}*/
