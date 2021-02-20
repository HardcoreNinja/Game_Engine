#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"
class Settings :
    public State
{
private:
    /*GUI Varaiables*/
    std::map<std::string, std::unique_ptr<GUI::Button>> buttons;
    std::map<std::string, std::unique_ptr<GUI::DropdownList>> dropdownLists;

    /*Video Modes*/
    std::vector<sf::VideoMode> videoModes;

    /*Initializers*/
    void initVariables();
    void initBackground(const std::string file_path);
    void initKeybinds(const std::string file_path);
    void initFonts(const std::string file_path);
    void initButtons();
    void initDropdownLists();
public:
    /*Constuctor / Destructor*/
    Settings(GameInfo* game_info);
    virtual ~Settings();

    /*Update Functions*/
    void updateButtons();
    void updateDropdownLists(const float& dt);
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Window Functions*/
    void recreateWindow();

    /*Render Functions*/
    void renderButtons(sf::RenderTarget& target);
    void renderDropdownLists(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
