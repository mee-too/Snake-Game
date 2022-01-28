#include <iostream>
#include<windows.h>
using namespace std;

//initialize variables
bool snakeGame;
enum game {MAIN, START};
game mode;
int menu;
const int width = 25;
const int height = 25;
//user variables
int x, y, spd = 1;
int tailX[100], tailY[100],tailLength;
//Tail Coordinates
int fposX, fposY, sposX, sposY;
//target variables
int targetX, targetY;
//game variables
int score;
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;

void game_Over() {
	
	tailLength = 0;
	score = 0;
	mode = MAIN;
}

void game_Setup() {
	snakeGame = true;
	mode = MAIN;
}

void main_Menu() {
	system("cls");
	cout << "Welcome to the Main Menu." << endl;

	if (menu == 0){
		cout << ">>Play the Game." << endl;
		cout << "Options." << endl;
		cout << "Exit Game." << endl;
	}
	else if (menu == 1) {
		cout << "Play the Game." << endl;
		cout << ">>Options." << endl;
		cout << "Exit Game." << endl;
	}
	else if (menu == 2) {
		cout << "Play the Game." << endl;
		cout << "Options." << endl;
		cout << ">>Exit Game." << endl;
	}

	if (GetAsyncKeyState(VK_RETURN)){
		switch (menu){
		case 0:
			mode = START;
			break;

		case 1:
			cout << "These are the options" << endl;
			break;

		case 2:
			exit(0);
			break;

		}
	}
	else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')){
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
		dir = STOP;
		menu++;
		Sleep(50);
	}
	else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
		dir = STOP;
		menu--;
		Sleep(50);
	}

	if (menu <= -1) {
		menu = 2;
	}
	else if (menu >= 3) {
		menu = 0;
	}

	cout << menu;
	
}

void normal_Setup() {

	
	//Starting Direction not moving
	dir = STOP;

	//setting up player
	x = rand() % width;
	y = rand() % height;

	//setting up target
	targetX = rand() % width;
	targetY = rand() % height;
	//error when target and player are on top
	while (x == targetX && y == targetY) {
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}
	
	
	score = 0;
}

void game_Window() {
	system("cls");
	//top border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}


	//body
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "*";
			}
			else if (i == y && j == x) {
				cout << "S";
			}
			else if(i == targetY && j== targetX){
				cout << "a";
			}
			else {
				bool tail = false;
				for (int k = 0; k < tailLength; k++)
				{
					if (j == tailX[k] && i == tailY[k]) {
						cout << "s";
						tail = true;
					}
				}
				if (!tail)
				{
					cout << " ";
				}
			}
			
		}
		cout << endl;
	}


	//bottom border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;
	//Display Score
	cout << "Score:" << score;
}

void game_Input() {
	if (mode == START) {
		if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && dir != RIGHT)
		{
			dir = LEFT;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && dir != LEFT) {
			dir = RIGHT;
		}
		else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && dir != UP) {
			dir = DOWN;
		}
		else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && dir != DOWN) {
			dir = UP;
		}
		else if (GetAsyncKeyState(VK_RETURN)){
			return;
		}

	}




	//using <conio.h> and wasd
	//if (_kbhit()) {
	//	switch (_getch()) {
	//		case 'a':                     //moves snake to the left
	//			if (dir != RIGHT) {
	//				dir = LEFT;
	//			}
	//			break;
	//		case 's':                     //moves snake to the bottom
	//			if (dir != UP) {
	//				dir = DOWN;
	//			}
	//			break;
	//		case 'd':                    //moves snake to the right
	//			if (dir != LEFT) {
	//				dir = RIGHT;
	//			}
	//			break;
	//		case 'w':                    //moves snake to the top
	//			if (dir != DOWN) {
	//				dir = UP;
	//			}
	//			break;
	//		case '0':
	//			snakeGame = false;
	//			break;
	//	}
	//}
}

void game_Program() {

	//Tail
	fposX = tailX[0]; //head is first position which is 0
	fposY = tailY[0]; //head is first position which is 0
	tailX[0] = x; // head of the tail is the same as the x of the user
	tailY[0] = y; // head of the tail is the same as the y of the user

	for (int i = 1; i < tailLength; i++)
	{
		sposX = tailX[i];
		sposY = tailY[i];// when you move the second position tail takes the previous first position place or whatever position it is.
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
		//error of target in tail 
		while (tailX[i] == targetX && tailY[i] == targetY) {
			targetX = rand() % width;
			targetY = rand() % height;
		}
	}

	//move snake
	switch (dir) {
	case LEFT:
		x -= spd;
		break;
	case UP:
		y -= spd;
		break;
	case DOWN:
		y += spd;
		break;
	case RIGHT:
		x += spd;
		break;
	}

	//Snake Border hit and die
	if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1) {
		game_Over();
	}

	//Snake Tail Hit
	for(int i = 0; i < tailLength; i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			game_Over();
		}
	}

	//Snake hits Target
	if (x == targetX && y == targetY)
	{
		targetX = rand() % width;
		targetY = rand() % height;
		score++;
		tailLength++;
	}
	

}

int main() {
	
	game_Setup();//outside of the while loop so that we set the game once 
	while (snakeGame == true) {
		if (mode == MAIN){
			main_Menu();//run main menu until start game
		}
		else if (mode == START) {

			normal_Setup();
			while (mode == START) {
				game_Window();
				game_Input();
				game_Program();
				Sleep(25);
			}
		}
	}
}