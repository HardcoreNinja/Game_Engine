#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "Player.h"

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

    /*Render Texture*/
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    /*Player*/
    std::unique_ptr<Player> player;

    /*Initializers*/
    void initVariables();
    void initKeybinds();
    void initFonts();
    void initRenderTexture();
    void initTileMap();
    void initPauseMenu();
    void initLatestTileMap();
    void initPlayer();

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
    void renderPlayer(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
