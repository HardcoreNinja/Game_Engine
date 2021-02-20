#ifndef MAINMENU_H
#define MAINMENU_H
#include "State.h"
#include "Settings.h"

/*Class Forward Declarations*/
class Settings;

class MainMenu :
    public State
{
public:
    /*Constuctor & Destructor*/
    MainMenu(GameInfo* game_info);
    virtual ~MainMenu();

    /*Update Functions*/
    void updateButtons();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Render Functions*/
    void renderButtons(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
