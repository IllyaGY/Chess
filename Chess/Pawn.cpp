#include "Pawn.h"
#include "Figure.h"



Pawn::Pawn(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	pointsForFigure = PawnP; 
	firstTime = cubePos;  //To compare it if the pawn still can make a two cube move
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




void Pawn::updateNext(Field *field) {			
	if (pos + pawnMoves != limit && !field->isTaken(pos + pawnMoves)) {
		active.push_back(pos + pawnMoves);
		if (firstTime == pos && pos + 2* pawnMoves != limit && !field->isTaken(pos + 2 * pawnMoves)) {
			active.push_back(pos + 2 * pawnMoves);
		}
	}
	if (!lB(pos) && ((sideColor && !tB(pos)) || (!sideColor && !bB(pos)))) {
		attackPos.push_back(pos + toAttack[0]);
	}
	if (!rB(pos) && ((sideColor && !tB(pos)) || (!sideColor && !bB(pos)))) {
			attackPos.push_back(pos + toAttack[1]);

	}	
}

	
