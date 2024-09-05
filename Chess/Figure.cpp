#include "Figure.h"
#include "Field.h"

std::vector<std::vector<int>> Figure::diagMoves{};
std::vector<std::vector<int>> Figure::XYMoves{};

int Figure::diagCoords[4] = { diagBottomRIGHT, diagBottomLEFT, diagUpRIGHT, diagUpLEFT };
int Figure::XYCoords[4] = { DOWN, LEFT, RIGHT, UP };


Figure::Figure(float x, float y, int side, int pos, float size) {
	sideColor = side;
	this->pos = pos;
	this->firstPos = pos;
	this->size = size;
	this->firstTime = true; 
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

std::vector<int> Figure::getActive() {
	return active;
}

std::vector<int> Figure::getAttackVec() {
	return attackPos;
}





int Figure::getSide()
{
	return sideColor;
}

int Figure::getPos() {
	return pos;
}
int Figure::getFirstPos() {
	return firstPos;
}

void Figure::setCubePos(int pos) {
	this->pos = pos; 

}



bool Figure::isFirst() {
	return firstTime;
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


void Figure::setFirstFalse() {
	firstTime = false; 
}



void Figure::setUndraw() {
	this->setPos(0, 0);
	this->figure.setSize(sf::Vector2f(0, 0));
	pos = -1;
	vecClean();
}








void Figure::selectedItem(sf::RenderWindow *window, Field* field, int action) {
	figure.setFillColor(action ? sf::Color::Green : sf::Color::White);
	if (action) { 
		field->setPassMove(this); 
		return;
	} 
	else field->deactivateMove();
	


}


bool Figure::canCastle() {
	return pos == firstTime;
}


void dirHelperFunc(Field* field, int& pos, int& side, std::vector<int>& movementVec, std::vector<int>& active, std::vector<int>& attackPos) {
	bool negativeSeen = false; //Helps skip all the left over squares if, the previous square is taken
	for (auto& i : movementVec) {
		if (!negativeSeen) {
			if (field->isTaken(i) == -1)
				active.push_back(i);
			else if (field->isTaken(i) != side) {
				attackPos.push_back(i);
				negativeSeen = true;
			}
			else negativeSeen = true;
		}
		if (i == -1) negativeSeen = false;
	}

}


void Figure::horizMove(Field* field, int &pos, int &side) {
	dirHelperFunc(field, pos, side, XYMoves.at(pos), active, attackPos); 
}


bool Figure::horizHelper(int &move, bool (* func)(int), int &pos, std::vector<int>& allDirsVec) {
	for (int i = pos;;i += move) {
		if (!(*func)(i)) {
			pos += move; 
			allDirsVec.push_back(pos);
			return true;
		}
		allDirsVec.push_back(-1);
		return false; 
	}
		
	
}

void Figure::fillOutXY() {
	bool (* func[4])(int) = { &tB, &lB, &rB,&bB };										//FIX
	std::array<bool, 4> axesPossible = {};
	std::array<int, 4> axes = {};
	for (int pos = 0; pos < limitDOWN; pos++) {
		for (auto& i : axesPossible) i = true;
		for (auto& i : axes) i = pos;
		std::vector<int> allDirsVec{}; 
		for (int i = 0; i < 4;) {
			if (axesPossible.at(i))
				axesPossible.at(i) = horizHelper(XYCoords[i], func[i], axes[i], allDirsVec);			//Goes through each direction bottom, left, right, top for white black's y-axis reverse
			else
				i++;
		}
		
		XYMoves.push_back(allDirsVec);
	}
}



void Figure::diagMove(Field* field, int& pos, int& side) {
	dirHelperFunc(field, pos, side, diagMoves.at(pos), active, attackPos);
}



/*Static diagonal movement fill*/
bool Figure::diagHelper(std::vector<int> &dirs, int &diag, bool(*func1)(int), bool(*func2)(int), int change){
	bool f1 = !(*func1)(diag);
	bool f2 = !(*func2)(diag); 
	if (!(*func1)(diag) && !(*func2)(diag) && diag + change > limitUP && diag + change < limitDOWN) {
		diag += change;
		dirs.push_back(diag);
		return true; 
		
	}

	dirs.push_back(-1);
	return false; 

}


void Figure::fillOutDiag() {
	bool (*func[4][2])(int) = { {&lB, &tB}, {&rB,&tB},{&lB, &bB},{&rB, &bB} };	//Edges for each diagonal direction
	std::array<bool, 4> diagPossible = {};
	std::array<int, 4> diag = {};
	for (int pos = 0; pos < SIZE; pos++) {
		std::vector<int> allDiagDirs{}; 
		for (auto& i : diagPossible) i = true;
		for (auto& i : diag) i = pos;
		for (int i = 0; i < 4;) {
			if (diagPossible.at(i))
				diagPossible.at(i) = diagHelper(allDiagDirs, diag.at(i), func[i][0], func[i][1], diagCoords[i]);
			else i++;
		}
		
		diagMoves.push_back(allDiagDirs);
	}
}


void fillOutXY() {

}