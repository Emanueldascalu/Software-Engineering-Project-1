#include "game.h"
#include <stdio.h>

/*  This function creates the board for the first time
    Input: board - a 6x9 array of squares  */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS])
{
    for (int i =0; i< NUM_ROWS; i++)
    {
        for(int j =0; j < NUM_COLUMNS; j++)
        {
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7))
            {
                board[i][j].type = OBSTACLE;
            } 
            
            else
            {
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            
            /* Assigning the stack and the number of tokens on each square to null and zero before placing tokens on the square */
            board[i][j].stack = NULL;
            board[i][j].numoftokens = 0;
        }
    }
} 
 /* This function creates players for the first time
    Input: the array of players to be initialised 
    Output: The number of players of the game   */
int initialize_players(player players[])
{
    int i=1, option;
    char colour;
    
    while(option!=0)
    {
        /* Asking for the player's input for their name and colour */
        printf("Enter name for Player %d.\n", i);
        scanf("%s", &players[i-1].names);
        printf("Select a colour:\n'B' for Blue,\n'R' for Red,\n'P' for Pink,\n'Y' for Yellow,\n'G' for Green,\n'O' for Orange.\n");
        scanf("%s", &colour);

        /* We are using a switch statement to assign the selected colour and the number of tokens in the last column to zero */
        switch(colour)
        {
                case 'B':
                    players[i-1].col = BLUE;
                    players[i-1].numtokenlastcol = 0;
                    break;
                    
                case 'R':
                    players[i-1].col = RED;
                    players[i-1].numtokenlastcol = 0;
                    break;
                    
                case 'P':
                    players[i-1].col = PINK;
                    players[i-1].numtokenlastcol = 0;
                    break;
                    
                case 'Y':
                    players[i-1].col = YELLOW;
                    players[i-1].numtokenlastcol = 0;
                    break;
                    
                case 'G':
                    players[i-1].col = GREEN;
                    players[i-1].numtokenlastcol = 0;
                    break;
                    
                case 'O':
                    players[i-1].col = ORANGE;
                    players[i-1].numtokenlastcol = 0;
                    break;
                    
                default:
                    /* Decrementing "i" so it can give the player a chance to input a new colour */
                    printf("Invalid input. Choose either 'B', 'R', 'P', 'Y', 'G' or 'O'.\n");
                    i--;
        }

        printf("Enter 1 to continue inputting names and 0 to stop inputting names.\n");
        scanf("%d", &option);
        
        if(option==1)
        {
            i++;
        }            
    }
    
    /* Returning i as this the number of players */
    return i;
}
