#include "Header.h"
#include "MainMenu.h"
/*Initializers*/
void MainMenu::initMainMenuBackground()
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
void MainMenu::initMainMenuKeybinds()
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
void MainMenu::initMainMenuFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/Dosis.ttf"))
	{
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:Dosis.ttf");
	}

	this->text.setFont(this->font);
}
void MainMenu::initMainMenuButtons()
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

	this->buttons["EDITOR"] = std::make_unique<GUI::Button>(
		100.f, 350.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Editor", 50,//Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}

/*Constuctor & Destructor*/
MainMenu::MainMenu(GameInfo* game_info)
	: State(game_info)
{
	this->initMainMenuBackground();
	this->initMainMenuKeybinds();
	this->initMainMenuFonts();
	this->initMainMenuButtons();
}
MainMenu::~MainMenu()
{
}

/*Update Functions*/
void MainMenu::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mousePositionView);

	//Quit Game
	if (this->buttons["QUIT_GAME"]->isPressed() && this->getKeyTime())
		this->endState();

	//Settings
	if (this->buttons["SETTINGS"]->isPressed() && this->getKeyTime())
		this->states->push_back(std::make_unique<Settings>(this->gameInfo));

	//Editor
	if (this->buttons["EDITOR"]->isPressed() && this->getKeyTime())
		this->states->push_back(std::make_unique<Editor>(this->gameInfo));
}
void MainMenu::updateUserInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT_GAME"))))
		this->endState();
}
void MainMenu::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateButtons();
	this->updateMousePosition();
	this->updateUserInput(dt);
}

/*Reinitialize Functions*/
void MainMenu::reinitializeState()
{
	std::cout << "Reinitializing MainMenu!\n";
	this->initMainMenuBackground();
	this->initMainMenuKeybinds();
	this->initMainMenuFonts();
	this->initMainMenuButtons();
}

/*Render Functions*/
void MainMenu::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}
void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->backgroundRect);
	this->renderButtons(*target);
}
