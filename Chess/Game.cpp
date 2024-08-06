#include "Game.h"


#define PLAYER_STATE 0

Game::Game(Field *field, int objectSize) {
	//Pawn 16 units
	//White 
	for (int i = 0; i < 8; i++) {
		playerBase.push_back(std::make_shared<Pawn>(field->getCoord(8 + i).x, field->getCoord(8 + i).y, 0, 8 + i, objectSize));
		if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(i)))
			pawn->setFigure(0);
		field->fillBoard(8 + i, playerBase.at(i));

	}
	for (int i = 0; i < 8; i++) {
		playerBase.push_back(std::make_shared<Pawn>(field->getCoord(48 + i).x, field->getCoord(48 + i).y, 1, 48 + i, objectSize));
		if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(8+i)))
			pawn->setFigure(1);
		field->fillBoard(48 + i, playerBase.at(8+i));

	}

}


int Game::getLast() {
	return lastSel;
}

void Game::remove(std::shared_ptr<Figure> figure) {
	auto it = std::find(playerBase.begin(), playerBase.end(),
		figure);
	if(it != playerBase.end())
		playerBase.erase(it);
}


void Game::drawAll(sf::RenderWindow *window, Field *field) {
	for (int i = 0; i < playerBase.size(); i++) {
		this->playerBase.at(i)->drawFigure(window);

	}
}

void Game::undo(sf::RenderWindow *window, Field *field) {
	playerBase.at(lastSel)->selectedItem(window, 0);
	if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(lastSel))) {
		pawn->figureAction(field, 0);

	}
	lastSel = -1;
	done = true;
}


void Game::checkIf(sf::RenderWindow *window, Field *field) {
		sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		for (size_t i = 0; i < playerBase.size(); i++) {
			if (playerBase.at(i)->isClicked(clickPos)) {
				playerBase.at(i)->selectedItem(window, 1);

				if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(i))) {
					pawn->figureAction(field, 1);
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
			if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(lastSel))) {
				field->emplaceBoard(pawn->getPos(), input);
				pawn->updateNext(input);
				
				
			}
		}
		undo(window, field);
		lock = true;
		
	
}
