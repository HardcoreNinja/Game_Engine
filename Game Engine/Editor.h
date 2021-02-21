#ifndef EDITOR_H
#define EDITOR_H
#include "State.h"
class Editor :
    public State
{
private:
    /*Initializers*/
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();

public:
    /*Constuctor & Destructor*/
    Editor(GameInfo* game_info);
    virtual ~Editor();

    /*Update Functions*/
    void updateButtons();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Render Functions*/
    void renderButtons(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
