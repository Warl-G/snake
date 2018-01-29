#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#pragma comment(lib, "Winmm.lib")

#define UP 72

#define DOWN 80

#define LEFT 75

#define RIGHT 77

#define FRAMECOL 64    //58个半点

#define FRAMEROW 20    //20个整点

#define SPACE 32

#define ENTER 13

#define ESC 27

#define w 119
#define W 87
#define a 97
#define A 65
#define S 83
#define s 115
#define D 68
#define d 100

void foodMove();

void gotoxy(int xpos,int ypos)
{
	COORD scrn;
	
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	scrn.X = ypos;scrn.Y=xpos;
	
	SetConsoleCursorPosition(hOuput,scrn);
}

struct SNAKE 
{
	int row;
	int col;
	SNAKE *next;
	
};

struct FOOD
{
	int row;
	int col;
	
}food,point;
//建立蛇头蛇尾指针
SNAKE *snakehead;
SNAKE *snakebody;
SNAKE *snaketail;




//计分
int sc=0;

void score()
{
	
	gotoxy(FRAMEROW+1,FRAMECOL-10);
	printf("score: %4d",sc);
}

//边界30*20
//横0-58，竖1-20  -2
void framePrint()
{
	system("cls");
	
	printf("  回车:确认   WS/方向键:开始   空格:继续/暂停   ESC:返回菜单\n");
	for(int col=0;col<=FRAMECOL/2;col++)
	{
		printf("■");
	}
	
	for(int row=2;row<=FRAMEROW-1;row++)
	{
		gotoxy(row,0);
		printf("■");
		gotoxy(row,FRAMECOL);
		printf("■");
	}
	
	for(int coll=0;coll<=FRAMECOL/2;coll++)
	{
		gotoxy(FRAMEROW,coll*2);
		printf("■");
	}

	gotoxy(FRAMEROW+1,0);
	printf(" made by GR");
	
}

void speed()
{
	if(sc<100)
		Sleep(400);
	if(sc>=100&&sc<200)
		Sleep(300);
	if(sc>=200&&sc<300)
		Sleep(200);
	if(sc>=300&&sc<400)
		Sleep(150);
	if(sc>=400&&sc<500)
		Sleep(100);
	if(sc>=500)
		Sleep(80);
}


//食物生成
void foodCreate()
{
	
	gotoxy(food.row,food.col);
	printf("  ");
	srand(unsigned(time(0)));
	food.col=(rand() % (FRAMECOL/2-1)+1)*2;
	food.row=rand() % (FRAMEROW-2) + 2;
	for(snakebody=snakehead;snakebody!=NULL;)
	{
		
		if(food.row==snakebody->row&&food.col==snakebody->col)
		{
			srand(unsigned(time(0)));
			food.col=(rand() % (FRAMECOL/2-1)+1)*2;
			food.row=rand() % (FRAMEROW-2) + 2;
			snakebody=snakehead;
			continue;
			
		}
		snakebody=snakebody->next;
	}
	gotoxy(food.row,food.col);
	printf("●");
}


void foodEat()
{
	
	//若吃食加分，生成新食物
	if(food.row==snakehead->row&&food.col==snakehead->col)
	{
		if(sc==0)
			PlaySound("firstblood.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		/*else if(sc==5)
			PlaySound("doublekill.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		else if(sc==10)
			PlaySound("triblekill.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		else if(sc==15)
			PlaySound("quadrakill.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		else if(sc==20)
			PlaySound("pantakill.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);*/
		else
		PlaySound("marioeat.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		sc+=5;
		foodCreate();
	}
	
	//若未吃食去蛇尾蛇身移动
	else
	{
		snakebody=snakehead;
		while(snakebody->next->next!=NULL)
		{
			snakebody=snakebody->next;
		}
		gotoxy(snakebody->next->row,snakebody->next->col);
		printf("  ");
		free(snakebody->next);
		snakebody->next=NULL;
		
	}
}


int esc=0;
//蛇移动+按键检测
int directold=RIGHT;
int pause=1;
void snakeMove()
{
	int row=snakehead->row;
	int col=snakehead->col;
	int direct=directold;;
	
	//WASD转换方向
	
	for(;kbhit()!=0;)
	{
		switch(getch())
		{
		case 224:
			direct=getch();
			pause=1;
			break;
		case w:case W:
			direct=UP;
			pause=1;
			break;
		case a:case A:
			direct=LEFT;
			pause=1;
			break;
		case s:case S:
			direct=DOWN;
			pause=1;
			break;
		case d:case D:
			direct=RIGHT;
			pause=1;
			break;
		case SPACE:
			pause=-pause;
			break;
		case ESC:
			esc=1;
		default:
			break;
		}
	}
	
	
	
	if(pause==1)
	{
		
		//消除反向
		switch(direct)
		{
		case UP:
			if(directold==DOWN)
				direct=directold;
			break;
		case DOWN:
			if(directold==UP)
				direct=directold;
			break;
		case LEFT:
			if(directold==RIGHT)
				direct=directold;
			break;
		case RIGHT:
			if(directold==LEFT)
				direct=directold;
			break;
		default:
			break;
			
		}
		
		
		
		
		switch(direct)
		{
		case DOWN://down
			row++;
			directold=DOWN;
			break;		
		case UP://up
			row--;
			directold=UP;
			break;
		case LEFT://left	
			col-=2;
			directold=LEFT;
			break;
		case RIGHT://right		
			col+=2;
			directold=RIGHT;
			break;
			
		default:
			break;
			
		}
		//蛇头移动加长
		snakebody=snakehead;
		snakehead=(SNAKE*)malloc(sizeof(struct SNAKE));
		snakehead->row=row;
		snakehead->col=col;
		snakehead->next=snakebody;
		
		foodEat();
		
	}
	
	
	
}
//蛇死亡
int snakeDead()
{
	if(snakehead->col>=FRAMECOL||snakehead->col<=0||snakehead->row>=FRAMEROW||snakehead->row<=1)
	{
		PlaySound("mariodead.wav", NULL, SND_FILENAME | SND_SYNC | SND_NODEFAULT);
		Sleep(200);
		return 1;
	}
	for(snakebody=snakehead->next;snakebody!=NULL;snakebody=snakebody->next)
	{
		if(snakebody->row==snakehead->row&&snakebody->col==snakehead->col)
		{
			PlaySound("mariodead.wav", NULL, SND_FILENAME | SND_SYNC | SND_NODEFAULT);
			return 1;
		}
	}
	
	return 0;
	
}

//蛇绘制
void snakePrint()
{
	gotoxy(snakehead->row,snakehead->col);
	printf("◆");
	snakebody=snakehead->next;
	while(snakebody!=NULL)
	{
		gotoxy(snakebody->row,snakebody->col);
		printf("■");
		snakebody=snakebody->next;
		
	}
	speed();
}

int foodDead()
{
	if(food.col>=FRAMECOL||food.col<=1||food.row>=FRAMEROW||food.row<=1)
		return 1;
	for(snakebody=snakehead;snakebody!=NULL;snakebody=snakebody->next)
	{
		if(snakebody->row==food.row&&snakebody->col==food.col)
			return 1;
	}
	
	return 0;
	
}

void foodMove()
{
	if(pause==1)
	{
	gotoxy(food.row,food.col);
	printf("  ");
	do{
		srand(unsigned(time(0)));
		switch(rand() %4)
		{
		case 0:
			food.col+=2;
			if(foodDead()==1)
				food.col-=2;
			break;
		case 1:
			food.row--;
			if(foodDead()==1)
				food.row++;
			break;
		case 2:
			food.col-=2;
			if(foodDead()==1)
				food.col+=2;
			break;
		case 3:
			food.row++;
			if(foodDead()==1)
				food.row--;
			break;
		default:
			break;
		}
	}while(foodDead()==1);
	
	gotoxy(food.row,food.col);
	printf("●");
	}
	
	
}
void snakeInt()
{
	
	
	struct SNAKE *p,*q;
	
	for(p=snakehead;p!=NULL;p=q)
	{
		q=p->next;
		free(p);
	}
	snakehead=(SNAKE*)malloc(sizeof(struct SNAKE));
	snakehead->row=FRAMEROW/2;
	snakehead->col=(FRAMECOL/4+1)*2;
	snakehead->next=NULL;
}




void startRegular()
{
	sc = 0;
	snakeInt();
	framePrint();
	foodCreate();
	pause=1;
	
	
	while(!snakeDead()&&esc==0)
	{
		score();
		snakePrint();
		
		snakeMove();	
		
	}
	
	
	
}

void startHunt()
{
	sc = 0;
	snakeInt();
	framePrint();
	foodCreate();
	pause=1;
	
	while(!snakeDead()&&esc==0)
	{
		score();
		snakePrint();
		
		snakeMove();
		foodMove();
		
	}
	
	
	
}

void snakeHunt()
{
	while(esc==0)
	{
		
		framePrint();
		gotoxy(FRAMEROW/2,FRAMECOL/2+1);
		printf("◆");
		
		score();
		switch(getch())
		{
		case 224:
			directold=getch();
			startHunt();
			break;
		case W:case w:
			directold=UP;
			startHunt();
			break;
		case A:case a:
			directold=LEFT;
			startHunt();
			break;
		case S:case s:
			directold=DOWN;
			startHunt();
			break;
		case D:case d:
			directold=RIGHT;
			startHunt();
			break;
		case SPACE:
			directold=RIGHT;
			startHunt();
			break;
		case ESC:
			esc=1;
			break;
			
			
		default:
			break;
		}		
	}
	
}


void snakeRegular()
{
	while(esc==0)
	{
		framePrint();
		gotoxy(FRAMEROW/2,FRAMECOL/2+1);
		printf("◆");
		
		score();
		switch(getch())
		{
		case 224:
			directold=getch();
			startRegular();
			break;
		case W:case w:
			directold=UP;
			startRegular();
			break;
		case A:case a:
			directold=LEFT;
			startRegular();
			break;
		case S:case s:
			directold=DOWN;
			startRegular();
			break;
		case D:case d:
			directold=RIGHT;
			startRegular();
			break;
		case SPACE:
			directold=RIGHT;
			startRegular();
			break;
		case ESC:
			esc=1;
			break;
			
			
			
		default:
			break;
		}		
	}
	
}

void pointMove()
{
	gotoxy(point.row,point.col);
	printf("◎");
	gotoxy(0,FRAMECOL);
	
}

void pointClear()
{
	gotoxy(point.row,point.col);
	printf("  ");
	gotoxy(0,FRAMECOL);
}
void menu()
{
	esc=0;
	PlaySound("mariomenu.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT );
//  PlaySound("mariomenu.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT );
	gotoxy(FRAMEROW/2-8,FRAMECOL/2-18);
	printf("      @           @        @    @   \n");
	gotoxy(FRAMEROW/2-7,FRAMECOL/2-18);
	printf("     @ @     @@@  @        @     @  \n");
	gotoxy(FRAMEROW/2-6,FRAMECOL/2-18);
	printf("   @@   @@   @ @  @@@@@@   @  @@@@@@\n");
	gotoxy(FRAMEROW/2-5,FRAMECOL/2-18);
	printf(" @@   @   @@ @ @ @       @@@@@@    @\n");
	gotoxy(FRAMEROW/2-4,FRAMECOL/2-18);
	printf("   @@@@@@@   @ @@        @ @ @      \n");
	gotoxy(FRAMEROW/2-3,FRAMECOL/2-18);
	printf("        @    @ @ @@@@@@  @ @ @ @   @\n");
	gotoxy(FRAMEROW/2-2,FRAMECOL/2-18);
	printf("  @@@@@@@@@  @ @      @  @ @ @ @  @ \n");
	gotoxy(FRAMEROW/2-1,FRAMECOL/2-18);
	printf("  @   @   @  @ @    @@   @@@@@ @ @  \n");
	gotoxy(FRAMEROW/2,FRAMECOL/2-18);
	printf("  @   @   @  @@@  @@       @   @@   \n");
	gotoxy(FRAMEROW/2+1,FRAMECOL/2-18);
	printf("     @ @@    @ @ @     @   @ @ @   @\n");
	gotoxy(FRAMEROW/2+2,FRAMECOL/2-18);
	printf("   @@    @@      @     @   @@@ @   @\n");
	gotoxy(FRAMEROW/2+3,FRAMECOL/2-18);
	printf(" @@        @      @@@@@@ @@  @  @@@@\n");
	
	gotoxy(FRAMEROW/2+5,FRAMECOL/2-4);
	printf("普通模式");
	gotoxy(FRAMEROW/2+7,FRAMECOL/2-4);
	printf("捕猎模式");
	point.row=FRAMEROW/2+5;
    point.col=FRAMECOL/2-6;
	pointMove();
	while(esc==0)
	{
		switch(getch())
		{
		case 224:
			pointClear();
			switch(getch())
			{
			case UP:
				if(point.row==FRAMEROW/2+7)
					point.row-=2;
				break;
			case DOWN:
				if(point.row==FRAMEROW/2+5)
					point.row+=2;
				break;
			default:
				break;
				
			}
			pointMove();
			break;
			case W:case w:
				pointClear();
				if(point.row==FRAMEROW/2+7)
					point.row-=2;
				pointMove();
				break;
			case s:case S:
				pointClear();
				if(point.row==FRAMEROW/2+5)
					point.row+=2;
				pointMove();
				break;
			case ENTER:
				PlaySound("coin.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT|SND_PURGE);
				if(point.row==FRAMEROW/2+5)
					snakeRegular();		
				else
					snakeHunt();
			default:
				break;
				
				
		}
	}
}

int main()
{

	
	system("color 34");
	while(1)
	{
		system("cls");
		framePrint();
		menu();
	}
	
	system("pause");
	return 0;
	
}
