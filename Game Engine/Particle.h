#ifndef PARTICLE_H
#define PARTICLE_H
#include "Player.h"

/*Class Forward Declarations*/
class sf::Sprite;
class sf::Texture;
class sf::RenderTarget;
class sf::RenderWindow;

class Particle
{
private:
	sf::Sprite sprite; 
	sf::Texture texture;
	sf::IntRect intRect;

	/*Shader*/
	sf::Shader shader;
	sf::Clock shaderClock;

	/*Initializers*/
	void initVariables(sf::RenderWindow& window);
	void initShader();
public:
	/*Constructor & Destructor*/
	Particle(sf::RenderWindow& window);
	virtual ~Particle();

	/*Getters*/
	sf::Vector2f getPosition();
	int getRandomInt(int min, int max);

	/*Update Functions*/
	void update(const float& dt);

	/*Render Functions*/
	void render(sf::RenderTarget& target, sf::RenderWindow& window, CurrentTileMap currentTileMap);
};
#endif
