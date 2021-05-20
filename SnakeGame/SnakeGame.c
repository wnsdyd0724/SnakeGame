#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

#define WIDTH 30
#define HEIGHT 20

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define SPACE 32

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

int key;
int dir = LEFT;
int length = 5;
int x[100], y[100];
int food_x = 10, food_y = 10;
int speed = 100;
int score = 0;
char snake[] = "��";
char wall[] = "��";
char food[] = "��";

void gotoxy(int x, int y);
void setcursortype(CURSOR_TYPE c);
void playSnakeGame();
void Map();
void Move(int dir);
void Start();
void GameOver();
void Status();
void DropFood();
void Menu();
void setMap(); void setSnake(); void setFood();
char* change_word(char* string, char* old_word, char* new_word);

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

	if (x[0] == food_x && y[0] == food_y) {							// ����
		score += 10;
		length++;
		DropFood();
		x[length - 1] = x[length - 2]; //���θ��� ���뿡 �� �Է� 
		y[length - 1] = y[length - 2];
		if (score % 4 == 0)
			speed -= 3;
	}
	if (x[0] == 0 || y[0] == 0 || x[0] == 58 || y[0] == 19) {		// ��
		GameOver(); return 0;
	}
	for (int i = 1; i < length; i++) {								// ����
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
	printf("��ǥ : %d, %d", x[0], y[0]);*/
	gotoxy(70, 2);
	printf("���� : %d", length);
	gotoxy(70, 3);
	printf("�ӵ� : %d  ", speed);
	gotoxy(70, 4);
	switch (dir) {
	case UP: printf("���� : UP   "); break;
	case DOWN: printf("���� : DOWN "); break;
	case LEFT: printf("���� : LEFT "); break;
	case RIGHT: printf("���� : RIGHT"); break;
	}
	gotoxy(70, 5);
	printf("���� : %d", score);
	/*gotoxy(70, 7);
	printf("���� : %d %d", food_x, food_y);*/
}

void GameOver() {
	gotoxy(25, 9);
	printf("Game Over");
	gotoxy(25, 10);
	printf("���� : %d", score);
}

void DropFood() {
	srand(time(NULL));
	food_x = (rand() % 56);
	if (food_x % 2 == 1) food_x += 1;
	if (food_x == 0) food_x += 2;
	food_y = (rand() % 17) + 1;

	for (int i = 0; i < length; i++) { //food�� �� ����� ��ġ���� Ȯ��  
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
		switch (key) { //�Է¹��� Ű�� �ľ��ϰ� ����  
		case LEFT: 	case RIGHT: case UP: case DOWN:
			if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) || (dir == DOWN && key != UP))//180ȸ���̵��� �����ϱ� ���� �ʿ�. 
				dir = key;
			key = 0; // Ű���� �����ϴ� �Լ��� reset 
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
	gotoxy(24, 6); printf("Snake Game");
	gotoxy(24, 8); printf("  Start");
	gotoxy(24, 9); printf("  Snake");
	gotoxy(24, 10); printf("  Map");
	gotoxy(24, 11); printf("  Food");
	gotoxy(24, 12); printf("  Exit");
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
			if (y < 12) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, ++y); printf(">");
			} break;
		case ENTER: case SPACE:
			switch (y) {
			case 8: return; break;
			case 9: setSnake(); break;
			case 10: setMap(); break;
			case 11: setFood(); break;
			case 12: exit(0);
			}
			check = true;
		}
		if (check == true)
			break;
	}
}

void setSnake() {
	int x = 34, y = 9;
	bool check = false;
	gotoxy(40, 9); printf("��");
	gotoxy(37, 9); printf("��");
	gotoxy(34, 9); printf("��");
	gotoxy(x, y - 1); printf("��");
	while (true) {
		int k = _getch();
		switch (k) {
		case LEFT:
			if (x > 34) {
				gotoxy(x, y - 1); printf("  ");
				x -= 3;
				gotoxy(x, y - 1); printf("��");
			} break;
		case RIGHT:
			if (x < 40) {
				gotoxy(x, y - 1); printf("  ");
				x += 3;
				gotoxy(x, y - 1); printf("��");
			} break;
		case ENTER: case SPACE:
			switch (x) {
			case 34:
				strcpy(snake, change_word(snake, snake, "��"));
				break;
			case 37:
				strcpy(snake, change_word(snake, snake, "��"));
				break;
			case 40:
				strcpy(snake, change_word(snake, snake, "��"));
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
	gotoxy(40, 10); printf("��");
	gotoxy(37, 10); printf("��");
	gotoxy(34, 10); printf("��");
	gotoxy(x, y - 1); printf("��");
	while (true) {
		int k = _getch();
		switch (k) {
		case LEFT:
			if (x > 34) {
				gotoxy(x, y - 1); printf("  ");
				x -= 3;
				gotoxy(x, y - 1); printf("��");
			} break;
		case RIGHT:
			if (x < 40) {
				gotoxy(x, y - 1); printf("  ");
				x += 3;
				gotoxy(x, y - 1); printf("��");
			} break;
		case ENTER:  case SPACE:
			switch (x) {
			case 34:
				strcpy(wall, change_word(wall, wall, "��"));
				break;
			case 37:
				strcpy(wall, change_word(wall, wall, "��"));
				break;
			case 40:
				strcpy(wall, change_word(wall, wall, "��"));
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
	gotoxy(40, 11); printf("��");
	gotoxy(37, 11); printf("��");
	gotoxy(34, 11); printf("��");
	gotoxy(x, y - 1); printf("��");
	while (true) {
		int k = _getch();
		switch (k) {
		case LEFT:
			if (x > 34) {
				gotoxy(x, y - 1); printf("  ");
				x -= 3;
				gotoxy(x, y - 1); printf("��");
			} break;
		case RIGHT:
			if (x < 40) {
				gotoxy(x, y - 1); printf("  ");
				x += 3;
				gotoxy(x, y - 1); printf("��");
			} break;
		case ENTER:  case SPACE:
			switch (x) {
			case 34:
				strcpy(food, change_word(food, food, "��"));
				break;
			case 37:
				strcpy(food, change_word(food, food, "��"));
				break;
			case 40:
				strcpy(food, change_word(food, food, "��"));
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