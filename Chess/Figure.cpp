#include "Figure.h"
#include "Field.h"




Figure::Figure(float x, float y, int side, int pos, float size) {
	sideColor = side;
	this->pos = pos;
	this->size = size;
	this->figure.setSize(sf::Vector2f(size, size));
	this->figure.setPosition(sf::Vector2f(x, y));

}

void Figure::setPos(float x, float y) {
	this->figure.setPosition(sf::Vector2f(x, y));


}


void Figure::def(std::string texturePath) {
	if (!textureForm.loadFromFile(texturePath))
		if (!textureForm.create(size, size))
			throw std::invalid_argument("Texture could not be loaded");
	figure.setTexture(&textureForm);
}

void Figure::setPos(sf::Vector2f cubePos) {
	this->figure.setPosition(cubePos);

}

int Figure::getPoints() {
	return pointsForFigure;
}
//Border check

bool Figure::lB(int pos) {
	return pos % 8 == 0;
}

bool Figure::rB(int pos) {
	return (pos - 7) % 8 == 0;
}

bool Figure::tB(int pos) {
	return pos < rowTOP;
}
bool Figure::bB(int pos) {
	return pos > rowBOTTOM;
}



void Figure::getAttackVec(std::vector<int>& attackVec) {
	attackVec = attackPos;
}



int Figure::getSide()
{
	return sideColor;
}

int Figure::getPos() {
	return pos;
}

void Figure::setCubePos(int pos) {
	this->pos = pos; 
}






void Figure::drawFigure(sf::RenderWindow *window) {
	window->draw(figure);
}






void Figure::vecClean() {
	active.clear();
	attackPos.clear();
}


void Figure::updateMoves(Field *field) {
	this->vecClean();
	this->updateNext(field);
}


bool Figure::isClicked(sf::Vector2f pos) {
	sf::Vector2f p = figure.getPosition();
	if (float(pos.x) >= figure.getPosition().x 
		&& float(pos.x) <= figure.getPosition().x + size && 
		float(pos.y) >= figure.getPosition().y && 
		float(pos.y) <= figure.getPosition().y + 100.f)
		return true;
	return false;
}






void Figure::setUndraw() {
	this->setPos(0, 0);
	this->figure.setSize(sf::Vector2f(0, 0));
	pos = -1;
}






void Figure::selectedItem(sf::RenderWindow *window, Field* field, int action) {
	if (action) {
		figure.setFillColor(sf::Color::Green);
		this->updateMoves(field);
		field->setPassMove(active, attackPos, pos);
	}
	else{
		figure.setFillColor(sf::Color::White);
		field->deactivateMove();
	}


}



void Figure::horizHelper(int move, Field* field, bool (Figure::* func)(int),  bool king) {
	if (!(this->*func)(pos)) {
		for (int i = pos + move;; i += move) {
			if (field->isTaken(i)) {
				attackPos.push_back(i);
				break;
			}
			else active.push_back(i);

			if ((this->*func)(i)) break;
			if (king) break;
		}
		
	}
}

void Figure::horizMove(Field* field,  bool king) {
	bool (Figure:: * func[4])(int) = { &Figure::tB, &Figure::lB, &Figure::rB,&Figure::bB };
	int moves[] = { -8, -1, 1, 8 }; 
	for (int i = 0; i < 4; i++) {
		horizHelper(moves[i], field, func[i], king);
	}

}

void Figure::diagHelper(Field* field, int &diag, bool &diagPossible, bool(Figure::*func1)(int), bool(Figure::* func2)(int), int toGo){
	bool f1 = !(this->*func1)(diag);
	bool f2 = !(this->*func2)(diag);
	if (diagPossible && !(this->*func1)(diag) && !(this->*func2)(diag) && diag + toGo >= 0 && diag + toGo < 64) {
		if (!field->isTaken(diag + toGo)) {
			diag += toGo;
			active.push_back(diag);
		}
		else {
			attackPos.push_back(diag + toGo);
			diagPossible = false;
		}
	}
	else diagPossible = false;
}

void Figure::diagMove(Field* field, bool king) {						
	bool (Figure:: * func[4][2])(int) = { {&Figure::lB, &Figure::tB}, {&Figure::rB,&Figure::tB},{&Figure::lB, &Figure::bB},{&Figure::rB, &Figure::bB} };
	bool diagPossible[4];
	for (auto& i : diagPossible) i = true;
	int diag[4] = {};
	for (auto& i : diag) i = pos;
	while (diagPossible[0] || diagPossible[1] || diagPossible[2] || diagPossible[3]) {
		for(int i = 0; i < 4; i++)
			diagHelper(field, diag[i], diagPossible[i], func[i][0], func[i][1], diagCoords[i]);
		if (king) break;
	}
}


