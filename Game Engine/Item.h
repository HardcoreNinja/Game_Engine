#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"

/*Class Forward Declarations*/
class Audio;
class sf::Text;
class sf::Font; 
class sf::RectangleShape;
class sf::RenderTarget;

/*Item Enums*/
enum class ItemType
{
    HP_Potion = 0,
    Stamina_Potion,
    Mana_Potion
};

/*Item Details Structure*/
struct ItemDetails
{
    ItemType itemType;

    /*Properties*/
    float hp;
    float stamina;
    float mana;

    sf::Sprite itemSprite;
    sf::IntRect itemIntRect;
    sf::Texture itemTexture;

    sf::Text itemCountText;
};

class Item :
    public Entity
{
private:
    /*Item Details*/
    ItemDetails itemDetails;

    /*Item Text & Font*/
    bool showItemText;
    sf::Text text;
    sf::Font font;
    sf::RectangleShape textShape;

    /*Initializers*/
    void initVariables();
    void initKeybinds(std::map<std::string, int>* supported_keys);
    void initSpriteRect();
    void initSprite();
    void initText();
    void initAudio();
public:
    /*Constructor & Destructor*/
    Item(std::map<std::string, int>* supported_keys, std::map<std::string, std::unique_ptr<Audio>>& audio_map);
    virtual ~Item(); 

    /*Getters*/
    std::tuple<sf::RectangleShape, sf::RectangleShape> getItemRect();
    ItemDetails getItemDetails();
    int getRandomInt(int min, int max);

    /*Setters*/
    void setPosition(sf::Vector2f spawn_position);
    void setItemType(ItemType item);

    /*Update Functions*/
    void updateUserInput(sf::Vector2f player, const float& dt);
    void update(sf::Vector2f player, const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
