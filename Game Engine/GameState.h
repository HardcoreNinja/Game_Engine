#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "Player.h"
#include "Projectile.h"
#include "HUD.h"
#include "Enemy.h"
#include "Item.h"
#include "Inventory.h"
#include "NPC.h"
#include "Audio.h"
#include "Particle.h"

/*Class Forward Declarations*/
class State;
class Tile;
class TileMap;
class Player;
class Projectile;
class HUD;
class Enemy;
class Item;
class Inventory;
class NPC;
class GameOver;
class Audio;
class Particle;
class sf::RenderTarget;
class sf::Clock;

class GameState :
    public State
{
private:
    /*Mana Fill Counter*/
    int manaFillCounter;

    /*Came From Main Menu Bool*/
    bool cameFromMainMenu;

    /*Tile Map*/
    sf::Vector2f enterTilePosition;

    /*Audio*/ 
    std::unique_ptr<Audio> audio;
    std::map<std::string, std::unique_ptr<Audio>> audioMap; 

    /*Player*/
    std::unique_ptr<Player> player;

    /*HUD*/
    std::unique_ptr <HUD> hud;

    /*Inventory*/
    std::unique_ptr<Inventory> inventory;

    /*Projectile Variables*/
    int projectileTypeCounter;
    ProjectileDetails projectileDetails;
    sf::Clock projectileClock;
    std::unique_ptr<Projectile> projectile;
    std::vector<std::unique_ptr<Projectile>> projectileVector;
    std::vector<std::unique_ptr<Projectile>>::const_iterator projectileItr;

    /*Enemy Variables*/
    int numberOfEnemies;
    int maxNumberOfEnemies; 
    std::unique_ptr<Enemy> enemy;
    std::vector<std::unique_ptr<Enemy>> enemyVector;
    std::vector<std::unique_ptr<Enemy>>::const_iterator enemyItr;

    /*Item Variables*/
    std::unique_ptr<Item> item; 
    std::vector<std::unique_ptr<Item>>::const_iterator itemItr;
    std::vector<std::unique_ptr<Item>> itemVector;

    /*NPC Variables*/
    std::unique_ptr<NPC> npc;
    std::vector<std::unique_ptr<NPC>>::const_iterator npcItr;
    std::vector<std::unique_ptr<NPC>> npcVector;

    /*Particle Variables*/
    std::unique_ptr<Particle> particle;
    std::vector<std::unique_ptr<Particle>>::const_iterator particleItr;
    std::vector< std::unique_ptr<Particle>> particleVector;

    /*Initializers*/
    void initVariables(bool came_from_main_menu, PlayerDetails player_details, ProjectileDetails projectile_details);
    void initAudio();
    void initKeybinds();
    void initFonts();
    void initShader();
    void initRenderTexture();
    void initPauseMenu();
    void initGameOver();
    void initPlayer(PlayerDetails player_details);
    void initTileMap(PlayerDetails player_details);
    void initHUD();
    void initInventory();
    void initEnemies();

public:
    /*Constuctor & Destructor*/
    GameState(GameInfo* game_info, PlayerDetails player_details, ProjectileDetails projectile_details, bool came_from_main_menu);
    virtual ~GameState();

    /*Setters*/
    void setManaDrainFactor();

    /*Update Functions*/
    void updatePauseMenuButtons();
    void updateGameOverButtons();
    void updateParticle(const float& dt);
    void updateParticleDestroyLoop();
    virtual void updateUserInput(const float& dt);
    void updateInGameActions();
    void updateHUD();
    void updateInventory(const float& dt);
    void updateManaFill();
    void updatePlayer(const float& dt);
    bool updatePlayerItemCollision();
    bool updatePlayerNPCCollision();
    void updatePlayerCollisions();
    void updateDoorCollisions(const float& dt);
    void updateAudio();
    void updateProjectileLoop(const float& dt);
    void updateProjectileCollisions();
    void updateProjectileDestroyLoop();
    void updateEnemyLoop(const float& dt);
    void updateEnemyCollisions();
    void updateEnemyDestroyLoop();
    void updateNPCLoop(const float& dt);
    void updateNPCCollisions();
    void updateItemLoop(const float& dt);
    void updateItemDestroyLoop();
    virtual void update(const float& dt);

    /*Reinitialize Functions*/
    void reinitializeState();

    /*Render Functions*/
    void renderPauseMenu(sf::RenderTarget& target);
    void renderGameOver(sf::RenderTarget& target);
    void renderParticles(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void renderPlayer(sf::RenderTarget& target);
    void renderProjectiles(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void renderNPCs(sf::RenderTarget& target);
    bool renderHUD();
    void renderInventory(sf::RenderTarget& target);
    void renderItems(sf::RenderTarget& target); 
    virtual void render(sf::RenderTarget* target);
};
#endif
