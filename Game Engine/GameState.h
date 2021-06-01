#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "Player.h"
#include "Projectile.h"
#include "HUD.h"
#include "Enemy.h"
#include "Item.h"

/*Class Forward Declarations*/
class Tile;
class TileMap;
class Player;
class Projectile;
class HUD;
class Enemy;
class Item;
class sf::RenderTarget;
class sf::Clock;

class GameState :
    public State
{
private:
    /*Mana*/
    float currentMana;
    float maxMana;
    int manaFillCounter;

    /*Came From Main Menu Bool*/
    bool cameFromMainMenu;

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
    int projectileTypeCounter;
    ProjectileDetails projectileDetails;
    sf::Clock projectileClock;
    std::unique_ptr<Projectile> projectile;
    std::vector<std::unique_ptr<Projectile>> projectileVector;
    std::vector<std::unique_ptr<Projectile>>::const_iterator projectileItr;

    /*Enemy Variables*/
    std::unique_ptr<Enemy> enemy;
    std::vector<std::unique_ptr<Enemy>> enemyVector;
    std::vector<std::unique_ptr<Enemy>>::const_iterator enemyItr;
    std::vector<sf::Vector2f> enemySpawnPositionVector; 

    /*Item Variables*/
    std::unique_ptr<Item> item; 
    std::vector<std::unique_ptr<Item>>::const_iterator itemItr;
    std::vector<std::unique_ptr<Item>> itemVector;

    /*Initializers*/
    void initVariables(bool came_from_main_menu, PlayerDetails player_details, ProjectileDetails projectile_details);
    void initKeybinds();
    void initFonts();
    void initRenderTexture();
    void initTileMap();
    void initPauseMenu();
    void initLatestTileMap();
    void initPlayer(PlayerDetails player_details);
    void initHUD();
    void initEnemies();

public:
    /*Constuctor & Destructor*/
    GameState(GameInfo* game_info, PlayerDetails player_details, ProjectileDetails projectile_details, bool came_from_main_menu);
    virtual ~GameState();

    /*Setters*/
    void setManaDrainFactor();

    /*Update Functions*/
    void updatePauseMenuButtons();
    virtual void updateUserInput(const float& dt);
    void updateInGameActions();
    void updateHUD();
    void updateManaFill();
    void updatePlayer(const float& dt);
    void updatePlayerCollisions();
    void updateProjectileLoop(const float& dt);
    void updateProjectileCollisions();
    void updateProjectileDestroyLoop();
    void updateEnemyLoop(const float& dt);
    void updateEnemyCollisions();
    void updateEnemyDestroyLoop();
    void updateItemLoop(const float& dt);
    virtual void update(const float& dt);

    /*Reinitialize Functions*/
    void reinitializeState();

    /*Render Functions*/
    void renderPauseMenu(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void renderPlayer(sf::RenderTarget& target);
    void renderProjectiles(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void renderHUD(sf::RenderTarget& target);
    void renderItems(sf::RenderTarget& target); 
    virtual void render(sf::RenderTarget* target);
};
#endif
