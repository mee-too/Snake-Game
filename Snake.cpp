#include <iostream>
using namespace std;

//initialize variables
bool snakeGame;
const int width = 25;
const int height = 25;
int x, y;
int targetX, targetY;
int score;
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;

void game_Setup() {
	snakeGame = true;
	dir = STOP;
	x = rand() % width;
	y = rand() % height;
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
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;
}

void game_Input() {

}

void game_Program() {

}

int main() {
	game_Setup();
	game_Window();
	game_Input();
	game_Program();

}