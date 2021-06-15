#ifndef ENTITY_H
#define ENTITY_H
#include "Audio.h"

/*Class Forward Declarations*/
class Audio;
class sf::Sprite;
class sf::RectangleShape;
class sf::Texture;
class sf::Clock;

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

	/*Audio*/
	std::map<std::string, std::unique_ptr<Audio>>& audioMap;

public:
	/*Constructor & Destructor*/
	Entity(std::map<std::string, std::unique_ptr<Audio>>& audio_map);
	virtual ~Entity();
};
#endif