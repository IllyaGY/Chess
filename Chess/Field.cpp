#include "Field.h"
#include "Game.h"

class Game; 

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
				if (j % 2 == 0) field[i][j] = white;
				else field[i][j] = green;
			}
			else {
				if (j % 2 == 0) field[i][j] = green;
				else field[i][j] = white;
			}
			field[i][j].setPosition(sideAdd, topAdd);
			sideAdd += s;
		}
		topAdd += s;
		sideAdd = leftOffset;


	}
}


sf::RectangleShape * Field::cubeRet(int pos) {
	return &(field [pos / 8] [pos % 8]);
}

sf::Vector2f Field::getCoord(int i) {
	return cubeRet(i)->getPosition();
}


bool Field::getStatus() {
	return setActive;
}

bool Field::isClicked(sf::Vector2f pos, sf::Vector2f posCurr) {
	if (pos.x >= posCurr.x && pos.x <= posCurr.x + 100.f && pos.y >= posCurr.y && pos.y <= posCurr.y + 100.f) return true;
	return false;
}

int Field::cubesClicked(sf::Vector2f pos, Game *game) {
	for (int i = 0; i < activeFields.size(); i++) {
		if (pos.x >= getCoord(activeFields.at(i)).x && pos.x <= getCoord(activeFields.at(i)).x + s &&
			pos.y >= getCoord(activeFields.at(i)).y && pos.y <= getCoord(activeFields.at(i)).y + s)
			return activeFields.at(i);

	}
	for (int i = 0; i < activeAttackFields.size(); i++) {
		if (pos.x >= getCoord(activeAttackFields.at(i)).x && pos.x <= getCoord(activeAttackFields.at(i)).x + s &&
			pos.y >= getCoord(activeAttackFields.at(i)).y && pos.y <= getCoord(activeAttackFields.at(i)).y + s) {
			board.at(activeAttackFields.at(i))->setUndraw();
			return activeAttackFields.at(i);
		}
	}
	return -1;
}

bool Field::sameSides(int currPos, int comparable) {				
	return board.at(currPos)->getSide() == board.at(comparable)->getSide();
}

bool Field::isTaken(int pos) {
	if (board.find(pos) != board.end())
		return true; 
	return false;
	
}

bool Field::isTaken(int posX, int posY) {
	if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8) {
		if (board.find(posX * 8 + posY) != board.end())
			return true;
	}
	return false;
	
}



void Field::setPassMove(std::vector<int> moveVec, std::vector<int> attackVec, int ourPos) {
	setActive = true;
	for (int i = 0; i < moveVec.size(); i++) {
		if (board.find(moveVec.at(i)) == board.end()) {									
			backUp.push_back(cubeRet(moveVec.at(i))->getFillColor());
			cubeRet(moveVec.at(i))->setFillColor(sf::Color::Green);
			activeFields.push_back(moveVec.at(i));
		}
		
		
	}
	for (int i = 0; i < attackVec.size(); i++) {
		if (board.find(attackVec.at(i)) != board.end() && !sameSides(ourPos, attackVec.at(i))) {
			backUpAttack.push_back(cubeRet(attackVec.at(i))->getFillColor());
			cubeRet(attackVec.at(i))->setFillColor(sf::Color::Red);
			activeAttackFields.push_back(attackVec.at(i));
		}

		
	}
}

void Field::fillBoard(int pos, std::shared_ptr<Figure> figure) {
	board[pos] = figure;
}
void Field::emplaceBoard(int oldPos, int newPos){
	std::shared_ptr<Figure> figure = board.at(oldPos); 
	board.erase(oldPos);
	board[newPos] = figure;

}


void Field::deactivateMove() {
	setActive = false;
	for (int i = 0; i < activeFields.size(); i++) {
		cubeRet(activeFields.at(i))->setFillColor(backUp.at(i));
	}
	for (int i = 0; i < activeAttackFields.size(); i++) {
		cubeRet(activeAttackFields.at(i))->setFillColor(backUpAttack.at(i));

	}
	activeAttackFields.clear();
	activeFields.clear();
	backUp.clear();
	backUpAttack.clear();
}


void Field::fieldToScreen(sf::RenderWindow *window) {


	for (int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++)
		window->draw(field[i][j]);

	}
}