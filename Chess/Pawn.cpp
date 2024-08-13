#include "Pawn.h"
#include "Figure.h"

Pawn::Pawn(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	
	firstTime = cubePos; 

	if(sideColor) def(-8, -9, -7, -1, "Textures/pawn.png");


	else def(8, 7, 9, 64, "Textures/pawnWhite.png");
	

}


void Pawn::def(int toGo, int toA1, int toA2, int limit, std::string texturePath) {
	this->toGo = toGo;
	toAttack[0] = toA1;
	toAttack[1] = toA2;
	limit = 64;
	if (!textureForm.loadFromFile(texturePath))
	if (!textureForm.create(size, size))
		throw std::invalid_argument("BLARGH");
	figure.setTexture(&textureForm);
}




void Pawn::updateNext(int pos, Field *field) {			
	this->pos = pos; 
	active.clear();
	attackPos.clear(); 
	if (pos + toGo != limit && !field->isTaken(pos + toGo)) {
		active.push_back(pos + toGo);
		if (firstTime == pos && pos + 2*toGo != limit && !field->isTaken(pos + 2 * toGo)) {
			active.push_back(pos + 2 * toGo);
		}
	}
	if (!lB(pos) && ((sideColor && !tB(pos)) || (!sideColor && !bB(pos)))) {
		attackPos.push_back(pos + toAttack[0]);
	}
	if (!rB(pos) && ((sideColor && !tB(pos)) || (!sideColor && !bB(pos)))) {
			attackPos.push_back(pos + toAttack[1]);

	}	
}

	
void Pawn::figureAction(Field *field, int action){					//Make a virtual
	if (action) 
		field->setPassMove(active,attackPos,pos);
	else
		field->deactivateMove();


}
