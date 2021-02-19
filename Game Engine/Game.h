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

	/*Initializers*/
	void initVariables();
	void initGraphicsSettings(const std::string file_path);
	void initWindow();
	void initGameInfo();
	void initSupportedKeys(const std::string file_path);
	void initStates();

public:
	/*Constuctor / Destructor*/
	Game();
	virtual ~Game();

	/*Update Functions*/
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();

	/*Render Functions*/
	void render();

	/*Run Functions*/
	void run();
};
#endif
