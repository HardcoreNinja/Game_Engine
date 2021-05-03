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

class Player :
    public Entity
{
private:
    Actors actor;

    /*Initializers*/
    void initIntRectVector();
    void initSpriteRect();
    void initSprite(Actors actor);

public:
    /*Constuctor & Destructor*/
    Player(Actors actor);
    virtual ~Player();

    void update(const float& dt);

    void render(sf::RenderTarget& target);

};
#endif
