#include <SFML/Graphics.hpp>
#include <iostream>
#include "wtypes.h"
#include "Field.h"
#include "Figure.h"
#include "Pawn.h"
#include "Game.h"

#define OBJECT_SIZE 100.f

void ScreenRes(int &x, int &y) {
	RECT desktop;
	HWND win = GetDesktopWindow();
	GetWindowRect(win, &desktop);
	x = desktop.right;
	y = desktop.bottom;


}


int main()
{


	int side = 0;
	int x = 0, y = 0;
	ScreenRes(x, y);
	sf::RenderWindow window(sf::VideoMode(x, y), "SFML works!");
	window.clear();


	Field field(OBJECT_SIZE, x, y);

	Game game(&field, OBJECT_SIZE);

	




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
				game.lock = false; 
				


		}
		window.clear();










		field.fieldToScreen(&window);
		game.drawAll(&window, &field);
		window.display();


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !game.lock){
			if(game.done)
				game.checkIf(&window, &field);

			if (!game.done && !game.lock && game.getLast() > -1) 
				game.makeMove(&window, &field);

		
		}



	}

	return 0;
}