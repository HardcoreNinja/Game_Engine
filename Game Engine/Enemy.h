#ifndef ENEMNY_H
#define ENEMY_H
#include "Entity.h"
#include "TileMap.h"

/*Class Forward Declarations*/
class TileMap; 
class sf::Sprite;
class sf::Texture; 
class sf::CircleShape;
class sf::RenderTarget;

enum class EmoteStates
{
    Default = 0,
    Alert_1
};
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
    /*EmoteState*/
    EmoteStates emoteState;

    /*Enemy Direction*/
    EnemyDirection currentDirection; 
    EnemyDirection oldDirection;

    /*Movement Variables*/
    sf::Vector2f velocity; 
    float maxVelocity;
    float acceleration; 
    float deceleration;

    /*Damage*/
    float damage;

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
    bool alertCircleCollisionBool;
    bool playerCollisionBool; 
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*AI Variables*/
    bool attackPlayer;
    int directionNumber;
    sf::CircleShape alertCircle;

    /*Emote Variables*/
    sf::Sprite emoteSprite;
    sf::Texture emoteTexture; 
    sf::IntRect emoteIntRect;
    sf::Clock emoteAnimationClock;

    /*Randomization Variables*/
    int randomDirectionCounter;
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
    void setEmoteState(EmoteStates emote_state);

   /*Getters*/
    int getRandomInt(int min, int max);
    sf::RectangleShape getSpriteRect();
    std::tuple<sf::RectangleShape, float> getEnemyDamageAndRect();

    /*Collisions Functions*/
    void tileCollision(std::tuple<bool, unsigned short> collision_tuple);
    void playerCollision(sf::RectangleShape player_rect);
    void alertCircleCollision(sf::RectangleShape player_rect);

    /*Update Functions*/
    void updateAIDirection(sf::RectangleShape player_rect, const float& dt);
    void updateAIAttackMovement(const float& dt);
    void updateEmoteAnimation();
    void updateRandomDirection(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation();
    void update(sf::RectangleShape player_rect, const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
