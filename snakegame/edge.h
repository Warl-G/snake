//�����߽稁 1   n��  m��  �Ŀ�
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
				printf("��");
			else if(field[i][j]==2)
				printf("��");
			else if(field[i][j]==3)
				printf("��");
			else if(field[i][j]==4)
				printf("��");
			else 
				printf("  ");
		}
		printf("\n");
	}
	printf("R ������Ϸ\t�������ʼ��Ϸ\tp ��ͣ��Ϸ\n");
}



/*void Edge_Check(int *SNAKE_HEAD)
{
	if(edge[[SNAKE_HEAD->column][SNAKE_HEAD->row]==1)
		printf("��Ϸ������");
}*/

