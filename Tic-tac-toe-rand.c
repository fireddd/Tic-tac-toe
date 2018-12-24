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

int getDirections(const int* board,const int dir,const int cell,int side)
{
	int found=0;
	int index=cell;
	while(board[index]!=BORDER)
	{
		
		if(board[index]==side)
		{
			found++;
		}
		index=index+dir;
	}
	return found;
}
int findThreeInARow(const int * board,const int cell,int side)
{
	int index=cell;
	int count=0;
	int dir;
	for(int i=0;i<4;i++)
	{
		dir=Directions[i];
		int posdir=getDirections(board,dir,cell,side);
		count=count+posdir;
		int negdir=getDirections(board,-1*dir,cell,side);
		count=count+negdir;
		//
		// count is set to 4 because we are double counting the intial cell
		//
			if(count==4)
			{
				//printf("dir is %d  cell is %d \n",dir,cell);
				//printf("posdir is %d negdir is %d \n",posdir,negdir);

				return 1;
			}
			else
			 	count=0;
			}
	//printf("count %d \n \n",count);
	return 0;

}
int getHumanMove(const int* board)
{
	char userInput[4];
	int moveOk=0;
	int move=-1;
	while(!moveOk)
	{
		//Taking the input from the user
		printf("Please Enter a move from 1 to 9\n");
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
	//printf("Making move ....\n");
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
			//printf("oye if\n");
			LastMovemade=getHumanMove(&board[0]);
			makeMove(&board[0],LastMovemade,NOUGHTS);
			printBoard(&board[0]);
			side=CROSSES;
			
		}
		else
		{
			//printf("oye else\n");
			LastMovemade=getComputerMove(&board[0]);
			makeMove(&board[0],LastMovemade,CROSSES);
			printBoard(&board[0]);
			side=NOUGHTS;
			
		}
		if(findThreeInARow(board,LastMovemade,CROSSES)==1||findThreeInARow(board,LastMovemade,NOUGHTS)==1)
		{
			printf("It's over\n \n ");
			if(side==NOUGHTS)
				printf("Computer wins \n \n");
			else
				printf("Human wins \n \n");
			Gameover=1;
		}
		if(!hasEmpty(board)&&Gameover==0)
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