#include "Game.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include <stdexcept>

class Pawn;
class Bishop;

template <typename T>
std::shared_ptr<T> Game::getType(int pos){
	if (std::shared_ptr<T> figure = std::dynamic_pointer_cast<T>(playerBase.at(pos))){
		return figure;
	}
	return nullptr;
}


template std::shared_ptr<Pawn> Game::getType<Pawn>(int);
template std::shared_ptr<Bishop> Game::getType<Bishop>(int);