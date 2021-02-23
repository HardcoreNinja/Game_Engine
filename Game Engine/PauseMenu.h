#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include "GUI.h"
/*Class Forward Declarations*/
class Button;
class sf::Font;
class sf::Text;
class sf::RectangleShape;
class sf::RenderTarget;

class PauseMenu
{
private:
	/*Background Variables*/
	sf::RectangleShape background;
	sf::RectangleShape buttonContainer;

	/*Font & Text*/
	sf::Font& font;
	sf::Text text;

	/*Button Map*/
	std::map<std::string, std::unique_ptr<GUI::Button>> buttons;
public:
	/*Constuctor & Destructor*/
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	/*Render Functions*/
	void render(sf::RenderTarget& target);
};
#endif
