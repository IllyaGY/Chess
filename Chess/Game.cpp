#include "Game.h"


#define PLAYER_STATE 0

Game::Game(Field *field, int objectSize) {
	
	
	int indexing = 0; 

	int pawnPos[16] = { 8,9,10,11,12,13,14,15,48,49,50,51,52,53,54,55 };
	int bishopPos[4] = {2, 5, 58, 61};
	int rookPos[4] = {0, 7, 56,63};
	int knightPos[4] = {1, 6, 57,62};
	int queenPos[2] = {3,59};
	int kingPos[2] = {4,60};

		
	figurePlacement<Pawn>(indexing, pawnPos, sizeof(pawnPos) / sizeof(int), field, objectSize);
	figurePlacement<Bishop>(indexing, bishopPos, sizeof(bishopPos) / sizeof(int), field, objectSize);
	figurePlacement<Rook>(indexing, rookPos, sizeof(rookPos) / sizeof(int), field, objectSize);
	figurePlacement<Knight>(indexing, knightPos, sizeof(knightPos) / sizeof(int), field, objectSize);
	figurePlacement<Queen>(indexing, queenPos, sizeof(queenPos) / sizeof(int), field, objectSize);
	figurePlacement<King>(indexing, kingPos, sizeof(kingPos) / sizeof(int), field, objectSize);



	

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
	playerBase.at(lastSel)->selectedItem(window, field, 0);
	lastSel = -1;
	done = true;
}



void Game::checkIf(sf::RenderWindow *window, Field *field) {
		sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));						
		for (int i = 0; i < playerBase.size(); i++) {															//For all the players check if any of them clicked
			if (playerBase.at(i)->isClicked(clickPos) && playerBase.at(i)->getSide() == currSideMove) {														
				playerBase.at(i)->selectedItem(window, field, 1);
				lastSel = i;																					//Last selected index = i
				lock = true;																					//lock the state for frame and click consistency
				done = false;																					//In the middle of choosing a move
				break;																							
			}

		}
		
}
	






void Game::makeMove(sf::RenderWindow* window, Field* field) {
		sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));								
		int input = field->cubesClicked(clickPos, this);																
		if (input > -1) {																								//if clicked on a cube that is currently active
			playerBase.at(lastSel)->setPos(field->getCoord(input).x, field->getCoord(input).y);							//set the pos of the last selected figure to the pos of the cube clicked
			field->emplaceBoard(playerBase.at(lastSel)->getPos(), input);															//emplace the old figure, if any, with the new one
			playerBase.at(lastSel)->setCubePos(input);																				//set the pos of the figure to input - cube index
			currSideMove = currSideMove > 0 ? 0 : 1;
			
		}
		undo(window, field);																							//Undo selection
		lock = true;																									//unlock for future selection
		
	
}


