#ifndef NPC_H
#define NPC_H
#include "Entity.h"
#include "TileMap.h"

/*Class Forward Declarations*/
class TileMap;
class sf::Sprite;
class sf::Texture;
class sf::CircleShape;
class sf::RenderTarget;

enum class NPCEmoteStates
{
    Default = 0,
    Alert_1
};
enum class NPCDirection
{
    Idle = 0,
    Up,
    Down,
    Left,
    Right
};

struct NPCDetails
{
    /*NPC Name*/
    std::string name;

    /*EmoteState*/
    NPCEmoteStates emoteState;

    /*Enemy Direction*/
    NPCDirection currentDirection;
    NPCDirection oldDirection;

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

    /*Dialog Strings*/
    std::string dialog1;
};

class NPC :
    public Entity
{
private:
    /*Enemy Details*/
    NPCDetails npcDetails;

    /*Male/Female Bool*/
    bool male1Female0;

    /*Text & Font Variables*/
    bool showNPCText;
    sf::Text textName;
    sf::Text textBody;
    sf::Font font;
    sf::Clock dialogClock; 
    int character;
    sf::RectangleShape textBackground;
    sf::RectangleShape textNameShape;
    sf::RectangleShape textBodyShape;

    /*Dialog Audio*/
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound; 

    /*Collision Variables*/
    bool projectileCollisionBool;
    bool alertCircleCollisionBool;
    bool playerCollisionBool;
    bool wallCollision;
    sf::Vector2f oldPosition;

    /*Destroy Variables*/
    bool destroy;

    /*AI Variables*/
    NPCDirection lastDirection;
    bool goingAroundWall;
    bool interactWithPlayer;
    bool talkingToPlayer;
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
    void initVariables(std::vector<sf::Vector2f> npc_spawn_positions, std::vector<sf::Vector2f> path_finder_markings);
    void initSpriteRect();
    void initSprite(bool male_1_female_0, int texture_switch_number);
    void initText();

public:
    /*Constructor & Destructor*/
    NPC(
        std::vector<sf::Vector2f> npc_spawn_positions, 
        std::vector<sf::Vector2f> path_finder_markings, 
        bool male_1_female_0, 
        int texture_switch_number
    );
    virtual ~NPC();

    /*Setters*/
    void setNPCPosition();
    void setNPC(bool male_1_female_0, int texture_switch_number);
    void setEmoteState(NPCEmoteStates emote_state);

    /*Getters*/
    bool getDestroy();
    int getRandomInt(int min, int max);
    sf::RectangleShape getSpriteRect();
    std::tuple<sf::RectangleShape, float, bool> getSpriteRectDamageInteractWithPlayerBool();

    /*Collisions Functions*/
    void projectileCollision(std::tuple<sf::RectangleShape, int> collision_tuple);
    void tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple);
    void playerCollision(sf::RectangleShape player_rect);
    void alertCircleCollision(sf::RectangleShape player_rect);

    /*Update Functions*/
    void updateDialog();
    void updateInteractWithPlayer(sf::RectangleShape player_rect, sf::Vector2f mouse_view, const sf::Event& smfl_events, const bool& key_time);
    void updatePath(sf::RectangleShape player_rect, const float& dt);
    void updateAIDirection(sf::RectangleShape player_rect, const float& dt);
    void updateAIMovement(const float& dt);
    void updateEmoteAnimation();
    void updateRandomDirection(const float& dt);
    void updateVelocity(float dir_x, float dir_y, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation();
    void update(sf::RectangleShape player_rect, sf::Vector2f mouse_view, const sf::Event& smfl_events, const bool& key_time, const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
