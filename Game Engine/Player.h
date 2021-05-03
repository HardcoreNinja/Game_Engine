#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
enum class Actors
{
    Actor_0,
    Actor_1,
    Actor_2,
    Actor_3,
    Actor_4,
    Actor_5,
    Actor_6,
    Actor_7,
    Actor_8,
    Actor_9,
    Actor_10,
    Actor_11,
    Actor_12,
    Actor_13,
    Actor_14,
    Actor_15,
    Actor_16,
    Actor_17,
    Actor_18,
    Actor_19,
    Actor_20,
    Actor_21,
    Actor_22,
    Actor_23,
};
enum class PlayerDirection
{
    Idle = 0,
    Up,
    Down,
    Left,
    Right
};

class Player :
    public Entity
{
private:
    /*Actor Enumerator*/
    Actors actor;
    PlayerDirection playerDirection;

    /*Movement Variables*/
    float movementSpeed;

    /*Collision Variables*/
    bool wallCollision;

    /*User Input*/
    std::map<std::string, int> keybinds;

    /*Initializers*/
    void initVariables();
    void initKeybinds();
    void initIntRectVector();
    void initSpriteRect();
    void initSprite(Actors actor);

public:
    /*Constuctor & Destructor*/
    Player(Actors actor, std::map<std::string, int>* supported_keys);
    virtual ~Player();

    /*Getters*/
    sf::RectangleShape getSpriteRect();

    /*Movement Functions*/
    void movement(const float& dt);

    /*Tile Collisions Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);

    /*Update Functions*/
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
