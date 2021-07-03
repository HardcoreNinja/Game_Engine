#ifndef STATE_H
#define STATE_H
#include "GraphicsSettings.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include "TileMap.h"

/*Class Forward Declarations*/
class State;
class Button;
class GraphicsSettings;
class PauseMenu;
class GameOver;
class Tile;
class TileMap;
class TextureSelector;
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

	/*Cursor*/
	sf::Cursor* cursor;
	sf::Cursor* cursorDown;
	sf::Image* cursorImage;
	sf::Image* cursorImageDown;

};
class State
{
protected:
	/*Game Info*/
	GameInfo* gameInfo;

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
	float keyTime;
	float maxKeyTime;

	/*User Input Variables*/
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	sf::Vector2i mousePositionDesktop;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Vector2f mousePositionGUI;
	sf::Vector2u mousePositionTile;

	/*View*/
	sf::View defaultWindowView;
	sf::View view;

	/*Pause Menu*/
	std::unique_ptr<PauseMenu> pauseMenu;

	/*Game Over*/
	std::unique_ptr<GameOver> gameOver;
	
	/*End StateFlags*/
	bool isQuit;

	/*Poll Event Flags*/
	bool mouseReleased;

	/*Pause Menu Flags*/
	bool isPaused;

	/*Game Over Flag*/
	bool isGameOver;

	/*Initializers*/
	void initVariables(GameInfo* game_info);
	void initView();
public:
	/*Constuctor & Destructor*/
	State(GameInfo* game_info);
	virtual ~State();

	/*Getters*/
	const bool& getKeyTime();
	const bool& getisQuit();

	/*Setters*/
	void endState();

	/*Update Functions*/
	void updateGraphicsSettings();
	void updateSFMLEvents();
	virtual void updateMousePosition(sf::View* view = NULL, sf::View* default_window_view = NULL);
	virtual void updateKeyTime(const float& dt);
	virtual void updateUserInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	/*Reinitialize Functions*/
	void createWindow();
	virtual void reinitializeState() = 0;
	void reinitializeStates();

	/*Resize View*/
	void resizeView();

	/*Pause Menu Functions*/
	void pause();
	void unpause();

	/*Render Functions*/
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif
