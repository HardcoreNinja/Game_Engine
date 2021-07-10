#include "Header.h"
#include "Game.h"

/*Initializers*/
void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;

	this->graphicsSettings = std::make_unique<GraphicsSettings>();
	this->sfmlEvent = std::make_unique<sf::Event>();
}
void Game::initAudio()
{
	std::ifstream ifs_sfx("Config/sfx.ini");

	if (ifs_sfx.is_open())
	{
		std::string key = "";
		std::string file_path = "";

		while (ifs_sfx >> key >> file_path)
		{
			std::cout << file_path << '\n';
			audio = std::make_unique<Audio>(true, file_path);
			audioMap[key] = std::move(audio);
		}
	}
	ifs_sfx.close();

	std::ifstream ifs_music("Config/music.ini");

	if (ifs_music.is_open())
	{
		std::string key = "";
		std::string file_path = "";

		while (ifs_music >> key >> file_path)
		{
			std::cout << file_path << '\n';
			audio = std::make_unique<Audio>(false, file_path);
			audioMap[key] = std::move(audio);
		}
	}
	ifs_music.close();

	//Debug Tester
	for (auto& i : this->audioMap)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void Game::initGraphicsSettings()
{
	this->graphicsSettings->loadFromFile();
}
void Game::initWindow()
{
	auto style = graphicsSettings->isFullscreen ? sf::Style::Fullscreen : sf::Style::Close | sf::Style::Titlebar;
	{
		this->window = std::make_unique<sf::RenderWindow>(
			this->graphicsSettings->resolution, 
			this->graphicsSettings->title,
			style,
			this->graphicsSettings->contextSettings
			);
	}
	this->window->setFramerateLimit(this->graphicsSettings->frameRateLimit);
	this->window->setVerticalSyncEnabled(this->graphicsSettings->isVSync);

	if (!this->appIcon.loadFromFile("Resources/Images/App Icon/window_icon.png"))
		throw ("ERROR::GAME::COULD_NOT_LOAD_APP_ICON");

	this->window->setIcon(this->appIcon.getSize().x, this->appIcon.getSize().y, this->appIcon.getPixelsPtr());
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
	this->gameInfo.graphicsSettings = this->graphicsSettings.get();
	this->gameInfo.window = this->window.get();
	this->gameInfo.sfmlEvent = this->sfmlEvent.get();
	this->gameInfo.supportedKeys = &this->supportedKeys;
}
void Game::initStates()
{
	this->states.push_back(std::make_unique<MainMenu>(&this->gameInfo));
}

/*Constuctor & Destructor*/
Game::Game()
	: gameInfo(this->audioMap)
{
	this->initVariables();
	this->initAudio();
	this->initGraphicsSettings();
	this->initWindow();
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
void Game::updateAudio()
{
	for (auto& i : this->audioMap)
	{
		i.second->update();
	}
}
void Game::update()
{
	this->updateDeltaTime();
	//this->updateSFMLEvents();
	if (!this->states.empty())
	{
		this->updateAudio();

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
