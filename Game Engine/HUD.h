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

	/*Text & Fonts*/
	sf::Text playerLevel;
	sf::Text staminaText; 
	sf::Text manaText;
	sf::Font font;

	/*Initializers*/
	void initSprites();
	void initText();

public: 
	/*Constructor & Destructor*/
	HUD();
	virtual ~HUD();

	/*Update Functions*/
	void updateHP(PlayerDetails player_details);
	void updateMana(float current_mana, float max_mana);
	void updateManaText(float current_mana, float max_mana);
	void updatePlayerLevelText(PlayerDetails player_details);
	void updateStamina(PlayerDetails player_details);
	void updateStaminaText(PlayerDetails player_details);
	void update(PlayerDetails player_details, float current_mana, float max_mana);

	/*Render Functions*/
	void render(sf::RenderTarget& target);
};
#endif
