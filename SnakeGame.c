#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>



#define WIDTH 30
#define HEIGHT 20

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define SPACE 32
#define ESC 27

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

int key;
int dir = LEFT;
int length = 5;         //초기 길이
int x[100], y[100];    // x,y 좌표값을 저장 총 100개
int food_x = 10, food_y = 10; //food좌표
int speed = 100;
int score;
int best_score = 0; //최고 점수 저장 --reset함수에 의해 초기화 되지 않음
char snake[] = "■";
char wall[] = "□";
char food[] = "★";

void gotoxy(int x, int y);
void setcursortype(CURSOR_TYPE c);
void playSnakeGame();
void Map();
void Move(int dir);
void Start();
void GameOver();
void reset(void); //게임을 초기화 
void info_draw(void); // 게임 방법 출력함수
void Status();
void DropFood();
void Menu();
void setMap(); void setSnake(); void setFood();
char* change_word(char* string, char* old_word, char* new_word);
void textcolor(int color_number) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}



enum
{
	BLUE,      /*  9 : 파랑 */
	RED,      /* 12 : 빨강 */
	VOILET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
};

int main() {
	playSnakeGame();
}

void Map() {
	int map[30][30] = {
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			gotoxy(i * 2, j);
			if (map[i][j] == 0)
				printf("");
			else if (map[i][j] == 1)
				printf("%s", wall);
		}
	}
}

void Start() {
	system("cls");
	setcursortype(NOCURSOR);
	Map();
	for (int i = 0; i < length; i++) {
		x[i] = 40 + (2 * i);
		y[i] = 10;
		gotoxy(x[i], y[i]);
		printf("%s", snake);
	}
	gotoxy(food_x, food_y);
	printf("%s", food);
}

void Move(int dir) {
	int i;

	if (x[0] == food_x && y[0] == food_y) {							// 먹이
		score += 10;
		length++;
		DropFood();
		x[length - 1] = x[length - 2]; //새로만든 몸통에 값 입력 
		y[length - 1] = y[length - 2];
		if (score % 4 == 0)
			speed -= 3;
	}
	if (x[0] == 0 || y[0] == 0 || x[0] == 58 || y[0] == 19) {		// 벽
		GameOver(); return 0;

	}
	for (int i = 1; i < length; i++) {								// 꼬리
		if (x[0] == x[i] && y[0] == y[i]) {
			GameOver(); return 0;
		}
	}

	gotoxy(x[length - 1], y[length - 1]); printf("  ");
	for (i = length - 1; i > 0; i--) {
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	switch (dir) {
	case UP: --y[0]; break;
	case DOWN: ++y[0]; break;
	case LEFT: x[0] -= 2; break;
	case RIGHT: x[0] += 2; break;
	}
	gotoxy(x[i], y[i]); printf("%s", snake);
}

void Status() {
	/*gotoxy(70, 1);
	printf("좌표 : %d, %d", x[0], y[0]);*/
	gotoxy(70, 4);
	printf("길이 : %d", length);
	gotoxy(70, 5);
	printf("속도 : %d  ", speed);
	gotoxy(70, 6);
	switch (dir) {
	case UP: printf("방향 : UP   "); break;
	case DOWN: printf("방향 : DOWN "); break;
	case LEFT: printf("방향 : LEFT "); break;
	case RIGHT: printf("방향 : RIGHT"); break;
	}
	gotoxy(70, 3);
	printf("점수 : %d", score);
	gotoxy(70, 2);
	printf("최고점수 : %3d", best_score);

	/*gotoxy(70, 7);
	printf("먹이 : %d %d", food_x, food_y);*/
}

void GameOver() {
	gotoxy(2, 1);
	printf("□□□■■■□□□□■□□□□■□■□□■■■■■□□□");
	gotoxy(2, 2);
	printf("□□■□□□□□□■□■□□□■□■□□■□□□□□□□");
	gotoxy(2, 3);
	printf("□□■□■■■□■■■■■□■□■□■□■■■■■□□□");
	gotoxy(2, 4);
	printf("□□■□□□■□■□□□■□■□■□■□■□□□□□□□");
	gotoxy(2, 5);
	printf("□□□■■■□□■□□□■□■□□□■□■■■■■□□□");
	gotoxy(2, 6);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□");
	gotoxy(2, 7);
	printf("□□□■■■□□■□□□■□■■■■■□■■■■□□□□");
	gotoxy(2, 8);
	printf("□□■□□□■□■□□□■□■□□□□□■□□□■□□□");
	gotoxy(2, 9);
	printf("□□■□□□■□■□□□■□■■■■■□■■■■□□□□");
	gotoxy(2, 10);
	printf("□□■□□□■□□■□■□□■□□□□□■□□□■□□□");
	gotoxy(2, 11);
	printf("□□□■■■□□□□■□□□■■■■■□■□□□■□□□");
	gotoxy(25, 13);
	printf("점수 : %d", score);//죽으면 점수출력
	if (score > best_score) {
		best_score = score;
		gotoxy(20, 12);
		printf("☆ 최고 점수 달성 ☆");
	}
	gotoxy(12, 14);
	printf("'A'키 입력 시 초기화면으로 돌아갑니다.");
	while (1)// A누르면 게임재시작 break
	{
		if (_getch() == 'a' || _getch() == 'A')
		{
			reset(); // 게임을 초기화 
			playSnakeGame();
			break;
		}
	}
}

void reset(void) // 게임 데이터 초기화
{
	int i;
	system("cls"); //화면을 지움 
	Map(); //맵 테두리를 그림

	dir = LEFT; // 방향 초기화  
	speed = 100; // 속도 초기화 
	length = 5; //뱀 길이 초기화 
	score = 0; //점수 초기화 
	for (i = 0;i < length;i++) { //뱀 몸통값 입력 
		x[i] = WIDTH / 2 + i;
		y[i] = HEIGHT / 2;
		gotoxy(x[i], y[i], "□");
	}
	gotoxy(x[0], y[0], "■"); //뱀 머리 그림 
}

void DropFood() {
	srand(time(NULL));
	food_x = (rand() % 56);
	if (food_x % 2 == 1) food_x += 1;
	if (food_x == 0) food_x += 2;
	food_y = (rand() % 17) + 1;

	for (int i = 0; i < length; i++) { //food가 뱀 몸통과 겹치는지 확인  
		if (food_x == x[i] && food_y == y[i]) {
			food_x = (rand() % 56);
			if (food_x % 2 == 1) food_x += 1;
			if (food_x == 0) food_x += 2;
			food_y = (rand() % 17) + 1;
		}
	}

	gotoxy(food_x, food_y);
	printf("%s", food);
}

void playSnakeGame(void) {
	Menu();
	Start();
	while (1) {
		if (_kbhit()) { key = _getch(); }
		Sleep(speed);
		switch (key) { //입력받은 키를 파악하고 실행  
		case LEFT: 	case RIGHT: case UP: case DOWN:
			if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) || (dir == DOWN && key != UP))//180회전이동을 방지하기 위해 필요. 
				dir = key;
			key = 0; // 키값을 저장하는 함수를 reset 
			break;
		}
		Move(dir);
		Status();
	}
}

void Menu() {
	system("cls");
	setcursortype(NOCURSOR);
	Map();
	int x = 25, y = 8;
	gotoxy(23, 6); printf("지렁이 게임");
	gotoxy(24, 8); printf("  시작");
	gotoxy(24, 9); printf("  가이드");
	gotoxy(24, 10); printf("  지렁이");
	gotoxy(24, 11); printf("  태두리");
	gotoxy(24, 12); printf("  음식");
	gotoxy(24, 13); printf("  종료");
	gotoxy(16, 15);	printf("<발표순서 6월 3일(목) 6번째>");
	gotoxy(16, 16);	printf("<오픈소스 소프트웨어 이민우>");
	gotoxy(x - 1, y); printf(">");
	while (true) {
		int k = _getch();
		bool check = false;
		//34 ~ 40 , 9 ~ 11
		for (int i = 34; i <= 40; i++) {
			for (int j = 8; j <= 11; j++) {
				gotoxy(i, j); printf(" ");
			}
		}
		switch (k) {
		case UP:
			if (y > 8) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, --y); printf(">");
			} break;
		case DOWN:
			if (y < 13) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, ++y); printf(">");
			} break;
		case ENTER: case SPACE:
			switch (y) {
			case 8: return; break;
			case 9: info_draw(); break;
			case 10: setSnake(); break;
			case 11: setMap(); break;
			case 12: setFood(); break;
			case 13: exit(0);
			}
			check = true;
		}
		if (check == true)
			break;
	}
}

void info_draw(void) // 게임정보 
{
	system("cls");
	gotoxy(1, 3);
	printf("                              [규칙]\n\n");
	printf("    * 지렁이는 현재 머리가 향하고 있는 방향으로 계속 이동합니다.\n");
	printf("    * 플레이어의 조작으로 머리의 진행 방향을 바꿀 수 있습니다.\n");
	printf("    * 지렁이는 벽이나 자신의 몸 일부에 닿으면 죽습니다.\n");
	printf("    * 지렁이는 먹이를 먹을때마다 몸이 길어집니다. \n");
	printf("    * 지렁이의 길이를 늘려 높은점수를 기록해보세요!\n\n\n\n");
	printf("                            [조작 방법]\n\n");
	printf("    * [↑] - 지렁이의 진행 방향을 위쪽으로 바꿀 수 있습니다. \n");
	printf("    * [→] - 지렁이의 진행 방향을 오른쪽으로 바꿀 수 있습니다. \n");
	printf("    * [←] - 지렁이의 진행 방향을 왼쪽으로 바꿀 수 있습니다. \n");
	printf("    * [↓] - 지렁이의 진행 방향을 아래쪽으로 바꿀 수 있습니다. \n\n\n\n");
	printf("    * E - 시작하기  \n");


	while (1) // E을 입력받으면 메인화면으로 돌아갑니다.
	{
		if (_getch() == 'e' || _getch() == 'E')
		{
			break;
		}
	}
}

void setSnake() {
	int x = 34, y = 9;
	bool check = false;
	gotoxy(40, 9); printf("▩");
	gotoxy(37, 9); printf("□");
	gotoxy(34, 9); printf("■");
	gotoxy(x, y - 1); printf("↓");
	while (true) {
		int k = _getch();
		switch (k) {
		case LEFT:
			if (x > 34) {
				gotoxy(x, y - 1); printf("  ");
				x -= 3;
				gotoxy(x, y - 1); printf("↓");
			} break;
		case RIGHT:
			if (x < 40) {
				gotoxy(x, y - 1); printf("  ");
				x += 3;
				gotoxy(x, y - 1); printf("↓");
			} break;
		case ENTER: case SPACE:
			switch (x) {
			case 34:
				strcpy(snake, change_word(snake, snake, "■"));
				break;
			case 37:
				strcpy(snake, change_word(snake, snake, "□"));
				break;
			case 40:
				strcpy(snake, change_word(snake, snake, "▩"));
				break;
			}
			check = true; break;
		}
		if (check == true)
			break;
	}
	Menu(); return;
}
void setMap() {
	int x = 34, y = 10;
	bool check = false;
	gotoxy(40, 10); printf("▣");
	gotoxy(37, 10); printf("■");
	gotoxy(34, 10); printf("□");
	gotoxy(x, y - 1); printf("↓");
	while (true) {
		int k = _getch();
		switch (k) {
		case LEFT:
			if (x > 34) {
				gotoxy(x, y - 1); printf("  ");
				x -= 3;
				gotoxy(x, y - 1); printf("↓");
			} break;
		case RIGHT:
			if (x < 40) {
				gotoxy(x, y - 1); printf("  ");
				x += 3;
				gotoxy(x, y - 1); printf("↓");
			} break;
		case ENTER:  case SPACE:
			switch (x) {
			case 34:
				strcpy(wall, change_word(wall, wall, "□"));
				break;
			case 37:
				strcpy(wall, change_word(wall, wall, "■"));
				break;
			case 40:
				strcpy(wall, change_word(wall, wall, "▣"));
				break;
			}
			check = true; break;
		}
		if (check == true)
			break;
	}
	Menu(); return;
}
void setFood() {
	int x = 34, y = 11;
	bool check = false;
	gotoxy(40, 11); printf("♡");
	gotoxy(37, 11); printf("☆");
	gotoxy(34, 11); printf("★");
	gotoxy(x, y - 1); printf("↓");
	while (true) {
		int k = _getch();
		switch (k) {
		case LEFT:
			if (x > 34) {
				gotoxy(x, y - 1); printf("  ");
				x -= 3;
				gotoxy(x, y - 1); printf("↓");
			} break;
		case RIGHT:
			if (x < 40) {
				gotoxy(x, y - 1); printf("  ");
				x += 3;
				gotoxy(x, y - 1); printf("↓");
			} break;
		case ENTER:  case SPACE:
			switch (x) {
			case 34:
				strcpy(food, change_word(food, food, "★"));
				break;
			case 37:
				strcpy(food, change_word(food, food, "☆"));
				break;
			case 40:
				strcpy(food, change_word(food, food, "♡"));
				break;
			}
			check = true; break;
		}
		if (check == true)
			break;
	}
	Menu(); return;
}

char* change_word(char* string, char* old_word, char* new_word) {
	char* token;
	char temp[30];

	memset(temp, 0, sizeof(temp));
	token = strtok(string, " ");

	while (token != NULL)
	{
		if (0 == strcmp(token, old_word))
		{
			strcat(temp, new_word);
		}
		else
		{
			strcat(temp, token);
		}
		strcat(temp, " ");
		token = strtok(NULL, " ");
	}
	temp[strlen(temp) - 1] = 0;

	return temp;
}
void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void setcursortype(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}