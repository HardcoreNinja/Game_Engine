#include "Header.h"
#include "GameState.h"

/*Initializers*/
void GameState::initVariables()
{
	this->projectileType = ProjectileTypes::Black_Tornado_0;
}
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/game_state_keybinds.ini");

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
void GameState::initRenderTexture()
{
	//std::cout << "Window Size: " << this->window->getSize().x << " x " << this->window->getSize().y << '\n';
	this->renderTexture.create(this->window->getSize().x, this->window->getSize().y);
	this->renderTexture.setSmooth(true);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->window->getSize().x, this->window->getSize().y));
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
void GameState::initPlayer(int texture_switch_counter, bool male_0_female_1)
{
	this->player = std::make_unique<Player>(this->supportedKeys, texture_switch_counter, male_0_female_1);
}

/*Constructor & Destructor*/
GameState::GameState(GameInfo* game_info, int texture_switch_counter, bool male_0_female_1)
	: State(game_info)
{
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initRenderTexture();
	this->initTileMap();
	this->initPauseMenu();
	this->initLatestTileMap();
	this->initPlayer(texture_switch_counter, male_0_female_1);
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
}
void GameState::updateInGameActions()
{
	/*Firing Projectile*/
	float projectile_DeltaTime = this->projectileClock.getElapsedTime().asSeconds();
	float projectile_SwitchTime = 0.2;

	if (projectile_DeltaTime > projectile_SwitchTime)
	{
		this->projectileClock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))))
		{
			this->projectile = std::make_unique<Projectile>();
			this->projectile->setProjectileType(this->projectileType);
			this->projectile->setProjectileDirection(this->player->getPlayerDirection());
			this->projectile->setProjectilePosition(this->player->getSpriteRect());
			this->projectileVector.push_back(std::move(this->projectile));
		}
	}
}
void GameState::updateProjectileSpawnLoop(const float& dt)
{
	int counter = 0;
	for (this->projectileItr = this->projectileVector.begin(); this->projectileItr != this->projectileVector.end(); this->projectileItr++)
	{
		this->projectileVector[counter]->update(dt);

		counter++;
	}
}
void GameState::updateProjectileDestroyLoop()
{
	int counter = 0;
	for (this->projectileItr = this->projectileVector.begin(); this->projectileItr != this->projectileVector.end(); this->projectileItr++)
	{
		
		if (this->projectileVector[counter]->getDestroy())
		{
			this->projectileVector.erase(projectileItr);
			break;
		}

		counter++;
	}
	
}
void GameState::updateProjectileWallCollision()
{
	int counter = 0;
	for (this->projectileItr = this->projectileVector.begin(); this->projectileItr != this->projectileVector.end(); this->projectileItr++)
	{
		this->projectileVector[counter]->tileCollision(this->tileMap->getCollision(this->projectileVector[counter]->getSpriteRect()));

		if (this->projectileVector[counter]->getDestroy())
		{
			this->projectileVector.erase(projectileItr);
			break;
		}

		counter++;
	}
}
void GameState::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateMousePosition(&this->view, &this->defaultWindowView);
	this->updateUserInput(dt);
	
	if (this->isPaused) //Paused
	{
		this->pauseMenu->update(static_cast<sf::Vector2f>(this->mousePositionGUI));
		this->updatePauseMenuButtons();
	}
	else               //Unpaused
	{
		/*Player*/
		this->player->update(dt);
		this->player->tileCollision(this->tileMap->getCollision(this->player->getSpriteRect()));
		this->view.setCenter(this->player->getSpriteRect().getPosition());

		/*In-Game Actions*/
		this->updateInGameActions();

		/*Projectile Spawn*/
		this->updateProjectileSpawnLoop(dt);

		/*Projectile Wall Collision Loop*/
		this->updateProjectileWallCollision();

		/*Projectile Destroy*/
		this->updateProjectileDestroyLoop();
	}
}

/*Reinitialize Functions*/
void GameState::reinitializeState()
{
	std::cout << "Reinitializing Game State!\n";
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initRenderTexture();
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
void GameState::renderProjectiles(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->projectileItr = this->projectileVector.begin(); this->projectileItr != this->projectileVector.end(); this->projectileItr++)
	{
		this->projectileVector[counter]->render(target);

		counter++;
	}
}
void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	/*Items Rendered to Render Texture*/
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);
	this->renderTileMap(this->renderTexture);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderProjectiles(this->renderTexture);
	this->renderPlayer(this->renderTexture);
	this->renderTexture.display();
	target->draw(this->renderSprite);

	/*Items Rendered with Default Window View*/
	this->window->setView(this->defaultWindowView);
	if (this->isPaused)
		this->renderPauseMenu(*target);
}