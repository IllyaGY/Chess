#include "Game.h"


#define PLAYER_STATE 0

Game::Game(Field *field, int objectSize) {
	int i = 0; 
	//Pawn 16 units
	//White 
	int bishopPos[4] = {2, 5, 58, 61};
	int rookPos[4] = {0, 7, 56,63};
	int knightPos[4] = {1, 6, 57,62};
		

 // SEPARATE INTO FUNCTIONS
	for (i = 0; i < 8; i++) {
		playerBase.push_back(std::make_shared<Pawn>(field->getCoord(8 + i).x, field->getCoord(8 + i).y, 0, 8 + i, objectSize));
		field->fillBoard(8 + i, playerBase.at(i));

	}
	int lim = i + 8; 
	for (; i < lim; i++) {
		playerBase.push_back(std::make_shared<Pawn>(field->getCoord(40 + i).x, field->getCoord(40 + i).y, 1, 40 + i, objectSize));
		field->fillBoard(40 + i, playerBase.at(i));

	}
	int ind = 0; 
	lim = i + 4; 
	for (; i < lim; i++, ind++) {
		playerBase.push_back(std::make_shared<Bishop>(field->getCoord(bishopPos[ind]).x, field->getCoord(bishopPos[ind]).y, 
			((bishopPos[ind] < 31) ? 0 : 1), bishopPos[ind], objectSize));
		field->fillBoard(bishopPos[ind], playerBase.at(i));

	}
	ind = 0; 
	lim = i + 4;
	for (; i < lim; i++, ind++) {
		playerBase.push_back(std::make_shared<Rook>(field->getCoord(rookPos[ind]).x, field->getCoord(rookPos[ind]).y,
			((rookPos[ind] < 31) ? 0 : 1), rookPos[ind], objectSize));
		field->fillBoard(rookPos[ind], playerBase.at(i));

	}
	ind = 0; 
	lim = i + 4;
	for (; i < lim; i++, ind++) {
		playerBase.push_back(std::make_shared<Knight>(field->getCoord(knightPos[ind]).x, field->getCoord(knightPos[ind]).y,
			((knightPos[ind] < 31) ? 0 : 1), knightPos[ind], objectSize));
		field->fillBoard(knightPos[ind], playerBase.at(i));

	}
}



int Game::getActionState() {
	return done; 
}
int Game::getLockState() {
	return lock;
}

int Game::getLast() {
	return lastSel;
}


int Game::getSideGlob(int index) {
	return playerBase.at(index)->getSide();
}

void Game::drawAll(sf::RenderWindow *window, Field *field) {
	for (int i = 0; i < playerBase.size(); i++) {
		this->playerBase.at(i)->drawFigure(window);
	}
}

void Game::undo(sf::RenderWindow *window, Field *field) {
	playerBase.at(lastSel)->selectedItem(window, 0);
	auto figure = getType<Figure>(lastSel);
	if (figure)
		figure->figureAction(field, 0);
	lastSel = -1;
	done = true;
}



void Game::checkIf(sf::RenderWindow *window, Field *field) {
		sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		for (int i = 0; i < playerBase.size(); i++) {
			if (playerBase.at(i)->isClicked(clickPos)) {
				playerBase.at(i)->selectedItem(window, 1);
				auto figure = getType<Figure>(i); 
				if (figure) {
					figure->updateNext(playerBase.at(i)->getPos(), field);
					figure->figureAction(field, 1);
				}
				lastSel = i;
				lock = true;
				done = false;
				break;
			}

		}
		
}
	






void Game::makeMove(sf::RenderWindow* window, Field* field) {
		sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		int input = field->cubesClicked(clickPos, this);
		if (input > -1) {
			playerBase.at(lastSel)->setPos(field->getCoord(input).x, field->getCoord(input).y);
			auto figure = getType<Figure>(lastSel); 
			if (figure) {
				field->emplaceBoard(figure->getPos(), input);
				figure->setCubePos(input);
			}
			
		}
		undo(window, field);
		lock = true;
		
	
}


