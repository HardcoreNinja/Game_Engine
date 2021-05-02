#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"

/*Class Forward Declarations*/
class Tile;
class TileMap;
class sf::RenderTarget;

class GameState :
    public State
{
private:
    /*Tile Map*/
    std::unique_ptr<TILEMAP::TileMap> tileMap;

    /*View Camera Speed*/
    float cameraSpeed;

    /*Initializers*/
    void initVariables();
    void initKeybinds();
    void initFonts();
    void initTileMap();
    void initPauseMenu();
    void initLatestTileMap();

public:
    /*Constuctor & Destructor*/
    GameState(GameInfo* game_info);
    virtual ~GameState();

    /*Update Functions*/
    void updatePauseMenuButtons();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Reinitialize Functions*/
    void reinitializeState();

    /*Render Functions*/
    void renderPauseMenu(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
