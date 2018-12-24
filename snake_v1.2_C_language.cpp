#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctime>
#include<time.h>
#include<windows.h>

const int H = 19, W = 43;
unsigned char playfield[H][W];
int snake_mv = 1;
int pts = 0;
short go = 0;
short lvl = 1;
int lenght = 2;
int body_x[150], body_y[150];
int fps = 450;

void set0(void) {
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Initialize game zone
void init_gzone(void) {
	//system("cls");
	for (int j = 0; j < H; j++) {
		for (int i = 0; i < W; i++) {
			playfield[j][i] = ' ';
		}
	}
}

//Level choose
void lvl_choose(void) {

	printf("                    CHOOSE LEVEL \n");
	printf("          Press 1 for: Level I. Classic  \n ");
	printf("         Press 2 for: Level II. Box     \n ");
	printf("         Press 3 for: Level III. Blocks \n ");
	lvl = _getch();
	if (lvl == '1') lvl = 1;
	if (lvl == '2') lvl = 2;
	if (lvl == '3') lvl = 3;
}

//Difficulty choose
void dif_choose(void) {

	printf("                    CHOOSE DIFFICULTY \n");
	printf("                    Press 1 for: EASY    \n ");
	printf("                   Press 2 for: NORMAL  \n ");
	printf("                   Press 3 for: HARD   \ \n ");
	int cmd = _getch();
	switch (cmd) {
	case '1': 
		fps = 350;
		break;
	case '2': 
		fps = 220;
		break;
	case '3': 
		fps = 150;
		break;
	}
}

//Menu
void menu(void) {
	for (int i = 0; i < W + 7; i++) { //Draw top wall
		putchar(177);
	}
	putchar('\n');
	printf("  _____ ____  _  __ _____             _        \n"); //FONT - Ivrit / http://patorjk.com
	printf(" |_   _|  _ \\| |/ // ____|           | |       \n");
	printf("   | | | |_) | ' /| (___  _ __   __ _| | _____ \n");
	printf("   | | |  _ <|  <  \\___ \\| '_ \\ / _` | |/ / _ \\'\n");
	printf("  _| |_| |_) | . \\ ____) | | | | (_| |   |  __/\n");
	printf(" |_____|____/|_|\\_|_____/|_| |_|\\__,_|_|\\_\\___|\n");
	putchar('\n');
	printf("   Group: 13558/5                      Ver. 1.2 \n");
	putchar('\n');
	for (int i = W + 7; i; i--) { // Draw bottom wall
		putchar(177);
	}
	putchar('\n');
}

//Redraw table
void redraw_table(void) {
	for (int i = 0; i < W + 2; i++) { //Draw top wall
		putchar(177);
	}
	putchar('\n');

	for (int j = 0; j < H; j++) { // Draw field
		putchar(177); // Draw side walls
		for (int i = 0; i < W; i++) {  //Draw game zone
			putchar(playfield[j][i]);
		}
		putchar(177); // Side wall
		putchar('\n');
	}
	for (int i = W + 2; i; i--) { // Draw bottom wall
		putchar(177);
	}
	putchar('\n');
	printf(" Level: %i || Point: %i \n", lvl, pts*100);
	printf(" P to pause || Q to quit \n");
}

//Block generator
void gen_block(int amount) {
	srand(time(NULL));
	//int size = rand() % 10 + 1;
	//int size = 10;

	for (int a = 0; a < amount; a++) {
		//srand(time(NULL));
		int size = rand() % 30 + 3;
		//int size = 50;
		
		start:
		int i = rand() % 16 + 3;
		if (i <= 11 && i>=9) {
			goto start;
		}
		int j = rand() % 40 + 3;
		if (j <= 23 && j >= 20) {
			goto start;
		}
		playfield[i][j] = 219;

		for (int q = 0; q <= size; q++) {
			//srand(time(NULL));
			int dec = rand() % 2;  //Decision for 'i' or 'j'
								   //printf("%i = %i = %i \n", a, q, dec);
			int dec2 = rand() % 2; //Decision for '+' or '-'
								   //printf("%i = %i = %i \n", a, q, dec2);
			if (dec == 0) { //For i
				if (dec2 == 0) { //For +
					if (playfield[i + 1][j] == ' ' && playfield[i+2][j] == ' ' && playfield[i + 1][j+1] == ' ' && playfield[i + 1][j-1] == ' ' && i+1!=17 ) {
						playfield[i + 1][j] = 219;
						i++;
					}
				}
				else { //For -
					if (playfield[i - 1][j] == ' ' && playfield[i - 2][j] == ' ' && playfield[i + 1][j+1] == ' ' && playfield[i + 1][j-1] == ' ' && i-1!=1) {
						playfield[i - 1][j] = 219;
						i--;
					}
				}
			}
			else { //For j
				if (dec2 == 0) { //For +
					if (playfield[i][j + 1] == ' ' && playfield[i][j+2] == ' ' && playfield[i + 1][j+1] == ' '  && playfield[i - 1][j + 1] == ' ' && j+1!=41) {
						playfield[i][j + 1] = 219;
						j++;
					}
				}
				else { //For -
					if (playfield[i][j - 1] == ' ' && playfield[i][j - 2] == ' ' && playfield[i + 1][j - 1] == ' '  && playfield[i - 1][j - 1] && j-1!=1) {
						playfield[i][j - 1] = 219;
						j--;
					}
				}
			}
		}
	}
}

//Apple generator
void gen_apple(int n) {
	srand(time(NULL));
	int amount = 0;
	while (amount < n) {
		int x = rand() % 18 + 1;
		int y = rand() % 42 + 1;
		if (playfield[x][y] == ' ' && playfield[x + 1][y] == ' ' && playfield[x - 1][y] == ' ' && playfield[x][y + 1] == ' ' && playfield[x][y - 1] == ' ') {
			playfield[x][y] = 'o';
			amount++;
		}
	}
}

//Check
int check(int x, int y) {
	char j = playfield[x][y];
	if (playfield[x][y] == 'o') {
		return 1;
	}
	else if (playfield[x][y] == 219 || playfield[x][y] == 186 || playfield[x][y] == 201 || playfield[x][y] == 187 || playfield[x][y] == 205 || playfield[x][y] == 200 || playfield[x][y] == '@') {
		return 2;
	}
}

//Clear part of snake
void snake_clear(void) {
	for (int i = 1; i <= lenght; ++i) {
		playfield[body_x[i]][body_y[i]] = ' ';
	}
}

//Tail moving 
void tail(void) {
	for (int i = lenght; i >= 2; i--) {
		body_x[i] = body_x[i - 1];
		body_y[i] = body_y[i - 1];
	}
}

//Draw snake tail
void draw_tail(void) {
	for (int i = 2; i <= lenght; i++)
		playfield[body_x[i]][body_y[i]] = '@';
}

//Snake moving
void move_head(int i) {
	snake_clear();
	tail();
	draw_tail();
	if (i == 1) {
		if (check(body_x[1] - 1, body_y[1]) == 1) {
			if (fps == 350) pts++;
			else if (fps == 220) pts = pts + 2;
			else if (fps == 150) pts = pts + 3;
			lenght++;
			gen_apple(1);
		}
		if (check(body_x[1] - 1, body_y[1]) == 2) {
			go = 1;
		}

		if (body_x[1] == 0) {
			if (lvl == 1 || lvl == 3) {
				body_x[1] = H-1;
			}
			else go = 1;
		}
		else body_x[1]--;
		playfield[body_x[1]][body_y[1]] = '^';
		snake_mv = 1;
	}
	if (i == 2) {
		if (check(body_x[1], body_y[1] +1) == 1) {
			if (fps == 350) pts++;
			else if (fps == 220) pts = pts + 2;
			else if (fps == 150) pts = pts + 3;
			lenght++;
			gen_apple(1);
		}
		if (check(body_x[1], body_y[1] + 1) == 2) {
			go = 1;
		}
		if (body_y[1] == W-1) {
			if (lvl == 1 || lvl == 3) {
				body_y[1] = 0;
			}
			else go = 1;
		}
		else body_y[1]++;
		playfield[body_x[1]][body_y[1]] = '>';
		snake_mv = 2;
	}
	if (i == 3) {
		if (check(body_x[1] + 1, body_y[1]) == 1) {
			if (fps == 350) pts++;
			else if (fps == 220) pts = pts + 2;
			else if (fps == 150) pts = pts + 3;
			lenght++;
			gen_apple(1);
		}
		if (check(body_x[1] + 1, body_y[1]) == 2) {
			go = 1;
		}
		if (body_x[1] == H-1) {
			if (lvl == 1 || lvl == 3) {
				body_x[1] = 0;
			}
			else go = 1;
		}
		else body_x[1]++;
		playfield[body_x[1]][body_y[1]] = 'v';
		snake_mv = 3;
	}
	if (i == 4) {
		if (check(body_x[1], body_y[1] -1) == 1) {
			if (fps == 350) pts++;
			else if (fps == 220) pts = pts + 2;
			else if (fps == 150) pts = pts + 3;
			lenght++;
			gen_apple(1);
		}
		if (check(body_x[1], body_y[1]-1) == 2) {
			go = 1;
		}
		if (body_y[1] == 1) {
			if (lvl == 1 || lvl == 3) {
				body_y[1] = W-1;
			}
			else go = 1;
		}
		else body_y[1]--;
		playfield[body_x[1]][body_y[1]] = '<';
		snake_mv = 4;
	}
}

//Pause
void pause(void) {
	system("cls");
	for (int i = 0; i < W + 7; i++) { //Draw top wall
		putchar(177);
	}
	putchar('\n');
	putchar('\n');

	printf("                  GAME PAUSED \n");
	
	printf("                     Press: \n");
	putchar('\n');
	printf("    q to 'game over'         p to unpause \n");

	putchar('\n');
	menu();
	putchar('\n');

	char cmd = _getch();
	switch (cmd) {
	case 'q':
		go = 1;
		break;
	}
	system("cls");
	//set0();
}

//Game over
short game_over() {
	go = 1;
	system("cls");

	for (int i = 0; i < W + 7; i++) { //Draw top wall
		putchar(177);
	}
	putchar('\n');
	putchar('\n');

	printf("                   GAME OVER \n");
	printf("                  Points: %i \n", pts*100);
	putchar('\n');
	printf("                    Press: \n");
	printf("        q to quit           r to restart \n");
	
	putchar('\n');
	menu();
	putchar('\n');
	ask:
	char cmd;
	int i;
	cmd = _getch();
	switch (cmd) {
	case 'q':
		i = 0;
		break;
	case 'r':
		i = 1;
		break;
	default:
		goto ask;
	}
	return i;
}

//Controll
void ctrl(void) {
	char cmd;

	cmd = _getch();

	switch (cmd) {
	case 'w':
		if (snake_mv != 3) {
			move_head(1);
		}
		break;
	case 72:
		if (snake_mv != 3) {
			move_head(1);
		}
		break;
	case 'd':
		if (snake_mv != 4) {
			move_head(2);
		}
		break;
	case 77:
		if (snake_mv != 4) {
			move_head(2);
		}
		break;
	case 's':
		if (snake_mv != 1) {
			move_head(3);
		}
		break;
	case 80:
		if (snake_mv != 1) {
			move_head(3);
		}
		break;
	case 'a':
		if (snake_mv != 2) {
			move_head(4);
		}
		break;
	case 75:
		if (snake_mv != 2) {
			move_head(4);
		}
		break;
	
	case 'q':
		go = 1;
		break;
	case 'p':
		pause();
		break;
	default:
		move_head(snake_mv);
		break;
	}
}

//Level 1
void level1(void) {
	lvl = 1;
	gen_apple(1);
}

//Level 2
void level2(void) {
	playfield[1][1] = 201; 
	playfield[1][W - 2] = 187; 
	for (int j = 2; j != W - 2; j++) {
		playfield[1][j] = 205;
	}
	for (int i = 2; i != H - 2; i++) {
		playfield[i][1] = 186;
		playfield[i][W - 2] = 186;
	}
	playfield[H - 2][1] = 200;
	playfield[H - 2][W - 2] = 188;
	for (int q = 2; q != W - 2; q++) {
		playfield[H - 2][q] = 205; 
	}
	gen_apple(1);
}

//Level 3
void level3(void) {
	gen_block(10);
	gen_apple(1);
}

//Start message
void start_msg(void) {
	system("cls");
	menu();
	putchar('\n');

	printf("                     Level: %i \n", lvl);
	if (fps == 350) {
		printf("                 Difficulty: Easy \n");
	}
	if (fps == 220) {
		printf("                Difficulty: Normal \n");
	}
	if (fps == 150) {
		printf("                Difficulty: Hard \n");
	}
	putchar('\n');
	printf("            Use WASD to controll snake \n");
	printf(" Make sure that you set the English keyboard layout \n");
	putchar('\n');
	printf("             Press any key to start... \n");

	putchar('\n');
	for (int i = 0; i < W + 7; i++) { //Draw top wall
		putchar(177);
	}
	putchar('\n');

	_getch();
	system("cls");
}

//Initialization of snake head
void draw_snake(void) {
	body_x[1] = 9;
	body_y[1] = 21;
	playfield[body_x[1]][body_y[1]] = '^';
}

void main(void) {
	start:
	go = 0;
	snake_mv = 1;

	init_gzone();
	menu();
	lvl_choose();
	system("cls");
	menu();
	dif_choose();
	start_msg();
	
	init_gzone();
	system("cls");
	
	if (lvl == 1) level1();
	else if (lvl == 2) level2();
	else if (lvl == 3) level3();
	
	draw_snake();

	while (true) {
		set0();

		if (_kbhit() != 0) {
			ctrl();
		}
		else move_head(snake_mv);

		redraw_table();
		if (go == 1) {
			system("cls");
			if (game_over() == 1) {
				system("cls");
				goto start;
			}
			else {
				exit(0);
			}
		}
		Sleep(fps);
	}
	_getch();
}