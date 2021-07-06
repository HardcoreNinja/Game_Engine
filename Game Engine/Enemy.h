#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "TileMap.h"

/*Class Forward Declarations*/
class TileMap; 
class Audio;
class sf::Sprite;
class sf::Texture; 
class sf::CircleShape;
class sf::RenderTarget;

struct EnemyDetails
{
    /*EmoteState*/
    EmoteStates emoteState;

    /*Enemy Direction*/
    Direction currentDirection; 
    Direction oldDirection;

    /*Movement Variables*/
    sf::Vector2f velocity; 
    float maxVelocity;
    float acceleration; 
    float deceleration;

    /*Damage*/
    float damage;

    /*HP*/
    int currentHP;
    int maxHP;

    /*Spawn Position Vector*/
    sf::Vector2f enemySpawnPosition;

    /*Path Finder Markings*/
    std::vector<sf::Vector2f> pathFinderMarkings; 
};

class Enemy :
    public Entity
{
private:
    /*Enemy Details*/
    EnemyDetails enemyDetails; 

    /*Audio*/
    bool playEmoteSFX;
    sf::Clock emoteSFXClock;

    /*Collision Variables*/
    bool projectileCollisionBool;
    bool alertCircleCollisionBool;
    bool playerCollisionBool; 
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*Destroy Variables*/
    bool destroy;

    /*AI Variables*/
    bool attackPlayer;

    /*Randomization Variables*/
    int randomDirectionCounter;
    int randomDirectionNumber;

    /*Initializers*/
    void initVariables(std::vector<sf::Vector2f> enemy_spawn_positions, std::vector<sf::Vector2f> path_finder_markings);
    void initSpriteRect();
    void initSprite();
public:
    /*Constructor & Destructor*/
    Enemy(std::vector<sf::Vector2f> enemy_spawn_positions, std::vector<sf::Vector2f> path_finder_markings, std::map<std::string, std::unique_ptr<Audio>>& audio_map);
    virtual ~Enemy();

    /*Setters*/
    void setDestroy(bool destroy);
    void setEnemyPosition();
    void setRandomEnemy();
    void setEmoteState(EmoteStates emote_state);

   /*Getters*/
    bool getDestroy();
    int getRandomInt(int min, int max);
    sf::RectangleShape getSpriteRect();
    std::tuple<sf::RectangleShape, float, bool> getSpriteRectDamageAttackPlayerBool();

    /*Collisions Functions*/
    void projectileCollision(std::tuple<sf::RectangleShape, int> collision_tuple);
    void tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple);
    void playerCollision(sf::RectangleShape player_rect);
    void alertCircleCollision(sf::RectangleShape player_rect);

    /*Update Functions*/
    void updatePath(sf::RectangleShape player_rect, const float& dt); 
    void updateAIDirection(sf::RectangleShape player_rect, const float& dt);
    void updateAIAttackMovement(const float& dt);
    void updateEmoteAnimation();
    void updateRandomDirection(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation();
    void updateAudio();
    void update(sf::RectangleShape player_rect, const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
