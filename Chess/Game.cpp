#include "Game.h"


Game::Game(Field *field, int objectSize) {
	//Pawn 16 units
	currentFrame = false;
	//White 
	for (int i = 0; i < 8; i++) {
		playerBase.push_back(std::make_shared<Pawn>(field->getCoord(8 + i).x, field->getCoord(8 + i).y, 0, 8 + i, objectSize));
		if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(i)))
			pawn->setFigure();
		//field->fillBoard(8 + i, playerBase.at(i));

	}

}

void Game::reverseCurrFrame() {
	currentFrame = false;
}
bool Game::getCurrFrame() {
	return currentFrame;
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
	if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(lastSel)))
		pawn->movement(field, 0);
	lastSel = -1;

}


void Game::checkIf(sf::RenderWindow *window, Field *field) {
	sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	

	if (lastSel != -1 && field->cubesClicked(clickPos) == -1) {
		undo(window, field);
	}

		for (int i = 0; i < playerBase.size(); i++) {
			if (playerBase.at(i)->isClicked(clickPos)) {
				playerBase.at(i)->selectedItem(window, 1);
				if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(i)))
					pawn->movement(field, 1);
				lastSel = i;
				break;
			}

		}
	

}

void Game::makeMove(sf::RenderWindow *window, Field *field) {
	
	sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	int input = field->cubesClicked(clickPos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && input > -1) {
		currentFrame = true; 
		playerBase.at(lastSel)->setPos(field->getCoord(input).x, field->getCoord(input).y);
		if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(playerBase.at(lastSel))) {
			pawn->updateNext(input);
		}
		undo(window, field);
	}



}