#include "Rook.h"
#include "Field.h"

Rook::Rook(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {


	if (sideColor) {
		if (!black.loadFromFile("Textures/rook.png"))
			if (!black.create(size, size))
				throw std::invalid_argument("BLARGH");
		figure.setTexture(&black);
	}

	else {
		if (!white.loadFromFile("Textures/rookWhite.png"))
			if (!white.create(size, size))
				throw std::invalid_argument("BLARGH");
		figure.setTexture(&white);
	}

}



void Rook::updateNext(int pos, Field* field) {											//TRASH CODE
	active.clear();
	attackPos.clear();
	if ((pos - 7) % 8 != 0) {														//Make border checks static in the field class
		for (int i = pos + 1;; i++) {
			if (field->isTaken(i)) {
				attackPos.push_back(i);
				break;
			}
			else active.push_back(i);

			if ((i - 7) % 8 == 0) break; 
		}
	}
	if (pos % 8 != 0) {														//Make border checks static in the field class
		for (int i = pos - 1; ; i--) {
			if (field->isTaken(i)) {
				attackPos.push_back(i);
				break;
			}
			else active.push_back(i);

			if (i % 8 == 0) break; 
		}
	}
	if (pos > 7) {														//Make border checks static in the field class
		for (int i = pos-8; ;i-=8) {
			if (field->isTaken(i)) {
				attackPos.push_back(i);
				break;
			}
			else active.push_back(i);

			if (i < 8) break;
		}
	}
	if (pos < 56) {														//Make border checks static in the field class
		for (int i = pos+8; ; i+=8) {
			if (field->isTaken(i)) {
				attackPos.push_back(i);
				break;
			}
			else active.push_back(i);

			if (i > 55) break;
		}
	}
}		
void Rook::figureAction(Field* field, int action) {
	if (action)
		field->setPassMove(active, attackPos, pos);
	else
		field->deactivateMove();


}