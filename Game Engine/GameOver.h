#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "GUI.h"
/*Class Forward Declarations*/
class Button;
class sf::Font;
class sf::Text;
class sf::RectangleShape;
class sf::RenderWindow;
class sf::RenderTarget;

class GameOver
{
private:
	/*Background Variables*/
	sf::RectangleShape background;
	sf::RectangleShape buttonContainer;

	/*Font & Text*/
	sf::Font& font;
	sf::Text text;
	sf::RectangleShape shape;

	/*Button Map*/
	std::map<std::string, std::unique_ptr<GUI::Button>> buttons;

	/*Initializers*/
	void initBackground(sf::RenderWindow& window);
	void initText(sf::RenderWindow& window, sf::Font& font);
public:
	/*Constuctor & Destructor*/
	GameOver(sf::RenderWindow& window, sf::Font& font);
	virtual ~GameOver();

	/*Add Button Function*/
	void addButton(std::string map_key, float pos_y, std::string button_text);

	/*Button Functions*/
	const bool isButtonPressed(const std::string map_key);

	/*Update Functions*/
	void update(const sf::Vector2f& mouse_position_window);

	/*Render Functions*/
	void render(sf::RenderTarget& target);
};
#endif
