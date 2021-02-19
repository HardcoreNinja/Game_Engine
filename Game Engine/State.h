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

	/*GUI*/
	sf::RectangleShape backgroundRect;
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::Text text;

	/*KeyTime Variables*/
	int keyTime;
	int maxKeyTime;

	/*User Input Variables*/
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	sf::Vector2i mousePositionDesktop;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;

	/*Flags*/
	bool isQuit;

public:
	/*Constuctor / Destructor*/
	State(GameInfo* game_info);
	virtual ~State();

	/*Getters*/
	const bool& getKeyTime();
	const bool& getisQuit();

	/*Setters*/
	void endState();

	/*Update Functions*/

	virtual void updateMousePosition(sf::View* view = NULL);
	virtual void updateKeyTime(const float& dt);
	virtual void updateUserInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	/*Render Functions*/
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif
