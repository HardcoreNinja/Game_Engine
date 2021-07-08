#include "Header.h"
#include "Game.h"

/*Initializers*/
void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
}
void Game::initGraphicsSettings()
{
	this->graphicsSettings.loadFromFile();
}
void Game::initWindow()
{
	auto style = graphicsSettings.isFullscreen ? sf::Style::Fullscreen : sf::Style::Close | sf::Style::Titlebar;
	{
		this->window = std::make_unique<sf::RenderWindow>(
			this->graphicsSettings.resolution, 
			this->graphicsSettings.title,
			style,
			this->graphicsSettings.contextSettings
			);
	}
	this->window->setFramerateLimit(this->graphicsSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->graphicsSettings.isVSync);
}
void Game::initCursor()
{
	/*Cursor*/
	if (!this->cursorImage.loadFromFile("Resources/Images/Cursor/cursor.gif"))
		throw ("ERROR::GAME::COULD_NOT_LOAD_CURSOR_IMAGE");
	if (
		!this->cursor.loadFromPixels(
			this->cursorImage.getPixelsPtr(),
			sf::Vector2u(this->cursorImage.getSize().x, this->cursorImage.getSize().y),
			sf::Vector2u(0, 0)
		)
		)
		throw ("ERROR::GAME::COULD_NOT_LOAD_CURSOR_PIXELS");

	/*Cursor Down*/
	if (!this->cursorImageDown.loadFromFile("Resources/Images/Cursor/cursor_down.gif"))
		throw ("ERROR::GAME::COULD_NOT_LOAD_CURSOR_IMAGE");
	if (
		!this->cursorDown.loadFromPixels(
			this->cursorImageDown.getPixelsPtr(),
			sf::Vector2u(this->cursorImageDown.getSize().x, this->cursorImageDown.getSize().y),
			sf::Vector2u(0, 0)
		)
		)
		throw ("ERROR::GAME::COULD_NOT_LOAD_CURSOR_PIXELS");

	this->window->setMouseCursor(this->cursor);
}
void Game::initSupportedKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int keyValue = 0;

		while (ifs >> key)
		{
			this->supportedKeys[key] = keyValue;
			keyValue++;
		}	
	}
	ifs.close();

		//Debug Tester
		for (auto i : this->supportedKeys)
		{
			std::cout << i.first << " " << i.second << '\n';
		}
}
void Game::initGameInfo()
{
	this->gameInfo.states = &this->states;
	this->gameInfo.graphicsSettings = &this->graphicsSettings;
	this->gameInfo.window = this->window.get();
	this->gameInfo.sfmlEvent = &this->sfmlEvent;
	this->gameInfo.supportedKeys = &this->supportedKeys;
	this->gameInfo.cursorImage = &this->cursorImage;
	this->gameInfo.cursor = &this->cursor;
	this->gameInfo.cursorImageDown = &this->cursorImageDown;
	this->gameInfo.cursorDown = &this->cursorDown;
}
void Game::initStates()
{
	this->states.push_back(std::make_unique<MainMenu>(&this->gameInfo));
}

/*Constuctor & Destructor*/
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initCursor();
	this->initSupportedKeys();
	this->initGameInfo();
	this->initStates();
}
Game::~Game()
{
}

/*Update Functions*/
void Game::updateDeltaTime()
{
	this->dt = this->dtClock.restart().asSeconds();
}
void Game::update()
{
	this->updateDeltaTime();
	//this->updateSFMLEvents();
	if (!this->states.empty())
	{
		this->states.back()->update(this->dt);

		if (this->states.back()->getisQuit())
			this->states.pop_back();
	}
	else
	{
		this->window->close();
	}
}

/*Render Functions*/
void Game::render()
{
	this->window->clear(sf::Color::Black);
	if(!this->states.empty())
	this->states.back()->render();
	this->window->display();
}

/*Run Functions*/
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
