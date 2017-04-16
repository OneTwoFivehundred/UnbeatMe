#include "Class.h"
#include "Main.h"
#include <iostream>
#include <stdio.h>
#include <random>
#include <ctime>

Ai::Ai() {
	//ctor
	alloc();
	keyboard();
	screenLoad();
	debug();
	aiData->outcome = 0;
	aiData->otherOutcome = 0;
	aiData->bestChoice = false;
	std::cout << "\n\nAi class has been created";
	//std::cout << clock() * time(0);
	time_t x = clock() * time(0);
	srand(x);
	//std::cout << std::endl << x;
}

void Ai::getBestMove() {
	std::cout << mapGrid[1][1];
	bestX = 0;
	bestY = 0;
	aiData->outcome = 0;
	aiData->otherOutcome = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (aiData->outcome == 0 || aiData->otherOutcome == 0) {
				isNull(x, y); }
		}
	}
	if (aiData->outcome != 0) { mapGrid[bestY][bestX] = O; }
	else if (aiData->otherOutcome != 0) { mapGrid[secondBestY][secondBestX] = O; }
	else mapGrid[defaultY][defaultX] = O;
}

void Ai::isNull(int x, int y) {
	if (mapGrid[y][x] == ETY) {
		mapGrid[y][x] = O;
		aiData->bestChoice = faintCheck(O);
		if (aiData->bestChoice) { mapGrid[y][x] = ETY;
		bestX = x; bestY = y; aiData->outcome = 1; return;
		}
		mapGrid[y][x] = X;
		aiData->bestChoice = faintCheck(X);
		if (aiData->bestChoice) { mapGrid[y][x] = ETY; 
		secondBestX = x; secondBestY = y; aiData->otherOutcome = 1; return;
		}
		mapGrid[y][x] = ETY;
		defaultX = x;
		defaultY = y;
		do {
			defaultX = (rand() % 3);
			defaultY = (rand() % 3);
		} while (mapGrid[defaultY][defaultX] != ETY); 
		return;
	}
}

Ai::~Ai() {
	//dtor
	std::cout << "\n\nAi class has been deleted";
}

void Ai::dealloc(Ai::DataBase* ptr) {
	delete ptr;
}