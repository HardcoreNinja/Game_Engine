#include "Header.h"
#include "State.h"
/*MainMenu Initializers*/
void State::initMainMenuBackground()
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
void State::initMainMenuKeybinds()
{
	std::ifstream ifs("Config/mainmenu_keybinds.ini");

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
void State::initMainMenuFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/Dosis.ttf"))
	{
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:Dosis.ttf");
	}

	this->text.setFont(this->font);
}
void State::initMainMenuButtons()
{
	this->buttons["QUIT_GAME"] = std::make_unique<GUI::Button>(
		100.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Quit Game", 50,//Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)

	this->buttons["SETTINGS"] = std::make_unique<GUI::Button>(
		100.f, 450.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Settings", 50,//Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}

/*Constuctor & Destructor*/
State::State(GameInfo* game_info)
{
	this->states = game_info->states;
	this->gameInfo = game_info;
	this->graphicsSettings = game_info->graphicsSettings;
	this->window = game_info->window;
	this->sfmlEvent = game_info->sfmlEvent;
	this->supportedKeys = game_info->supportedKeys;
	this->keyTime = 0;
	this->maxKeyTime = 100;
	this->isQuit = false;
	this->mouseReleased = false;
}
State::~State()
{
}

/*Getters*/
const bool& State::getKeyTime()
{
	if (this->keyTime >= this->maxKeyTime)
	{
		this->keyTime = 0;
		return true;
	}
	else
		return false;
}
const bool& State::getisQuit()
{
	return this->isQuit;
}

/*Setters*/
void State::endState()
{
	this->isQuit = true;
}

/*Polling Event Functions*/
void State::updateSFMLEvents()
{
	while (this->window->pollEvent(*this->sfmlEvent))
	{
		if (this->sfmlEvent->type == sf::Event::MouseButtonPressed)
		{
			std::cout << "Mouse Pressed!\n";
			this->mouseReleased = false;
		}
		if (this->sfmlEvent->type == sf::Event::MouseButtonReleased)
		{
			std::cout << "Mouse Released!\n";
			this->mouseReleased = true;
		}
	}
}

/*Update Functions*/
void State::updateMousePosition(sf::View* view)
{
	this->mousePositionDesktop = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	this->window->setView(this->window->getDefaultView());
}
void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->maxKeyTime)
		this->keyTime += static_cast<int>(2.f * dt * (1.f / dt));

	/*Test Debug
	std::cout << this->keyTime << '\n';
	*/
}
