#pragma once
#include "Figure.h"

enum Castling {
	CastleLeft = -4,
	CastleRight = 3,
	CastlingLeft = -3,
	CastlingRight = 2,
	CastleNewPosLeft = -2,
	CastleNewPosRight = 1,

};


class King :
    public Figure
{
public:


	std::map<int, std::vector<int>> castlingToCastle{ };

	std::vector<int> castlingVec{};
	std::vector<int> castlingFig{}; 
	std::vector<int> castleNewPos{}; 
	std::vector<int> checkList{}; 

	bool castlingLeft;
	bool castlingRight;
	bool castling;

	King(float x, float y, int sideColor, int cubePos, float size);

	std::vector<int> getRook(int castlingPos);


	std::vector<int> getChecks();

	void setCastling();
	void setCastlingLeft(bool);
	void setCastlingRight(bool);

	bool XYPosEnemy(int thread, int kingPos);

	bool getFirst();

	bool diagPosEnemy(int thread, int kingPos);

	void setFirstFalse();

	void castlingCheck(Field* field);

	void updateNext(Field* field) override;
	static void lookUpFill();

	std::vector<int> getCastlingVec();
	bool getCastlingBool(); 



};

