#include "stdafx.h"
#include "GameState.h"

void GameState::initTextures()
{
	textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Player_Spritesheet/Player_Animation_Sheet.png");
}

void GameState::initPauseMenu()
{
	pmenu = new PauseMenu(*window, font);
	pmenu->addButton("QUIT", 1300.f, "Quit");
}

void GameState::initFonts()
{
	if (!font.loadFromFile("Fonts/Brant.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
	}
}

void GameState::initKeybinds()
{
	keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");
}

void GameState::initPlayers()
{
	player = new Player(0, 0, textures["PLAYER_SHEET"]);

}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initKeybinds();
	initTextures();
	initFonts();
	initPauseMenu();
	initPlayers();
}

GameState::~GameState()
{
	delete pmenu;
	delete player;
}


void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyTime())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

//Functions
void GameState::updatePlayerInput(const float& dt)
{

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player->move(0.f, 1.f, dt);


}

void GameState::updatePauseMenuButtons()
{
	if (pmenu->isButtonPressed("QUIT"))
		endState();
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateKeyTime(dt);
	updateInput(dt);

	if (!paused) //Unpaused update
	{
		updatePlayerInput(dt);
		player->update(dt, window->getSize().x, window->getSize().y);

	}
	else //Paused update
	{
		pmenu->update(mousePosView);
		updatePauseMenuButtons();

	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	player->render(*target);

	if (paused) //Pause menu render
	{
		pmenu->render(*target);
	}
}