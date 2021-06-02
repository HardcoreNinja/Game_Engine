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
	this->background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	this->background.setOutlineThickness(1.f);
	this->background.setOutlineColor(sf::Color(58, 55, 55, 255));

	this->backgroundIntRect = sf::IntRect(0, 0, static_cast<int>(this->background.getSize().x), static_cast<int>(this->background.getSize().y));
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Inventory/background_texture.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/background_texture.png");
	this->backgroundTexture.setRepeated(true);
	this->background.setTextureRect(this->backgroundIntRect); 
	this->background.setTexture(&this->backgroundTexture);
}
void Inventory::initCells(sf::RenderWindow& window)
{
	/*Cell Container*/
	this->cellContainer.setSize(sf::Vector2f(640.f, 384.f));
	this->cellContainer.setOutlineThickness(1.f);
	this->cellContainer.setOutlineColor(sf::Color::Transparent);
	this->cellContainer.setFillColor(sf::Color::Transparent);
	this->cellContainer.setOrigin(this->cellContainer.getGlobalBounds().width / 2.f, this->cellContainer.getGlobalBounds().height / 2.f); 
	this->cellContainer.setPosition(this->background.getSize().x / 2.f, this->background.getSize().y - 256.f); 

	/*Cells*/
	int cellsX = 10;
	int cellsY = 6;
	float cellSize = 64.f;
	this->cellIntRect = sf::IntRect(0, 0, 32, 32);
	if (!this->inactiveCellTexture.loadFromFile("Resources/Images/Inventory/inactive_cell_32.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/inactive_cell_32.png");

	if (!this->activeCellTexture.loadFromFile("Resources/Images/Inventory/active_cell_32.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/active_cell_32.png");

	for (int y = 0; y < cellsY; y++)
	{
		for (int x = 0; x < cellsX; x++)
		{
			this->cell = std::make_unique<sf::RectangleShape>();
			this->cell->setSize(sf::Vector2f(cellSize, cellSize));
			this->cell->setTextureRect(this->cellIntRect);
			this->cell->setTexture(&this->inactiveCellTexture);
			this->cell->setPosition(
				this->cellContainer.getPosition().x - this->cellContainer.getSize().x / 2.f + (x * cellSize),
				this->cellContainer.getPosition().y - this->cellContainer.getSize().y / 2.f + (y * cellSize)
			);
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
void Inventory::updateUserInput(sf::Vector2i mouse_window, bool key_time, const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOW_INVENTORY"))) && key_time)
	{
		if (!this->showInventory)
			this->showInventory = true;
		else if (this->showInventory)
			this->showInventory = false;
	}	

	int counter = 0;
	for (this->cellItr = this->cellVector.begin(); this->cellItr != this->cellVector.end(); this->cellItr++)
	{
		if (this->cellVector[counter]->getGlobalBounds().contains(static_cast<float>(mouse_window.x), static_cast<float>(mouse_window.y)))
			this->cellVector[counter]->setTexture(&this->activeCellTexture);
		else if (!this->cellVector[counter]->getGlobalBounds().contains(static_cast<float>(mouse_window.x), static_cast<float>(mouse_window.y)))
			this->cellVector[counter]->setTexture(&this->inactiveCellTexture);

		counter++;		
	}
}
void Inventory::update(sf::Vector2i mouse_window, bool key_time, const float& dt)
{
	this->updateUserInput(mouse_window, key_time, dt);
}

/*Render Functions*/
void Inventory::render(sf::RenderTarget& target)
{
	if (this->showInventory)
	{
		target.draw(this->background);
		target.draw(this->cellContainer);

		for (int i = 0; i < this->cellVector.size(); i++)
		target.draw(*this->cellVector[i]);
	}
}