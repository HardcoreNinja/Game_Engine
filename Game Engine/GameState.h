#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "Player.h"
#include "Projectile.h"
#include "HUD.h"

/*Class Forward Declarations*/
class Tile;
class TileMap;
class sf::RenderTarget;
class sf::Clock;

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

    /*HUD*/
    std::unique_ptr <HUD> hud;

    /*Projectile Variables*/
    sf::Clock projectileClock;
    ProjectileTypes projectileType;
    std::unique_ptr<Projectile> projectile;
    std::vector<std::unique_ptr<Projectile>> projectileVector;
    std::vector<std::unique_ptr<Projectile>>::const_iterator projectileItr;

    /*Initializers*/
    void initVariables();
    void initKeybinds();
    void initFonts();
    void initRenderTexture();
    void initTileMap();
    void initPauseMenu();
    void initLatestTileMap();
    void initPlayer(PlayerDetails player_details);
    void initHUD(PlayerDetails player_details);

public:
    /*Constuctor & Destructor*/
    GameState(GameInfo* game_info, PlayerDetails player_details);
    virtual ~GameState();

    /*Update Functions*/
    void updatePauseMenuButtons();
    virtual void updateUserInput(const float& dt);
    void updateInGameActions();
    void updateProjectileSpawnLoop(const float& dt);
    void updateProjectileDestroyLoop();
    void updateProjectileWallCollision();
    virtual void update(const float& dt);

    /*Reinitialize Functions*/
    void reinitializeState();

    /*Render Functions*/
    void renderPauseMenu(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void renderPlayer(sf::RenderTarget& target);
    void renderProjectiles(sf::RenderTarget& target);
    void renderHUD(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
