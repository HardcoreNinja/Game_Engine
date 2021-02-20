#include "Header.h"
#include "Settings.h"

/*Initializers*/
void Settings::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
}
void Settings::initBackground(const std::string file_path)
{
	this->backgroundRect.setSize(
		sf::Vector2f(
			static_cast<float>(this->graphicsSettings->resolution.width),
			static_cast<float>(this->graphicsSettings->resolution.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile(file_path))
		throw("ERROR::MAIN_MENU::FAILED_TO_LOAD::mainmenu_background.jpg");

	this->backgroundRect.setTexture(&this->backgroundTexture);
}
void Settings::initKeybinds(const std::string file_path)
{
	std::ifstream ifs(file_path);

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
void Settings::initFonts(const std::string file_path)
{
	if (!this->font.loadFromFile(file_path))
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
	std::vector<std::string> videoModeStringVector;

	for (auto& i : this->videoModes)
		videoModeStringVector.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

	this->dropdownLists["RESOLUTION"] = std::make_unique<GUI::DropdownList>(
		100.f, 150.f,                                         //Dropdown List Position
		200.f, 50.f,                                          //Dropdown List Size 
		this->font, videoModeStringVector.data(), 25,         //Dropdown List Font, String Vector, and Character Size
		this->keyTime, this->maxKeyTime,                      //Dropdown List Key Time Info
		static_cast<unsigned>(videoModeStringVector.size())); // Dropdown ListString Vector Size
}

/*Constuctor & Destructor*/
Settings::Settings(GameInfo* game_info)
	: State(game_info)
{
	this->initVariables();
	this->initBackground("Resources/Images/mainmenu_background.jpg");
	this->initKeybinds("Config/mainmenu_keybinds.ini");
	this->initFonts("Resources/Fonts/Dosis.ttf");
	this->initButtons();
	this->initDropdownLists();
}
Settings::~Settings()
{
}

/*Update Functions*/
void Settings::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mousePositionView);

	//Back to Main Menu
	if (this->buttons["BACK"]->isPressed() && this->getKeyTime())
		this->endState();

	//Apply Seceleted Settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//Test Debug
		std::cout << this->dropdownLists["RESOLUTION"]->getActiveElementID() << '\n';

		this->gameInfo->graphicsSettings->resolution = this->videoModes[this->dropdownLists["RESOLUTION"]->getActiveElementID()];

		this->recreateWindow();
	}
}
void Settings::updateDropdownLists(const float& dt)
{
	this->dropdownLists["RESOLUTION"]->update(this->mousePositionView, dt);
}
void Settings::updateUserInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT_GAME"))))
		this->endState();
}
void Settings::update(const float& dt)
{
	this->updateKeyTime(dt);
	this->updateButtons();
	this->updateDropdownLists(dt);
	this->updateMousePosition();
	this->updateUserInput(dt);
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

	this->initBackground("Resources/Images/mainmenu_background.jpg");
}

/*Render Functions*/
void Settings::renderButtons(sf::RenderTarget& target)
{
	for (auto& itr1 : this->buttons)
		itr1.second->render(target);
}
void Settings::renderDropdownLists(sf::RenderTarget& target)
{
	this->dropdownLists["RESOLUTION"]->render(target);
}
void Settings::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->backgroundRect);
	this->renderButtons(*target);
	this->renderDropdownLists(*target);
}
