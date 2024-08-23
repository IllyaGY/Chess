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

	if (side) {																		//REWRITE 
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



	int indexing = 0; 

	pawnPos = new int[PAWNS]{ 8,9,10,11,12,13,14,15,48,49,50,51,52,53,54,55 };
	bishopPos  = new int[BISHOPS] {2, 5, 58, 61};
	rookPos = new int[ROOKS] {0, 7, 56,63};
	knightPos  = new int[KNIGHTS] {1, 6, 57,62};
	queenPos  = new int[QUEENS] {3,59};
	kingPos  = new int[KINGS] {4,60};

	kings[side] = kingPos[side];
	kings[side == 1 ? 0 : 1 ] = kingPos[side == 1 ? 0 : 1];
		
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
	if (side)
		sideMarker.setPosition(sf::Vector2f(posBlack.x -  MARKER_OFFSET, posBlack.y));
	else 
		sideMarker.setPosition(sf::Vector2f(posWhite.x -  MARKER_OFFSET, posWhite.y));

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
}

void Game::undo(sf::RenderWindow *window, Field *field) {
	playerBase.at(lastSel)->selectedItem(window, field, 0);
	lastSel = -1;
	done = true;
}




void Game::check(Field* field) {													//CHECK IF KNIGHT DOES IT TOO!!!!!!!!	
	for (auto king : kings) {												//After the updateKingThread function, we can have a vector of all the enemy figures that posses a check on our king
		auto figure = getType<King>(field->figurePoint(king));
		for (auto i : figure->getChecks()) {								//Get all the figures, making up check condition on our king
			if (figure->diagPosEnemy(i, figure->getPos())) {				//If any of the diagonal direction are open to our king, it checks till it meets an enemy figures
				if ((getType<Queen>(field->figurePoint(i)) ||				//Each Queen, Bishop and Pawn, can only attack it diagonally, though a Pawn can only attack if it is one square apart
					getType<Bishop>(field->figurePoint(i))) ||				//thats where the chickHit comes in handy
					getType<Pawn>(field->figurePoint(i))->checkHit(i, king)) {
					if (checkS != -1 && checkS != currSideMove) {			//If checkS at this point was already not -1 meaning check was already placed on the king, and checkS doesnt equal the current side moving
						checkText.setString("Check Mate");					//Mate is placed
						endGame = true;										//Ending the game 
						return;
					}
					else {													//If no check was yet, we place a check for that king
						checkS = field->figurePoint(i)->getSide();
						return;
					}
				}
			}
			else if (figure->XYPosEnemy(i, figure->getPos()) &&				//In the XY plane, Queen, Rook are the ones dangerous
				(getType<Queen>(field->figurePoint(i)) ||
				getType<Rook>(field->figurePoint(i)))) {
				if (checkS != -1)checkText.setString("Check Mate");
				checkS = field->figurePoint(i)->getSide();		
				return;
			}
		}
	}
	checkS = -1; 
	
}

void Game::checkIf(sf::RenderWindow *window, Field *field) {
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

void helpDiff(std::shared_ptr<Pawn> figure, int border, Field *field, int attackDir) {			//-1 for Left, 1 for Right
	if (figure->getPos() % 8 != border && field->isTaken(figure->getPos() + attackDir) == figure->getSide() == 0 ? 1 : 0) {
		if (auto enemyPawn = std::dynamic_pointer_cast<Pawn>(field->figurePoint(figure->getPos() + attackDir))) {			//Maybe let the template do the job instead
			enemyPawn->passToEn(figure->getPos());
		}
	}
} 




//Helper 
void Game::different(std::shared_ptr<Figure> piece, Field*field) {
	

	if (currentEnPassPawn != NULL) {													//If an attacking pawn just stepped on a cube that is drawn as en Pass
		currentEnPassPawn = NULL;		//Any further step disables the en Pass
	}
	auto pawn = getType<Pawn>(piece);				//The position of the pawn is new at this point
	if (pawn){
		if (pawn->checkIfEnPass()) {
			currentEnPassPawn = (pawn);					//If an attack by en Pass is applicable to this pawn, set a pointer to it
			helpDiff(pawn, LEFT_BORDER, field, -1);
			helpDiff(pawn, RIGHT_BORDER, field, 1);

		}
	}
	auto figure = getType<King>(piece);
	if (!figure)
		piece->updateMoves(field);


	

}


void Game::move(int moveTo, Field *field, int lastSel, int fieldPos) {
	auto piece = (lastSel != -1) ? playerBase.at(lastSel) : field->figurePoint(fieldPos);		//If lastSel index is provided, access the pointer straight from the playerBase vector
	piece->setPos(field->getCoord(moveTo).x, field->getCoord(moveTo).y);						//set the pos of the last selected figure to the pos of the cube clicked
	this->addToSide(currSideMove, field->emplaceBoard(piece->getPos(), moveTo));				//emplace the old figure, if any, with the new one																			
	piece->setCubePos(moveTo);			
	different(piece, field);	
	piece->setFirstFalse();


}




void rookCastlingHelper(int king, int rook, std::shared_ptr<King> kingFigure) {
	if (king) {
		if (rook % 2 == 0) kingFigure->setCastlingRight(false);
		else kingFigure->setCastlingLeft(false);
	}
	else
		if (rook % 2 == 0) kingFigure->setCastlingLeft(false);
		else kingFigure->setCastlingRight(false);
	
}


void Game::updateKingsThreads(Field* field, int lastSel, int input, int* KingsPos) {


	for (int i = 0; i < 2; i++) {
		playerBase.at(KingsPos[i])->updateMoves(field);			//Update both kings and their threads
	}

	if (std::shared_ptr<King> figure = std::dynamic_pointer_cast<King>(playerBase.at(lastSel))) {	//If one of the kings was chosen to move, update global king position
		kings[figure->getSide()] = input;
		figure->setFirstFalse();	
		figure->setCastling();													//Castling set to false
		if (field->isCastleSquare(figure->getPos())) {							//If the new position of the king belongs to castling positions, the corresponding rook is moved
			std::vector<int> ptr = figure->getRook(figure->getPos());		
			move(ptr.at(1), field, -1, ptr.at(0));
			
		}
	}
	for (int king = 0; king < 2 && getType<King>(KingsPos[king])->getFirst(); king++) {				//Among the two Kings if it still hasn't done any moves yet 									 
		for (int rook = king * 2; rook < (king + 1) * 2; rook++) {									//0 and 1 are for the White King - index 0, and 2 and 3 are for the Black King - index 1
			if (auto figure = getType<Rook>(field->figurePoint(rookPos[rook]))) {						//If the rook is in the starting position
				if (!figure->isFirst())																//Check if it didn't make any moves yet, because it could simply go back to the starting pos
					rookCastlingHelper(king, rook, getType<King>(field->figurePoint(kings[king])));
				else 
					rookCastlingHelper(king, rook, getType<King>(field->figurePoint(kings[king])));
			}

		}
	}
	delete[] KingsPos;
}








void Game::makeMove(sf::RenderWindow* window, Field* field) {
		sf::Vector2f clickPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));								
		int input = field->cubesClicked(clickPos, this);																
		if (input > -1) {																								//if clicked on a cube that is currently active
			move(input, field, lastSel);																			//Move the object																													
			updateKingsThreads(field, lastSel, input, new int[2] { KING_LIST_WHITE, KING_LIST_BLACK } );			//Update the current kings check mate condition. 
			check(field);																							//Check condition
			currSideMove = currSideMove > 0 ? 0 : 1;																//Switch current playing side
			switchMarkerPos(currSideMove);																			//Switch the green marker

			
			
		}
		undo(window, field);																							//Undo selection
		lock = true;																									//unlock for future selection
		
	
}


