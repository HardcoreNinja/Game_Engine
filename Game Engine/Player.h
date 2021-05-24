#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
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
    std::string name;
};

class Player :
    public Entity
{
private:
    /*Player Details Struct*/
    PlayerDetails playerDetails;

    /*Direction Enumerator*/
    PlayerDirection playerDirection;
    PlayerDirection oldDirection;

    /*Movement Variables*/
    sf::Vector2f velocity;
    float maxVelocity;
    float acceleration;
    float deceleration;

    /*Collision Variables*/
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*User Input*/
    std::map<std::string, int> keybinds;

    /*Initializers*/
    void initVariables(std::string name);
    void initKeybinds();
    void initSpriteRect();
    void initSprite(int texture_switch_counter, bool male_0_female_1);

public:
    /*Constructor & Destructor*/
    Player(std::map<std::string, int>* supported_keys, int texture_switch_counter, bool male_0_female_1, std::string name);
    virtual ~Player();

    /*Getters*/
    sf::RectangleShape getSpriteRect();
    int getPlayerDirection();

    /*Tile Collisions Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);

    /*Update Functions*/
    void updateUserInput(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation();
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
