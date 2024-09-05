#include "King.h"
#include "Field.h"
#include <math.h>



King::King(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {
	
	castlingLeft = false;
	castlingRight = false;
	castlingVec = { firstPos+CastlingLeft, firstPos +CastlingRight };			//Castling pos
	castlingFig = { firstPos +CastleLeft, firstPos +CastleRight};			//Initial rook pos
	castleNewPos = { firstPos + CastleNewPosLeft, firstPos + CastleNewPosRight };			//New Rook pos
	castlingToCastle[castlingVec.at(0)] = std::vector<int>{castlingFig.at(0), castleNewPos.at(0) };
	castlingToCastle[castlingVec.at(1)] = std::vector<int> {castlingFig.at(1), castleNewPos.at(1)};
	pointsForFigure = KingP;
	if (sideColor) 	def("Textures/king.png");
	else def("Textures/kingWhite.png");
}


std::vector<int> King::getRook(int castlingPos) {
	return castlingToCastle.at(castlingPos);
}


std::vector<int> King::getChecks() {
	return checkList;
}

void King::setCastlingLeft(bool state)										//REFACTOR THE TWO FUNCTIONS BELOW INTO A SINGLE ONE
{
	if (state) {
		if (sideColor) {
			castlingVec.at(1) = (firstPos + CastlingRight);
		}
		else {
			castlingVec.at(0) = firstPos + CastlingLeft;
		}
	}
	else {
		if (sideColor) {
			castlingVec.at(1) = (-1);
		}
		else {
			castlingVec.at(0) = -1;
		}
	}
	
	castlingLeft = state;
}

void King::setCastlingRight(bool state)
{
	if (state) {
		if (sideColor) {
			castlingVec.at(0) = firstPos + CastlingLeft;
		}
		else {
			castlingVec.at(1) = (firstPos + CastlingRight);
		}
	}
	else {
		if (sideColor) {
			castlingVec.at(0) = -1;
		}
		else {
			castlingVec.at(1) = (-1);
		}
	}

	castlingRight = state;
}

void King::setCastling() {
	castlingLeft = false;
	castlingRight = false;
	castlingVec.clear();
	castlingVec = {-1,-1};
}

bool King::diagPosEnemy(int thread, int kingPos) {
	if (abs(thread - kingPos) % 7 == 0 || abs(thread - kingPos) % 9 == 0) return true;
	return false;
}bool King::XYPosEnemy(int thread, int kingPos) {
	if ( thread / 8 == kingPos / 8  || thread % 8 == kingPos % 8) return true;
	return false;
}

bool King::getFirst() {
	return firstTime; 
}

void King::setFirstFalse() {
	firstTime = false;
}

void King::castlingCheck(Field *field) {			//Checks whether the row, where the king and the rooks are, is empty between the king and the left and right rooks 
	setCastlingLeft(true);
	setCastlingRight(true);	
	for (int i = castlingVec.at(sideColor); i != pos; i+= (sideColor ? -1 : 1)) {
		if (field->isTaken(i) != -1) {
			setCastlingLeft(false);
			break;
		}
	}
	for (int i = castlingVec.at(sideColor ? 0 : 1); i != pos; i += (sideColor ? 1 : -1)) {
		if (field->isTaken(i) != -1) {
			setCastlingRight(false);
			break;
		}
	}

}

void King::updateNext(Field* field) {
	this->checkList.clear();
	horizMove(field, pos, sideColor);
	diagMove(field, pos, sideColor);
	for (int i = 0; i < active.size();) {	//Kings diagonal move is only one square, so we erase everything, //REFACTOR
		if (abs(active.at(i) / 8 - pos / 8) > 1 || abs(active.at(i) % 8 - pos % 8) > 1) {
			active.erase(active.begin() + i);
		}
		else i++;
	}
	for (int i = 0; i < attackPos.size();) {
		if (abs(attackPos.at(i) / 8 - pos / 8) > 1 || abs(attackPos.at(i) % 8 - pos % 8) > 1) {
			checkList.push_back(*(attackPos.begin() + i));
			attackPos.erase(attackPos.begin() + i);
		}
		else {
			checkList.push_back(*(attackPos.begin() + i));
			i++;
		}
	}
	if(firstTime)castlingCheck(field);
	
}

void King::lookUpFill()
{
}

std::vector<int> King::getCastlingVec() {
	return castlingVec;
}

bool King::getCastlingBool() {
	return castlingLeft || castlingRight;
}