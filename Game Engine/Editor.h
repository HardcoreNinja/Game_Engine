#ifndef EDITOR_H
#define EDITOR_H
#include "State.h"
#include "TileMap.h"

/*Class Forward Declarations*/
class Tile;
class TileMap;
class sf::RenderTarget;

class Editor :
    public State
{
private:
    /*Tile Map*/
    std::unique_ptr<TILEMAP::TileMap> tileMap;

    /*Pause Menu*/
    std::unique_ptr<PauseMenu> pauseMenu;

    /*Initializers*/
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();
    void initTileMap();
    void initPauseMenu();

public:
    /*Constuctor & Destructor*/
    Editor(GameInfo* game_info);
    virtual ~Editor();

    /*Update Functions*/
    void updateTileMap();
    void updateButtons();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Render Functions*/
    void renderPauseMenu(sf::RenderTarget& target);
    void renderTiles(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
