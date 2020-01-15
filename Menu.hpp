#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#define MAX_LICZBA_POZIOMOW 2

class Menu {

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0;

public:
	Menu(float width, float height);
	~Menu() {};
	void moveUp();
	void moveDown();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow &window);
};

#endif 
