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
    
    /* Allowing each player to place their four tokens on a square
       selected by the user */
    for(i=0;i<4;i++)   
    {
        for(j=0;j<numPlayers;j++)
        {
            printf("Player %d, please select a square\n", (j+1));
            scanf("%d", &selectedSquare);
            
            /* We made sure all the square in the first column are populated 
               before allowing the stacking of tokens */
            if(board[selectedSquare][0].numoftokens == minimumTokens && board[selectedSquare][0].stack == NULL)
            {
                /* the function addTokens is called to add the player's token to the selected square */
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
            
            /* This allows the stacking of tokens once all the square have been
               covered in the first column */
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
    
    /* The game runs until a winner is found */
    while(players->numtokenlastcol != 3) 
    {
        for(i=1;i<=numPlayers;i++)
        {
            /* Asking for the players how they want to move their tokens */
            printf("Player %d input:\n", i); 
            printf("1 if you want to move one of your tokens up or down.\nOtherwise, chose 2 to move a token forward.\n");
            
            scanf("%d",&choice);
            if(choice == 1)
            {
                START:
                /* Asking for the row and column of the token they want to move vertically */
                printf("Enter the row your token is located on.\n");
                scanf("%d", &row);
                printf("Enter the column your token is located on.\n");
                scanf("%d", &column);
                
                /* If there is no token on the square, the player gets to input another square */
                if(board[row][column].stack == NULL)
                {
                    printf("There is no token placed here.\nTry again.\n"); 
                    goto START;
                }
                printf("Enter 1 to move up or 2 to move down.\n");
                scanf("%d", &choice1);
                
                /* We are making sure the input by the player fits into the game's
                   criteria and it has their token on the top of the stack before
                   they move their token upwards */
                if(choice1 == 1 && (row < 6 && row >= 1) && (column < 9 && column >= 0) && (board[row][column].stack->col == players[i-1].col))
                {
                    /* We are checking if the token is on an obstacle square and restricting
                       the player from moving the token unless all there are no token behind 
                       it  */
                    if((row==0 && column==3) || (row==1 && column==6) || (row==2 && column==4) || (row==3 && column==5) || (row==4 && column==2) || (row==5 && column==7))
                    {
                        /* Going through the squares behind the token to check if there are Null */
                        int numNULL = 0;
                        for(int k=0; k<column; k++)
                        {   for(int l=0; l<NUM_ROWS; l++)
                            {
                                if(board[l][k].stack == NULL)
                                ++numNULL;
                            }
                        }

                        /* If there are no tokens behind the selected token, it can be moved 
                           to another square and the new board is printed */
                        if(numNULL == NUM_ROWS * column)
                        {
                            printf("There are no tokens behind your chosen token.\n It can now be moved.\n\n");
                            board[row-1][column].stack = addTokens(board[row][column].stack->col, board[row-1][column].stack);
                            board[row][column].stack = removeTokens(board[row][column].stack);
                            print_board(board);
                            goto END;
                        }

                        else
                            printf("This token can't be moved as it's on an obstacle square.\n\n");
                    }

                    /* If the token is not on an obstacle, it automatically allows the player
                       to move their token */
                    else
                    {
                        board[row-1][column].stack = addTokens(board[row][column].stack->col, board[row-1][column].stack);
                        board[row][column].stack = removeTokens(board[row][column].stack);
                        print_board(board);
                        goto END;
                    }

                }

                /* The same method is implemented if a player wants to move their token downwards */
                else if (choice1 == 2 && (row < 5 && row >= 0) && (column < 9 && column >= 0) && (board[row][column].stack->col == players[i-1].col))
                {
                    if((row==0 && column==3) || (row==1 && column==6) || (row==2 && column==4) || (row==3 && column==5) || (row==4 && column==2) || (row==5 && column==7))
                    {
                        int numNULL = 0;
                        for(int k=0; k<column; k++)
                        {   for(int l=0; l<NUM_ROWS; l++)
                            {
                                if(board[l][k].stack == NULL)
                                ++numNULL;
                            }
                        }

                        if(numNULL == NUM_ROWS * column)
                        {
                            printf("There are no tokens behind your chosen token.\n It can now be moved.\n\n");
                            board[row+1][column].stack = addTokens(board[row][column].stack->col, board[row+1][column].stack);
                            board[row][column].stack = removeTokens(board[row][column].stack);
                            print_board(board);
                            goto END;
                        }

                        else
                            printf("This token can't be moved as it's on an obstacle square.\n\n");
                    }

                    else
                    {
                        board[row+1][column].stack = addTokens(board[row][column].stack->col, board[row+1][column].stack);
                        board[row][column].stack = removeTokens(board[row][column].stack);
                        print_board(board);
                        goto END;
                    }

                }

                /* If a player inputs the wrong details, i is 
                   decremented to give them another try */
                else
                {
                    printf("One or more of your inputs was invalid. Try again.\n");
                    i--;
                }
            }
            
            /* Players have to move a token forward and they can move other 
               player's token not only theirs */
            else if(choice == 2)
            {   
                int n;
                
                END:
                dice = rand()%6;
                printf("\nRolling the dice.\nDice = %d.\n\n", dice);
                printf("If there are no tokens on this row, input 1 to reroll the dice else input 2.\n\n");
                scanf("%d", &n);
                
                if(n==1)
                {
                    goto END;
                }
                
                printf("Enter the column in which your chosen token is located.\n");
                scanf("%d", &column);
                
                /* The dice is used as the row for each player and they are 
                   allowed to input their own column. The square selected is
                   checked to make sure it is not empty */
                if(board[dice][column].stack == NULL)
                {
                    printf("There is no token placed here.\nTry again.\n"); 
                    goto END;
                }
                
                /* If it is not empty, the game's criteria are checked before
                   the token can be moved */
                else if(column < 8 && column >=0 )
                {
                    /* If the obstacle is on an obstacle, it is once again checked to 
                       make sure there are no tokens behind it, if so it can be moved 
                       forward */
                    if((dice==0 && column==3) || (dice==1 && column==6) || (dice==2 && column==4) || (dice==3 && column==5) || (dice==4 && column==2) || (dice==5 && column==7))
                    {
                        int numNULL = 0;
                        for(int k=0; k<column; k++)
                        {   for(int l=0; l<NUM_ROWS; l++)
                            {
                                if(board[l][k].stack == NULL)
                                ++numNULL;
                            }
                        }

                        if(numNULL == NUM_ROWS * column)
                        {
                            printf("There are no tokens behind your chosen token.\n It can now be moved.\n\n");
                            board[dice][column+1].stack = addTokens(board[dice][column].stack->col, board[dice][column+1].stack);
                            
                            /* If a player selects column 7 when moving a token 
                               forward, it is going onto the last column which
                               should increase the player who owns that token, number
                               of tokens on the last column */
                            if(column == 7)
                            {
                                for (int m=1; m<numPlayers; m++)
                                {
                                    /* We go through the players to make sure the right player's
                                       tokens on the last column are incremented and if it is
                                       equivalent to 3 they win */
                                    if(players[m-1].col == board[dice][column].stack->col)
                                    {
                                        ++players[m-1].numtokenlastcol;
                                        if(players[m-1].numtokenlastcol == 3)
                                            goto WIN;
                                    }
                                }
                            }
                            board[dice][column].stack = removeTokens(board[dice][column].stack);
                            print_board(board);
                        }
                        else
                            printf("This token can't be moved as it's on an obstacle square.\n\n");    
                    }

                    /* If there are no tokens behind the selected token, it can be 
                       moved forward to another square and the new board is printed */
                    else
                    {
                        board[dice][column+1].stack = addTokens(board[dice][column].stack->col, board[dice][column+1].stack);
                        if(column == 7)
                        {
                            for (int m=1; m<numPlayers; m++)
                            {
                                if(players[m-1].col == board[dice][column].stack->col)
                                {
                                    ++players[m-1].numtokenlastcol;
                                    if(players[m-1].numtokenlastcol == 3)
                                        goto WIN;
                                }
                            }
                        }
                        board[dice][column].stack = removeTokens(board[dice][column].stack);
                        print_board(board);  
                    }
                }
            }
            
            else
                {
                    printf("One or more of your inputs were invalid. Try again.\n");
                    i--;   
                } 
        }
    }
    WIN:
    /* The winner is printed */
    printf("The winner is player %d or %s", i, players[i-1].names);
}

token * addTokens(enum color col, token * top)
{
    /* This uses malloc to create memory for the
       stack of tokens */
    token * current = top;
    top = (token*)malloc(sizeof(token));
    top->col = col;
    top->next = current;
    return top;
}
token * removeTokens(token * top)
{
    /* This function checks the top token
       and removes it from the stack */
    token * current = top;
    if(current != NULL)
    {
        top = current->next;
        free(current);        
    }
    return top;
}
