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


#pragma once
#include <memory>
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>

#include "Field.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"




#define KING_LIST_WHITE 30
#define KING_LIST_BLACK 31 

#define MIDDLE_BOTTOM_INDEX 3
#define MIDDLE_TOP_INDEX 59
#define MARKER_OFFSET 50

#define LEFT_BORDER 0
#define RIGHT_BORDER 8


enum NUMS {
	PAWNS = 16,
	BISHOPS = 4,
	ROOKS = 4,
	KNIGHTS = 4,
	QUEENS = 2,
	KINGS = 2

};

struct PromMenu {
	std::array<std::string, 4> paths{ "bishop","rook","queen","knight" };
	std::string path = "Textures/";
	std::vector<Bishop> figuresObj{};
	int size; 
	sf::Vector2f posBlack;
	sf::Vector2f posWhite;
	PromMenu() {}
	PromMenu( int size, sf::Vector2f posBlack, sf::Vector2f posWhite) {
		this->posBlack = posBlack;
		this->posWhite = posWhite;
		this->size = size; 
		
		
	}

public: 
	void menuDraw(sf::RenderWindow *window) {
		/*for (auto& i : figuresObj) {
			i.drawFigure(window);
		}*/
		/*figuresObj.at(0).drawFigure(window);*/
	}
	void init(int side) {
		/*sf::Vector2f pos = side ? posBlack : posWhite; 
		int offset = 0;
		for (std::string i : paths) {
			std::string texture = path + i + (side ? "" : "White") + ".png";
			figuresObj.push_back(Bishop(pos.x + offset, pos.y, side, -1, size));
			figuresObj.back().def(texture);
			offset += size;
		}*/
	}


};


class Game
{
public:

	int* pawnPos = nullptr;
	int* bishopPos = nullptr;
	int* rookPos = nullptr;
	int* knightPos = nullptr;
	int* queenPos = nullptr;
	int* kingPos = nullptr;

	std::shared_ptr<Pawn> currentEnPassPawn; 
	std::vector<std::shared_ptr<Pawn>> enPawnAttackers{};

	std::vector<std::shared_ptr<Figure>> possesCheck{};

	std::vector<std::shared_ptr<Figure>> refsToObj{}; 



	int kings[2] = {-1,-1 }; 


	bool endGame = false;


	PromMenu promMenu;
	int sideProm = -1;

	int playerSide; 
	int checkS = -1; 

	sf::Font font;
	int white = 0; 
	int black = 0; 

	sf::Vector2f posWhite; 
	sf::Vector2f posBlack; 


	std::string WHITE = "White: ";
	std::string BLACK = "Black: ";

	sf::Text scoreWhite; 
	sf::Text scoreBlack; 
	sf::Text checkText; 

	sf::CircleShape sideMarker;


	int currSideMove = 0; //0 - White, 1 - Black

	std::vector<std::shared_ptr<Figure>> playerBase{};
	int lastSel = -1;
	bool done = true;
	bool lock = false; 


	Game(int side, Field *field, int objectSize);

	void defScore(sf::Vector2f pos1, sf::Vector2f pos2, float offset1, float offset2);


	template <typename T>
	std::shared_ptr<T> getType(int pos);


	template <typename T>
	std::shared_ptr<T> getType(std::shared_ptr<Figure>);


	template <typename T>
	void figurePlacement(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);

	template <typename T>
	void objPosDef(T &obj, int offset, int side);


	
	int getLast();
	int getActionState();
	int getLockState(); 
	int getSideGlob(int index); 


	void switchMarkerPos(int side);
	void addToSide(int side, int points);
	void drawAll(sf::RenderWindow *window, Field *field);
	void undo(sf::RenderWindow *window, Field *field);
	
	void enPass(std::shared_ptr<Pawn> pawnAtUse, Field* field);

	void showPawnPromMenu(std::shared_ptr<Pawn> pawn);
	void checkPawnPromotion(std::shared_ptr<Pawn> pawn, Field* field);
	void checkIf(sf::RenderWindow *window, Field *field);
	bool end();
	void deletePlayers(Field* field);
	void winScreen(sf::RenderWindow* window, int x, int y);
	void logicUpdate(std::shared_ptr<Figure> piece, Field* field,int input);
	void move(int moveTo, Field* field, int lastSel, int fieldPos = -1);
	void rookCastlingUpdate(Field* field, std::shared_ptr<Rook> rook);
	void ifKingChosen(std::shared_ptr<King> figure, int input, Field* field);
	void updateKings(Field* field, std::array<int, 2> KingsPos);
	void beforeFigUpdate(std::shared_ptr<Figure> piece, Field* field);
	void afterFigUpdate(std::shared_ptr<Figure> piece, Field* field, int input);
	void makeMove(sf::RenderWindow *window, Field *field);

	void check(Field* field);	
};


#include "Game.tpp"
