#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

int printBoard(char*);
int getMove(int, char*, int);
int calculateMove(char*, int, int);
int victoryConditions(char*, int);
int getComputerMove(char gameTracker);
int preventMove(char*);

// Define the game board tokens and size/rows.
#define P_1 'X'
#define P_2 'O'
#define EMPTY ' '
#define SIZE 9
#define F_ROW 0
#define S_ROW 3
#define T_ROW 6

int main() {
	// Allocate 9 bytes of memory.
	char* gameTracker = malloc(sizeof(char * SIZE));
	
	// Player 1=1, player 2=2.
	int playerTurn = 1;
	
	// store the amont empty spots.
	int marked;
	
	// Store game move/status and track if the game is runnig.
    int move, validMove, is_Running = 1;
    
	// Fill the allocated storage with data.
	for(int i = 0; i < SIZE; i++)
	    gameTracker[i] = EMPTY;
	
	// Store data of game setup.
	int init;
	
	// Get game setup.
	printf("human vs human(1)\nhuman vs computer(2)\n: ");
	while(init != 1 && init != 2) {
		scanf("%d", &init);
	}
	
	// Run if vs computer
	if(init == 2) {
	  srand(time(NULL));
	  system("cls");
    }
	
    // Print basic gameboard.
    printBoard(gameTracker);
    
	while(is_Running == 1) {			     
	   move = getMove(playerTurn, gameTracker, init);
	     
	   validMove = calculateMove(gameTracker, playerTurn, move);	
	
	   if(victoryConditions(gameTracker, playerTurn) == 1) { 	
	     	system("cls");
	     	printBoard(gameTracker);
		    if(playerTurn == 1)
		       printf("\nplayer 1 won the game.");
		    else
		       printf("\nplayer 2 won the game.");
		    
		    break;     
	     }
	     
	    if(validMove == 1) {
	        if(playerTurn == 1)
	           playerTurn = 2;
	        else
	          playerTurn = 1;	
	    }     
	    
	     if(validMove == 1) {
	         system("cls");
	         marked = printBoard(gameTracker);
	     }
	     
	     if(marked > 8) {
	     	printf("\nDraw");
	     	break;
	     }
	}
	
	// Free the stacked buffer.
	free(gameTracker);
	
	return 0;
}
int printBoard(char* gameTracker) {
	int marked = 0;
	// Print the board by reading the allocated data.
	for(int i = 0; i < SIZE; i++)
	{
		if(i == F_ROW || i == S_ROW || i == T_ROW)
		    printf("\n");
		
		printf("[%c]", gameTracker[i]);
		
		if(gameTracker[i] != EMPTY)
		   marked++;
	}
	
	return marked;
}
int getMove(int playerTurn, char* gameTracker, int init) { 
	// Store data of a game move.
	int move = 0;
    
    // Run if vs computer
    if(init == 2 && playerTurn == 2) {
		move = getComputerMove(gameTracker);
		return move;
	}
	
	// Ask for a valid move.
	while(move > SIZE || move == 0)	{
	    printf("\nPlayer %d, please make a move\n: ", playerTurn);
	    scanf("%d", &move);
	       
	    if(move >  SIZE || move == 0)
	    {
	       system("cls");
	       printBoard(gameTracker);
	    }	   
	}	
	return move;
}
int calculateMove(char* gameTracker, int playerTurn, int move) {
	// 0 = unvalid move, 1 = valid move.
	int validMove = 0;
	
	// Control the made move.
	for(int i = 1; i <= SIZE; i++) {
		if(i == move ) {
			if(playerTurn == 1) {
			   if(gameTracker[i - 1] == P_2) {
			   	  return validMove = 0; 
			   }
			   gameTracker[i - 1] = P_1;
			}
			else {
			   if(gameTracker[i - 1] == P_1) {
			   	  return validMove = 0;
			   }
			   gameTracker[i - 1] = P_2;
			}
			
			break;
		}
	}
	return validMove = 1;
}
int victoryConditions(char* gameTracker, int playerTurn) {
	// 0 = unvalid, 1 = valid.
	int condition = 0;
	char token;
	if(playerTurn == 1)
	  token = P_1;
	else
	  token = P_2;
	
	// conditions for winning the game.
	if(gameTracker[0] == token && gameTracker[1] == token && gameTracker[2] == token) return condition = 1;
	if(gameTracker[3] == token && gameTracker[4] == token && gameTracker[5] == token) return condition = 1;
	if(gameTracker[6] == token && gameTracker[7] == token && gameTracker[8] == token) return condition = 1;
	if(gameTracker[0] == token && gameTracker[3] == token && gameTracker[6] == token) return condition = 1;
	if(gameTracker[1] == token && gameTracker[4] == token && gameTracker[7] == token) return condition = 1;
	if(gameTracker[2] == token && gameTracker[5] == token && gameTracker[8] == token) return condition = 1;
	if(gameTracker[0] == token && gameTracker[4] == token && gameTracker[8] == token) return condition = 1;
	if(gameTracker[2] == token && gameTracker[4] == token && gameTracker[6] == token) return condition = 1;
	
	return condition;  
}
int getComputerMove(char* gameTracker) {
	int move;
	int makingMove = 1;
	
	//good start
	if(gameTracker[4] == EMPTY) return move = 5;
    
	move = preventMove(gameTracker);
	if(move != 0) return move;
	
	//calculting a move.
	while(makingMove == 1) {
        move = rand() % 9 + 1;
        
        if(gameTracker[move - 1] == EMPTY) {
        	makingMove = 0;
        	return move;
        }
    }
    
	
	return move;
}
int preventMove(char* q) {
	char token = P_1;
	int move;
	
	if(q[0] == token && q[1] == token && q[2] == EMPTY) return move = 3;
	if(q[2] == token && q[1] == token && q[0] == EMPTY) return move = 1;
	if(q[4] == token && q[5] == token && q[3] == EMPTY) return move = 4;
	if(q[3] == token && q[4] == token && q[5] == EMPTY) return move = 6;
	if(q[7] == token && q[8] == token && q[6] == EMPTY) return move = 7;
	if(q[6] == token && q[7] == token && q[8] == EMPTY) return move = 9;
	
    if(q[3] == token && q[6] == token && q[0] == EMPTY) return move = 1;
    if(q[0] == token && q[3] == token && q[6] == EMPTY) return move 7;
    if(q[1] == token && q[4] == token && q[7] == EMPTY) return move = 8;
    if(q[7] == token && q[4] == token && q[1] == EMPTY) return move = 2;
    if(q[2] == token && q[5] == token && q[8] == EMPTY) return move = 9;
    if(q[8] == token && q[5] == token && q[2] == EMPTY) return move = 3;
 
    // Block any diagonalmove.
    if(q[0] == token && q[4] == token && q[8] == EMPTY) return 9;
    if(q[8] == token && q[4] == token && q[0] == EMPTY) return 1;
    if(q[2] == token && q[4] == token && q[6] == EMPTY) return 7;
    if(q[6] == token && q[4] == token && q[2] == EMPTY) return 3;
 
    // Block any [X][ ][X]
    if(q[0] == token && q[2] && q[1] == EMPTY) return 2;
    if(q[3] == token && q[5] == token q[4] == EMPTY) return 5;
    if(q[6] == token && q[8] == token && q[7] == EMPTY) return 8;
    if(q[0] == token && q[6] && token q[3] == EMPTY) return 4;
    if(q[2] == token && q[8] == token && q[5] == EMPTY) return 6;
    
	return move = 0;
}


