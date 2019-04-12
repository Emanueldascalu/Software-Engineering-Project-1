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
        printf("Enter name for Player %d\n", i);
        scanf("%s", &players->names[i-1]);
        printf("Select a colour: B, R, P, Y, G, O ?\n");
        scanf(" %s", &colour);

        switch(colour){
                case 'B':
                    players[i-1].col=BLUE;
                    break;
                case 'R':
                    players[i-1].col=RED;
                    break;
                case 'P':
                    players[i-1].col=PINK;
                    break;
                case 'Y':
                    players[i-1].col=YELLOW;
                    break;
                case 'G':
                    players[i-1].col=GREEN;
                    break;
                case 'O':
                    players[i-1].col=ORANGE;
                    break;
                default:
                    printf("Error\n");
                    i--;
        }
        
        printf("Enter 1 to Input Names and 0 to Stop Inputting Names\n");
        scanf("%d", &option);
        
        if(option==1)
        {
            i++;
        }            
 
    }
    
    return i;
   
}


    
   
     


