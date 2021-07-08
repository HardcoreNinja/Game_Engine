#include "Header.h"
#include "MainMenu.h"
/*Initializers*/
void MainMenu::initKeybinds()
{
	std::ifstream ifs("Config/mainmenu_keybinds.ini");

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
void MainMenu::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
	{
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:Dosis.ttf");
	}

	this->text.setFont(this->font);
}
void MainMenu::initButtons()
{
	this->buttons["QUIT_GAME"] = std::make_unique<GUI::Button>(
		120.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Quit Game", 50,  //Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["SETTINGS"] = std::make_unique<GUI::Button>(
		120.f, 450.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Settings", 50,   //Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["EDITOR"] = std::make_unique<GUI::Button>(
		120.f, 350.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Editor", 50,     //Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["NEW_GAME"] = std::make_unique<GUI::Button>(
		120.f, 250.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "New Game", 50,   //Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["CONTINUE_GAME"] = std::make_unique<GUI::Button>(
		120.f, 150.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Continue", 50,   //Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)
}
void MainMenu::initShader()
{
	if (!this->shader.loadFromFile("Shaders/Player/vertex.vert", "Shaders/Player/fragment.frag"))
		std::cout << "Error Loading Shader!\n";
}
void MainMenu::initRenderTexture()
{
	//std::cout << "Window Size: " << this->gameInfo->window->getSize().x << " x " << this->gameInfo->window->getSize().y << '\n';
	this->renderTexture.create(this->gameInfo->window->getSize().x, this->gameInfo->window->getSize().y);
	this->renderTexture.setSmooth(true);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->gameInfo->window->getSize().x, this->gameInfo->window->getSize().y));
}
void MainMenu::initTileMap()
{
	sf::Vector2i mapDimensions = sf::Vector2i(0, 0);
	int tileSize = 0;

	std::ifstream ifs("Config/main_menu_tile_map.ini");
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

	this->tileMap->loadFromFile("Config/main_menu_tile_map.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
}
void MainMenu::initAudio()
{
	std::ifstream ifs_sfx("Config/sfx.ini");

	if (ifs_sfx.is_open())
	{
		std::string key = "";
		std::string file_path = "";

		while (ifs_sfx >> key >> file_path)
		{
			std::cout << file_path << '\n';
			this->audio = std::make_unique<Audio>(true, file_path);
			this->audioMap[key] = std::move(this->audio);
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
			this->audio = std::make_unique<Audio>(false, file_path);
			this->audioMap[key] = std::move(this->audio);
		}
	}
	ifs_music.close();

	//Debug Tester
	for (auto& i : this->audioMap)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void MainMenu::initNPC()
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
}


/*Constructor & Destructor*/
MainMenu::MainMenu(GameInfo* game_info)
	: State(game_info)
{
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initRenderTexture();
	this->initTileMap();
	this->initAudio();
	this->initNPC();
}
MainMenu::~MainMenu()
{
}

/*Update Functions*/
void MainMenu::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mousePositionView);

	/*Quit Game*/
	if (this->buttons["QUIT_GAME"]->isPressed() && this->getKeyTime())
		this->endState();

	/*Settings*/
	if (this->buttons["SETTINGS"]->isPressed() && this->getKeyTime())
		this->gameInfo->states->push_back(std::make_unique<Settings>(this->gameInfo));

	/*Editor*/
	if (this->buttons["EDITOR"]->isPressed() && this->getKeyTime())
		this->gameInfo->states->push_back(std::make_unique<Editor>(this->gameInfo));

	/*New Character Screen*/
	if (this->buttons["NEW_GAME"]->isPressed() && this->getKeyTime())
		this->gameInfo->states->push_back(std::make_unique<NewCharacterScreen>(this->gameInfo));

	/*Continue Game*/
	if (this->buttons["CONTINUE_GAME"]->isPressed() && this->getKeyTime())
	{
		this->loadPlayerDetailsFromFile();
		this->loadProjectileDetailsFromFile();
		this->gameInfo->states->push_back(std::make_unique<GameState>(this->gameInfo, this->playerDetails, this->projectileDetails, true));
	}

}
void MainMenu::updateNPCLoop(const float& dt)
{
	int counter1 = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter1]->update(dt);
		counter1++;
	}
}
void MainMenu::updateNPCCollisions()
{
	/*NPC/Wall*/
	int counter1 = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter1]->tileCollision(this->tileMap->getCollision(this->npcVector[counter1]->getSpriteRect()));
		counter1++;
	}
}
void MainMenu::updateUserInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT_GAME"))) && this->getKeyTime())
		this->endState();
}
void MainMenu::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateButtons();
	this->updateMousePosition();
	this->updateUserInput(dt);
	this->updateNPCLoop(dt);
	this->updateNPCCollisions();
}

/*Getters*/
int MainMenu::getRandomInt(int min, int max)
{
	return rand() % max + min;
}

/*Reinitialize Functions*/
void MainMenu::reinitializeState()
{
	std::cout << "Reinitializing MainMenu!\n";
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initShader();
	this->initRenderTexture(); 
	this->initTileMap();
	this->initAudio();
	this->initNPC();
}

/*Save & Load Functions*/
void MainMenu::loadPlayerDetailsFromFile()
{
	int currenmtTileMap = 0;
	int oldDirection = 0;
	
	std::ifstream ifs("Config/player_details.ini");

	if (ifs.is_open())
	{
		/*New Character Variable*/
		std::getline(ifs, this->playerDetails.name);
		ifs >> this->playerDetails.textureSwitchCounter;
		ifs >> this->playerDetails.male1Female0;

		/*Current Tile Map*/
		ifs >> currenmtTileMap;

		/*Position & Direction*/
		ifs >> this->playerDetails.position.x >> this->playerDetails.position.y;
		ifs >> oldDirection;

		/*Movement Variables*/
		ifs >> this->playerDetails.velocity.x >> this->playerDetails.velocity.y;
		ifs >> this->playerDetails.maxVelocity;
		ifs >> this->playerDetails.acceleration;
		ifs >> this->playerDetails.deceleration;

		/*Level*/
		ifs >> this->playerDetails.level;

		/*HP*/
		ifs >> this->playerDetails.currentHP;
		ifs >> this->playerDetails.maxHP;

		/*Stamina*/
		ifs >> this->playerDetails.currentStamina;
		ifs >> this->playerDetails.maxStamina;
		ifs >> this->playerDetails.staminaDrainFactor;
		ifs >> this->playerDetails.staminaFillFactor;

		/*Mana*/
		ifs >> this->playerDetails.currentMana;
		ifs >> this->playerDetails.maxMana;

		this->playerDetails.currentTileMap = static_cast<CurrentTileMap>(currenmtTileMap);
		this->playerDetails.oldDirection = static_cast<Direction>(oldDirection);
	}

	ifs.close();
}
void MainMenu::loadProjectileDetailsFromFile()
{
	int projectileType = 0;
	std::ifstream ifs("Config/projectile_details.ini");

	if (ifs.is_open())
	{
		/*Projectile Type*/
		ifs >> projectileType;

		/*Movement Variables*/
		ifs >> this->projectileDetails.velocity.x >> this->projectileDetails.velocity.y;
		ifs >> this->projectileDetails.maxVelocity;
		ifs >> this->projectileDetails.acceleration;
		ifs >> this->projectileDetails.deceleration;

		/*Mana*/
		ifs >> this->projectileDetails.manaDrainFactor;

		/*Destroy Variables*/
		ifs >> this->projectileDetails.lifeTimeCounter;
		ifs >> this->projectileDetails.maxLifeTimeCounter;

		this->projectileDetails.projectileType = static_cast<ProjectileTypes>(projectileType);
	}

	ifs.close();

	std::cout << "Loaded Projectile Details from Main Menu!\n";
}

/*Render Functions*/
void MainMenu::renderTileMap(sf::RenderTarget& target)
{
	this->tileMap->render(target, this->view, sf::Vector2f(static_cast<float>(this->gameInfo->window->getSize().x) / 2.f, static_cast<float>(this->gameInfo->window->getSize().y) / 2.f), &this->shader);
}
void MainMenu::renderNPCs(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->npcItr = this->npcVector.begin(); this->npcItr != this->npcVector.end(); this->npcItr++)
	{
		this->npcVector[counter]->render(target);

		counter++;
	}
}
void MainMenu::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}
void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameInfo->window;
	//target->draw(this->backgroundRect);

	/*Items Rendered to Render Texture*/
	this->renderTexture.clear();
	this->renderTileMap(this->renderTexture);
	this->renderNPCs(this->renderTexture);
	this->renderTexture.display();
	target->draw(this->renderSprite);

	this->renderButtons(*target);

}
