#include "Header.h"
#include "PauseMenu.h"

/*Constructor & Destructor*/
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	/*Background*/
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	)
	);

	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	/*Button Container*/
	this->buttonContainer.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x / 4.f),
		static_cast<float>(window.getSize().y)
	)
	);
	this->buttonContainer.setOrigin(sf::Vector2f(this->buttonContainer.getGlobalBounds().width / 2.f, this->buttonContainer.getGlobalBounds().height));
	this->buttonContainer.setPosition(sf::Vector2f(
		static_cast<float>(window.getSize().x / 2.f),
		static_cast<float>(window.getSize().y)
	)
	);
	this->buttonContainer.setFillColor(sf::Color(20, 20, 20, 200));
	
	/*Menu Text*/
	this->text.setFont(this->font);
	this->text.setCharacterSize(25);
	this->text.setOrigin(sf::Vector2f(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f));
	this->text.setPosition(this->buttonContainer.getPosition().x - this->buttonContainer.getGlobalBounds().width / 4.f, 30.f);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("PAUSE MENU");
}
PauseMenu::~PauseMenu()
{
}

/*Add Button Function*/
void PauseMenu::addButton(std::string map_key, float pos_y, std::string button_text)
{
	float pos_x = this->buttonContainer.getPosition().x;
	float width = 200.f;
	float height = 50.f;
	

	this->buttons[map_key] = std::make_unique<GUI::Button>(
		pos_x, pos_y,                  //Button Rect Position
		width, height,                 //Button Rect Size
		&this->font, button_text, 50,   //Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}

/*Button Functions*/
const bool PauseMenu::isButtonPressed(const std::string map_key)
{
	return this->buttons[map_key]->isPressed();
}

/*Update Functions*/
void PauseMenu::update(const sf::Vector2f& mouse_position_window)
{
	for (auto& i : this->buttons)
		i.second->update(mouse_position_window);
}

/*Render Functions*/
void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->buttonContainer);
	target.draw(this->text);

	for (auto& i : this->buttons)
		i.second->render(target);
}

