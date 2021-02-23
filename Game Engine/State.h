#ifndef STATE_H
#define STATE_H
#include "GraphicsSettings.h"
#include "GUI.h"

/*Class Forward Declarations*/
class State;
class Button;
class GraphicsSettings;
class sf::RenderWindow;
class sf::RectangleShape;
class sf::Texture;
class sf::RenderTarget;
class sf::View;

struct GameInfo
{
	/*State Vector*/
	std::vector<std::unique_ptr<State>>* states;

	/*Window & Graphics*/
	GraphicsSettings* graphicsSettings;
	sf::RenderWindow* window;

	/*Polling Events*/
	sf::Event* sfmlEvent;

	/*User Input*/
	std::map<std::string, int>* supportedKeys;
};
class State
{
protected:
	/*State Vector*/
	std::vector<std::unique_ptr<State>>*states;

	/*Game Info*/
	GameInfo* gameInfo;

	/*Window Variables*/
	GraphicsSettings* graphicsSettings;
	sf::RenderWindow* window;

	/*Polling Events*/
	sf::Event* sfmlEvent;

	/*GUI*/
	sf::RectangleShape backgroundRect;
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::Text text;
	std::map<std::string, std::unique_ptr<GUI::Button>> buttons;
	std::map<std::string, std::unique_ptr<GUI::DropdownList>> dropdownLists;

	/*Tile Size*/
	float tileSize;

	/*KeyTime Variables*/
	int keyTime;
	int maxKeyTime;

	/*User Input Variables*/
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	sf::Vector2i mousePositionDesktop;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Vector2u mousePositionTile;

	/*End StateFlags*/
	bool isQuit;

	/*Poll Event Flags*/
	bool mouseReleased;

public:
	/*MainMenu Initializers*/
	void initMainMenuBackground();
	void initMainMenuKeybinds();
	void initMainMenuFonts();
	void initMainMenuButtons();

public:
	/*Constuctor & Destructor*/
	State(GameInfo* game_info);
	virtual ~State();

	/*Getters*/
	const bool& getKeyTime();
	const bool& getisQuit();

	/*Setters*/
	void endState();

	/*Polling Event Functions*/
	void updateSFMLEvents();

	/*Update Functions*/
	virtual void updateMousePosition(sf::View* view = NULL);
	virtual void updateKeyTime(const float& dt);
	virtual void updateUserInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	/*Render Functions*/
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif
