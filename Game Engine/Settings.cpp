#include "Header.h"
#include "Settings.h"

/*Initializers*/
void Settings::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
	this->pauseButtons = false;
	this->pauseFullScreen = false;
	this->pauseVSync = false;
	this->pauseAnti_Aliasing = false;
}
void Settings::initOverlay()
{
	this->overlay.setSize(
		sf::Vector2f(
			static_cast<float>(this->gameInfo->window->getSize().x),
			static_cast<float>(this->gameInfo->window->getSize().x)
		)
	);

	this->overlay.setFillColor(sf::Color(0, 0, 0, 150));
}
void Settings::initKeybinds()
{
	std::ifstream ifs("Config/settings_keybinds.ini");

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
void Settings::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
	{
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:Dosis.ttf");
	}

	this->text.setFont(this->font);
}
void Settings::initButtons()
{
	this->buttons["APPLY"] = std::make_unique<GUI::Button>(
		300.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   //Button Rect Size
		&this->font, "Apply", 50,//Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)

	this->buttons["BACK"] = std::make_unique<GUI::Button>(
		100.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   //Button Rect Size
		&this->font, "Back", 50,//Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}
void Settings::initDropdownLists()
{
	/*Load Active Element IDs*/
	this->loadFromFile();

	/*Resolution*/
	std::vector<std::string> videoModeStringVector;
	for (auto& i : this->videoModes)
		videoModeStringVector.push_back(std::to_string(i.width) + " x " + std::to_string(i.height));
	this->dropdownLists["RESOLUTION"] = std::make_unique<GUI::DropdownList>(
		200.f, 163.f,                                         //Dropdown List Position
		100.f, 25.f,                                          //Dropdown List Size 
		this->font, videoModeStringVector.data(), 20,         //Dropdown List Font, String Vector, and Character Size
		this->keyTime, this->maxKeyTime,                      //Dropdown List Key Time Info
		static_cast<unsigned>(videoModeStringVector.size())); //Dropdown ListString Vector Size
	this->dropdownLists["RESOLUTION"]->setActiveElementID(this->resolutionID);

	/*Fullscreen*/
	std::vector<std::string> fullscreenStringVector = { "No", "Yes" };
	this->dropdownLists["FULLSCREEN"] = std::make_unique<GUI::DropdownList>(
		200.f, 227.f,                                          //Dropdown List Position
		100.f, 25.f,                                           //Dropdown List Size 
		this->font, fullscreenStringVector.data(), 25,         //Dropdown List Font, String Vector, and Character Size
		this->keyTime, this->maxKeyTime,                       //Dropdown List Key Time Info
		static_cast<unsigned>(fullscreenStringVector.size())); //Dropdown ListString Vector Size
	this->dropdownLists["FULLSCREEN"]->setActiveElementID(this->fullscreenID);

	/*VSync*/
	std::vector<std::string> vSyncStringVector = { "No", "Yes" };
	this->dropdownLists["VSYNC"] = std::make_unique<GUI::DropdownList>(
		200.f, 291.f,                                     //Dropdown List Position
		100.f, 25.f,                                      //Dropdown List Size 
		this->font, vSyncStringVector.data(), 25,         //Dropdown List Font, String Vector, and Character Size
		this->keyTime, this->maxKeyTime,                  //Dropdown List Key Time Info
		static_cast<unsigned>(vSyncStringVector.size())); //Dropdown ListString Vector Size
	this->dropdownLists["VSYNC"]->setActiveElementID(this->vSynceID);

	std::vector<std::string> anti_AliasingStringVector = { "0x", "1x", "2x", "4x", "8x", "16x", "32x" };
	this->dropdownLists["ANTI_ALIASING"] = std::make_unique<GUI::DropdownList>(
		200.f, 355.f,                                             //Dropdown List Position
		100.f, 25.f,                                              //Dropdown List Size 
		this->font, anti_AliasingStringVector.data(), 25,         //Dropdown List Font, String Vector, and Character Size
		this->keyTime, this->maxKeyTime,                          //Dropdown List Key Time Info
		static_cast<unsigned>(anti_AliasingStringVector.size())); //Dropdown ListString Vector Size
	this->dropdownLists["ANTI_ALIASING"]->setActiveElementID(this->anti_AliasingID);
}
void Settings::initTextTitles()
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(25);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setPosition(sf::Vector2f(0.f, 144.f));
	this->text.setFillColor(sf::Color::White);
	this->text.setString("Resolution: \n\n Fullscreen: \n\n VSync: \n\n Anti-Aliasing: \n\n");
}
void Settings::initRenderTexture()
{
	//std::cout << "Window Size: " << this->gameInfo->window->getSize().x << " x " << this->gameInfo->window->getSize().y << '\n';
	this->renderTexture.create(this->gameInfo->window->getSize().x, this->gameInfo->window->getSize().y);
	this->renderTexture.setSmooth(true);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->gameInfo->window->getSize().x, this->gameInfo->window->getSize().y));
}

/*Constuctor & Destructor*/
Settings::Settings(
	GameInfo* game_info, 
	std::vector<std::unique_ptr<NPC>>::const_iterator& npc_itr,
	std::vector<std::unique_ptr<NPC>>& npc_vector,
	std::unique_ptr<TILEMAP::TileMap>& tile_map
)
	: State(game_info), mainMenuNPCItr(npc_itr), mainMenuNPCVector(npc_vector), mainMenuTileMap(tile_map)
{
	this->initVariables();
	this->initOverlay();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initDropdownLists();
	this->initTextTitles();
	this->initRenderTexture();
}
Settings::~Settings()
{
}

/*Update Functions*/
void Settings::updateButtons()
{
	if(!this->pauseButtons)
	for (auto& i : this->buttons)
		i.second->update(this->mousePositionView);

	//Back to Main Menu
	if (this->buttons["BACK"]->isPressed() && this->getKeyTime())
		this->endState();

	//Apply Seceleted Settings
	if (this->buttons["APPLY"]->isPressed())
	{
		/*Resolution*/
		std::cout << this->dropdownLists["RESOLUTION"]->getActiveElementID() << '\n';
		this->resolutionID = this->dropdownLists["RESOLUTION"]->getActiveElementID();
		this->gameInfo->graphicsSettings->resolution = this->videoModes[this->dropdownLists["RESOLUTION"]->getActiveElementID()];

		/*Fullscreen*/
		std::cout << this->dropdownLists["FULLSCREEN"]->getActiveElementID() << '\n';
		this->fullscreenID = this->dropdownLists["FULLSCREEN"]->getActiveElementID();
		this->gameInfo->graphicsSettings->isFullscreen = this->dropdownLists["FULLSCREEN"]->getActiveElementID();
		
		/*VSync*/
		std::cout << this->dropdownLists["VSYNC"]->getActiveElementID() << '\n';
		this->vSynceID = this->dropdownLists["VSYNC"]->getActiveElementID();
		this->gameInfo->graphicsSettings->isVSync = this->dropdownLists["VSYNC"]->getActiveElementID();

		/*Anti-Aliasing*/
		std::cout << this->dropdownLists["ANTI_ALIASING"]->getActiveElementID() << '\n';
		this->anti_AliasingID = this->dropdownLists["ANTI_ALIASING"]->getActiveElementID();

		switch (this->dropdownLists["ANTI_ALIASING"]->getActiveElementID())
		{
		case 0:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 0;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 1:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 1;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 2:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 2;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 3:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 4;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 4:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 8;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 5:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 16;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 6:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 32;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		}
		this->saveToFile();
	}
}
void Settings::updateDropdownLists(const float& dt)
{
	/*Resolution*/
		this->dropdownLists["RESOLUTION"]->update(this->mousePositionView, dt);

		if (this->dropdownLists["RESOLUTION"]->getShowList())
		{
			this->pauseButtons = true;
			this->pauseFullScreen = true;
			this->pauseVSync = true;
			this->pauseAnti_Aliasing = true;
		}
		else if (!this->dropdownLists["RESOLUTION"]->getShowList() && this->mouseReleased)
		{
			this->pauseButtons = false;
			this->pauseFullScreen = false;
			this->pauseVSync = false;
			this->pauseAnti_Aliasing = false;
		}

		/*Fullscreen*/
		if (!pauseFullScreen)
		{
			this->dropdownLists["FULLSCREEN"]->update(this->mousePositionView, dt);

			if (this->dropdownLists["FULLSCREEN"]->getShowList())
				this->pauseVSync = true;

			if (!this->dropdownLists["FULLSCREEN"]->getShowList() && this->mouseReleased)
				this->pauseVSync = false;
		}

		/*VSync*/
		if (!this->pauseVSync)
		{
			this->dropdownLists["VSYNC"]->update(this->mousePositionView, dt);

			if (this->dropdownLists["VSYNC"]->getShowList())
				this->pauseAnti_Aliasing = true;

			if (!this->dropdownLists["VSYNC"]->getShowList() && this->mouseReleased)
				this->pauseAnti_Aliasing = false;
		}

		/*Anti-Aliasing*/
		if (!this->pauseAnti_Aliasing)
		{
			this->dropdownLists["ANTI_ALIASING"]->update(this->mousePositionView, dt);

			if (this->dropdownLists["ANTI_ALIASING"]->getShowList())
				this->pauseButtons = true;

			if (!this->dropdownLists["ANTI_ALIASING"]->getShowList() && this->mouseReleased)
				this->pauseButtons = false;
		}
}
void Settings::updateUserInput(const float& dt)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT_GAME"))))
		this->endState();*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("APPLY_SETTINGS"))))
	{
		/*Resolution*/
		std::cout << this->dropdownLists["RESOLUTION"]->getActiveElementID() << '\n';
		this->resolutionID = this->dropdownLists["RESOLUTION"]->getActiveElementID();
		this->gameInfo->graphicsSettings->resolution = this->videoModes[this->dropdownLists["RESOLUTION"]->getActiveElementID()];

		/*Fullscreen*/
		std::cout << this->dropdownLists["FULLSCREEN"]->getActiveElementID() << '\n';
		this->fullscreenID = this->dropdownLists["FULLSCREEN"]->getActiveElementID();
		this->gameInfo->graphicsSettings->isFullscreen = this->dropdownLists["FULLSCREEN"]->getActiveElementID();

		/*VSync*/
		std::cout << this->dropdownLists["VSYNC"]->getActiveElementID() << '\n';
		this->vSynceID = this->dropdownLists["VSYNC"]->getActiveElementID();
		this->gameInfo->graphicsSettings->isVSync = this->dropdownLists["VSYNC"]->getActiveElementID();

		/*Anti-Aliasing*/
		std::cout << this->dropdownLists["ANTI_ALIASING"]->getActiveElementID() << '\n';
		this->anti_AliasingID = this->dropdownLists["ANTI_ALIASING"]->getActiveElementID();

		switch (this->dropdownLists["ANTI_ALIASING"]->getActiveElementID())
		{
		case 0:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 0;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 1:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 1;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 2:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 2;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 3:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 4;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 4:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 8;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 5:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 16;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		case 6:
			this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel = 32;
			//std::cout << this->gameInfo->graphicsSettings->contextSettings.antialiasingLevel << '\n';
			break;
		}
		this->saveToFile();
	}
}
void Settings::updateNPCLoop(const float& dt)
{
	int counter1 = 0;
	for (this->mainMenuNPCItr = this->mainMenuNPCVector.begin(); this->mainMenuNPCItr != this->mainMenuNPCVector.end(); this->mainMenuNPCItr++)
	{
		this->mainMenuNPCVector[counter1]->update(dt);
		counter1++;
	}
}
void Settings::updateNPCCollisions()
{
	/*NPC/Wall*/
	int counter1 = 0;
	for (this->mainMenuNPCItr = this->mainMenuNPCVector.begin(); this->mainMenuNPCItr != this->mainMenuNPCVector.end(); this->mainMenuNPCItr++)
	{
		this->mainMenuNPCVector[counter1]->tileCollision(this->mainMenuTileMap->getCollision(this->mainMenuNPCVector[counter1]->getSpriteRect()));
		counter1++;
	}
}
void Settings::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateMousePosition();
	this->updateButtons();
	this->updateDropdownLists(dt);
	this->updateUserInput(dt);
	this->updateNPCLoop(dt);
	this->updateNPCCollisions();

}

/*Window Functions*/
void Settings::recreateWindow()
{
	auto style = this->gameInfo->graphicsSettings->isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	{
		this->gameInfo->window->create(
			this->gameInfo->graphicsSettings->resolution,     //Window Resolution
			this->gameInfo->graphicsSettings->title,          //Window Title
			style,                                            //Fullscreen Style or not
			this->gameInfo->graphicsSettings->contextSettings //Anti Aliasing Level
		);
	}
	this->gameInfo->window->setFramerateLimit(this->gameInfo->graphicsSettings->frameRateLimit); //Framerate Limit
	this->gameInfo->window->setVerticalSyncEnabled(this->gameInfo->graphicsSettings->isVSync);   //VSync Enabled

	this->reinitializeStates();
}

/*Reinitialize Functions*/
void Settings::reinitializeState()
{
	std::cout << "Reinitializing Settings!\n";
	this->initVariables();
	this->initOverlay();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initDropdownLists();
}

/*Save & Load Functions*/
void Settings::saveToFile()
{
	std::ofstream ofs("Config/settings_active_element_ID.ini");

	if (ofs.is_open())
	{
		ofs << this->resolutionID << '\n';
		ofs << this->fullscreenID << '\n';
		ofs << this->vSynceID << '\n';
		ofs << this->anti_AliasingID << '\n';
	}
	ofs.close();

	this->gameInfo->graphicsSettings->saveToFile();
	this->recreateWindow();
}
void Settings::loadFromFile()
{
	std::ifstream ifs("Config/settings_active_element_ID.ini");

	if (ifs.is_open())
	{
		ifs >> this->resolutionID;
		ifs >> this->fullscreenID;
		ifs >> this->vSynceID;
		ifs >> this->anti_AliasingID;
	}
	ifs.close();
}

/*Render Functions*/
void Settings::renderOverlay(sf::RenderTarget& target)
{
	target.draw(this->overlay);
}
void Settings::renderTileMap(sf::RenderTarget& target)
{
	this->mainMenuTileMap->render(target, this->view, sf::Vector2f(static_cast<float>(this->gameInfo->window->getSize().x) / 2.f, static_cast<float>(this->gameInfo->window->getSize().y) / 2.f), &this->shader);
}
void Settings::renderNPCs(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->mainMenuNPCItr = this->mainMenuNPCVector.begin(); this->mainMenuNPCItr != this->mainMenuNPCVector.end(); this->mainMenuNPCItr++)
	{
		this->mainMenuNPCVector[counter]->render(target);

		counter++;
	}
}
void Settings::renderButtons(sf::RenderTarget& target)
{
	for (auto& itr1 : this->buttons)
		itr1.second->render(target);
}
void Settings::renderDropdownLists(sf::RenderTarget& target)
{
	this->dropdownLists["ANTI_ALIASING"]->render(target);
	this->dropdownLists["VSYNC"]->render(target);
	this->dropdownLists["FULLSCREEN"]->render(target);
	this->dropdownLists["RESOLUTION"]->render(target);
}
void Settings::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameInfo->window;
	this->renderTexture.clear();
	this->renderTileMap(this->renderTexture);
	this->renderNPCs(this->renderTexture);
	this->renderOverlay(this->renderTexture);
	this->renderTexture.display();
	target->draw(this->renderSprite);

	target->draw(this->text);
	this->renderButtons(*target);
	this->renderDropdownLists(*target);	
}
