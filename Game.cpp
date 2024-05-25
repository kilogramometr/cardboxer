#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
	this->mouseHold = false;
}

//Private functions
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initButtons()
{
	button.initButton(sf::Vector2f(100, 100), sf::Vector2f(200, 100), sf::Vector2f(20, 15), 55, sf::Color::Green, "Button 1");
	button2.initButton(sf::Vector2f(300, 300), sf::Vector2f(200, 100), sf::Vector2f(20, 15), 55, sf::Color::Red, "Button 2");
}

void Game::updateMouse()
{
	sf::Vector2i mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosition = this->window->mapPixelToCoords(mousePosWindow);
}

void Game::updateButtonClicks()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button.getGlobalBounds().contains(this->mousePosition) && this->mouseHold == false)
		{
			std::cout << "Button1 clicked" << std::endl;
		}
		if (this->button2.getGlobalBounds().contains(this->mousePosition) && this->mouseHold == false)
		{
			std::cout << "Button2 clicked" << std::endl;
		}

		this->mouseHold = true;	
	}
	else
	{
		this->mouseHold = false;
	}
}

//Constructor destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();

	this->initButtons();
}

Game::~Game()
{
	delete this->window;
}

//Getters
const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

//Update
void Game::update()
{
	this->pollEvents();

	this->updateMouse();

	this->updateButtonClicks();
}

//Render
void Game::render()
{
	this->window->clear();

	this->button.render(*this->window);
	this->button2.render(*this->window);

	this->window->display();
}