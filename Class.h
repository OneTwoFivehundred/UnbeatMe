#pragma once
#ifndef CLASS_H
#define CLASS_H

class Ai {
public:
	/*ctor*/ Ai();
	/*dtor*/ ~Ai();

	//Typedef Struct(s)
	typedef struct DataBase {
		//Wins In A Row
		bool takeTurn;
		int outcome;
		bool bestChoice;
		int otherOutcome;
	};
	int defaultX;
	int defaultY;
	int bestX;
	int bestY;
	int secondBestX;
	int secondBestY;
	void getBestMove();
	void isNull(int x, int y);
	void dealloc(Ai::DataBase* ptr);
	Ai::DataBase* aiData = new Ai::DataBase;

private:

protected:

};



#endif