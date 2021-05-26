#ifndef NEWCHARACTERSCREEN_H
#define NEWCHARACTERSCREEN_H
#include "State.h"
#include "GUI.h"
#include "GameState.h"
#include "Player.h"
#include "Projectile.h"

/*Class Forward Declarations*/
class Button;
class GameState;
class Player;
class Projectile;
class sf::Sprite;
class sf::Texture;
class sf::Clock;
class sf::RectangleShape;
class sf::Text;
sf::RenderTarget;

class NewCharacterScreen :
    public State
{
private:
	/*Player Details*/
	PlayerDetails playerDetails;

	/*Projectile Details*/
	ProjectileDetails projectileDetails;

	/*Sprite Variables*/
	sf::Sprite sprite;
	sf::IntRect spriteIntRect;
	sf::Texture texture;
	int textureSwitchCounter;
	bool male1Female0;

	/*Animation Variables*/
	sf::Clock animationClock;

	/*Background Variables*/
	sf::RectangleShape background;
	sf::RectangleShape buttonContainer;

	/*Font & Text*/
	sf::Text nameText;
	sf::RectangleShape nameTextShape;
	sf::RectangleShape titleShape;
	sf::RectangleShape textBox;
	std::string nameString;
	sf::Text nameWarningText;
	bool displayNameWarning;

	/*Initializers*/
	void initVariables();
	void initKeybinds();
	void initBackground();
	void initText();
	void initButtons();
	void initSprite();

public:
	/*Constructor & Destructor*/
	NewCharacterScreen(GameInfo* game_info);
	virtual ~NewCharacterScreen();

	/*Update Functions*/
	void updateTexture();
	void updateAnimation();
	void updateButtons();
	virtual void updateUserInput(const float& dt);
	void updateNameText();
	virtual void update(const float& dt);

	/*Reinitialize Functions*/
	void reinitializeState();

	/*Render Functions*/
	void renderSprite(sf::RenderTarget& target);
	void renderBackground(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
	virtual void render(sf::RenderTarget* target);
};
#endif
