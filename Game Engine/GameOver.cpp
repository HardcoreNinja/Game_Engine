#include "Header.h"
#include "GameOver.h"

/*Initializers*/
void GameOver::initBackground(sf::RenderWindow& window)
{
	/*Background*/
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	)
	);

	this->background.setFillColor(sf::Color(255, 0, 0, 175));

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
}
void GameOver::initText(sf::RenderWindow& window, sf::Font& font)
{
	/*Menu Text*/
	this->shape.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.f, 30.f));
	this->shape.setSize(sf::Vector2f(200.f, 50.f));
	this->shape.setOrigin(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);

	this->text.setFont(font);
	this->text.setString("Game Over");
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
}

/*Constructor & Destructor*/
GameOver::GameOver(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->initBackground(window);
	this->initText(window, font);
}
GameOver::~GameOver()
{
}

/*Add Button Function*/
void GameOver::addButton(std::string map_key, float pos_y, std::string button_text)
{
	float pos_x = this->buttonContainer.getPosition().x;
	float width = 200.f;
	float height = 50.f;


	this->buttons[map_key] = std::make_unique<GUI::Button>(
		pos_x, pos_y,                  //Button Rect Position
		width, height,                 //Button Rect Size
		&this->font, button_text, 50,   //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}

/*Button Functions*/
const bool GameOver::isButtonPressed(const std::string map_key)
{
	return this->buttons[map_key]->isPressed();
}

/*Update Functions*/
void GameOver::update(const sf::Vector2f& mouse_position_window)
{
	for (auto& i : this->buttons)
		i.second->update(mouse_position_window);
}

/*Render Functions*/
void GameOver::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->buttonContainer);
	target.draw(this->text);

	for (auto& i : this->buttons)
		i.second->render(target);
}
