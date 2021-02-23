#include "Header.h"
#include "PauseMenu.h"

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

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->buttonContainer);
	target.draw(this->text);
}

