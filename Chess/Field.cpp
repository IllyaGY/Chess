#include "Field.h"
#include "Game.h"

class Game; 

#define STARTING_BLOCK 0
#define ENDING_BLOCK 7 



Field::Field(int side, int squareSize, int &x, int &y) {
	s = float(squareSize);


	leftOffset = x / 2 - (squareSize * 4);	//Offset Left
	topOffset = y / 2 + (squareSize * 2);		//Offset Top 


	green.setSize(sf::Vector2f(float(squareSize), float(squareSize)));
	green.setFillColor(sf::Color(118, 150, 86));

	white.setSize(sf::Vector2f(float(squareSize), float(squareSize)));
	white.setFillColor(sf::Color(238, 238, 210));


	if (side) def(ENDING_BLOCK, STARTING_BLOCK - 1, -1);
	else def(STARTING_BLOCK, ENDING_BLOCK + 1, 1);
}


void Field::def(int start, int end, int inc) {
	float sideAdd = leftOffset;
	float topAdd = topOffset;

	for (int i = start; i != end; i+=inc) {
		for (int j = start; j != end; j += inc) {
			if (i % 2 == 0) {
				if (j % 2 == 0) field[i][j] = green;
				else field[i][j] = white;
				
			}
			else {
				if (j % 2 == 0) field[i][j] = white;
				else field[i][j] = green;
			}
			field[i][j].setPosition(sideAdd, topAdd);
			sideAdd += s;
		}
		topAdd -= s;
		sideAdd = leftOffset;
	}
}



sf::RectangleShape * Field::cubeRet(int pos) {
	return &(field [pos / 8] [pos % 8]);
}

sf::Vector2f Field::getCoord(int i) {
	return cubeRet(i)->getPosition();
}


bool Field::isKing(int pos, int currSide) {
	if (board.find(pos) != board.end()) {											//Checks if the king exists in the attack Vec and if the king is from opposite team 
		if (std::shared_ptr<King> figure = std::dynamic_pointer_cast<King>(board.at(pos)))
			return figure->getSide() != currSide;
	}
	return false;
}



bool Field::isClicked(sf::Vector2f pos, sf::Vector2f posCurr) {
	if (pos.x >= posCurr.x && pos.x <= posCurr.x + 100.f && pos.y >= posCurr.y && pos.y <= posCurr.y + 100.f) return true;
	return false;
}

int Field::helper(int &i, sf::Vector2f pos, int end) {
	for (; i < end; i++) {															//AGAIN COULD USE A HELPER FUNCTION !!!!!
		if (pos.x >= getCoord(activeFields.at(i)).x && pos.x <= getCoord(activeFields.at(i)).x + s &&
			pos.y >= getCoord(activeFields.at(i)).y && pos.y <= getCoord(activeFields.at(i)).y + s)
			return activeFields.at(i);

	}
	return -1;
}

int Field::cubesClicked(sf::Vector2f pos, Game *game) {
	int index = 0; 
	int cube;
	if ((cube = helper(index, pos,  activeSize)) != -1) 
		return cube; 
	if ((cube = helper(index, pos, index + attackSize))!= -1)
		return cube; 
	return -1;
}



int Field::isTaken(int pos) {
	if (board.find(pos) != board.end()) {
		return board.at(pos)->getSide();
	}
	return -1;
	
}

void Field::clearField() {
	board.clear(); 

}

std::shared_ptr<Figure> Field::figurePoint(int boardIndex) {
	if (board.find(boardIndex) != board.end())
		return board.at(boardIndex);
	else return NULL; 
}

int Field::isTaken(int posX, int posY) {
	if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8) {
		if (board.find(posX * 8 + posY) != board.end()) {
			return board.at(posX * 8 + posY)->getSide();
		}
	}
	return -1;
	
}

bool Field::isCastleSquare(int pos) {
	return field[pos / 8][pos % 8].getFillColor() == sf::Color::Yellow;
}

void helpSetPass(std::vector<int> actionVec, std::vector<sf::Color>& bcColor,
	std::vector<int>& activeVec, Field* field, sf::Color color, int& vecToInc, int sideToEqual, int side = -1) {


	if (side != -1) {					//Used for correct square drawing for the EnPassant move
		side = (side ? -8 : 8);
	}
	else side = 0; 


	for (auto i : actionVec) {
		if (i >= 0 && field->isTaken(i) == sideToEqual) {
			bcColor.push_back(field->cubeRet(i + side)->getFillColor());		
			field->cubeRet(i + side)->setFillColor(color);
			activeVec.push_back(i + side);
			vecToInc++;
		}
		
	}
}

void Field::setPassMove(Figure *figure) {
	if (figure != NULL) {
		int indexing = 0;
		helpSetPass(figure->getActive(), backUp, activeFields, this, sf::Color::Green, activeSize, -1);	//Active fields
		if (King* king = dynamic_cast<King*>(figure))
			helpSetPass(king->getCastlingVec(), backUp, activeFields, this, sf::Color::Yellow, activeSize, -1);//cubes, the figure can move to
		//All the moving(non attacking) indexes are appended to the activeFields vector first 
		//All the attacking indexes are appended afterwards
		//This helps for an shortening everything into a single vector instead of two .
		helpSetPass(figure->getAttackVec(), backUp, activeFields, this, sf::Color::Red, attackSize, (figure->getSide() == 1 ? 0 : 1));		//where the figure attacks 
		if (Pawn* pawn = dynamic_cast<Pawn*>(figure))
			helpSetPass({ pawn->getEnPass() }, backUp, activeFields, this, sf::Color::Yellow, attackSize, (figure->getSide() == 1 ? 0 : 1), figure->getSide());	//en Passant
	}
}

void Field::fillBoard(int pos, std::shared_ptr<Figure> figure) {
	board[pos] = figure;
}


int Field::emplaceBoard(int oldPos, int newPos){
	int points = 0; 
	std::shared_ptr<Figure> figure = board.at(oldPos); 
	int enPass = 0;
	if (auto pawn = std::dynamic_pointer_cast<Pawn>(figure)) {
		if (pawn->getEnPass() == newPos + (figure->getSide() ? 8 : -8)) {
			enPass = (figure->getSide() ? 8 : -8);
			pawn->clearElPass();
		}
	}
	board.erase(oldPos);
	if (board.find(newPos + enPass) != board.end()) {
		board.at(newPos + enPass)->setUndraw();
		points = board.at(newPos + enPass)->getPoints();
		
		
	}
	board[newPos] = figure;
	return points; 
}


void Field::deactivateMove() {
	for (int i = 0; i < activeFields.size(); i++) {
		cubeRet(activeFields.at(i))->setFillColor(backUp.at(i));
	}
	activeFields.clear();
	backUp.clear();
	activeSize = 0; 
	attackSize = 0;
}


void Field::fieldToScreen(sf::RenderWindow *window) {


	for (int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++)
		window->draw(field[i][j]);

	}
}