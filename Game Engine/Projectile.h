#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"

/*Forward Declarations*/
class TileMap;
class Player;
class Audio;
class sf::RectangleShape;
class sf::RenderTarget;
class sf::Clock;

/*Enumerators*/
enum class ProjectileTypes
{
    Black_Tornado = 0,
    Blue_Tornado,
    Brown_Tornado,
    Cyan_Ball_1,
    Cyan_Ball_2,
    Cyan_Ball_3,
    Cyan_Ball_4,
    Cyan_Ball_5,
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

    /*Mana*/
    float manaDrainFactor;

    /*Damage*/
    int damage;

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
    bool enemyCollisionBool;
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*Animation Variables*/
    sf::Clock projectileAnimationClock;
    sf::Clock explosionAnimationClock;

    /*Initializers*/
    void initVariables(ProjectileDetails projectile_details);
    void initSpriteRect();
    void initSprite();
    void initAudio();
public:
    /*Constructor & Destructor*/
    Projectile(ProjectileDetails projectile_details, std::map<std::string, std::unique_ptr<Audio>>& audio_map);
    virtual ~Projectile();

    /*Getters*/
    std::tuple<sf::RectangleShape, int> getProjectileSpriteRectAndInt();
    bool getDestroy();
    sf::RectangleShape getSpriteRect();
    float getManaDrainFactor();
    ProjectileDetails getProjectileDetails();

    /*Setters*/
    void setProjectileType(ProjectileTypes projectile_type);
    void setProjectileDirection(PlayerDirection player_direction);
    void setProjectilePosition(sf::RectangleShape player);
    void setExplosionTexture();

    /*Collision Functions*/
    void enemyCollision(sf::RectangleShape enemy_rect);
    void tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple);

    /*Update Functions*/
    void updateAudio();
    void updateDirection(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateLifeTimeCounter();
    void updateProjectileAnimation();
    void updateExplosionAnimation();
    void update(const float& dt);

    /*Save & Load Functions*/
    void saveToFile();

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
