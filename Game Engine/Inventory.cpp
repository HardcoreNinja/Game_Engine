#include "Header.h"
#include "Inventory.h"

/*Initializers*/
void Inventory::initVariables()
{
	this->showInventory = false;
}
void Inventory::initKeybinds(std::map<std::string, int>* supported_keys)
{
	std::ifstream ifs("Config/inventory_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = supported_keys->at(keyboardKey);
	}
	ifs.close();

	//Debug Tester
	for (auto i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void Inventory::initBackground(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();
	float quarterWindowX = static_cast<float>(windowSize.x) * 0.25;
	float halfWindowY = static_cast<float>(windowSize.y) * 0.5;

	std::cout << "Background Size X: " << quarterWindowX << " x " << "Background Size Y: " << halfWindowY; 

	this->background.setSize(sf::Vector2f(quarterWindowX, halfWindowY));
	this->background.setOutlineThickness(1.f);
	this->background.setOutlineColor(sf::Color(58, 55, 55, 255));

	float xPositionOffset = 32.f;
	this->background.setOrigin(quarterWindowX, halfWindowY / 2.f);
	this->background.setPosition(static_cast<float>(windowSize.x) - xPositionOffset, static_cast<float>(windowSize.y) / 2.f);

	this->backgroundIntRect = sf::IntRect(0, 0, quarterWindowX, halfWindowY);
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Inventory/background_texture.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/background_texture.png");
	this->background.setTextureRect(this->backgroundIntRect); 
	this->background.setTexture(&this->backgroundTexture);
}
void Inventory::initCells(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();
	float quarterWindowX = static_cast<float>(windowSize.x) * 0.25;
	float quarterWindowY = static_cast<float>(windowSize.y) * 0.25;

	int cellsX = 10;
	int cellsY = 6;
	float cellSize = 32.f;
	this->cellIntRect = sf::IntRect(0, 0, 32, 32);
	if (!this->cellTexture.loadFromFile("Resources/Images/Inventory/inactive_cell_32.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/inactive_cell_32.png");

	for (int y = 0; y < cellsY; y++)
	{
		for (int x = 0; x < cellsX; x++)
		{
			this->cell = std::make_unique<sf::RectangleShape>();
			this->cell->setSize(sf::Vector2f(cellSize, cellSize));
			//this->cell->setOutlineThickness(1.f);
			//this->cell->setOutlineColor(sf::Color::White);
			this->cell->setTextureRect(this->cellIntRect);
			this->cell->setTexture(&this->cellTexture);
			this->cell->setPosition(this->background.getPosition().x - static_cast<float>(x * cellSize) - (this->background.getGlobalBounds().width / 4.25f), this->background.getPosition().y + static_cast<float>(y * cellSize) - (this->background.getGlobalBounds().height / 22.f));
			this->cellVector.push_back(std::move(this->cell));
		}
	}
}

/*Constructor & Destructor*/
Inventory::Inventory(std::map<std::string, int>* supported_keys, sf::RenderWindow& window)
{
	this->initKeybinds(supported_keys);
	this->initBackground(window);
	this->initCells(window);
}
Inventory::~Inventory()
{
}

/*Update Functions*/
void Inventory::updateUserInput(bool key_time, const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOW_INVENTORY"))) && key_time)
	{
		if (!this->showInventory)
			this->showInventory = true;
		else if (this->showInventory)
			this->showInventory = false;
	}	
}
void Inventory::update(bool key_time, const float& dt)
{
	this->updateUserInput(key_time, dt);
}

/*Render Functions*/
void Inventory::render(sf::RenderTarget& target)
{
	if (this->showInventory)
	{
		target.draw(this->background);

		for (int i = 0; i < this->cellVector.size(); i++)
		target.draw(*this->cellVector[i]);
	}
}