#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"

/*Class Forward Declarations*/
class sf::Text;
class sf::Font; 
class sf::RectangleShape;
class sf::RenderTarget;

/*Item Details Structure*/
struct ItemDetails
{
    ItemType itemType;

    /*Properties*/
    float hp;
    float stamina;
    float mana;
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
public:
    /*Constructor & Destructor*/
    Item(std::map<std::string, int>* supported_keys);
    virtual ~Item(); 

    /*Getters*/
    ItemDetails getItemDetails();
    int getRandomInt(int min, int max);

    /*Setters*/
    void setPosition(sf::Vector2f spawn_position);
    void setItemType(ItemType item);

    /*Update Functions*/
    void updateUserInput(sf::Vector2f mouse_view, const float& dt);
    void update(sf::Vector2f mouse_view, const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
