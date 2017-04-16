#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
//#include <fstream>
#include <Windows.h>
#include <string>
//#include <vector>
#include <mutex>
#include <chrono>
#include <thread>
#include "Class.h"

//Defined Chars
#define sWin "You have won!"
#define sLose "You have lost..."
#define sTie "The game ended in a tie."

//Key codes
#define topLeft 0x54 //T
#define topMid 0x59 //Y
#define topRight 0x55 //U

#define midLeft 0x47 //G
#define midMid 0x48 //H
#define midRight 0x4A //J

#define lowLeft 0x42 //B
#define lowMid 0x4E //N
#define lowRight 0x4D //M

#define ESC VK_ESCAPE

//X && O
#define X 'X'
#define O 'O'
/*ETY is for Empty*/
#define ETY ' '

//Structs

//Basic Screen

//Precalls 
 void screenLoad();
 void alloc();
 void dealloc();
 void keyboard();
 void debug();
 bool faintCheck(const char C);
 void screenCheck();
 bool horizontalCheck(const char C);
 bool verticalCheck(const char C);
 bool diagonalCheck(const char C);
 void winScreen();
 void keyTrack();
 void tieScreen();

 bool correctKey;
Ai classPtr;

typedef struct DataBase {
	//Map
	std::string Map;
	size_t mapLen;
	bool winBool;
	bool loseBool;
	bool faintBool;
} DataBase;

typedef struct BuffferBase {
	char buff[150];
} BufferBase;

DataBase* DataPtr;
BufferBase* BufferPtr;
std::mutex theLock;

char mapGrid[3][3] = {
	{ ETY, ETY, ETY },
	{ ETY, ETY, ETY },
	{ ETY, ETY, ETY }
};

 void keyboard() {
	/*Every Row*/
	std::thread keys(keyTrack); keys.detach();
}

 void debug() {
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << "Row = " << i << "~||~";
		for (int o = 0; o < 3; o++) {
			std::cout << mapGrid[i][o];
		}
		std::cout << std::endl;
	}
}

 void alloc() {
	DataPtr = new DataBase;
	BufferPtr = new BufferBase;
	DataPtr->winBool = false;
	DataPtr->loseBool = false;
	DataPtr->faintBool = false;
}

 void dealloc() { delete DataPtr; delete BufferPtr; }

 void screenLoad() {
	system("CLS");
	//system("COLOR 09");

	DataPtr->Map = sprintf(BufferPtr->buff,
		"|-----|-----|-----|\n"
		"|  %c  |  %c  |  %c  |\n"
		"|-----|-----|-----|\n"
		"|  %c  |  %c  |  %c  |\n"
		"|-----|-----|-----|\n"
		"|  %c  |  %c  |  %c  |\n"
		"|-----|-----|-----|\n",
		/*Formats*//*Row One*/
		mapGrid[0][0], mapGrid[0][1], mapGrid[0][2],
		/*Row Two*/
		mapGrid[1][0], mapGrid[1][1], mapGrid[1][2],
		/*Row Three*/
		mapGrid[2][0], mapGrid[2][1], mapGrid[2][2]);
	DataPtr->Map = BufferPtr->buff;

	std::cout << DataPtr->Map;
}

 int turnsTaken = 0;
 void keyTrack() {
	//std::lock_guard<std::mutex> lock(theLock);
	while (true) {
		for (int c = 0; c < 256; c++) {
			if (GetAsyncKeyState(c)) {
				theLock.lock();
				correctKey = false;;
				/*Switch statements to check keys*/
				switch (c) {

					/*Exit*/
				case ESC: dealloc(); std::terminate(); exit(0);
					classPtr.dealloc(classPtr.aiData);

					/*Top Row*/
				case topLeft: if (mapGrid[0][0] == ETY) { correctKey = true; mapGrid[0][0] = X; } break;
				case topMid: if (mapGrid[0][1] == ETY) { correctKey = true; mapGrid[0][1] = X; } break;
				case topRight: if (mapGrid[0][2] == ETY) { correctKey = true; mapGrid[0][2] = X; } break;

					/*Mid Row*/
				case midLeft: if (mapGrid[1][0] == ETY) { correctKey = true; mapGrid[1][0] = X; } break;
				case midMid: if (mapGrid[1][1] == ETY) { correctKey = true; mapGrid[1][1] = X; } break;
				case midRight: if (mapGrid[1][2] == ETY) { correctKey = true; mapGrid[1][2] = X; } break;

					/*Bottom Row*/
				case lowLeft: if (mapGrid[2][0] == ETY) { correctKey = true; mapGrid[2][0] = X; } break;
				case lowMid: if (mapGrid[2][1] == ETY) { correctKey = true; mapGrid[2][1] = X; } break;
				case lowRight: if (mapGrid[2][2] == ETY) { correctKey = true; mapGrid[2][2] = X; } break;

				default: correctKey = false; break;
				}
				/*To cause a sick glicth
				type screenLoad(); below this code and
				press H :D*/
				//screenLoad();

				if (correctKey) {
					//std::terminate();
					screenLoad();
					Beep(700, 500);
					turnsTaken++;
					debug();
					screenCheck();
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					classPtr.getBestMove();
					screenLoad();
					Beep(600, 500);
					debug();
					screenCheck();
					theLock.unlock();
				}
				else { theLock.unlock(); }
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

 bool horizontalCheck(const char C) {
	for (int c = 0; c < 3; c++) {
		if (mapGrid[c][0] == C &&
			mapGrid[c][1] == C &&
			mapGrid[c][2] == C) return true;
	}
	return false;
}

 bool verticalCheck(const char C) {
	for (int o = 0; o < 3; o++) {
		if (mapGrid[0][o] == C &&
			mapGrid[1][o] == C &&
			mapGrid[2][o] == C) return true;
	}
	return false;
}

 bool diagonalCheck(const char C) {
	if (mapGrid[0][0] == C &&
		mapGrid[1][1] == C &&
		mapGrid[2][2] == C) return true;
	else if (mapGrid[0][2] == C &&
		mapGrid[1][1] == C &&
		mapGrid[2][0] == C) return true;
	return false;
}

 void winScreen() {
	if (DataPtr->winBool) {
		MessageBoxA(NULL, sWin, "End Game", NULL);
		dealloc(); exit(0);
	} else if (DataPtr->loseBool) {
		MessageBoxA(NULL, sLose, "End Game", NULL);
		dealloc(); exit(0);
	}
}

void tieScreen() {
		 MessageBoxA(NULL, sTie, "End Game", NULL);
		 dealloc(); exit(0);
 }

 void screenCheck() {
	/*Vertical and Horizontal bool*/
	/*Player Check*/
	DataPtr->winBool = horizontalCheck(X);
	winScreen();
	DataPtr->winBool = verticalCheck(X);
	winScreen();
	DataPtr->winBool = diagonalCheck(X);
	winScreen();

	/*Ai Check*/
	DataPtr->loseBool = horizontalCheck(O);
	winScreen();
	DataPtr->loseBool = verticalCheck(O);
	winScreen();
	DataPtr->loseBool = diagonalCheck(O);
	winScreen();

	if (!DataPtr->loseBool && !DataPtr->winBool && turnsTaken > 4)
		tieScreen();
}

 bool Bool;
 bool faintCheck(const char C) {
	Bool = false;
	Bool = horizontalCheck(C);
	if (!Bool) { Bool = diagonalCheck(C); }
	if (!Bool) { Bool = verticalCheck(C); }
	return Bool;
}
#endif