#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"
class Settings :
    public State
{
private:
    /*GUI Varaiables*/
    std::map<std::string, std::unique_ptr<GUI::Button>> buttons;

    /*Initializers*/
    void initBackground(const std::string file_path);
    void initKeybinds(const std::string file_path);
    void initFonts(const std::string file_path);
    void initButtons();
public:
    /*Constuctor / Destructor*/
    Settings(GameInfo* game_info);
    virtual ~Settings();

    /*Update Functions*/
    void updateButtons();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Render Functions*/
    void renderButtons(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
