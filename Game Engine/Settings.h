#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"
#include "NPC.h"

/*Class Forward Declarations*/
class State;
class NPC;
class TileMap;
class Button;
class DropdownList;
class sf::Shader;
class sf::RenderTarget;
class sf::RectangleShape;

class Settings :
    public State
{
private:
    /*Video Modes*/
    std::vector<sf::VideoMode> videoModes;

    /*Overlay*/
    sf::RectangleShape overlay;

    /*Main Menu NPCs*/
    std::vector<std::unique_ptr<NPC>>::const_iterator& mainMenuNPCItr;
    std::vector<std::unique_ptr<NPC>>& mainMenuNPCVector;

    /*Main Menu TileMap*/
    std::unique_ptr<TILEMAP::TileMap>& mainMenuTileMap;

    /*Main Menu Render Texture Variables*/
    sf::RenderTexture* mainMenuRenderTexture;
    sf::Sprite* mainMenuRenderSprite;

    /*Initializers*/
    void initVariables(
        sf::RenderTexture* render_texture,
        sf::Sprite* render_sprite
    );
    void initVariables();
    void initOverlay();
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
    Settings(
        GameInfo* game_info, 
        std::vector<std::unique_ptr<NPC>>::const_iterator& npc_itr,
        std::vector<std::unique_ptr<NPC>>& npc_vector, 
        std::unique_ptr<TILEMAP::TileMap>& tile_map,
        sf::RenderTexture* mainMenuRenderTexture,
        sf::Sprite* mainMenuRenderSprite
    );
    virtual ~Settings();

    /*Update Functions*/
    void updateButtons();
    void updateDropdownLists(const float& dt);
    virtual void updateUserInput(const float& dt);
    void updateNPCLoop(const float& dt);
    void updateNPCCollisions();
    virtual void update(const float& dt);

    /*Reinitialize Functions*/
    void recreateWindow();
    void reinitializeState();

    /*Save & Load Functions*/
    void saveToFile();
    void loadFromFile();

    /*Render Functions*/
    void renderOverlay(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void renderNPCs(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    void renderDropdownLists(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
