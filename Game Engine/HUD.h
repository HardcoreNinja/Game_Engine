#ifndef HUD_H
#define HUD_H
#include "Player.h"

class HUD
{
private:
	/*Sprites*/
	sf::Sprite spriteHUDSystem;
	sf::Sprite spriteRedBar;
	sf::Sprite spriteYellowBar;
	sf::Sprite spriteBlueBar;
	
	/*Textures*/
	sf::Texture textureHUDSystem; 
	sf::Texture textureRedBar;
	sf::Texture textureYellowBar;
	sf::Texture textureBlueBar;

	/*IntRects*/
	sf::IntRect intRectHUDSystem;
	sf::IntRect intRectRedBar;
	sf::IntRect intRectYellowBar;
	sf::IntRect intRectBlueBar;

	/*Initializers*/
	void initSprites();

public: 
	/*Constructor & Destructor*/
	HUD(PlayerDetails player_details);
	virtual ~HUD();

	/*Update Functions*/
	void update(const float& dt);

	/*Render Functions*/
	void render(sf::RenderTarget& target);
};
#endif
