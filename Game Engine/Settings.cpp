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
void Settings::initBackground()
{
	this->backgroundRect.setSize(
		sf::Vector2f(
			static_cast<float>(this->graphicsSettings->resolution.width),
			static_cast<float>(this->graphicsSettings->resolution.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/mainmenu_background.jpg"))
		throw("ERROR::MAIN_MENU::FAILED_TO_LOAD::mainmenu_background.jpg");

	this->backgroundRect.setTexture(&this->backgroundTexture);
}
void Settings::initKeybinds()
{
	std::ifstream ifs("Config/settings_keybinds.ini");

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
void Settings::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/Dosis.ttf"))
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
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)

	this->buttons["BACK"] = std::make_unique<GUI::Button>(
		100.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   //Button Rect Size
		&this->font, "Back", 50,//Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
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

/*Constuctor & Destructor*/
Settings::Settings(GameInfo* game_info)
	: State(game_info)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initDropdownLists();
	this->initTextTitles();
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
		}

		if (!this->dropdownLists["RESOLUTION"]->getShowList() && this->mouseReleased)
		{
			this->pauseButtons = false;
			this->pauseFullScreen = false;
			this->pauseVSync = false;
		}

		/*Fullscreen*/
		if(!pauseFullScreen)
		this->dropdownLists["FULLSCREEN"]->update(this->mousePositionView, dt);

		if (this->dropdownLists["FULLSCREEN"]->getShowList())
			this->pauseVSync = true;

		if (!this->dropdownLists["FULLSCREEN"]->getShowList() && this->mouseReleased)
			this->pauseVSync = false;

		/*VSync*/
		if(!this->pauseVSync)
		this->dropdownLists["VSYNC"]->update(this->mousePositionView, dt);	

		if (this->dropdownLists["VSYNC"]->getShowList())
			this->pauseAnti_Aliasing = true;

		if (!this->dropdownLists["VSYNC"]->getShowList() && this->mouseReleased)
			this->pauseAnti_Aliasing = false;

		/*Anti-Aliasing*/
		if(!this->pauseAnti_Aliasing)
			this->dropdownLists["ANTI_ALIASING"]->update(this->mousePositionView, dt);

		if (this->dropdownLists["ANTI_ALIASING"]->getShowList())
			this->pauseButtons = true;

		if (!this->dropdownLists["ANTI_ALIASING"]->getShowList() && this->mouseReleased)
			this->pauseButtons = false;
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
void Settings::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateMousePosition();
	this->updateButtons();
	this->updateDropdownLists(dt);
	this->updateUserInput(dt);

	if (this->resized)
		this->reinitializeSettings();
}

/*Window Functions*/
void Settings::recreateWindow()
{
	auto style = this->gameInfo->graphicsSettings->isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	{
		this->window->create(
			this->gameInfo->graphicsSettings->resolution,     //Window Resolution
			this->gameInfo->graphicsSettings->title,          //Window Title
			style,                                            //Fullscreen Style or not
			this->gameInfo->graphicsSettings->contextSettings //Anti Aliasing Level
		);
	}
	this->window->setFramerateLimit(this->gameInfo->graphicsSettings->frameRateLimit); //Framerate Limit
	this->window->setVerticalSyncEnabled(this->gameInfo->graphicsSettings->isVSync);   //VSync Enabled

	this->reinitializeSettings();	
	this->reinitializeMainMenu();
}

/*Reinitialize Settings State*/
void Settings::reinitializeSettings()
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initDropdownLists();
	this->resized = false;
}
void Settings::reinitializeMainMenu()
{
	this->states[0].at(0)->initMainMenuBackground();
	this->states[0].at(0)->initMainMenuKeybinds();
	this->states[0].at(0)->initMainMenuFonts();
	this->states[0].at(0)->initMainMenuButtons();
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

	this->graphicsSettings->saveToFile();
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
		target = this->window;
	target->draw(this->backgroundRect);
	target->draw(this->text);
	this->renderButtons(*target);
	this->renderDropdownLists(*target);	
}
