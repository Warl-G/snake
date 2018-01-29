//创建边界▉ 1   n长  m宽  的框
void Field_Create()
{
	extern int field[100][100];
	extern int score;
	extern int row;
	extern int column;
	printf("score=%d\n",score);
	int i=0,j=0;
	for(i=0;i<column;i++)
	{
		for(j=0;j<row;j++)
		{
			if(i==0||i==column-1)
			{
				field[i][j]=1;
				continue;
			}
			else if(j==0||j==row-1)
				field[i][j]=1;
		}
	}
	for(i=0;i<column;i++)
	{
		for(j=0;j<row;j++)
		{
			if(field[i][j]==1)
				printf("▉");
			else if(field[i][j]==2)
				printf("☆");
			else if(field[i][j]==3)
				printf("□");
			else if(field[i][j]==4)
				printf("◆");
			else 
				printf("  ");
		}
		printf("\n");
	}
	printf("R 重新游戏\t方向键开始游戏\tp 暂停游戏\n");
}



/*void Edge_Check(int *SNAKE_HEAD)
{
	if(edge[[SNAKE_HEAD->column][SNAKE_HEAD->row]==1)
		printf("游戏结束！");
}*/

