//☆  2
//食物产生
#include "math.h"
#include "time.h"
void Food_Create()
{
	extern int row;
	extern int column;
	int m,n,i,j,k=0;
	extern int field[100][100]; 
	srand((unsigned)time(NULL));
	while(1)
	{
		
		n=rand()%(column-1)+1;
		m=rand()%(row-1)+1;
		if(field[n][m]==0)
		break;
	}
	field[n][m]=2;
}