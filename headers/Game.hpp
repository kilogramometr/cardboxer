#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"

class Game
{
	//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	Button button;
	Button button2;

	sf::Vector2f mousePosition;

	bool mouseHold;

	//Private functions
	void initVariables();
	void initWindow();

	void initButtons();

	void updateMouse();
	void updateButtonClicks();

public:
	//Constructor destructor
	Game();
	virtual ~Game();

	//Getters
	const bool running() const;

	//Functions
	void pollEvents();
	void update();
	void render();
};
