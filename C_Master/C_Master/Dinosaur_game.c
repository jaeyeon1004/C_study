#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include <stdbool.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

void SetConsole()
{
	system("mode con:cols=100 lines=25");
	//줄 25줄
	system("title Dinosaur_game-C lan study");
}

//Windows.h 인클루드
void GotoXY(int x, int y)
{
	//COORD 구조체
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//키보드 입력 받고 반환
//conio.h 인클루드
int GetKeyDown()
{
	//키보드 입력이 있을때 _kbhit() 함수 사용
	//여기선 키보드 입력이 무조건 있을때를 말하는 것
	if (_kbhit() != 0)
	{
		//키보드 입력 받고 출력은 안해줌 리턴만
		//why 내부적으로만 알고 동작 구도만 보는것
		return _getch();
	}
	return 0;
}

//공룡 그리기 하나하나 출력 다해줄고임 
void DrawDino(int dinoY)
{
	GotoXY(0, dinoY);
	//stdbool.h 선언 안해주면 에러남
	static boolean legFlag = true;
	printf("        $$$$$$$ \n");
	printf("       $$ $$$$$$\n");
	printf("       $$$$$$$$$\n");
	printf("$      $$$      \n");
	printf("$$     $$$$$$$  \n");
	printf("$$$   $$$$$     \n");
	printf(" $$  $$$$$$$$$$ \n");
	printf(" $$$$$$$$$$$    \n");
	printf("  $$$$$$$$$$    \n");
	printf("    $$$$$$$$    \n");
	printf("     $$$$$$     \n");
	if (legFlag)
	{
		printf("     $    $$$    \n");
		printf("     $$          ");
		legFlag = false;
	}
	else
	{
		printf("     $$$  $     \n");
		printf("          $$    ");
		legFlag = true;
	}
}

void DrawTree(int treeX) {
	//세로로 세워지는 것
	GotoXY(treeX, TREE_BOTTOM_Y);
	printf("$$$$");
	GotoXY(treeX, TREE_BOTTOM_Y + 1);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 2);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 3);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 4);
	printf(" $$ ");
}

//gameover 표시
void DrawGameOver(const int score)
{
	system("cls");
	int x = 18;
	int y = 8;
	GotoXY(x, y);
	printf("===========================");
	GotoXY(x, y + 1);
	printf("======❤G A M E O V E R❤======");
	GotoXY(x, y + 2);
	printf("===========================");
	GotoXY(x, y + 5);
	printf("SCORE : %d❤", score);

	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
}

bool isCollision(const int treeX, const int dinoY)
{
	GotoXY(0, 0);
	printf("treeX : %d, dinoY : %d", treeX, dinoY);
	//공룡의 몸통y가 트리의 x과 맞닿을 때
	//공룡 높이 충분하지 않으면 충돌 처리
	if (treeX <= 8 && treeX >= 4 && dinoY > 8)
	{
		return true;
	}
	return false;
}
int main(void) 
{
	SetConsole();

	while (true) {
		bool isStart = false; //시작시 초기화
		bool isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;

		int  score = 0;
		clock_t start, curr; //점수 변수 초기화
		start = clock(); //시작시간 초기화

		while (true)
		{
			if (isCollision(treeX, dinoY))
				break;
			if (GetKeyDown() == 'z' && isBottom)
			{
				isStart = true;
				isBottom = false;
			}
			if (isStart)
			{
				dinoY -= gravity;
			}
			else
			{
				dinoY += gravity;
			}

			if (dinoY >= DINO_BOTTOM_Y)
			{
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			treeX -= 2;
			if (treeX <= 0)
			{
				treeX = TREE_BOTTOM_X;
			}

			if (dinoY <= 3) {
				isStart = false;
			}

			DrawDino(dinoY);
			DrawTree(treeX);

			curr = clock();
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)
			{
				score++;
				start = clock();
			}
			Sleep(60);
			system("cls");

			GotoXY(22, 0);
			printf("Score : %d❤", score);
		}
		DrawGameOver(score);
	}
	return 0;
}
