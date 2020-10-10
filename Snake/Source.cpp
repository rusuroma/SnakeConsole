#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h> 

using namespace std;
bool gameOver ;
const int width = 40;//latimea campului
const int length = 20;//lungimea campului
int x, y, fruitX, fruitY, score;//coordonatele  snake si coordonatele  obiectului
int talX[100];//cordonatele dupa x a cozii sarpelui
int talY[100];//cordonatele dupa y, se  pun cordonatele
int ntail;// numarulde  coordonate, se aduna la mancarea unui obiect
enum eDirection{STOP,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void Setup() {
	srand(width);
	gameOver = false; //incepem  jocul
	dir = STOP;//initial  e oprit
	x = width / 2-1;
	y = length / 2-1;// pozitionam la mijlocul  campului  obiectul
	fruitX = rand()%width;//aparitia fructului pe axa x  sa fie  aleatoare
	fruitY = rand()%length;//aparitia fructului pe axa y  sa fie  aleatoare
	score = 0;
}
void Draw() { //desenam campul 
	system("cls");
	for (int i = 0; i < width+1; i++)//partea de sus
		cout << "#";
	cout << endl;

	for (int i = 0; i < length; i++) { //peretii din parti
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == (width - 1)) //conditia pentru desenare
				cout << "#";
			if (i == y && j == x)//plasarea in centru a obiectului
				cout << "S";
			else if (i == fruitY && j == fruitX)//plaarea pe harta a fructului
				cout << "f";
			else {
				bool print = false;
				for (int k = 0; k < ntail; k++) {
					if (talX[k] == j && talY[k] == i) {
						print = true;
						cout << "o";
					}
			}
				if(!print)
				cout << " ";
			}
		}
		cout << endl;
		
	}
	
	for (int i = 0; i < width+1; i++) //partea de jos
		cout << "#";
	cout << endl;
	cout << "score= " << score;
}

void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX=talX[0];//pozitia precedenta  pe x
	int prevY = talY[0];//pozitia precedenta  pe y
	int prev2X,  prev2Y;
	talX[0] = x;
	talY[0] = y;
	for (int i = 1; i < ntail; i++) {
		prev2X = talX[i];
		prev2Y = talY[i];
		talX[i] = prevX;
		talY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
	case RIGHT:
		x++;
		break;
	case LEFT:
		x=x-1;
		break;
	case UP:
		y=y-1;
		break;
	case DOWN:
		y++;
		break;
	
	}
	
	
	if (x == fruitX && y == fruitY) {
		score += 1;
		fruitX = rand() % width;//aparitia fructului pe axa x  sa fie  aleatoare
		fruitY = rand() % length;
		ntail++;
	}
	
}

int  main(){
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100); //sleep(10);
	}
	return 0;
}