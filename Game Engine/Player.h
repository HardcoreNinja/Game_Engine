#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "TileMap.h"

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
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*User Input*/
    std::map<std::string, int> keybinds;

    /*Initializers*/
    void initVariables(PlayerDetails player_details);
    void initKeybinds();
    void initSpriteRect();
    void initSprite();

public:
    /*Constructor & Destructor*/
    Player(std::map<std::string, int>* supported_keys, PlayerDetails player_details);
    virtual ~Player();

    /*Getters*/
    sf::RectangleShape getSpriteRect();
    PlayerDirection getPlayerDirection();
    PlayerDetails getPlayerDetails();

    /*Tile Collisions Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);

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
