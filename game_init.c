#include "game_init.h"
#include <stdio.h>


/*
* This function creates the board for the first time
* Input: board - a 6x9 array of squares.
*/
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
}    
}

}
    
    
 
/*
* This function creates players for the first time  
* Input: the array of players to be initialized
* Output: The number of players of the game 
*/
int initialize_players(player players[6])
{
    int i=0, option;
    while(i<6)
    {   
        printf("Enter the name of the next player.\n");
        scanf("%d", players[i]);
        printf("Enter 1 to continue or 0 to stop entering names.\n");
        scanf("%d", option);
        
        if(option==1)
            i++;
        
        else if(option==0)
            goto END;
        
        else
            printf("Error.\n");
    }
    
   END:
   return i;
}
    
   
     

