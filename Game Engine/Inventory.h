#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"

/*Class Forward Declarations*/
class Item;
class sf::RectangleShape;
class sf::Texture;
class sf::RenderWindow;
class sf::RenderTarget;

struct InventoryDetails
{
	int totalInventory; 

	int numberOfHealthPotions; 
	int numberOfStaminaPotions;
	int numberOfManaPotions;

	std::vector<ItemDetails> itemDetailsVector;
};

class Inventory
{
private:
	/*Inventory Details*/
	InventoryDetails inventoryDetails;

	/*Shape Variables*/
	sf::RectangleShape background; 
	sf::RectangleShape cellContainer;
	std::unique_ptr<sf::RectangleShape> cell; 
	std::vector<std::unique_ptr<sf::RectangleShape>> cellVector;
	std::vector<std::unique_ptr<sf::RectangleShape>>::const_iterator cellItr;

	/*Texture Variables*/
	sf::Texture backgroundTexture;
	sf::Texture inactiveCellTexture;
	sf::Texture activeCellTexture;

	/*IntRect Variables*/
	sf::IntRect backgroundIntRect;
	sf::IntRect cellIntRect;

	/*Show Inventory Bool*/
	bool showInventory;

	/*User Input*/
	std::map<std::string, int> keybinds;

	/*Initializers*/
	void initVariables();
	void initKeybinds(std::map<std::string, int>* supported_keys);
	void initBackground(sf::RenderWindow& window);
	void initCells(sf::RenderWindow& window);
public: 
	/*Constructor & Destructor*/
	Inventory(std::map<std::string, int>* supported_keys, sf::RenderWindow& window);
	virtual ~Inventory();

	/*Getters*/
	bool getShowInventory();

	/*Setters*/
	void setItemToInventory(ItemDetails item_details);

	/*Update Functions*/
	void updateItems();
	void updateUserInput(sf::Vector2i mouse_window, bool key_time, const float& dt);
	void update(sf::Vector2i mouse_window, bool key_time, const float& dt);

	/*Render Functions*/
	void render(sf::RenderTarget& target); 
};
#endif
