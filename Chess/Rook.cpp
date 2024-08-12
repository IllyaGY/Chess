#include "Rook.h"



Rook::Rook(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {


	if (sideColor) {
		if (!black.loadFromFile("Textures/pawn.png"))
			if (!black.create(size, size))
				throw std::invalid_argument("BLARGH");
		figure.setTexture(&black);
	}

	else {
		if (!white.loadFromFile("Textures/pawnWhite.png"))
			if (!white.create(size, size))
				throw std::invalid_argument("BLARGH");
		figure.setTexture(&white);
	}

}



void Rook::updateNext(int pos, Field* field) {
	
}		
void Rook::figureAction(Field* field, int action) {


}