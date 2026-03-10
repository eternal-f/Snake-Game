#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>


/*全局变量*/
char ch='1';
int snake_tail[10][2];
int i;
int j;
int x;
int apple[2];
int len = 2;
int snake[10][2] = { 0 };
int wall[23][23] = { 0 };
int score = 0;


/*控制台*/
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


/*颜色*/
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}


/*围墙*/
void wall_info()
{
	color(10);
	for (i = 1; i <=21; i++)
	{
		for (j = 1; j <= 21; j++)
		{
			wall[i][j] = 1;
		}
	}
	for (i = 0; i < 23; i++)
	{
		for (j = 0; j < 23; j++)
		{
			gotoxy(i, j);
			if (wall[i][j] == 0)
			{
				printf("□");
			}
			else
			{
				printf("■");
			}
		}
	}
	color(14);
	gotoxy(25, 5);
	printf("按w、s、a、d（或↑、↓、←、→ ）改变方向");
	gotoxy(25, 7);
	printf("按任意键暂停");
	gotoxy(25, 9);
	printf("得分：0");
}


/*蛇与苹果*/
void snake_apple()
{
	snake[0][0] = rand() % 17 + 3;
	snake[0][1] = rand() % 17 + 3;
	apple[0] = rand() % 21 + 1;
	apple[1] = rand() % 21 + 1;
	snake[1][0] = snake[0][0];
	snake[2][0] = snake[0][0];
	snake[1][1] = snake[0][1]+1;
	snake[2][1] = snake[0][1]+2;
	gotoxy(snake[0][0], snake[0][1]);
	color(14);
	printf("¤");
	gotoxy(snake[1][0], snake[1][1]);
	printf("★");
	gotoxy(snake[2][0], snake[2][1]);
	printf("★");
	gotoxy(apple[0], apple[1]);
	color(12);
	printf("●");
	color(14);
}


/*移动蛇*/
void movesnake()
{
	color(14);
	int i, x, y;
	for (i = 0; i <= len; i++)
	{
		snake_tail[i][0] = snake[i][0];
		snake_tail[i][1] = snake[i][1];
	}
	if (_kbhit())ch = _getch();
	if (_kbhit())ch = _getch();
	switch (ch)
	{
		case(72):
		case ('w'):snake[0][1]--; break;
		case(80):
		case('s'):snake[0][1]++; break;
		case(75):
		case('a'):snake[0][0]--; break;
		case(77):
		case('d'):snake[0][0]++; break;
	}
	if (snake_tail[0][0] != snake[0][0] || snake_tail[0][1] != snake[0][1])
	{
		gotoxy(snake[0][0], snake[0][1]);
		printf("¤");
		for (i = 1; i <= len; i++)
		{
			snake[i][0] = snake_tail[i - 1][0];
			snake[i][1] = snake_tail[i - 1][1];
			gotoxy(snake[i][0], snake[i][1]);
			printf("★");
		}
		if (snake_tail[len][0] != 0)
		{
			gotoxy(snake_tail[len][0], snake_tail[len][1]);
			color(10);
			printf("■");
		}
	}
	Sleep(200-0.6*score);
}


/*吃苹果*/
void eat_apple()
{
	score += 1;
	if (len != 9)
	{
		len += 1;
	}
	apple[0] = rand() % 21 + 1;
	apple[1] = rand() % 21 + 1;
	gotoxy(apple[0], apple[1]);
	color(12);
	printf("●");
	gotoxy(28, 9);
	color(14);
	printf("%d",score);
}


/*蛇撞墙*/
void if_wall()
{
	gotoxy(11, 11);
	color(10);
	if (score < 7)
	{
		printf("游戏失败");
	}
	gotoxy(11, 12);
	printf("按下ENTER键退出游戏");
}


/*蛇吃自己*/
void if_self()
{
	gotoxy(11, 11);
	color(10);
	if (score < 7)
	{
		printf("游戏失败");
	}
	gotoxy(11, 12);
	printf("按下ENTER键退出游戏");
}


/*主函数*/
int main()
{
	srand((int)time(0));
	wall_info();
	snake_apple();
	while (1)
	{
		movesnake();
		if (snake[0][0] == apple[0] && snake[0][1] == apple[1])
		{
			eat_apple();
		}
		if (snake[0][0] == 0 || snake[0][1] == 0 || snake[0][0] == 22 || snake[0][1] == 22)
		{
			if_wall();
			break;
		}
		if (score == 7)
		{
			gotoxy(11, 11);
			color(14);
			printf("恭喜成功！");
			gotoxy(5, 24);
			printf("继续进行游戏，将不会增加长度！");
		}
		for (i = 1,x=0; i <= len; i++)
		{
			if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
			{
				x = 1;
				break;
			}
		}
		if (x == 1)
		{
			if_self();
			break;
		}
	}
	getchar();
	return 0;
}