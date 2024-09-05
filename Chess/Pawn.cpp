#include "Pawn.h"
#include "Figure.h"


int Pawn::pawnMovesWhite = 0;
int Pawn::pawnMovesBlack = 0;
int Pawn::toAttackWhite[2] = {0,0};
int Pawn::toAttackBlack[2] = { 0,0 };
int Pawn::limitWhite = 0;
int Pawn::limitBlack = 0;

std::vector<std::vector<int>> Pawn::moveLookUpBlack = {};
std::vector<std::vector<int>> Pawn::moveLookUpWhite = {};

Pawn::Pawn(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	promote = false;
	pointsForFigure = PawnP; 
	def("Textures/pawn" + std::string(sideColor ? ".png" : "White.png"));

	

}


void definingHelp(int &pawnMoves, int newPawnMove, int* toAttack, int toA1, int toA2, int &limit, int newLimit) {
	pawnMoves= newPawnMove;
	toAttack[0] = toA1;
	toAttack[1] = toA2;
	limit = newLimit;
}

void Pawn::define() {
	definingHelp(pawnMovesWhite, UP, toAttackWhite, diagUpRIGHT, diagUpLEFT, limitWhite, limitDOWN);
	definingHelp(pawnMovesBlack, DOWN, toAttackBlack, diagBottomRIGHT, diagBottomLEFT, limitBlack, limitUP);
}


bool Pawn::checkHit(int hitPos, int objPos) {
	if (abs(hitPos - objPos) <= 9) {
		if (sideColor) return hitPos > objPos;
		else return hitPos < objPos;
	}
	return false;
}

bool Pawn::checkPromotion() {
	if ((sideColor && pos / 8 == 0) || (!sideColor && pos / 8 == 7)) 
		promote = true;
	return promote;
}


void Pawn::lookUpFillHelper(std::vector<std::vector<int>> &moveLookUp, const int &pawnMoves, const int* toAttack, const int& limit, int side) {
	std::vector<int> moveVec = {};
	for (int i = 0; i < SIZE; i++) {
		moveVec.clear();
		moveVec.push_back(i + pawnMoves != limit ? i + pawnMoves : -1);
		if (!lB(i) && ((side && !tB(i)) || (!side && !bB(i)))) {
			moveVec.push_back(i + toAttack[0]);
		}
		if (!rB(i) && ((side && !tB(i)) || (!side && !bB(i)))) {
			moveVec.push_back(i + toAttack[1]);
		}
		moveLookUp.push_back(moveVec);
	}
} 

void Pawn::lookUpFill() {
	define();
	lookUpFillHelper(moveLookUpWhite, pawnMovesWhite, toAttackWhite, limitWhite, 0);
	lookUpFillHelper(moveLookUpBlack, pawnMovesBlack, toAttackBlack, limitBlack, 1);

	
} 

void Pawn::updateNext(Field *field) {			
	if (!checkPromotion()) {
		std::vector<std::vector<int>> moveLookUp = (sideColor ? moveLookUpBlack : moveLookUpWhite);
		int movePawn = sideColor ? pawnMovesBlack : pawnMovesWhite;
		int index = 0; 
		if (field->isTaken(moveLookUp.at(pos).at(index))==-1) {
			active.push_back(moveLookUp.at(pos).at(index));
			if (firstTime && field->isTaken(moveLookUp.at(pos).at(index)+movePawn) == -1) {
				active.push_back(moveLookUp.at(pos).at(index) + movePawn);
			}
			
		}
		index++;
		for(; index < moveLookUp.at(pos).size();index++)
		if (index < moveLookUp.at(pos).size()){
			int attack = field->isTaken(moveLookUp.at(pos).at(index));
			if(attack  != sideColor && attack  != -1 )
				attackPos.push_back(moveLookUp.at(pos).at(index));

		}
	}
}

bool Pawn::checkIfEnPass() {
	int pawnMove = sideColor ? pawnMovesBlack : pawnMovesWhite;
	if (firstTime && pos == firstPos + 2 * pawnMove) {
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

void Pawn::clearEnPass() {
	enPass = -1; 
}