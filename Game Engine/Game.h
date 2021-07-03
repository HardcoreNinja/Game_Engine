#ifndef GAME_H
#define GAME_H
#include "MainMenu.h"

/*Class Forward Declarations*/
class MainMenu;
class sf::Event;
class sf::Clock;

class Game
{
private:
	/*Game Info*/
	GameInfo gameInfo;

	/*State Vector*/
	std::vector<std::unique_ptr<State>> states;

	/*Window Variables*/
	GraphicsSettings graphicsSettings;
	std::unique_ptr<sf::RenderWindow> window;
	sf::Event sfmlEvent;

	/*Delta Time Variables*/
	float dt;
	sf::Clock dtClock;

	/*Input Variables*/
	std::map<std::string, int> supportedKeys;

	/*Cursor*/
	sf::Image cursorImage;
	sf::Cursor cursor;
	sf::Image cursorImageDown;
	sf::Cursor cursorDown;

	/*Initializers*/
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initCursor();
	void initGameInfo();
	void initSupportedKeys();
	void initStates();
public:
	/*Constuctor & Destructor*/
	Game();
	virtual ~Game();

	/*Update Functions*/
	void updateDeltaTime();
	//void updateSFMLEvents();
	void update();

	/*Render Functions*/
	void render();

	/*Run Functions*/
	void run();
};
#endif
