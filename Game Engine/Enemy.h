#ifndef ENEMNY_H
#define ENEMY_H
#include "Entity.h"
#include "TileMap.h"


/*Class Forward Declarations*/
class TileMap; 
class sf::RenderTarget;

enum class EnemyDirection
{
    Idle = 0, 
    Up,
    Down,
    Left,
    Right
};
struct EnemyDetails
{
    /*Enemy Direction*/
    EnemyDirection currentDirection; 
    EnemyDirection oldDirection;

    /*Movement Variables*/
    sf::Vector2f velocity; 
    float maxVelocity;
    float acceleration; 
    float deceleration;

    /*Spawn Position Vector*/
    sf::Vector2f enemySpawnPosition;
};

class Enemy :
    public Entity
{
private:
    /*Enemy Details*/
    EnemyDetails enemyDetails; 

    /*Collision Variables*/
    bool wallCollision;
    sf::Vector2f oldPosition;

    int directionCounter;
    int randomDirectionNumber;

    /*Initializers*/
    void initVariables(std::vector<sf::Vector2f> enemy_spawn_positions);
    void initSpriteRect();
    void initSprite();
public:
    /*Constructor & Destructor*/
    Enemy(std::vector<sf::Vector2f> enemy_spawn_positions);
    virtual ~Enemy();

    /*Setters*/
    void setEnemyPosition();
    void setRandomEnemy();

   /*Getters*/
    int getRandomInt(int min, int max);
    sf::RectangleShape getSpriteRect();

    /*Tile Collisions Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);

    /*Update Functions*/
    void updateRandomDirection(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation();
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
