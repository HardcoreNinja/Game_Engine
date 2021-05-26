#include "Header.h"
#include "GameState.h"

/*Initializers*/
void GameState::initVariables(bool came_from_main_menu, PlayerDetails player_details, ProjectileDetails projectile_details)
{
	this->projectileDetails = projectile_details;
	this->cameFromMainMenu = came_from_main_menu;
	this->currentMana = player_details.currentMana;
	this->maxMana = player_details.maxMana;
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
	this->tileMap->loadFromFile("Config/level_1.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
}
void GameState::initPlayer(PlayerDetails player_details)
{
	this->player = std::make_unique<Player>(this->supportedKeys, player_details);
}
void GameState::initHUD()
{
	this->hud = std::make_unique<HUD>();
}

/*Constructor & Destructor*/
GameState::GameState(GameInfo* game_info, PlayerDetails player_details, ProjectileDetails projectile_details, bool came_from_main_menu)
	: State(game_info)
{
	this->initVariables(came_from_main_menu, player_details, projectile_details);
	this->initKeybinds();
	this->initFonts();
	this->initRenderTexture();
	this->initTileMap();
	this->initPauseMenu();
	this->initLatestTileMap();
	this->initPlayer(player_details);
	this->initHUD();
}
GameState::~GameState()
{
}

/*Update Functions*/
void GameState::updateHUD()
{
	this->hud->update(this->player->getPlayerDetails(), this->currentMana, this->maxMana);
}
void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("EXIT") && this->getKeyTime())
	{
		/*Save Player Details*/
		this->player->setCurrentMana(this->currentMana);
		this->player->saveToFile();

		/*Erase the NewCharacter Screen and Shrink States Vector*/
		if (!this->cameFromMainMenu)
		{
			this->states->erase(this->states->begin() + 1);
			this->states->shrink_to_fit();
		}

		/*End State*/
		this->endState();
	}
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
	/*Scrolling Projectile Types*/
	if (this->sfmlEvent->type == sf::Event::MouseWheelScrolled)
	{
		if (this->sfmlEvent->mouseWheelScroll.delta > 0)
		{
			if (this->projectileTypeCounter != 19)
				this->projectileTypeCounter += 1;
			//std::cout << "Projectile Counter: " << this->projectileTypeCounter << '\n';
			this->sfmlEvent->mouseWheelScroll.delta = 0;
			this->projectileDetails.projectileType = static_cast<ProjectileTypes>(this->projectileTypeCounter);
		}
		else if (this->sfmlEvent->mouseWheelScroll.delta < 0)
		{
			if (this->projectileTypeCounter != 0)
				this->projectileTypeCounter -= 1;
			//std::cout << "Projectile Counter: " << this->projectileTypeCounter << '\n';
			this->sfmlEvent->mouseWheelScroll.delta = 0;
			this->projectileDetails.projectileType = static_cast<ProjectileTypes>(this->projectileTypeCounter);
		}
	}

	/*Firing Projectile*/
	float projectile_DeltaTime = this->projectileClock.getElapsedTime().asSeconds();
	float projectile_SwitchTime = 0.2;

	if (projectile_DeltaTime > projectile_SwitchTime)
	{
		this->projectileClock.restart();
		if (this->currentMana != 0.f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))))
			{
				this->projectile = std::make_unique<Projectile>(this->projectileDetails);
				this->projectile->setProjectileType(this->projectileDetails.projectileType);
				this->projectile->setProjectileDirection(this->player->getPlayerDirection());
				this->projectile->setProjectilePosition(this->player->getSpriteRect());
				this->currentMana = this->currentMana - this->projectile->getManaDrainFactor();
				this->projectile->saveToFile();
				this->projectileVector.push_back(std::move(this->projectile));
			}
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

		/*Update HUD*/
		this->updateHUD();

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
	this->initVariables(this->cameFromMainMenu, this->player->getPlayerDetails(), this->projectile->getProjectileDetails());
	this->initKeybinds();
	this->initFonts();
	this->initRenderTexture();
	this->initTileMap();
	this->initPauseMenu();
	this->initLatestTileMap();
	this->initPlayer(this->player->getPlayerDetails());
	this->initHUD();
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
void GameState::renderHUD(sf::RenderTarget& target)
{
	this->hud->render(target);
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
	this->renderHUD(*target);

	if (this->isPaused)
		this->renderPauseMenu(*target);	
}