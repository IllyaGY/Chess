/*
© 2024 IllyaGY
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see https://www.gnu.org/licenses/.
*/


#include "Game.h"
#include <sstream>
#include <string>





void defText(sf::Font& font, sf::Text* text, int fontSize, sf::Vector2f coords = sf::Vector2f(0, 0));



  

Game::Game(int side, Field *field, int objectSize) {
	

	currentEnPassPawn = NULL;

	playerSide = side; 
	float top = (-objectSize / 2);
	float bottom = 1.5f * objectSize;
	
	
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		throw std::invalid_argument("Font could not be loaded");
	}
	
	sf::Vector2f posT = field->getCoord(MIDDLE_TOP_INDEX);
	sf::Vector2f posB = field->getCoord(MIDDLE_BOTTOM_INDEX);

	if (side) {																		
		defScore(posB, posT, top, bottom);
	}
	else {
		defScore(posB, posT, bottom, top);
	}
	

	defText(font, &scoreWhite, 24, posWhite);
	defText(font, &scoreBlack, 24, posBlack);
	defText(font, &checkText, 24);
	checkText.setString("Check");

	sideMarker.setFillColor(sf::Color::Green);
	sideMarker.setRadius(15);
	switchMarkerPos(0);

	promMenu = PromMenu(SIZE, posBlack, posWhite);

	int indexing = 0; 

	pawnPos = new int[PAWNS]{ 8,9,10,11,12,13,14,15,48,49,50,51,52,53,54,55 };
	bishopPos  = new int[BISHOPS] {2, 5, 58, 61};
	rookPos = new int[ROOKS] {0, 7, 56,63};
	knightPos  = new int[KNIGHTS] {1, 6, 57,62};
	queenPos  = new int[QUEENS] {3,59};
	kingPos  = new int[KINGS] {4,60};

	kings[side] = kingPos[side];
	kings[side == 1 ? 0 : 1 ] = kingPos[side == 1 ? 0 : 1];


	/*Filling out look up matrix*/
	Pawn::lookUpFill(); 
	Figure::fillOutDiag();
	Figure::fillOutXY();
		
	/*Spawning all the figures */
	figurePlacement<Pawn>(indexing, pawnPos, PAWNS, field, objectSize);
	figurePlacement<Bishop>(indexing, bishopPos, BISHOPS, field, objectSize);
	figurePlacement<Rook>(indexing, rookPos, ROOKS, field, objectSize);
	figurePlacement<Knight>(indexing, knightPos, KNIGHTS, field, objectSize);
	figurePlacement<Queen>(indexing, queenPos, QUEENS, field, objectSize);
	figurePlacement<King>(indexing, kingPos, KINGS, field, objectSize);


	
	

}


void Game::defScore(sf::Vector2f pos1, sf::Vector2f pos2, float offset1, float offset2) {
	posWhite = sf::Vector2f(pos1.x, pos1.y + offset1);
	posBlack = sf::Vector2f(pos2.x, pos2.y + offset2);
}


void defText(sf::Font& font, sf::Text* text, int fontSize, sf::Vector2f coords) {
	text->setFont(font); 
	text->setCharacterSize(fontSize);
	text->setPosition(coords); 
	text->setFillColor(coords == sf::Vector2f(0,0) ? sf::Color::Red  : sf::Color::White );
} 

std::string toString(std::string s, int arg) {
	std::stringstream argString;
	argString << arg;
	return s + argString.str();
}



void Game::switchMarkerPos(int side) {
	objPosDef(sideMarker, MARKER_OFFSET, side);
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




void Game::addToSide(int side, int points) {
	if (side) white += points;
	else black += points; 
}

int Game::getSideGlob(int index) {
	return playerBase.at(index)->getSide();
}

void Game::drawAll(sf::RenderWindow *window, Field *field) {
	for (int i = 0; i < playerBase.size(); i++) {
		this->playerBase.at(i)->drawFigure(window);
	}

	scoreWhite.setString(toString(WHITE, white));
	scoreBlack.setString(toString(BLACK, black));
	window->draw(scoreWhite);
	window->draw(scoreBlack);
	window->draw(sideMarker);
	if (checkS > -1) {
		checkText.setPosition(checkS ? sf::Vector2f(posBlack.x + 2 * MARKER_OFFSET, posBlack.y) 
			: sf::Vector2f(posWhite.x + 2 * MARKER_OFFSET, posWhite.y));
		window->draw(checkText);
	}
	if (sideProm != -1) {
		promMenu.menuDraw(window);
	}
}

void Game::undo(sf::RenderWindow *window, Field *field) {
	playerBase.at(lastSel)->selectedItem(window, field, 0);
	lastSel = -1;
	done = true;
}


bool setCheckMate(int &checkS, int currSideMove, sf::Text &checkText, Field *field, int posInCube) {
	if (checkS != -1 && checkS != currSideMove) {			//If checkS at this point was already not -1 meaning check was already placed on the king, and checkS doesnt equal the current side moving
		checkText.setString("Check Mate");					//Mate is placed
		return true;										//Ending the game 
	}
												//If no check was yet, we place a check for that king
	checkS = field->figurePoint(posInCube)->getSide();
	return false; 

}



void Game::check(Field* field) {													//CHECK IF KNIGHT DOES IT TOO!!!!!!!!	
	for (auto king : kings) {												//After the updateKingThread function, we can have a vector of all the enemy figures that posses a check on our king
		auto figure = getType<King>(field->figurePoint(king));
		for (auto i : figure->getChecks()) {								//Get all the figures, making up check condition on our king
			if (figure->diagPosEnemy(i, figure->getPos())) {				//If any of the diagonal direction are open to our king, it checks till it meets an enemy figures
				if ((getType<Queen>(field->figurePoint(i)) ||				//Each Queen, Bishop and Pawn, can only attack it diagonally, though a Pawn can only attack if it is one square apart
					getType<Bishop>(field->figurePoint(i))) ||				//thats where the chickHit comes in handy
					getType<Pawn>(field->figurePoint(i))->checkHit(i, king)) {
					endGame = setCheckMate(checkS, currSideMove, checkText, field, i);
					return; 

				}
			}
			else if (figure->XYPosEnemy(i, figure->getPos()) &&				//In the XY plane, Queen, Rook are the ones dangerous
				(getType<Queen>(field->figurePoint(i)) ||
				getType<Rook>(field->figurePoint(i)))) {
				endGame = setCheckMate(checkS, currSideMove, checkText, field, i);
				return;
			}
		}
	}
	checkS = -1;															//If there are no  pointers in the king's check list, this means there is no check 
	
}


	

bool Game::end() {
	return endGame;
} 


void Game::deletePlayers(Field *field) {
	playerBase.clear();
	field->clearField();

}

void Game::winScreen(sf::RenderWindow* window, int x, int y) {
	sf::Text winnerText;
	defText(font, &winnerText, 50, sf::Vector2f(x, y));
	if (checkS) winnerText.setString("Black wins"); 
	else winnerText.setString("White wins");
	window->draw(winnerText);

} 



void clearEnPassAttackers(std::vector<std::shared_ptr<Pawn>>& enPawnAttackers) {
	for (auto& i : enPawnAttackers) {
		i->clearEnPass();
	}
}




void helpSide(std::shared_ptr<Pawn> &figure, int border, Field *field, int attackDir, std::vector<std::shared_ptr<Pawn>> &enPawnAttackers) {			//-1 for Left, 1 for Right
	if (figure->getPos() % 8 != border && field->isTaken(figure->getPos() + attackDir) == figure->getSide() == 0 ? 1 : 0) {
		if (auto enemyPawn = std::dynamic_pointer_cast<Pawn>(field->figurePoint(figure->getPos() + attackDir))) {			//Maybe let the template do the job instead
			enemyPawn->passToEn(figure->getPos());
			enPawnAttackers.push_back(enemyPawn);
		}
	}
} 

//Helper for En Passant
void Game::enPass(std::shared_ptr<Pawn> pawnAtUse, Field* field) {
	if (currentEnPassPawn != NULL) {													//If an attacking pawn just stepped on a cube that is drawn as en Pass
		currentEnPassPawn = NULL;		//Any further step disables the en Pass
	}
					//The position of the pawn is new at this point
	if (pawnAtUse) {
		if (pawnAtUse->checkIfEnPass()) {
			currentEnPassPawn = (pawnAtUse);					//If an attack by en Pass is applicable to this pawn, set a pointer to it
			helpSide(currentEnPassPawn, LEFT_BORDER, field, -1, enPawnAttackers);
			helpSide(currentEnPassPawn, RIGHT_BORDER, field, 1, enPawnAttackers);

		}
	}
}



void Game::checkPawnPromotion(std::shared_ptr<Pawn> pawn, Field *field) {
	if (pawn && pawn->checkPromotion()) {
		sideProm = pawn->getSide();
		promMenu.init(pawn->getSide());
		/*playerBase.at(pawn->getFirstPos()) = std::make_shared<Bishop>(field->getCoord(pawn->getPos()).x, field->getCoord(pawn->getPos()).y,
			(pawn->getSide()), pawn->getPos(), 100);
		pawn->setUndraw();*/
		
	}
}



//Castling logic 
void rookCastlingHelper(std::shared_ptr<King> king, std::shared_ptr<Rook> rook) {					
	if (rook->getSide()) {
		if (rook->getFirstPos() % 2 == 0) king->setCastlingRight(false);
		else king->setCastlingLeft(false);
	}
	else {
		if (rook->getFirstPos() % 2 == 0) king->setCastlingLeft(false);
		else king->setCastlingRight(false);
	}
}

void Game::rookCastlingUpdate (Field *field, std::shared_ptr<Rook> rook) {
	if (rook && rook->isFirst()) {
		auto king = getType<King>(field->figurePoint(kings[rook->getSide()]));
		if(king->isFirst())
			rookCastlingHelper(king, rook);
	}
}








void Game::ifKingChosen(std::shared_ptr<King> figure, int input, Field* field) {
	//Separate these 
	if (figure) {
		kings[figure->getSide()] = input;
		figure->setCastling();													//Castling set to false
		if (field->isCastleSquare(figure->getPos())) {							//If the new position of the king belongs to castling positions, the corresponding rook is moved
			std::vector<int> ptr = figure->getRook(figure->getPos());
			move(ptr.at(1), field, -1, ptr.at(0));

		}
	}

}



void Game::updateKings(Field* field, std::array<int, 2> KingsPos) {
	for (int i = 0; i < 2; i++) {
		playerBase.at(KingsPos[i])->updateMoves(field);			//Update both kings and their threads of check 
	}

	
}


void Game::beforeFigUpdate(std::shared_ptr<Figure> piece, Field* field) {
	clearEnPassAttackers(enPawnAttackers);
	checkPawnPromotion(getType<Pawn>(piece), field);
}

void Game::afterFigUpdate(std::shared_ptr<Figure> piece, Field* field, int input) {
	std::array<int, 2> indexOfKings{ KING_LIST_WHITE, KING_LIST_BLACK };
	updateKings(field, indexOfKings);
	enPass(getType<Pawn>(piece), field);					//Pawn enPass , can be disabled if chosen to															
	ifKingChosen(getType<King>(piece), input, field);
	rookCastlingUpdate(field, getType<Rook>(piece));
	check(field);	

}


void Game::logicUpdate(std::shared_ptr<Figure> piece, Field* field, int input) {
	beforeFigUpdate(piece, field);
	piece->updateMoves(field);
	afterFigUpdate(piece, field, input);
															
	
}


void Game::checkIf(sf::RenderWindow* window, Field* field) {
	sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	for (int i = 0; i < playerBase.size(); i++) {															//For all the players check if any of them clicked
		if (playerBase.at(i)->isClicked(clickPos) && playerBase.at(i)->getSide() == currSideMove) {
			playerBase.at(i)->updateMoves(field);
			playerBase.at(i)->selectedItem(window, field, 1);
			lastSel = i;																					//Last selected index = i
			lock = true;																					//lock the state for frame and click consistency
			done = false;																					//In the middle of choosing a move
			break;
		}

	}

}

void Game::move(int moveTo, Field* field, int lastSel, int fieldPos) {
	auto piece = (lastSel != -1) ? playerBase.at(lastSel) : field->figurePoint(fieldPos);		//If lastSel index is provided, access the pointer straight from the playerBase vector
	piece->setPos(field->getCoord(moveTo).x, field->getCoord(moveTo).y);						//set the pos of the last selected figure to the pos of the cube clicked
	this->addToSide(currSideMove, field->emplaceBoard(piece->getPos(), moveTo));				//emplace the old figure, if any, with the new one																			
	piece->setCubePos(moveTo);



}



void Game::makeMove(sf::RenderWindow* window, Field* field) {
		sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));								
		int input = field->cubesClicked(clickPos, this);																
		if (input > -1) {																								//if clicked on a cube that is currently active
			move(input, field, lastSel);																			//Move the object																													
			
			logicUpdate(playerBase.at(lastSel), field, input);															//Update the figure moved, and both of the kings
			
																					
			playerBase.at(lastSel)->setFirstFalse();
			currSideMove = currSideMove > 0 ? 0 : 1;
			switchMarkerPos(currSideMove);				//Switch the green marker
		}
		undo(window, field);																							//Undo selection
		lock = true;																									//unlock for future selection
		
	
}


