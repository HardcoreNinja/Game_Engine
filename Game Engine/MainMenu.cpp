#include "Header.h"
#include "MainMenu.h"

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
