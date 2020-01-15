#include "Menu.hpp"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("trs-million.ttf"))
	{
		return;
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color(50, 50, 50));
	menu[0].setString("PLAY");
	menu[0].setCharacterSize(55);
	menu[0].setPosition(sf::Vector2f(width / 3, height / 6));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("QUIT");
	menu[1].setCharacterSize(55);
	menu[1].setPosition(sf::Vector2f(width / 3, height / 3 * 2));
}

void Menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp() {
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color(50, 50, 50));
		menu[selectedItem].setStyle(sf::Text::Regular);
	}
}

void Menu::moveDown() {
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color(50, 50, 50));
		menu[selectedItem].setStyle(sf::Text::Regular);
	}
}
