#include "Wynik.hpp"
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <iterator>
#include <algorithm>
#include <string>
#include <list>
																		
Wynik::Wynik() : _Font(), _LevelText(), _WynikText(), _WyczyszczoneText(),_isGameOver(false),_InstrukcjaText(), _Wynik(0), _loadsWynik(0), _linieWyczyszczone(0) {
	_Font.loadFromFile("trs-million.ttf");
	_WynikText.setFont(_Font);
	_WynikText.setCharacterSize(20);
	_WynikText.setPosition(10 * 20 + 5, 20.f);

	_LevelText.setFont(_Font);
	_LevelText.setCharacterSize(20);
	_LevelText.setPosition(10 * 20 + 5, 90.f );

	_WyczyszczoneText.setFont(_Font);
	_WyczyszczoneText.setCharacterSize(20);
	_WyczyszczoneText.setPosition(10 * 20 + 5, 160.f);

	_GameOverText.setFont(_Font);
	_GameOverText.setString("GAME\nOVER");
	_GameOverText.setCharacterSize(45);
	_GameOverText.setPosition(45, 50);

	_InstrukcjaText.setFont(_Font);
	_InstrukcjaText.setString("ASD-Move\nSpace-Rotate\nI-Difficulty");
	_InstrukcjaText.setCharacterSize(15);
	_InstrukcjaText.setPosition(190,290);
	
	_InstrukcjaText2.setFont(_Font);
	_InstrukcjaText2.setString("ASD-Move\nSpace-Rotate\nI-Difficulty");
	_InstrukcjaText2.setCharacterSize(0);
	_InstrukcjaText2.setPosition(300,300);
}

void Wynik::update(const sf::Time &dt) {
	_LevelText.setString(std::string{ "Level:\n" + std::to_string(_linieWyczyszczone / 10) });
	_WynikText.setString(std::string{ "Wynik:\n" + std::to_string(_Wynik) });
	_WyczyszczoneText.setString(std::string{ "Linie:\n" + std::to_string(_linieWyczyszczone) });
}

void Wynik::reset() {
	_linieWyczyszczone = 0;
	_Wynik = 0;
}

void Wynik::dodajsWynik(int wynik) {
	_loadsWynik += wynik;
}

void Wynik::sumujsWynik() {
	_Wynik += _loadsWynik;
	_loadsWynik = 0;
}

void Wynik::zapiszWynik() {
	std::fstream plik;
	plik.open("Wynik.txt",std::fstream::app);
	plik << _Wynik;
	plik << (" ");
	plik.close();
}

void Wynik::Highscore() {
/*
	std::string line;
	std::ifstream plik;
	std::list<sf::Text> textList;
	sf::Text text("HS", _Font, 30);
	plik.open("Wynik.txt");
	if (plik.is_open()) {
		while (std::getline(plik,line)) {
			text.setString(line);
			textList.push_back(text);
		}
	}
	float i = 0;
	for (std::list<sf::Text>::iterator it = textList.begin(); it != textList.end(); it++) {
		sf::Text& text = *it;
		sf::FloatRect boundings = text.getLocalBounds();
		text.setPosition(0.f, i*(boundings.height + 5));
		i++;
		
	}*/

	std::fstream plik("Wynik.txt");
	std::vector<double>x(std::istream_iterator<double>(plik), {});
	std::sort(x.begin(), x.end(),std::greater<double>());
	std::cout << "Highscore:" << std::endl;
	for (const auto& elem : x) {
		std::cout << elem << " " << std::endl;
	} 
}

 bool Wynik::sort_function(double p, double q)
{
	return p>q;
}

void Wynik::draw(sf::RenderWindow &window) {
	if (not _isGameOver) {
		window.draw(_LevelText);
		window.draw(_WynikText);
		window.draw(_WyczyszczoneText);
		if (_ifdrawPause) {
			if( stan % 2!=0){
			window.draw(_InstrukcjaText);
			}
			else {
				window.draw(_InstrukcjaText2);
			}
		}
	}
	else {
		window.draw(_GameOverText);
	}
}

void Wynik::drawPause() {
	_ifdrawPause = true;
	 stan =stan+ 1;
}

void Wynik::GameOver() {
	_isGameOver = true;
}

void Wynik::dodajWyczyszczone(int liczba) {
	_linieWyczyszczone += liczba;
	int level = _linieWyczyszczone / 10;
	switch (liczba) {
	case (1): {
		_Wynik += 50 * (level + 1);
		break;
	}
	case (2): {
		_Wynik += 100 * (level + 1);
		break;
	}
	case (3): {
		_Wynik += 500 * (level + 1);
		break;
	}
	case (4): {
		_Wynik += 100 * (level + 1);
		break;
	}
	}
}

int Wynik::getLevel() const {
	return _linieWyczyszczone / 10;
}
