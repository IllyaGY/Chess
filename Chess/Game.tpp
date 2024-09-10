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
#include <stdexcept>

class Pawn;
class Bishop;
class Knight;
class Rook;
class Queen;
class King;
class Field;


template <typename T>
std::shared_ptr<T> Game::getType(int pos){
	if (std::shared_ptr<T> figure = std::dynamic_pointer_cast<T>(playerBase.at(pos))){
		return figure;
	}
	return nullptr;
}template <typename T>
std::shared_ptr<T> Game::getType(std::shared_ptr<Figure> fig){
	if (std::shared_ptr<T> figure = std::dynamic_pointer_cast<T>(fig)){
		return figure;
	}
	return nullptr;
}

template <typename T>
void Game::figurePlacement(int& i, int* positions, int size_of_pos, Field* field, int objectSize) {
	for (int ind = 0; ind < size_of_pos; i++, ind++) {
		playerBase.push_back(std::make_shared<T>(field->getCoord(positions[ind]).x, field->getCoord(positions[ind]).y,
			((positions[ind] < 31) ? 0 : 1), positions[ind], objectSize));
		field->fillBoard(positions[ind], playerBase.at(i));
		
		

	}
	for(auto player: playerBase)
		player->updateMoves(field);
}


template <typename T>
void Game::objPosDef(T &obj, int offset, int side) {
	if (side) {
		obj.setPosition(sf::Vector2f(posBlack.x - offset, posBlack.y));
		return; 
	}
	obj.setPosition(sf::Vector2f(posWhite.x - offset, posWhite.y));
} 


template void Game::figurePlacement<Pawn>(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize); 
template void Game::figurePlacement<Bishop>(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);
template void Game::figurePlacement<Rook>(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);
template void Game::figurePlacement<Knight>(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);
template void Game::figurePlacement<Queen>(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);
template void Game::figurePlacement<King>(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);

template std::shared_ptr<Pawn> Game::getType<Pawn>(int);
template std::shared_ptr<Bishop> Game::getType<Bishop>(int);
template std::shared_ptr<Rook> Game::getType<Rook>(int);
template std::shared_ptr<Knight> Game::getType<Knight>(int);
template std::shared_ptr<Queen> Game::getType<Queen>(int);
template std::shared_ptr<King> Game::getType<King>(int);