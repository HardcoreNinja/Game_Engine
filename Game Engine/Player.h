#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "TileMap.h"
#include "Item.h"

enum class CurrentTileMap
{
    LEVEL_A, 
    HOUSE_A
};
enum class PlayerDirection
{
    Idle = 0,
    Up,
    Down,
    Left,
    Right
};

struct PlayerDetails
{
    /*New Character Variable*/
    std::string name;
    int textureSwitchCounter;
    bool male1Female0;

    /*Current Tile Map*/
    CurrentTileMap currentTileMap;

    /*Position & Direction*/
    sf::Vector2f position;
    PlayerDirection oldDirection;

    /*Movement Variables*/
    sf::Vector2f velocity;
    float maxVelocity;
    float acceleration;
    float deceleration;

    /*Level*/
    int level;

    /*HP*/
    float currentHP;
    float maxHP;

    /*Stamina*/
    float currentStamina;
    float maxStamina;
    float staminaDrainFactor;
    float staminaFillFactor;

    /*Mana*/
    float currentMana;
    float maxMana;
};

class Player :
    public Entity
{
private:
    /*Stamina Variables*/
    float quarterMaxVelocity;

    /*Player Details Struct*/
    PlayerDetails playerDetails;

    /*Direction Enumerator*/
    PlayerDirection playerDirection;

    /*Collision Variables*/
    bool enemyCollisionBool; 
    bool doorCollision;
    std::string doorName; 
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*Clocks*/
    sf::Clock hpDrainClock;

    /*Initializers*/
    void initVariables(PlayerDetails player_details);
    void initKeybinds(std::map<std::string, int>* supported_keys);
    void initSpriteRect();
    void initSprite();

public:
    /*Constructor & Destructor*/
    Player(std::map<std::string, int>* supported_keys, PlayerDetails player_details);
    virtual ~Player();

    /*Setters*/
    void setCurrentTileMap(CurrentTileMap current_tile_map);
    void setOldDirection(PlayerDirection player_direction);
    void setPosition(sf::Vector2f player_position);
    void setManaFill(float mana_fill);
    void setManaDrain(float mana_drain);
    void setItemBenefits(ItemDetails item_details);

    /*Getters*/
    std::tuple<bool, std::string> getDoorInfo();
    sf::RectangleShape getSpriteRect();
    PlayerDirection getPlayerDirection();
    PlayerDetails getPlayerDetails();
    std::tuple<float, float>getMana();

    /*Collisions Functions*/
    void tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple);
    void enemyCollision(std::tuple< sf::RectangleShape, float, bool> enemy_tuple);

    /*Update Functions*/
    void updateUserInput(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation();
    void updateStamina();
    void update(const float& dt);

    /*Save & Load Functions*/
    void saveToFile();
    
    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
