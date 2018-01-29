#include "stdio.h"
#include "conio.h"
#include "edge.h"
#include "math.h"
#include <windows.h>
#include <stdlib.h>
#include "food.h"
#include "time.h"
	int field[100][100]={0};
	int score=0;
	int row=37;
	int column=21;
void main()
{
	while(1)
	{
		++score;
		Food_Create();
	Field_Create();
	Sleep(1000);
	  system("cls");

	}
}