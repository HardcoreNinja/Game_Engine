#include "Header.h"
#include "Settings.h"

/*Initializers*/
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
	this->buttons["QUIT_GAME"] = std::make_unique<GUI::Button>(
		100.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Quit Game", 50,//Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}

/*Constuctor & Destructor*/
Settings::Settings(GameInfo* game_info)
	: State(game_info)
{
	this->initBackground("Resources/Images/mainmenu_background.jpg");
	this->initKeybinds("Config/mainmenu_keybinds.ini");
	this->initFonts("Resources/Fonts/Dosis.ttf");
	this->initButtons();
}
Settings::~Settings()
{
}

/*Update Functions*/
void Settings::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mousePositionView);

	//Quit Game
	if (this->buttons["QUIT_GAME"]->isPressed() && this->getKeyTime())
		this->endState();
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
	this->updateMousePosition();
	this->updateUserInput(dt);
}

/*Render Functions*/
void Settings::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}
void Settings::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->backgroundRect);
	this->renderButtons(*target);
}
