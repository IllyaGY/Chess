#include "Pawn.h"
#include "Figure.h"



Pawn::Pawn(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {


	pointsForFigure = PawnP; 
	if(sideColor) def(DOWN, diagBottomRIGHT, diagBottomLEFT, limitUP, "Textures/pawn.png");
	else def(UP, diagUpRIGHT, diagUpLEFT, limitDOWN, "Textures/pawnWhite.png");
	

}


void Pawn::def(int pawnMoves, int toA1, int toA2, int limit, std::string texturePath) {
	this->pawnMoves = pawnMoves;
	this->toAttack[0] = toA1;
	this->toAttack[1] = toA2;
	this->limit = limit;
	Figure::def(texturePath);
}


bool Pawn::checkHit(int hitPos, int objPos) {
	if (abs(hitPos - objPos) <= 9) {
		if (sideColor) return hitPos > objPos;
		else return hitPos < objPos;
	}
	return false;
}

void Pawn::updateNext(Field *field) {			
	if (pos + pawnMoves != limit && field->isTaken(pos + pawnMoves)==-1) {
		active.push_back(pos + pawnMoves);
		if (firstPos == pos && field->isTaken(pos + 2 * pawnMoves)==-1) {
			active.push_back(pos + 2 * pawnMoves);
		}
	}
	if (!lB(pos) && ((sideColor && !tB(pos)) || (!sideColor && !bB(pos)))) {
		if(field->isTaken(pos + toAttack[0]) != sideColor) attackPos.push_back(pos + toAttack[0]);
	}
	if (!rB(pos) && ((sideColor && !tB(pos)) || (!sideColor && !bB(pos)))) {
		if (field->isTaken(pos + toAttack[1]) != sideColor) attackPos.push_back(pos + toAttack[1]);

	}	
}

bool Pawn::checkIfEnPass() {
	if (firstTime && pos == firstPos + 2 * pawnMoves) {
		return true;
		
	}
	return false;

}

void Pawn::passToEn(int enPos) {
	enPass = enPos;
}


int Pawn::getEnPass() {
	return enPass;
}

void Pawn::clearElPass() {
	enPass = -1; 
}