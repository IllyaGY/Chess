#include "Knight.h"
#include "Field.h"


Knight::Knight(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {




	if (sideColor) {
		if (!black.loadFromFile("Textures/knight.png"))
			if (!black.create(size, size))
				throw std::invalid_argument("BLARGH");
		figure.setTexture(&black);
	}

	else {
		if (!white.loadFromFile("Textures/knightWhite.png"))
			if (!white.create(size, size))
				throw std::invalid_argument("BLARGH");
		figure.setTexture(&white);
	}

}



void Knight::updateNext(int pos, Field* field) {											//TRASH CODE
	active.clear();
	attackPos.clear();
	int posIn2D[2] = {pos/8, pos%8};
	for (int i = 0; i < 8; i++) {
		int x = posIn2D[0] + toGo[i][0];
		int y = posIn2D[1] + toGo[i][1];
		if (field->isTaken(x, y))
			attackPos.push_back(x*8 + y);
		
		else if(x >= 0 && x<8 && y >= 0 && y < 8 ) 
			active.push_back(x * 8 + y);
	}
}
void Knight::figureAction(Field* field, int action) {
	if (action)
		field->setPassMove(active, attackPos, pos);
	else
		field->deactivateMove();


}