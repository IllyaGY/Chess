#include "Field.h"



Field::Field(int squareSize, int &x, int &y) {
	s = float(squareSize);


	leftOffset = x / 2 - (squareSize * 4);	//Offset Left
	topOffset = y / 2 - (squareSize * 4);		//Offset Top 


	green.setSize(sf::Vector2f(float(squareSize), float(squareSize)));
	green.setFillColor(sf::Color(118, 150, 86));

	white.setSize(sf::Vector2f(float(squareSize), float(squareSize)));
	white.setFillColor(sf::Color(238, 238, 210));


	float sideAdd = leftOffset;
	float topAdd = topOffset;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) field[(i * 8) + (j)] = white;
				else field[(i * 8) + (j)] = green;
			}
			else {
				if (j % 2 == 0) field[(i * 8) + (j)] = green;
				else field[(i * 8) + (j)] = white;
			}
			field[(i * 8) + (j)].setPosition(sideAdd, topAdd);
			sideAdd += s;
		}
		topAdd += s;
		sideAdd = leftOffset;


	}
}

sf::Vector2f Field::getCoord(int i) {
	return field[i].getPosition();
}


bool Field::getStatus() {
	return setActive;
}

bool Field::isClicked(sf::Vector2f pos, sf::Vector2f posCurr) {
	if (pos.x >= posCurr.x && pos.x <= posCurr.x + 100.f && pos.y >= posCurr.y && pos.y <= posCurr.y + 100.f) return true;
	return false;
}

int Field::cubesClicked(sf::Vector2f pos) {
	for (int i = 0; i < activeFields.size(); i++) {
		if (pos.x >= field[activeFields.at(i)].getPosition().x && pos.x <= field[activeFields.at(i)].getPosition().x + s &&
			pos.y >= field[activeFields.at(i)].getPosition().y && pos.y <= field[activeFields.at(i)].getPosition().y + s)
			return activeFields.at(i);
	}
	return -1;
}


void Field::setPassMove(std::vector<int> pVec) {
	activeFields = pVec;
	setActive = true;
	for (int i = 0; i < pVec.size(); i++) {
		backUp.push_back(field[pVec.at(i)].getFillColor());
		field[pVec.at(i)].setFillColor(sf::Color::Green);

	}
}

//void Field::fillBoard(int pos, std::shared_ptr<Figure> figure) {
	//board[pos] = figure;
//}

void Field::deactivateMove() {
	setActive = false;
	for (int i = 0; i < activeFields.size(); i++) {
		field[activeFields.at(i)].setFillColor(backUp.at(i));
	}
	activeFields.clear();
	backUp.clear();
}



void Field::fieldToScreen(sf::RenderWindow *window) {


	for (int i = 0; i < SIZE; i++) {
		window->draw(field[i]);

	}
}