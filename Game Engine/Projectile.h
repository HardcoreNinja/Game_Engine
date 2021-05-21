#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Entity.h"

/*Forward Declarations*/
class sf::RectangleShape;
class sf::RenderTarget;
class sf::Clock;

/*Enumerators*/
enum class ProjectileTypes
{
    Type_0 = 0
};
enum class  ProjectileDirection
{
    Idle = 0,
    Up, 
    Down, 
    Left,
    Right
};

class Projectile :
    public Entity
{
private:
    /*Object Enumerators*/
    ProjectileTypes projectileType;
    ProjectileDirection projectileDirection;

    /*Velocity Variables*/
    float maxvelocity;

    /*Destroy Variables*/
    bool destroy;
    int lifeTimeCounter;
    int maxLifeTimeCounter;

    /*Collision Variables*/
    bool wallCollision;

    /*Animation Variables*/
    sf::Clock animationClock;

    /*Initializers*/
    void initVariables();
    void initSpriteRect();
    void initSprite();

public:
    /*Constructor & Destructor*/
    Projectile();
    virtual ~Projectile();

    /*Getters*/
    bool getDestroy();
    sf::RectangleShape getSpriteRect();

    /*Setters*/
    void setProjectileType(ProjectileTypes projectile_type);
    void setProjectileDirection(int player_direction);
    void setProjectilePosition(sf::RectangleShape player);

    /*Tile Collision Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);

    /*Update Functions*/
    void updateMovement(const float& dt);
    void updateLifeTimeCounter();
    void updateAnimation();
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
