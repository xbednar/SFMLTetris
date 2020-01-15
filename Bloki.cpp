#include "Bloki.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

unsigned int BlokTyp[7][4] = {
	{1,5,9,13},//I
	{5,9,10,14},//Z
	{5,9,8,12},//S
	{5,8,9,10},//T
	{5,9,13,14},//L
	{5,9,13,12},//~L
	{4,5,8,9},//SQ	
};

Bloki::Bloki(sf::Texture& tekstura, int ID) : _Pozycja(sf::Vector2i{ 3, 0 }), _aktObrot(0), _ID(ID), _Blok(), Sprite(tekstura, sf::IntRect{ (ID % 7) * 18, 0, 18, 18 }) {
	_ID = _ID % 7; 
	for (auto i = 0; i < 4; i++) {
		_Blok[i].x = BlokTyp[_ID][i] % 4;																//Zamiana z 1D na 2D
		_Blok[i].y = BlokTyp[_ID][i] / 4;
	}
}

void Bloki::obrot() {
	_staryBlok = _Blok;																					//Zapisuje stara pozycje do ew powrotu

	if (_ID == 6) {
		return;
	}

	for (auto i = 0; i < 4; i++) {
		sf::Vector2i staryPkt = _Blok[i];																//Aktualna pozycja bloku								
		sf::Vector2i wektor = staryPkt - sf::Vector2i{ 1,2 };											//Wektor miedzyblokiem a sr obrotu
		sf::Vector2i nowyPkt{ (0 * wektor.x) + (-1 * wektor.y), (1 * wektor.x) + (0 * wektor.y) };		//Obrot
		_Blok[i] = sf::Vector2i{ 1,2 } + nowyPkt;
	}
}

void Bloki::ruch(Sterowanie kierunek) {
	if (kierunek == Sterowanie::Left) {
		_Pozycja.x--;
	}
	else if (kierunek == Sterowanie::Right) {
		_Pozycja.x++;
	}
	else {
		_Pozycja.y++;
	}
}

void Bloki::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (int i = 0; i < 4; i++) {
		Sprite.setPosition((_Blok[i].x * 18) + (_Pozycja.x * 18), (_Blok[i].y * 18) + (_Pozycja.y * 18));
		target.draw(Sprite);
	}
}

std::array<sf::Vector2i, 4> Bloki::getBlokPos() const {													//Zwraca pozycje 4 blokow
	std::array<sf::Vector2i, 4> blokPos;
	for (auto i = 0; i < 4; i++) {
		blokPos[i] = sf::Vector2i{ _Blok[i].x + _Pozycja.x, _Blok[i].y + _Pozycja.y };
	}
	return blokPos;
}

std::array<sf::Vector2i, 4> Bloki::getFutBlokPos(Sterowanie kierunek) const {
	std::array<sf::Vector2i, 4> blokPos;
	sf::Vector2i tempPos{ _Pozycja };
	if (kierunek == Sterowanie::Left) {
		tempPos.x--;
	}
	else if (kierunek == Sterowanie::Right) {
		tempPos.x++;
	}
	else {
		tempPos.y++;
	}
	for (auto i = 0; i < 4; i++) {
		blokPos[i] = sf::Vector2i{ _Blok[i].x + tempPos.x, _Blok[i].y + tempPos.y };
	}
	return blokPos;
}

void Bloki::powrot() {																					//Gdy napotka blad
	_Blok = _staryBlok;
}

int Bloki::getID() const {
	return _ID;
}

void Bloki::setPos(const sf::Vector2i& pozycja) {
	_Pozycja = pozycja;
}
