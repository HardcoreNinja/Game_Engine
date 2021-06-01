#ifndef INVENTORY_H
#define INVENTORY_H

/*Class Forward Declarations*/
class sf::RectangleShape;
class sf::Texture;
class sf::RenderWindow;
class sf::RenderTarget;

class Inventory
{
private:
	/*Shape Variables*/
	sf::RectangleShape background; 
	std::unique_ptr<sf::RectangleShape> cell; 
	std::vector<std::unique_ptr<sf::RectangleShape>> cellVector;
	std::vector<std::unique_ptr<sf::RectangleShape>>::const_iterator cellItr;

	/*Texture Variables*/
	sf::Texture backgroundTexture;
	sf::IntRect backgroundIntRect;
	sf::Texture inactiveCellTexture;
	sf::IntRect cellIntRect;
	sf::Texture activeCellTexture;

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

	/*Update Functions*/
	void updateUserInput(sf::Vector2i mouse_window, bool key_time, const float& dt);
	void update(sf::Vector2i mouse_window, bool key_time, const float& dt);

	/*Render Functions*/
	void render(sf::RenderTarget& target); 
};
#endif
