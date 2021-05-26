#ifndef MAINMENU_H
#define MAINMENU_H
#include "State.h"
#include "Settings.h"
#include "Editor.h"
#include "NewCharacterScreen.h"
#include "GameState.h"
#include "Player.h"

/*Class Forward Declarations*/
class Settings;
class Editor;
class NewCharacterScreen;
class GameState;
class Player;
class Projectile;
class sf::RenderTarget;

class MainMenu :
    public State
{
private:
    /*Player Details*/
    PlayerDetails playerDetails;

    /*Projectile Details*/
    ProjectileDetails projectileDetails;

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

    /*Save & Load Functions*/
    void loadPlayerDetailsFromFile();
    void loadProjectileDetailsFromFile();

    /*Render Functions*/
    void renderButtons(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
