#include "Header.h"
#include "GameState.h"

/*Initializers*/
void GameState::initVariables()
{
}
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/editor_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = this->supportedKeys->at(keyboardKey);
	}
	ifs.close();

	//Debug Tester
	for (auto i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void GameState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/Dosis.ttf"))
	{
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:Dosis.ttf");
	}

	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(sf::Vector2f(static_cast<float>(this->mousePositionWindow.x), static_cast<float>(this->mousePositionWindow.y)));
}
void GameState::initTileMap()
{
	this->tileMap = std::make_unique<TILEMAP::TileMap>(
		this->tileSize,                                //Tile Size
		42, 42,                                        //Map Width & Height (in Squares)
		this->tileSize, this->tileSize,                //Texture Width & Height
		"Resources/Images/Tiles/PipoyaMasterLevel.png" //Tile Sheet File Path
		);
}
void GameState::initPauseMenu()
{
	this->pauseMenu = std::make_unique<PauseMenu>(
		*this->window, //Pause Menu Render Window
		this->font    //Pause Menu Font;
		);

	this->pauseMenu->addButton(
		"EXIT",                                                 //Key
		static_cast<float>(this->window->getSize().y) - 100.f,  // Pos_Y
		"Exit"                                                  // Button Text
	);
}
void GameState::initLatestTileMap()
{
	this->tileMap->loadFromFile("Config/tile_map.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
}
void GameState::initPlayer()
{
	this->player = std::make_unique<Player>(Actors::Actor_0, this->supportedKeys);
}

/*Constuctor & Destructor*/
GameState::GameState(GameInfo* game_info)
	: State(game_info)
{
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initTileMap();
	this->initPauseMenu();
	this->initLatestTileMap();
	this->initPlayer();
}
GameState::~GameState()
{
}

/*Update Functions*/
void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("EXIT") && this->getKeyTime())
		this->endState();
}
void GameState::updateUserInput(const float& dt)
{
	/*Pause Game*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE_GAME"))) && this->getKeyTime())
		if (!this->isPaused)
			this->pause();
		else
			this->unpause();

	if (!this->isPaused)
	{
	}
}
void GameState::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateMousePosition(&this->view, &this->defaultWindowView);
	this->updateUserInput(dt);
	this->player->update(dt);

	if (this->isPaused) //Paused
	{
		this->pauseMenu->update(static_cast<sf::Vector2f>(this->mousePositionGUI));
		this->updatePauseMenuButtons();
	}
	else               //Unpaused
	{
	}
}

/*Reinitialize Functions*/
void GameState::reinitializeState()
{
	std::cout << "Reinitializing Game State!\n";
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initTileMap();
	this->initPauseMenu();
	this->initLatestTileMap();
}

/*Render Functions*/
void GameState::renderPauseMenu(sf::RenderTarget& target)
{
	this->pauseMenu->render(target);
}
void GameState::renderTileMap(sf::RenderTarget& target)
{
	this->tileMap->render(target, this->view);
}
void GameState::renderPlayer(sf::RenderTarget& target)
{
	this->player->render(target);
}
void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	/*Items Rendered with Camera View*/
	target->setView(this->view);
	this->renderTileMap(*target);
	this->renderPlayer(*target);

	/*Items Rendered with Default Window View*/
	this->window->setView(this->defaultWindowView);

	/*Items Rendered with Camera View*/
	target->setView(this->view);

	/*Items Rendered with Default Window View*/
	this->window->setView(this->defaultWindowView);
	if (this->isPaused)
		this->renderPauseMenu(*target);
}