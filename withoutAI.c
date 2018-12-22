#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { NOUGHTS , CROSSES , BORDER ,EMPTY };
enum { HUMANWIN , COMPWIN , DRAW} ;

const int Directions[4]={1,4,5,6};
//
// The squares that matter to us 
//
const int ConvertTo25[9]=
{
	6,7,8,
	11,12,13,
	16,17,18
};

void initaliseBoard(int* board)
{
	int index;
	for(index=0;index<25;index++)
	{
		board[index]=BORDER; 
	}
	for(index=0;index<9;index++)
	{
		board[ConvertTo25[index]]=EMPTY;
	}
}
void printBoard(const int *board)
{
	char chars[]={'O','X','|','-'};
	printf("The board is \n \n");
	for(int index=0;index<9;index++)
	{
		if(index!=0&&index%3==0)
			printf("\n \n");
		printf("%c ",chars[board[ConvertTo25[index]]]);
	}
	printf("\n \n");
}
int hasEmpty(const int *board)
{
	for(int index=0;index<9;index++)
	{
		if(board[ConvertTo25[index]]==EMPTY)
			return 1;
	}
	return 0;
}
void makeMove(int* board,const int cell,int side)
{
	board[cell]=side;
}
int getHumanMove(const int* board)
{
	char userInput[4];
	int moveOk=0;
	int move=-1;
	while(!moveOk)
	{
		//Taking the input from the user
		printf("Please Enter a move from 1 to 9");
		fgets(userInput,3,stdin);
		fflush(stdin);

		//
		//
		if(strlen(userInput)!=2)
		{
			printf("Invalid String Input\n");
			continue;
		}
		if(sscanf(userInput,"%d",&move)!=1)
		{
			move=-1;
			printf("Invalid sscanf()\n");
			continue;
		}
		if( move > 9 || move < 1 )
		{
			move=-1;
			printf("Invalid range\n");
			continue;
		}
		move--;
		if(board[ConvertTo25[move]]!=EMPTY)
		{
			move=-1;	
			printf("Square not available \n");
			continue;
		}
		moveOk=1;
	}
	printf("Making move ....\n");
	return ConvertTo25[move];
}

int getComputerMove(const int* board)
{
	int index=0;
	int numFree=0;
	int availableMoves[9];
	int randMove=0;
	for(index=0;index<9;index++)
	{
		if(board[ConvertTo25[index]]==EMPTY)
		{
			availableMoves[numFree++]=ConvertTo25[index];
		}
	}
	randMove=rand()%numFree;
	return availableMoves[randMove];
}

void runGame()
{
	int Gameover=0;
	int side=NOUGHTS;
	int LastMovemade=0;
	int board[25];
	initaliseBoard(&board[0]);
	printBoard(&board[0]);
	while(!Gameover)
	{
		if(side==NOUGHTS)
		{
			printf("oye if\n");
			LastMovemade=getHumanMove(&board[0]);
			makeMove(&board[0],LastMovemade,NOUGHTS);
			printBoard(&board[0]);
			side=CROSSES;
			
		}
		else
		{
			printf("oye else\n");
			LastMovemade=getComputerMove(&board[0]);
			makeMove(&board[0],LastMovemade,CROSSES);
			printBoard(&board[0]);
			side=NOUGHTS;
			
		}
		if(!hasEmpty(board))
		{
			printf("Game Over \n \n");
			printf("It is a draw \n \n");
			Gameover=1;

		}
		
	}
}
int main()
{
	runGame();
}