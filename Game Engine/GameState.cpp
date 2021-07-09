#include "Header.h"
#include "GameState.h"

/*Initializers*/
void GameState::initVariables(bool came_from_main_menu, PlayerDetails player_details, ProjectileDetails projectile_details)
{
	this->gameInfo->window->setMouseCursorVisible(false);
	this->isGameOver = false;
	this->projectileDetails = projectile_details;
	this->cameFromMainMenu = came_from_main_menu;
	this->manaFillCounter = 0;
	this->maxNumberOfEnemies = 4;
	this->numberOfEnemies = this->maxNumberOfEnemies;
}
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/game_state_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = this->gameInfo->supportedKeys->at(keyboardKey);
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
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
	{
		throw ("ERROR::GAME_STATE::FAILED_TO_LOAD:BreatheFire.ttf");
	}

	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(sf::Vector2f(static_cast<float>(this->mousePositionWindow.x), static_cast<float>(this->mousePositionWindow.y)));
}
void GameState::initRenderTexture()
{
	//std::cout << "Window Size: " << this->gameInfo->window->getSize().x << " x " << this->gameInfo->window->getSize().y << '\n';
	this->renderTexture.create(this->gameInfo->window->getSize().x, this->gameInfo->window->getSize().y);
	this->renderTexture.setSmooth(true);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->gameInfo->window->getSize().x, this->gameInfo->window->getSize().y));
}
void GameState::initPauseMenu()
{
	this->pauseMenu = std::make_unique<PauseMenu>(
		*this->gameInfo->window, //Pause Menu Render Window
		this->font    //Pause Menu Font;
		);

	this->pauseMenu->addButton(
		"EXIT",                                                 //Key
		static_cast<float>(this->gameInfo->window->getSize().y) - 100.f,  // Pos_Y
		"Exit"                                                  // Button Text
	);
}
void GameState::initGameOver()
{
	this->gameOver = std::make_unique<GameOver>(
		*this->gameInfo->window, //Pause Menu Render Window
		this->font    //Pause Menu Font;
		);

	this->gameOver->addButton(
		"RETRY",                                                //Key
		static_cast<float>(this->gameInfo->window->getSize().y) / 2.f,  // Pos_Y
		"Retry"                                                 // Button Text
	);

	this->gameOver->addButton(
		"EXIT",                                                 //Key
		static_cast<float>(this->gameInfo->window->getSize().y) - 100.f,  // Pos_Y
		"Exit"                                                  // Button Text
	);
}
void GameState::initPlayer(PlayerDetails player_details)
{
	this->player = std::make_unique<Player>(this->gameInfo->supportedKeys, player_details, this->gameInfo->audioMap);
}
void GameState::initTileMap(PlayerDetails player_details)
{
	/*Level_A*/
	if (player_details.currentTileMap == CurrentTileMap::LEVEL_A)
	{
		/*Tile Map*/
		sf::Vector2i mapDimensions = sf::Vector2i(0, 0);
		int tileSize = 0;

		std::ifstream ifs("Config/level_1.ini");
		if (ifs.is_open())
		{
			ifs >> mapDimensions.x >> mapDimensions.y;
			ifs >> tileSize;
		}
		ifs.close();

		this->tileMap = std::make_unique<TILEMAP::TileMap>(
			static_cast<float>(tileSize),                  //Tile Size
			mapDimensions.x, mapDimensions.y,              //Map Width & Height (in Squares)
			tileSize, tileSize,                            //Texture Width & Height
			"Resources/Images/Tiles/PipoyaMasterLevel.png" //Tile Sheet File Path
			);

		this->tileMap->loadFromFile("Config/level_1.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
		//this->enterTilePosition = this->tileMap->getEnterTilePosition();

		this->player->setPosition(player_details.position);
		this->player->setOldDirection(player_details.oldDirection);

		/*Initialize Enemies*/
		this->initEnemies();

		/*Audio*/
		this->gameInfo->audioMap["LEVEL_A"]->setLoop(true);
		this->gameInfo->audioMap["LEVEL_A"]->setFadeIn(true);
		this->gameInfo->audioMap["LEVEL_A"]->play();
	}

	/*House_A*/
	if (player_details.currentTileMap == CurrentTileMap::HOUSE_A)
	{
		/*Tile Map*/
			sf::Vector2i mapDimensions = sf::Vector2i(0, 0);
			int tileSize = 0;

			std::ifstream ifs("Config/house_a.ini");
			if (ifs.is_open())
			{
				ifs >> mapDimensions.x >> mapDimensions.y;
				ifs >> tileSize;
			}
			ifs.close();

			this->tileMap = std::make_unique<TILEMAP::TileMap>(
				static_cast<float>(tileSize),                                //Tile Size
				mapDimensions.x, mapDimensions.y,              //Map Width & Height (in Squares)
				tileSize, tileSize,                            //Texture Width & Height
				"Resources/Images/Tiles/PipoyaMasterLevel.png" //Tile Sheet File Path
				);

			this->tileMap->loadFromFile("Config/house_a.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
			//this->enterTilePosition = this->tileMap->getEnterTilePosition();

			this->player->setPosition(player_details.position);
			this->player->setOldDirection(player_details.oldDirection);

			/*NPC Female #9*/
			this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 9, this->gameInfo->audioMap, this->gameInfo->supportedKeys);
			//this->npc->setNPCPosition();
			this->npcVector.push_back(std::move(this->npc));

			/*NPC Female #17*/
			this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 17, this->gameInfo->audioMap, this->gameInfo->supportedKeys);
			//this->npc->setNPCPosition();
			this->npcVector.push_back(std::move(this->npc));

			/*NPC Male #53*/
			this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 1, 53, this->gameInfo->audioMap, this->gameInfo->supportedKeys);
			//this->npc->setNPCPosition();
			this->npcVector.push_back(std::move(this->npc));

			/*Audio*/
			this->gameInfo->audioMap["HOUSE_A"]->setLoop(true);
			this->gameInfo->audioMap["HOUSE_A"]->setFadeIn(true);
			this->gameInfo->audioMap["HOUSE_A"]->play();	
	}
}
void GameState::initHUD()
{
	this->hud = std::make_unique<HUD>();
}
void GameState::initInventory()
{
	this->inventory = std::make_unique<Inventory>(this->gameInfo->supportedKeys, *this->gameInfo->window, this->gameInfo->audioMap);

	if (this->cameFromMainMenu)
		this->inventory->loadToFile();
}
void GameState::initEnemies()
{
	for (int i = 0; i < this->numberOfEnemies; i++)
	{
		this->enemy = std::make_unique<Enemy>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->gameInfo->audioMap);
		this->enemy->setEnemyPosition();
		this->enemyVector.push_back(std::move(this->enemy));
	}
}

/*Constructor & Destructor*/
GameState::GameState(GameInfo* game_info, PlayerDetails player_details, ProjectileDetails projectile_details, bool came_from_main_menu)
	: State(game_info)
{
	this->initVariables(came_from_main_menu, player_details, projectile_details);
	this->initKeybinds();
	this->initFonts();
	this->initRenderTexture();
	this->initPauseMenu();
	this->initGameOver();
	this->initPlayer(player_details);
	this->initTileMap(player_details);
	this->initHUD();
	this->initInventory();
}
GameState::~GameState()
{
}

/*Setters*/
void GameState::setManaDrainFactor()
{
	switch (static_cast<ProjectileTypes>(this->projectileTypeCounter))
	{
	case ProjectileTypes::Black_Tornado:
		this->projectileDetails.manaDrainFactor = 5.f;
		break;
	case ProjectileTypes::Blue_Tornado:
		this->projectileDetails.manaDrainFactor = 5.f;
		break;
	case ProjectileTypes::Brown_Tornado:
		this->projectileDetails.manaDrainFactor = 5.f;
		break;
	case ProjectileTypes::Cyan_Ball_1:
		this->projectileDetails.manaDrainFactor = 3.f;
		break;
	case ProjectileTypes::Cyan_Ball_2:
		this->projectileDetails.manaDrainFactor = 3.f;
		break;
	case ProjectileTypes::Cyan_Ball_3:
		this->projectileDetails.manaDrainFactor = 3.f;
		break;
	case ProjectileTypes::Cyan_Ball_4:
		this->projectileDetails.manaDrainFactor = 3.f;
		break;
	case ProjectileTypes::Cyan_Ball_5:
		this->projectileDetails.manaDrainFactor = 3.f;
		break;
	case ProjectileTypes::Green_Tornado:
		this->projectileDetails.manaDrainFactor = 5.f;
		break;
	case ProjectileTypes::Pink_Ball_1:
		this->projectileDetails.manaDrainFactor = 4.f;
		break;
	case ProjectileTypes::Pink_Ball_2:
		this->projectileDetails.manaDrainFactor = 4.f;
		break;
	case ProjectileTypes::Pink_Ball_3:
		this->projectileDetails.manaDrainFactor = 4.f;
		break;
	case ProjectileTypes::Pink_Ball_4:
		this->projectileDetails.manaDrainFactor = 4.f;
		break;
	case ProjectileTypes::Pink_Ball_5:
		this->projectileDetails.manaDrainFactor = 4.f;
		break;
	case ProjectileTypes::Red_Tornado:
		this->projectileDetails.manaDrainFactor = 5.f;
		break;
	case ProjectileTypes::Yellow_Ball_1:
		this->projectileDetails.manaDrainFactor = 6.f;
		break;
	case ProjectileTypes::Yellow_Ball_2:
		this->projectileDetails.manaDrainFactor = 6.f;
		break;
	case ProjectileTypes::Yellow_Ball_3:
		this->projectileDetails.manaDrainFactor = 6.f;
		break;
	case ProjectileTypes::Yellow_Ball_4:
		this->projectileDetails.manaDrainFactor = 6.f;
		break;
	case ProjectileTypes::Yellow_Ball_5:
		this->projectileDetails.manaDrainFactor = 6.f;
		break;
	default:
		std::cout << "ERROR::PROJECITLE::void Projectile::setProjectileType(ProjectileTypes projectile_type))::Invalid Switch Entry!\n";
	}
}

/*Update Functions*/
void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("EXIT") && this->getKeyTime())
	{
		/*Save Player Details*/
		this->player->saveToFile();

		/*Save Invetory Details*/
		this->inventory->saveToFile();

		/*Stop Current Audio*/
		for (auto& i : this->gameInfo->audioMap)
			i.second->stop();
		
		/*Play Main Menu Audio*/
		this->gameInfo->audioMap["MAIN_MENU"]->setFadeIn(true);
		this->gameInfo->audioMap["MAIN_MENU"]->play();

		/*Erase the NewCharacter Screen and Shrink States Vector*/
		if (!this->cameFromMainMenu)
		{
			this->gameInfo->states->erase(this->gameInfo->states->begin() + 1);
			this->gameInfo->states->shrink_to_fit();
		}

		/*End State*/
		this->endState();
	}
}
void GameState::updateGameOverButtons()
{
	if (this->gameOver->isButtonPressed("RETRY") && this->getKeyTime())
	{
		/*Save Player Details*/
		this->player->setHealthToFull();
		this->player->saveToFile();

		this->reinitializeState();
	} 


	if (this->gameOver->isButtonPressed("EXIT") && this->getKeyTime())
	{
		/*Save Player Details*/
		this->player->setHealthToFull();
		this->player->saveToFile();

		/*Save Invetory Details*/
		this->inventory->saveToFile();

		/*Stop Current Audio*/
		for (auto& i : this->gameInfo->audioMap)
			i.second->stop();
		
		/*Play Main Menu Audio*/
		this->gameInfo->audioMap["MAIN_MENU"]->setFadeIn(true);
		this->gameInfo->audioMap["MAIN_MENU"]->play();

		/*Erase the NewCharacter Screen and Shrink States Vector*/
		if (!this->cameFromMainMenu)
		{
			this->gameInfo->states->erase(this->gameInfo->states->begin() + 1);
			this->gameInfo->states->shrink_to_fit();
		}

		/*End State*/
		this->endState();
	}
}
void GameState::updateParticle(const float& dt)
{
	this->particle = std::make_unique<Particle>(*this->gameInfo->window); 
	this->particleVector.push_back(std::move(this->particle));

	int counter1 = 0;
	for (this->particleItr = this->particleVector.begin(); this->particleItr != this->particleVector.end(); this->particleItr++)
	{
		this->particleVector[counter1]->update(dt);
		counter1++;
	}
}
void GameState::updateParticleDestroyLoop()
{
	int counter = 0;
	for (this->particleItr = this->particleVector.begin(); this->particleItr != this->particleVector.end(); this->particleItr++)
	{
		if (this->particleVector[counter]->getPosition().y > this->gameInfo->window->getSize().y)
		{
			this->particleVector.erase(this->particleItr);
			//std::cout << "Destroyed Rain!\n";
			break;
		}
		counter++;
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
	if (this->gameInfo->sfmlEvent->type == sf::Event::MouseWheelScrolled)
	{
		if (this->gameInfo->sfmlEvent->mouseWheelScroll.delta > 0)
		{
			if (this->projectileTypeCounter != 19)
			{
				this->projectileTypeCounter += 1;
				this->setManaDrainFactor();
				//std::cout << "Projectile Counter: " << this->projectileTypeCounter << '\n';
				this->gameInfo->sfmlEvent->mouseWheelScroll.delta = 0;
				this->projectileDetails.projectileType = static_cast<ProjectileTypes>(this->projectileTypeCounter);
			}
		}
		else if (this->gameInfo->sfmlEvent->mouseWheelScroll.delta < 0)
		{
			if (this->projectileTypeCounter != 0)
			{
				this->projectileTypeCounter -= 1;
				this->setManaDrainFactor();
				//std::cout << "Projectile Counter: " << this->projectileTypeCounter << '\n';
				this->gameInfo->sfmlEvent->mouseWheelScroll.delta = 0;
				this->projectileDetails.projectileType = static_cast<ProjectileTypes>(this->projectileTypeCounter);
			}
		}
	}

	/*Firing Projectile*/
	float projectile_DeltaTime = this->projectileClock.getElapsedTime().asSeconds();
	float projectile_SwitchTime = 0.2;

	if (projectile_DeltaTime > projectile_SwitchTime)
	{
		this->projectileClock.restart();

		if (this->player->getPlayerDetails().currentMana - this->projectileDetails.manaDrainFactor >= 0.f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))))
			{
				this->projectile = std::make_unique<Projectile>(this->projectileDetails, this->gameInfo->audioMap);
				this->projectile->setProjectileType(this->projectileDetails.projectileType);
				this->projectile->setDirection(this->player->getDirection());
				this->projectile->setProjectilePosition(this->player->getSpriteRect());
				this->player->setManaDrain(this->projectile->getManaDrainFactor());
				this->projectile->saveToFile();
				this->projectileVector.push_back(std::move(this->projectile));
			}
		}
	}
}
void GameState::updateHUD()
{
	this->hud->update(this->player->getPlayerDetails(), std::get<0>(this->player->getMana()), std::get<1>(this->player->getMana()));
}
void GameState::updateInventory(const float& dt)
{
	this->inventory->update(*this->gameInfo->window, *this->gameInfo->sfmlEvent, this->mousePositionWindow, this->getKeyTime(), dt);

	if (this->inventory->getUsedItem())
	{
		this->player->setItemBenefits(this->inventory->getUsedItemDetails());
		this->inventory->setUsedItem(false);
	}
}
void GameState::updateManaFill()
{
	this->manaFillCounter++;

	float manaFillRate = 1.f;

	if (std::get<0>(this->player->getMana()) < std::get<1>(this->player->getMana()) && this->manaFillCounter > 500)
	{
		this->player->setManaFill(manaFillRate);
		this->manaFillCounter = 0;
	}

	if (std::get<0>(this->player->getMana()) == std::get<1>(this->player->getMana()) && this->manaFillCounter > 500)
	{
		this->manaFillCounter = 0;
	}
}
void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt);
	this->view.setCenter(std::floor(this->player->getSpriteRect().getPosition().x), std::floor(this->player->getSpriteRect().getPosition().y));

	if (this->player->getPlayerDetails().currentHP <= 0.f)
		this->isGameOver = true;
}
bool GameState::updatePlayerItemCollision()
{
	int counter = 0;

	for (this->itemItr = this->itemVector.begin(); this->itemItr != this->itemVector.end(); this->itemItr++)
	{
		if (this->player->itemCollision(this->itemVector[counter]->getSpriteRect(), this->itemVector[counter]->getAlertCircle()))
			return true;
		counter++;
	}
	return false;
}
bool GameState::updatePlayerNPCCollision()
{
	/*Player/NPC*/
	int counter = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		if (this->player->npcCollision( this->npcVector[counter]->getSpriteRect(), this->npcVector[counter]->getAlertCircle()))
			return true;
		counter++;
	}
	return false; 
}
void GameState::updatePlayerCollisions()
{
	/*Player/Wall*/
	this->player->tileCollision(this->tileMap->getCollision(this->player->getSpriteRect()));

	/*Player/Enemy*/
	int counter1 = 0;
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		this->player->enemyCollision(this->enemyVector[counter1]->getSpriteRectDamageAttackPlayerBool());
		counter1++;
	}

	/*Player/NPC Collision*/
	if (this->updatePlayerNPCCollision())
		this->player->setPlayerNPCCollisionBool(true);
	else if (!this->updatePlayerNPCCollision())
		this->player->setPlayerNPCCollisionBool(false);
	
	/*PLayer/Item Collision*/
	if (this->updatePlayerItemCollision())
		this->player->setPlayerItemCollisionBool(true);
	else if (!this->updatePlayerItemCollision())
		this->player->setPlayerItemCollisionBool(false);
}
void GameState::updateDoorCollisions(const float& dt)
{
	/*Level_A*/
	if (std::get<0>(this->player->getDoorInfo()) == true && std::get<1>(this->player->getDoorInfo()) == "LEVEL_A")
	{
		/*Tile Map*/
		this->tileMap.reset();

		sf::Vector2i mapDimensions = sf::Vector2i(0, 0);
		int tileSize = 0;

		std::ifstream ifs("Config/level_1.ini");
		if (ifs.is_open())
		{
			ifs >> mapDimensions.x >> mapDimensions.y;
			ifs >> tileSize;
		}
		ifs.close();

		this->tileMap = std::make_unique<TILEMAP::TileMap>(
			static_cast<float>(tileSize),                  //Tile Size
			mapDimensions.x, mapDimensions.y,              //Map Width & Height (in Squares)
			tileSize, tileSize,                            //Texture Width & Height
			"Resources/Images/Tiles/PipoyaMasterLevel.png" //Tile Sheet File Path
			);

		this->tileMap->loadFromFile("Config/level_1.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
		this->enterTilePosition = this->tileMap->getEnterTilePosition();

		/*Player*/
		this->player->setPosition(this->enterTilePosition);
		this->player->setOldDirection(Direction::Down);
		this->player->setCurrentDirection(Direction::Idle);
		this->player->setVelocity(sf::Vector2f(0.f, 0.f));
		this->player->setCurrentTileMap(CurrentTileMap::LEVEL_A);

		/*Destroy NPCs*/
		for (auto& element : this->npcVector)
			this->npcVector.pop_back();

		/*Remake Enemies*/
		for (int i = 0; i < this->numberOfEnemies; i++)
		{
			this->enemy = std::make_unique<Enemy>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->gameInfo->audioMap);
			this->enemy->setEnemyPosition();
			this->enemyVector.push_back(std::move(this->enemy));
		}

		/*Play Music*/
		this->gameInfo->audioMap["HOUSE_A"]->setFadeOut(true);
		this->gameInfo->audioMap["LEVEL_A"]->setLoop(true);
		this->gameInfo->audioMap["LEVEL_A"]->setFadeIn(true);
		this->gameInfo->audioMap["LEVEL_A"]->play();
	}

	/*House_A*/
	if (std::get<0>(this->player->getDoorInfo()) == true && std::get<1>(this->player->getDoorInfo()) == "HOUSE_A")
	{
		/*Tile Map*/
		this->tileMap.reset();

		sf::Vector2i mapDimensions = sf::Vector2i(0, 0);
		int tileSize = 0;

		std::ifstream ifs("Config/house_a.ini");
		if (ifs.is_open())
		{
			ifs >> mapDimensions.x >> mapDimensions.y;
			ifs >> tileSize;
		}
		ifs.close();

		this->tileMap = std::make_unique<TILEMAP::TileMap>(
			static_cast<float>(tileSize),                  //Tile Size
			mapDimensions.x, mapDimensions.y,              //Map Width & Height (in Squares)
			tileSize, tileSize,                            //Texture Width & Height
			"Resources/Images/Tiles/PipoyaMasterLevel.png" //Tile Sheet File Path
			);

		this->tileMap->loadFromFile("Config/house_a.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
		this->enterTilePosition = this->tileMap->getEnterTilePosition();

		/*Player*/
		this->player->setPosition(this->enterTilePosition);
		this->player->setOldDirection(Direction::Up);
		this->player->setCurrentDirection(Direction::Idle);
		this->player->setVelocity(sf::Vector2f(0.f, 0.f));
		this->player->setCurrentTileMap(CurrentTileMap::HOUSE_A);

		/*NPC Female #9*/
		this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 9, this->gameInfo->audioMap, this->gameInfo->supportedKeys);
		//this->npc->setNPCPosition();
		this->npcVector.push_back(std::move(this->npc));

		/*NPC Female #17*/
		this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 17, this->gameInfo->audioMap, this->gameInfo->supportedKeys);
		//this->npc->setNPCPosition();
		this->npcVector.push_back(std::move(this->npc));

		/*NPC Male #53*/
		this->npc = std::make_unique<NPC>( this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 1, 53, this->gameInfo->audioMap, this->gameInfo->supportedKeys);
		//this->npc->setNPCPosition();
		this->npcVector.push_back(std::move(this->npc));

		/*Destroy Enemies*/
		for (auto& element : this->enemyVector)
			this->enemyVector.pop_back();

		/*Destroy Items*/
		for (auto& element : this->itemVector)
			this->itemVector.pop_back();

		/*Play Music*/
		this->gameInfo->audioMap["LEVEL_A"]->setFadeOut(true);
		this->gameInfo->audioMap["HOUSE_A"]->setLoop(true);
		this->gameInfo->audioMap["HOUSE_A"]->setFadeIn(true);
		this->gameInfo->audioMap["HOUSE_A"]->play();
	}	
}
void GameState::updateAudio()
{
	this->gameInfo->audioMap["LEVEL_A"]->update();
	this->gameInfo->audioMap["HOUSE_A"]->update();
}
void GameState::updateProjectileLoop(const float& dt)
{
	int counter = 0;
	for (this->projectileItr = this->projectileVector.begin(); this->projectileItr != this->projectileVector.end(); this->projectileItr++)
	{
		this->projectileVector[counter]->update(dt);

		counter++;
	}
}
void GameState::updateProjectileCollisions()
{
	/*Projectile/Wall*/
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

	/*Projectile/Enemy*/
	for (int i = 0; i < this->projectileVector.size(); i++)
	{
		for (int j = 0; j < this->enemyVector.size(); j++)
		{
			this->projectileVector[i]->enemyCollision(this->enemyVector[j]->getSpriteRect());
		}
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
void GameState::updateEnemyLoop(const float& dt)
{
	int counter1 = 0;
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		this->enemyVector[counter1]->update(this->player->getSpriteRect(), dt);
		counter1++;
	}
}
void GameState::updateEnemyCollisions()
{
	/*Enemy/Wall*/
	int counter1 = 0;
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		this->enemyVector[counter1]->tileCollision(this->tileMap->getCollision(this->enemyVector[counter1]->getSpriteRect()));
		counter1++;
	}

	/*Enemy Alert Circle/Player*/
	int counter2 = 0;
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		this->enemyVector[counter2]->alertCircleCollision(this->player->getSpriteRect());
		counter2++;
	}

	/*Player/Enemy*/
	int counter3 = 0;
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		this->enemyVector[counter3]->playerCollision(this->player->getSpriteRect());
		counter3++;
	}

	/*Enemy/Projectile*/
	for (int i = 0; i < this->projectileVector.size(); i++)
	{
		for (int j = 0; j < this->enemyVector.size(); j++)
		{
			this->enemyVector[j]->projectileCollision(this->projectileVector[i]->getProjectileSpriteRectAndInt());
		}
	}
}
void GameState::updateEnemyDestroyLoop()
{
	int counter = 0; 
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		if (this->enemyVector[counter]->getDestroy())
		{
			this->item = std::make_unique<Item>(this->gameInfo->supportedKeys, this->gameInfo->audioMap);
			this->item->setPosition(this->enemyVector[counter]->getSpriteRect().getPosition());
			this->itemVector.push_back(std::move(this->item));

			this->enemyVector.erase(this->enemyItr);
			this->numberOfEnemies -= 1;
			break;
		}
		counter++;
	}
}
void GameState::updateNPCLoop(const float& dt)
{
	int counter1 = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter1]->update(this->player->getSpriteRect(), *this->gameInfo->sfmlEvent, this->getKeyTime(), dt);
		counter1++;
	}
}
void GameState::updateNPCCollisions()
{
	/*NPC/Wall*/
	int counter1 = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter1]->tileCollision(this->tileMap->getCollision(this->npcVector[counter1]->getSpriteRect()));
		counter1++;
	}

	/*NPC/Player*/
	int counter2 = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter2]->playerCollision(this->player->getSpriteRect());
		counter2++;
	}

	/*NPC/Projectile*/
	for (int i = 0; i < this->projectileVector.size(); i++)
	{
		for (int j = 0; j < this->npcVector.size(); j++)
		{
			this->npcVector[j]->projectileCollision(this->projectileVector[i]->getProjectileSpriteRectAndInt());
		}
	}

	/*NPC Alert Circle/Player*/
	int counter3 = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter3]->alertCircleCollision(this->player->getSpriteRect());
		counter3++;
	}
}
void GameState::updateItemLoop(const float& dt)
{
	int counter = 0;
	for (this->itemItr = this->itemVector.begin(); this->itemItr != this->itemVector.end(); this->itemItr++)
	{
		this->itemVector[counter]->update(this->player->getSpriteRect(), dt);
		counter++;
	}
}
void GameState::updateItemDestroyLoop()
{
	int counter = 0;
	for (this->itemItr = this->itemVector.begin(); this->itemItr != this->itemVector.end(); this->itemItr++)
	{
		if (
			this->itemVector[counter]->getAlertCircle().getGlobalBounds().intersects(this->player->getSpriteRect().getGlobalBounds()) 
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PICK_UP_ITEM")))
			)
		{
			this->gameInfo->audioMap["GAMESTATE_PICKUP_ITEM"]->play();
			this->inventory->setItemToInventory(this->itemVector[counter]->getItemDetails());
			this->itemVector.erase(this->itemItr);
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
	
	/*Paused*/
	if (this->isPaused) 
	{
		this->gameInfo->window->setMouseCursorVisible(true);
		this->pauseMenu->update(static_cast<sf::Vector2f>(this->mousePositionGUI));
		this->updatePauseMenuButtons();
	}
	/*Unpaused*/
	else
	{
		if (!this->inventory->getShowInventory() && !this->isGameOver)
		{
			this->gameInfo->window->setMouseCursorVisible(false);

			/*In-Game Actions*/
			this->updateInGameActions();

			/*Particle Functions*/
			this->updateParticle(dt);
			this->updateParticleDestroyLoop();

			/*HUD Functions*/
			this->updateHUD();

			/*Inventory Functions*/
			this->updateInventory(dt);

			/*Mana Fill*/
			this->updateManaFill();

			/*Player Functions*/
			this->updatePlayer(dt);
			this->updateDoorCollisions(dt);
			this->updatePlayerCollisions();

			/*Audio*/
			this->updateAudio();

			/*Projectile Functions*/
			this->updateProjectileLoop(dt);
			this->updateProjectileCollisions();
			this->updateProjectileDestroyLoop();

			/*Enemy Functions*/
			this->updateEnemyLoop(dt);
			this->updateEnemyDestroyLoop();
			this->updateEnemyCollisions();

			/*NPC Functions*/
			this->updateNPCLoop(dt);
			this->updateNPCCollisions();

			/*Item Functions*/
			this->updateItemLoop(dt);
			this->updateItemDestroyLoop();
		}
		else if(this->inventory->getShowInventory() && !this->isGameOver)
			/*Inventory Functions*/
			this->updateInventory(dt);
		else if (!this->inventory->getShowInventory() && this->isGameOver)
		{
			this->gameInfo->window->setMouseCursorVisible(true);
			this->gameOver->update(static_cast<sf::Vector2f>(this->mousePositionGUI));
			this->updateGameOverButtons();
		}
	}
}

/*Reinitialize Functions*/
void GameState::reinitializeState()
{
	std::cout << "Reinitializing Game State!\n";
	this->initKeybinds();
	this->initFonts();
	this->initRenderTexture();
	this->initPauseMenu();
	if (this->isGameOver)
	{
		for (auto& element : this->enemyVector)
			element->setDestroy(true);

		this->initVariables(this->cameFromMainMenu, this->player->getPlayerDetails(), this->projectileDetails);
		this->initPlayer(this->player->getPlayerDetails());
		this->initTileMap(this->player->getPlayerDetails());
	}
	this->initHUD();

	/*Inventory*/
	this->inventory->saveToFile();
	this->inventory = std::make_unique<Inventory>(this->gameInfo->supportedKeys, *this->gameInfo->window, this->gameInfo->audioMap);
	this->inventory->loadToFile();
}

/*Render Functions*/
void GameState::renderPauseMenu(sf::RenderTarget& target)
{
	this->pauseMenu->render(target);
}
void GameState::renderGameOver(sf::RenderTarget& target)
{
	this->gameOver->render(target);
}
void GameState::renderParticles(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->particleItr = this->particleVector.begin(); this->particleItr != this->particleVector.end(); this->particleItr++)
	{
		this->particleVector[counter]->render(target, *this->gameInfo->window, this->player->getPlayerDetails().currentTileMap);

		counter++;
	}
}
void GameState::renderTileMap(sf::RenderTarget& target)
{
	this->tileMap->render(target, this->view, this->player->getCenter(), &this->shader);
}
void GameState::renderPlayer(sf::RenderTarget& target)
{
	this->player->render(target, &this->shader);
}
void GameState::renderProjectiles(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->projectileItr = this->projectileVector.begin(); this->projectileItr != this->projectileVector.end(); this->projectileItr++)
	{
		this->projectileVector[counter]->render(target, this->player->getCenter(), &this->shader);

		counter++;
	}
}
void GameState::renderEnemies(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		this->enemyVector[counter]->render(target, this->player->getCenter(), &this->shader);

		counter++;
	}
}
void GameState::renderNPCs(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter]->render(target, this->player->getCenter(), &this->shader);

		counter++;
	}
}
bool GameState::renderHUD()
{
	int counter = 0;
	
		for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
		{
			if (this->npcVector[counter]->getShowNPCText())
				return false;
			counter++;
		}
		return true;
}
void GameState::renderInventory(sf::RenderTarget& target)
{
	this->inventory->render(target);
}
void GameState::renderItems(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->itemItr = this->itemVector.begin(); this->itemItr != this->itemVector.end(); this->itemItr++)
	{
		this->itemVector[counter]->render(target, this->player->getCenter(), &this->shader);

		counter++;
	}
}
void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameInfo->window;

	/*Items Rendered to Render Texture*/
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);
	this->renderTileMap(this->renderTexture);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderProjectiles(this->renderTexture);
	this->renderEnemies(this->renderTexture);
	this->renderPlayer(this->renderTexture);
	this->renderNPCs(this->renderTexture);
	this->renderItems(this->renderTexture);
	this->renderTexture.display();
	target->draw(this->renderSprite);

	/*Items Rendered with Default Window View*/
	this->gameInfo->window->setView(this->defaultWindowView);
	if(this->renderHUD())
		this->hud->render(*target);
	this->renderParticles(*target);
	this->renderInventory(*target);

	if (this->isPaused)
		this->renderPauseMenu(*target);	

	if (this->isGameOver)
		this->renderGameOver(*target);
}