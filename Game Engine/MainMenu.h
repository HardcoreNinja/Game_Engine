#ifndef MAINMENU_H
#define MAINMENU_H
#include "State.h"
#include "Settings.h"
#include "Editor.h"
#include "GameState.h"

/*Class Forward Declarations*/
class Settings;
class Editor;
class GameState;

class MainMenu :
    public State
{
private:
    void initMainMenuBackground();
    void initMainMenuKeybinds();
    void initMainMenuFonts();
    void initMainMenuButtons();
public:
    /*Constuctor & Destructor*/
    MainMenu(GameInfo* game_info);
    virtual ~MainMenu();

    /*Update Functions*/
    void updateButtons();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Reinitialize Functions*/
    void reinitializeState();

    /*Render Functions*/
    void renderButtons(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
