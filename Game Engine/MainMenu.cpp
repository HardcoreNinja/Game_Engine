#include "Header.h"
#include "MainMenu.h"
/*Initializers*/
void MainMenu::initOverlay()
{
	this->overlay.setSize(
		sf::Vector2f(
			static_cast<float>(this->gameInfo->window->getSize().x),
			static_cast<float>(this->gameInfo->window->getSize().y)
		)
	);

	this->overlay.setFillColor(sf::Color(0, 0, 0, 150));
}
void MainMenu::initTitleText()
{
	if (!this->titleFont.loadFromFile("Resources/Fonts/WarPriestExpanded.ttf"))
	{
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:WarPriestExpanded.ttf");
	}

	this->titleText.setFont(this->titleFont);

	this->titleText.setOutlineColor(sf::Color::Red);
	this->titleText.setOutlineThickness(2.f);
	this->titleText.setFillColor(sf::Color::Yellow);
	this->titleText.setCharacterSize(40);
	this->titleText.setString("            Wake's \n               2D \n SFML RPG ENGINE");
	this->titleText.setOrigin(this->titleText.getGlobalBounds().width / 2.f, this->titleText.getGlobalBounds().height / 2.f);
	this->titleText.setPosition(sf::Vector2f(static_cast<float>(this->gameInfo->window->getSize().x / 2.f) + 150.f, + 125.f));
	this->titleText.rotate(25.f);
	
}
void MainMenu::initMusic()
{
	this->gameInfo->audioMap["MAIN_MENU"]->setLoop(true);
	this->gameInfo->audioMap["MAIN_MENU"]->setFadeIn(true);
	this->gameInfo->audioMap["MAIN_MENU"]->play();
}
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
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:BreatheFire.ttf");
	}

	this->text.setFont(this->font);
}
void MainMenu::initButtons()
{
	this->buttons["QUIT_GAME"] = std::make_unique<GUI::Button>(
		120.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Quit Game", 50,  //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["SETTINGS"] = std::make_unique<GUI::Button>(
		120.f, 450.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Settings", 50,   //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["EDITOR"] = std::make_unique<GUI::Button>(
		120.f, 350.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Editor", 50,     //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["NEW_GAME"] = std::make_unique<GUI::Button>(
		120.f, 250.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "New Game", 50,   //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["CONTINUE_GAME"] = std::make_unique<GUI::Button>(
		120.f, 150.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Continue", 50,   //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)
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
void MainMenu::initNPC()
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->gameInfo->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->gameInfo->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->gameInfo->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->gameInfo->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
	this->npc = std::make_unique<NPC>(this->tileMap->getSpawnPositions(), this->tileMap->getPathFinderMarkings(), this->getRandomInt(0, 3), this->getRandomInt(1, 70), this->gameInfo->audioMap);
	//this->npc->setNPCPosition();
	this->npcVector.push_back(std::move(this->npc));
}

/*Constructor & Destructor*/
MainMenu::MainMenu(GameInfo* game_info)
	: State(game_info)
{
	this->initOverlay();
	this->initTitleText();
	this->initMusic();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initRenderTexture();
	this->initTileMap();
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
		this->gameInfo->states->push_back(std::make_unique<Settings>(this->gameInfo, this->npcItr, this->npcVector, this->tileMap, this->titleText, &this->renderTexture, &this->renderSprite));

	/*Editor*/
	if (this->buttons["EDITOR"]->isPressed() && this->getKeyTime())
		this->gameInfo->states->push_back(std::make_unique<Editor>(this->gameInfo));

	/*New Character Screen*/
	if (this->buttons["NEW_GAME"]->isPressed() && this->getKeyTime())
		this->gameInfo->states->push_back(std::make_unique<NewCharacterScreen>(this->gameInfo, this->npcItr, this->npcVector, this->tileMap, this->titleText, &this->renderTexture, &this->renderSprite));

	/*Continue Game*/
	if (this->buttons["CONTINUE_GAME"]->isPressed() && this->getKeyTime())
	{
		this->gameInfo->audioMap["MAIN_MENU"]->setFadeOut(true);
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
	this->initOverlay();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initTileMap();
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
void MainMenu::renderOverlay(sf::RenderTarget& target)
{
	target.draw(this->overlay);
}
void MainMenu::renderTitleText(sf::RenderTarget& target)
{
	target.draw(this->titleText);
}
void MainMenu::renderTileMap(sf::RenderTarget& target)
{
	this->tileMap->render(target, this->view, this->tileMap->getEnterTilePosition(), &this->shader);
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
	//target->draw(this->overlayRect);

	/*Items Rendered to Render Texture*/
	this->renderTexture.clear();
	this->renderTileMap(this->renderTexture);
	this->renderNPCs(this->renderTexture);
	this->renderOverlay(this->renderTexture);
	this->renderTexture.display();
	target->draw(this->renderSprite);

	this->renderTitleText(*target);
	this->renderButtons(*target);
}
