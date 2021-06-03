#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"

/*Class Forward Declarations*/
class Item;
class sf::RectangleShape;
class sf::Texture;
class sf::Font;
class sf::Text;
class sf::RenderWindow;
class sf::RenderTarget;

struct InventoryDetails
{
	int totalInventory; 

	int numberOfHealthPotions; 
	int numberOfStaminaPotions;
	int numberOfManaPotions;

	std::vector<ItemDetails> itemDetailsVector;

	ItemDetails usedItemDetails;
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

	/*Font*/
	sf::Font font; 

	/*Show Inventory Bool*/
	bool showInventory;

	/*Used Item Bool*/
	bool usedItem;

	/*User Input*/
	std::map<std::string, int> keybinds;

	/*Initializers*/
	void initVariables();
	void initFont();
	void initKeybinds(std::map<std::string, int>* supported_keys);
	void initBackground(sf::RenderWindow& window);
	void initCells(sf::RenderWindow& window);
public: 
	/*Constructor & Destructor*/
	Inventory(std::map<std::string, int>* supported_keys, sf::RenderWindow& window);
	virtual ~Inventory();

	/*Getters*/
	bool getShowInventory();
	bool getUsedItem();
	ItemDetails getUsedItemDetails();

	/*Setters*/
	void setItemToInventory(ItemDetails item_details);
	void setUsedItem(bool used_item);

	/*Update Functions*/
	void updateUseItem(const sf::Event& sfml_events, const sf::Vector2i& mouse_window, const bool& key_time, const float& dt);
	void updateItems();
	void updateUserInput(const sf::Vector2i& mouse_window, const bool& key_time, const float& dt);
	void update(const sf::Event& sfml_events, const sf::Vector2i& mouse_window, const bool& key_time, const float& dt);

	/*Render Functions*/
	void render(sf::RenderTarget& target); 
};
#endif
