#include "Header.h"
#include "GameState.h"

/*Initializers*/
void GameState::initVariables(bool came_from_main_menu, PlayerDetails player_details, ProjectileDetails projectile_details)
{
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
void GameState::initGameOver()
{
	this->gameOver = std::make_unique<GameOver>(
		*this->window, //Pause Menu Render Window
		this->font    //Pause Menu Font;
		);

	this->gameOver->addButton(
		"RETRY",                                                //Key
		static_cast<float>(this->window->getSize().y) / 2.f,  // Pos_Y
		"Retry"                                                 // Button Text
	);

	this->gameOver->addButton(
		"EXIT",                                                 //Key
		static_cast<float>(this->window->getSize().y) - 100.f,  // Pos_Y
		"Exit"                                                  // Button Text
	);
}
void GameState::initPlayer(PlayerDetails player_details)
{
	this->player = std::make_unique<Player>(this->supportedKeys, player_details);
}
void GameState::initTileMap(PlayerDetails player_details)
{
	/*Level_A*/
	if (player_details.currentTileMap == CurrentTileMap::LEVEL_A)
	{
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

		this->initEnemies();
	}

	/*House_A*/
	if (player_details.currentTileMap == CurrentTileMap::HOUSE_A)
	{
		
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
			this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 9);
			this->npc->setNPCPosition();
			this->npcVector.push_back(std::move(this->npc));

			/*NPC Female #17*/
			this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 17);
			this->npc->setNPCPosition();
			this->npcVector.push_back(std::move(this->npc));

			/*NPC Male #53*/
			this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 1, 53);
			this->npc->setNPCPosition();
			this->npcVector.push_back(std::move(this->npc));
	}
}
void GameState::initHUD()
{
	this->hud = std::make_unique<HUD>();
}
void GameState::initInventory()
{
	this->inventory = std::make_unique<Inventory>(this->supportedKeys, *this->window);
}
void GameState::initEnemies()
{
	for (int i = 0; i < this->numberOfEnemies; i++)
	{
		this->enemy = std::make_unique<Enemy>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings());
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
			{
				this->projectileTypeCounter += 1;
				this->setManaDrainFactor();
				//std::cout << "Projectile Counter: " << this->projectileTypeCounter << '\n';
				this->sfmlEvent->mouseWheelScroll.delta = 0;
				this->projectileDetails.projectileType = static_cast<ProjectileTypes>(this->projectileTypeCounter);
			}
		}
		else if (this->sfmlEvent->mouseWheelScroll.delta < 0)
		{
			if (this->projectileTypeCounter != 0)
			{
				this->projectileTypeCounter -= 1;
				this->setManaDrainFactor();
				//std::cout << "Projectile Counter: " << this->projectileTypeCounter << '\n';
				this->sfmlEvent->mouseWheelScroll.delta = 0;
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
				this->projectile = std::make_unique<Projectile>(this->projectileDetails);
				this->projectile->setProjectileType(this->projectileDetails.projectileType);
				this->projectile->setProjectileDirection(this->player->getPlayerDirection());
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
	this->inventory->update(*this->sfmlEvent, this->mousePositionWindow, this->getKeyTime(), dt);

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
	this->view.setCenter(this->player->getSpriteRect().getPosition());

	if (this->player->getPlayerDetails().currentHP <= 0.f)
		this->isGameOver = true;
}
void GameState::updateDoorCollisions(const float& dt)
{
	/*Level_A*/
	if (std::get<0>(this->player->getDoorInfo()) == true && std::get<1>(this->player->getDoorInfo()) == "LEVEL_A")
	{
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

		this->player->setPosition(this->enterTilePosition);
		this->player->setOldDirection(PlayerDirection::Down);
		this->player->setCurrentTileMap(CurrentTileMap::LEVEL_A);

		for (auto& element : this->npcVector)
			this->npcVector.pop_back();

		for (int i = 0; i < this->numberOfEnemies; i++)
		{
			this->enemy = std::make_unique<Enemy>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings());
			this->enemy->setEnemyPosition();
			this->enemyVector.push_back(std::move(this->enemy));
		}
	}

	/*House_A*/
	if (std::get<0>(this->player->getDoorInfo()) == true && std::get<1>(this->player->getDoorInfo()) == "HOUSE_A")
	{
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
			static_cast<float>(tileSize),                                //Tile Size
			mapDimensions.x, mapDimensions.y,              //Map Width & Height (in Squares)
			tileSize, tileSize,                            //Texture Width & Height
			"Resources/Images/Tiles/PipoyaMasterLevel.png" //Tile Sheet File Path
			);

		this->tileMap->loadFromFile("Config/house_a.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
		this->enterTilePosition = this->tileMap->getEnterTilePosition();

		this->player->setPosition(this->enterTilePosition);
		this->player->setOldDirection(PlayerDirection::Up);
		this->player->setCurrentTileMap(CurrentTileMap::HOUSE_A);

		/*NPC Female #9*/
		this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 9);
		this->npc->setNPCPosition();
		this->npcVector.push_back(std::move(this->npc));

		/*NPC Female #17*/
		this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 0, 17);
		this->npc->setNPCPosition();
		this->npcVector.push_back(std::move(this->npc));

		/*NPC Male #53*/
		this->npc = std::make_unique<NPC>( this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), 1, 53);
		this->npc->setNPCPosition();
		this->npcVector.push_back(std::move(this->npc));

		for (auto& element : this->enemyVector)
			this->enemyVector.pop_back();

		for (auto& element : this->itemVector)
			this->itemVector.pop_back();
	}
	
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
			this->item = std::make_unique<Item>(this->supportedKeys); 
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
		this->npcVector[counter1]->update(this->player->getSpriteRect(), this->mousePositionView, *this->sfmlEvent, this->getKeyTime(), dt);
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
}
void GameState::updateItemLoop(const float& dt)
{
	int counter = 0;
	for (this->itemItr = this->itemVector.begin(); this->itemItr != this->itemVector.end(); this->itemItr++)
	{
		this->itemVector[counter]->update(this->mousePositionView, dt);
		counter++;
	}
}
void GameState::updateItemDestroyLoop()
{
	int counter = 0;
	for (this->itemItr = this->itemVector.begin(); this->itemItr != this->itemVector.end(); this->itemItr++)
	{
		if ((std::get<0>(this->itemVector[counter]->getItemRect()).getGlobalBounds().contains(this->mousePositionView) 
			|| std::get<1>(this->itemVector[counter]->getItemRect()).getGlobalBounds().contains(this->mousePositionView)) 
			&& this->sfmlEvent->mouseButton.button == sf::Mouse::Left)
		{
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
		this->pauseMenu->update(static_cast<sf::Vector2f>(this->mousePositionGUI));
		this->updatePauseMenuButtons();
	}
	/*Unpaused*/
	else
	{
		if (!this->inventory->getShowInventory() && !this->isGameOver)
		{
			/*In-Game Actions*/
			this->updateInGameActions();

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
void GameState::renderEnemies(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->enemyItr = this->enemyVector.begin(); this->enemyItr != this->enemyVector.end(); this->enemyItr++)
	{
		this->enemyVector[counter]->render(target);

		counter++;
	}
}
void GameState::renderNPCs(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter]->render(target);

		counter++;
	}
}
void GameState::renderHUD(sf::RenderTarget& target)
{
	this->hud->render(target);
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
		this->itemVector[counter]->render(target);

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
	this->renderEnemies(this->renderTexture);
	this->renderNPCs(this->renderTexture);
	this->renderItems(this->renderTexture);
	this->renderPlayer(this->renderTexture);
	this->renderTexture.display();
	target->draw(this->renderSprite);

	/*Items Rendered with Default Window View*/
	this->window->setView(this->defaultWindowView);
	this->renderHUD(*target);
	this->renderInventory(*target);

	if (this->isPaused)
		this->renderPauseMenu(*target);	

	if (this->isGameOver)
		this->renderGameOver(*target);
}