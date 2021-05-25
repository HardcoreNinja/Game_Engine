#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"

/*Forward Declarations*/
class TileMap;
class Player;
class sf::RectangleShape;
class sf::RenderTarget;
class sf::Clock;

/*Enumerators*/
enum class ProjectileTypes
{
    Black_Tornado = 0,
    Blue_Tornado,
    Brown_Tornado,
    Green_Ball_1,
    Green_Ball_2,
    Green_Ball_3,
    Green_Ball_4,
    Green_Ball_5,
    Green_Tornado,
    Pink_Ball_1,
    Pink_Ball_2,
    Pink_Ball_3,
    Pink_Ball_4,
    Pink_Ball_5,
    Red_Tornado,
    Yellow_Ball_1,
    Yellow_Ball_2,
    Yellow_Ball_3,
    Yellow_Ball_4,
    Yellow_Ball_5,
    Projectile_MAX,
};
enum class  ProjectileDirection
{
    Idle = 0,
    Up, 
    Down, 
    Left,
    Right
};
struct ProjectileDetails
{
    /*Enumerators*/
    ProjectileTypes projectileType;
    ProjectileDirection projectileDirection;

    /*Movement Variables*/
    sf::Vector2f velocity;
    float maxVelocity;
    float acceleration;
    float deceleration;

    /*Destroy Variables*/
    int lifeTimeCounter;
    int maxLifeTimeCounter;

    /*Explosion Variables*/
    sf::Texture explosionTexture;
    sf::IntRect explosionIntRect;
};
class Projectile :
    public Entity
{
private:
    /*Projectile Details Struct*/
    ProjectileDetails projectileDetails;

    /*Movement Variables*/
    bool stop;

    /*Destroy Variables*/
    bool destroy;

    /*Explosion Variables*/
    bool explode;

    /*Collision Variables*/
    bool wallCollision;
    sf::Vector2f oldPosition;

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
    void setProjectileDirection(PlayerDirection player_direction);
    void setProjectilePosition(sf::RectangleShape player);
    void setExplosionTexture();

    /*Tile Collision Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);

    /*Update Functions*/
    void updateDirection(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateLifeTimeCounter();
    void updateProjectileAnimation();
    void updateExplosionAnimation();
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
