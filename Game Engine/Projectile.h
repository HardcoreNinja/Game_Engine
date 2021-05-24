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
    Black_Tornado_0 = 0,
    Blue_Tornado_1,
    Brown_Tornado_2,
    Green_Tornado_3,
    Red_Tornado_4,
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
    bool stop;

    /*Destroy Variables*/
    bool destroy;
    int lifeTimeCounter;
    int maxLifeTimeCounter;

    /*Explosion Variables*/
    sf::Texture explosionTexture;
    sf::IntRect explosionIntRect;
    bool explode;

    /*Collision Variables*/
    bool wallCollision;

    /*Animation Variables*/
    sf::Clock projectileAnimationClock;
    sf::Clock explosionAnimationClock;

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
    void setExplosionTexture();

    /*Tile Collision Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);

    /*Update Functions*/
    void updateMovement(const float& dt);
    void updateLifeTimeCounter();
    void updateProjectileAnimation();
    void updateExplosionAnimation();
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
