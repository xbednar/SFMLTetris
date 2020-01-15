#include "Game.hpp"
#include "Random.hpp"
#include <SFML/Window.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include "Menu.hpp"

using namespace std::chrono_literals;

Game::Game() : _RenderWindow{ sf::VideoMode{10 * 20 + 100, 19 * 19}, "Tetris", sf::Style::Default }, _Tekstura(), _liniaSep(), _Blok(nullptr), _Podglad(nullptr), _Siatka(), _wynik(), _ElapsedTime(sf::Time::Zero), _ID(getRandomNumber(7)){
	_liniaSep.setSize(sf::Vector2f{ 1.f, 20.f * 20.f });
	_liniaSep.setPosition(sf::Vector2f{ 10.f * 18.f, 0 });
	_liniaSep.setFillColor(sf::Color::Magenta);
	_Tekstura.loadFromFile("tiles.png");
	_Siatka = std::make_unique<Siatka>(sf::Vector2i{ 10, 20 }, *this);									//Utworzenie obiektu siatki
	stworzBlok();
}

void Game::run() {
	sf::Clock zegar;
	sf::Time dT{ sf::Time::Zero };
	while (_RenderWindow.isOpen()) {
		sf::Time trigger{ sf::seconds(85.f / (85.f + (_wynik.getLevel() * (_wynik.getLevel() * 5.f)))) };			//Wyzszy level = trudniej
		dT = zegar.restart();
		_ElapsedTime += dT;
		wydarzenia();
		update(dT);
		if (_ElapsedTime > trigger) {
			_ElapsedTime = sf::Time::Zero;
			przystap(Sterowanie::Down);
		}
		render();
	}
}

void Game::update(const sf::Time &dt) {	
		_Siatka->update(dt);
		_wynik.update(dt);
		if (!_Blok) {
			if (_Siatka->UsunBlok()) {
				return;
			}
			stworzBlok();
		}
	}

void Game::obrot() {
	if (!_Blok)
		return;
	_Blok->obrot();
	if (!czyMoznaRuch(_Blok->getBlokPos())) {
		_Blok->powrot();
	}
}

void Game::wydarzenia() {
	sf::Event event;
	while (_RenderWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) _RenderWindow.close();
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::S) {
				przystap(Sterowanie::sDown);
			}
			else if (event.key.code == sf::Keyboard::D) {
				przystap(Sterowanie::Right);
			}
			else if (event.key.code == sf::Keyboard::A) {
				przystap(Sterowanie::Left);
			}
			else if (event.key.code == sf::Keyboard::Space) {
				obrot();
			}	
			else if (event.key.code == sf::Keyboard::I) {
				_wynik.dodajWyczyszczone(10);
			}
			else if (event.key.code == sf::Keyboard::Escape) {
				_RenderWindow.close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
				_wynik.drawPause();
			//	Sleep(1000);
			//	std::this_thread::sleep_for(std::chrono::microseconds(2));
			}
		}
	}
}

void Game::render() {
	_RenderWindow.clear(sf::Color::Black);
	_wynik.draw(_RenderWindow);
	_Siatka->draw(_RenderWindow);
	if (_Blok) {
		_RenderWindow.draw(*_Blok);
	}
	_RenderWindow.draw(*_Podglad);
	_RenderWindow.draw(_liniaSep);
	_RenderWindow.display();
}

void Game::przystap(Sterowanie kierunek) {
	if (!_Blok) {
		return;
	}
	if (czyMoznaRuch(_Blok->getFutBlokPos(kierunek))) {														//Sprawdzenie zgodnosci nast pozycji
		_Blok->ruch(kierunek);
		if (kierunek == Sterowanie::sDown)
			_wynik.dodajsWynik(1);
	}
	else {
		if (kierunek == Sterowanie::Down || kierunek == Sterowanie::sDown) {
			int ID = _Blok->getID();
			_Siatka->dodajBlok(ID, _Blok->getBlokPos());
			_Blok.reset(nullptr);
			_wynik.sumujsWynik();
		}
	}
}

bool Game::czyMoznaRuch(std::array<sf::Vector2i, 4> blok) {													//Sprawdzenie kolizji
	for (int i = 0; i < 4; i++) {
		if (blok[i].x < 0 || blok[i].x > 9 || blok[i].y > 19) {
			return false;
		}
		if (czyZajety(blok[i].x, blok[i].y)) {
			return false;
		}
	}
	return true;
}

bool Game::czyZajety(int x, int y) {
	return _Siatka->getPole(x, y)->Zajety;
}

void Game::stworzBlok() {
	_Blok.reset(new Bloki{ _Tekstura, _ID });																//Gdy siatka pelna nowa gra
	if (_Siatka->czyZajety(_Blok->getBlokPos())) {
		_Siatka->wyczysc();
		_wynik.zapiszWynik();
		_wynik.reset();
		_RenderWindow.clear();
		_wynik.GameOver();
		_wynik.Highscore();
	}
	_ID = getRandomNumber(7);
	_Podglad.reset(new Bloki{ _Tekstura, _ID });
	_Podglad->setPos(sf::Vector2i{ 11, 12 });
}
