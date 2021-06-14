#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "TileMap.h"
#include "Item.h"
#include "Audio.h"

/*Class Forward Declarations*/
class Entity;
class TileMap;
class Audio;
class Item;
class Audio;
class sf::Sprite;
class sf::Texture;
class sf::CircleShape;
class sf::RenderTarget;

enum class CurrentTileMap
{
    LEVEL_A, 
    HOUSE_A
};
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
    /*New Character Variable*/
    std::string name;
    int textureSwitchCounter;
    bool male1Female0;

    /*Current Tile Map*/
    CurrentTileMap currentTileMap;

    /*Position & Direction*/
    sf::Vector2f position;
    PlayerDirection currentDirection;
    PlayerDirection oldDirection;

    /*Movement Variables*/
    sf::Vector2f velocity;
    float maxVelocity;
    float acceleration;
    float deceleration;

    /*Level*/
    int level;

    /*HP*/
    float currentHP;
    float maxHP;

    /*Stamina*/
    float currentStamina;
    float maxStamina;
    float staminaDrainFactor;
    float staminaFillFactor;

    /*Mana*/
    float currentMana;
    float maxMana;
};

class Player :
    public Entity
{
private:
    /*Stamina Variables*/
    float quarterMaxVelocity;

    /*Player Details Struct*/
    PlayerDetails playerDetails;

    /*Audio*/
    std::unique_ptr<Audio> audio;
    std::map<std::string, std::unique_ptr<Audio>> audioMap;
    sf::Clock footStepsClock;
    int footStepCounter;

    /*Collision Variables*/
    bool enemyCollisionBool; 
    bool npcCollisionBool;
    bool doorCollision;
    std::string doorName; 
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*Clocks*/
    sf::Clock hpDrainClock;

    /*Initializers*/
    void initVariables(PlayerDetails player_details);
    void initKeybinds(std::map<std::string, int>* supported_keys);
    void initSpriteRect();
    void initSprite();
    void initAudio();

public:
    /*Constructor & Destructor*/
    Player(std::map<std::string, int>* supported_keys, PlayerDetails player_details);
    virtual ~Player();

    /*Setters*/
    void setHealthToFull();
    void setCurrentTileMap(CurrentTileMap current_tile_map);
    void setOldDirection(PlayerDirection old_direction);
    void setCurrentDirection(PlayerDirection current_direction);
    void setVelocity(sf::Vector2f velocity);
    void setPosition(sf::Vector2f player_position);
    void setManaFill(float mana_fill);
    void setManaDrain(float mana_drain);
    void setItemBenefits(ItemDetails item_details);

    /*Getters*/
    std::tuple<bool, std::string> getDoorInfo();
    sf::RectangleShape getSpriteRect();
    PlayerDirection getPlayerDirection();
    PlayerDetails getPlayerDetails();
    std::tuple<float, float>getMana();

    /*Collisions Functions*/
    void tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple);
    void enemyCollision(std::tuple< sf::RectangleShape, float, bool> enemy_tuple);
    void npcCollision(sf::RectangleShape npc_rect);

    /*Update Functions*/
    void updateUserInput(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation();
    void updateStamina();
    void updateAudio();
    void update(const float& dt);

    /*Save & Load Functions*/
    void saveToFile();
    
    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
