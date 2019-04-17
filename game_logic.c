#include "game.h"
#include "gamelogic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printLine();

/*  Returns the first letter associated with the colour of the token
    Input: t - pointer to a token
    Output: initial of the colour of the token */
char print_token(token *t)
{
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLUE) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/* Prints the board
    Input: the board to be printed. */
void print_board(square board[NUM_ROWS][NUM_COLUMNS])
{
    printf("                THE BOARD\n");
    
    for(int i =0; i < NUM_ROWS; i++)
    {
        /* prints an horizontal line */
        printLine();
        
        /* prints the row number */
        printf(" %d ", i);
        char c = '\0' ;
        
        /* if the square (i,j) is occupied, c is assigned the initial of the colour 
           of the token that occupies the square */
        for (int j = 0; j < NUM_COLUMNS; j++)
        {
            if(board[i][j].stack != NULL)
            {
                c = print_token(board[i][j].stack);
            }
            
            /* if the square (i,j) is empty */
            else
            {
                /* c is assigned 'X' if the square represents an obstacle */
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                /* c is assigned an empty space otherwise */
                else c = ' ';
            }
            
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    
    printLine();
    /* prints the number of the columns at the end of the board */
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine()
{
    printf("   -------------------------------------\n");  
}

/*  Place tokens in the first column of the board 
    Input: board - a 6x9 array of squares that represents the board
    players - the array of the players
    numPlayers - the number of players */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)// token *top)
{
    /* Variables for selected square and number of tokens */
    int minimumTokens = 0;
    int selectedSquare = 0;
    int i, j;
    
    for(i=0;i<4;i++)   
    {
        for(j=0;j<numPlayers;j++)
        {
            printf("Player %d, please select a square\n", (j+1));
            scanf("%d", &selectedSquare);
            
            if(board[selectedSquare][0].numoftokens == minimumTokens && board[selectedSquare][0].stack == NULL)
            {
                board[selectedSquare][0].stack = addTokens(players[j].col, board[selectedSquare][0].stack);
                board[selectedSquare][0].numoftokens++;
                print_board(board);
        
                if(((numPlayers*i) + j + 1)%NUM_ROWS == 0)
                {
                    minimumTokens++;
                }
 
            }
            
            else if(board[selectedSquare][0].numoftokens != minimumTokens || board[selectedSquare][0].stack->col == players[j].col)
            {
                printf("Error\n");
                j--;
            }
                
            else if(board[selectedSquare][0].numoftokens == minimumTokens && board[selectedSquare][0].stack != NULL) 
            {
                board[selectedSquare][0].stack = addTokens(players[j].col, board[selectedSquare][0].stack);
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
    
    int choice, choice1, i, j;
    int dice;
    int row, column;
   
    while(players->numtokenlastcol != 3)   
    {
        for(i=1;i<=numPlayers;i++)
        {
            dice = rand()%5;
            printf("\nRolling the dice.\nDice = %d.\n\n", dice);
            printf("Player %d input: ", i); 
            printf("1 if you want to move one of your tokens up or down.\nOtherwise, chose 2 to move forward a token on [%d].\n", dice);
            scanf("%d",&choice);
            
            switch(choice)
            {
                case 1:
                    printf("Enter the row your token is located on.\n");
                    scanf("%d", &row);
                    printf("Enter the column your token is located on.\n");
                    scanf("%d", &column);
                    printf("Enter 1 to move up or 2 to move down.\n\n");
                    scanf("%d", &choice1);
                  
                    if(choice1 == 1 && (row < 6 && row >= 1) && (column < 9 && column >= 0) && (board[row][column].stack->col == players[i-1].col))
                    {
                        if((row==1 && column==3) || (row==2 && column==6) || (row==3 && column==4) || (row==4 && column==5) || (row==5 && column==2))
                        {
                            printf("Error, Obstacle Ahead\n\n");
                        }
                        
                        else
                        {    
                            board[row-1][column].stack = addTokens(players[i-1].col, board[row-1][column].stack);
                            board[row][column].stack = removeTokens(board[row][column].stack);
                            print_board(board);
                        }
                    }
                    
                    else if (choice1 == 2 && (row < 5 && row >= 0) && (column < 9 && column >= 0) && (board[row][column].stack->col == players[i-1].col))
                    {
                        if((row==0 && column==6) || (row==1 && column==4) || (row==2 && column==5) || (row==3 && column==2) || (row==4 && column==7))
                        {
                            printf("Error, Obstacle Ahead\n\n");
                        }
                        
                        else
                        {
                            board[row+1][column].stack = addTokens(players[i-1].col, board[row+1][column].stack);
                            board[row][column].stack = removeTokens(board[row][column].stack);
                            print_board(board);
                        }
                    }
                    
                    else
                    {
                        printf("Invalid input, Try Again.\n");
                        i--;
                    }
                    break;
                    
                case 2:
                    printf("Enter the column in which your chosen token is located.\n");
                    scanf("%d", &column);
                    if(column < 8 && column >=0 )
                    {
                        if((dice==0 && column==2) || (dice==1 && column==5) || (dice==2 && column==3) || (dice==3 && column==4) || (dice==4 && column==1) || (dice==5 && column==6))
                        {
                            printf("Error, Obstacle Ahead\n\n");
                        }

                        else
                        {
                         
                            board[dice][column+1].stack = addTokens(players[i-1].col, board[dice][column+1].stack);
                            board[dice][column].stack = removeTokens(board[dice][column].stack);
                            print_board(board);
                        
                            if(column==7)
                            {
                                players[i-1].numtokenlastcol++;
                            }
                    }
                    }
                    break;
                    
                default:
                    printf("Invalid input, Try Again.\n");
                    i--;    
            }
            
        }
    }
    
    printf("Winner is Player %d\n", i-1);
}

token * addTokens(enum color col, token * top)
{
    token * current = top;
    top = (token*)malloc(sizeof(token));
    top->col = col;
    top->next = current;
    return top;
}
token * removeTokens(token * top)
{
    token * current = top;
    if(current != NULL)
    {
        top = current->next;
        free(current);        
    }
    return top;
}
