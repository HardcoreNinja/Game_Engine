#ifndef ENTITY_H
#define ENTITY_H
class Entity
{
protected:

	/*Sprite Variables*/
	sf::Sprite sprite;
	sf::RectangleShape spriteRect;
	sf::Texture texture;
	std::vector<sf::IntRect> intRectVector;
	sf::IntRect spriteIntRect;

};
#endif
