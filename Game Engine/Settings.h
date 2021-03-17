#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"
class Settings :
    public State
{
private:
    /*Video Modes*/
    std::vector<sf::VideoMode> videoModes;

    /*Initializers*/
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();
    void initDropdownLists();
    void initTextTitles();

    /*Active Element IDs*/
   unsigned short resolutionID ;
   unsigned short fullscreenID;
   unsigned short vSynceID;
   unsigned short anti_AliasingID;

   /*Dropdown Overlap Flags*/
   bool pauseButtons;
   bool pauseFullScreen;
   bool pauseVSync;
   bool pauseAnti_Aliasing;

public:
    /*Constuctor & Destructor*/
    Settings(GameInfo* game_info);
    virtual ~Settings();

    /*Update Functions*/
    void updateButtons();
    void updateDropdownLists(const float& dt);
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Reinitialize Functions*/
    void recreateWindow();
    void reinitializeState();

    /*Save & Load Functions*/
    void saveToFile();
    void loadFromFile();

    /*Render Functions*/
    void renderButtons(sf::RenderTarget& target);
    void renderDropdownLists(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
