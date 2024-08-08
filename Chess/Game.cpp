#include "Game.h"


#define PLAYER_STATE 0

Game::Game(Field *field, int objectSize) {
	//Pawn 16 units
	//White 
		
	for (int i = 0; i < 8; i++) {
		playerBase.push_back(std::make_shared<Pawn>(field->getCoord(8 + i).x, field->getCoord(8 + i).y, 0, 8 + i, objectSize));
		auto figure = getType<Pawn>(i);
		if (figure)
			figure->setFigure(0);
		field->fillBoard(8 + i, playerBase.at(i));

	}
	for (int i = 0; i < 8; i++) {
		playerBase.push_back(std::make_shared<Pawn>(field->getCoord(48 + i).x, field->getCoord(48 + i).y, 1, 48 + i, objectSize));
		auto figure = getType<Pawn>(8+i);
		if (figure)
			figure->setFigure(1);
		field->fillBoard(48 + i, playerBase.at(8+i));

	}
	//for (int i = 0; i < 4; i++) {
		playerBase.push_back(std::make_shared<Bishop>(field->getCoord(27).x, field->getCoord(27).y, 0, 27, objectSize));
		auto figure = getType<Bishop>(16);
		if (figure) {
			figure->setFigure(0);
			figure->updateNext(figure->getPos(),field);
		}
		field->fillBoard(27, playerBase.at(16));
	

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
				auto figure = getType<Figure>(i); // Use correct function name and ensure Figure is the correct type
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


