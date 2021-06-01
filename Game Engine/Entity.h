#ifndef ENTITY_H
#define ENTITY_H

/*Class Forward Declarations*/
sf::Sprite;
sf::RectangleShape;
sf::Texture;
sf::Clock;

class Entity
{
protected:

	/*Sprite Variables*/
	sf::Sprite sprite;
	sf::RectangleShape spriteRect;
	sf::Texture texture;
	std::vector<sf::IntRect> intRectVector;
	sf::IntRect spriteIntRect;

	/*Animation Clocks*/
	sf::Clock animationClock;

	/*User Input*/
	std::map<std::string, int> keybinds;
};
#endif