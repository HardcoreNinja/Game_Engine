#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"


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
    ItemDetails itemDetails;

    /*Initializers*/
    void initVariables();
    void initSpriteRect();
    void initSprite();
public:
    /*Constructor & Destructor*/
    Item();
    virtual ~Item(); 

    /*Getters*/
    ItemDetails getItemDetails();
    int getRandomInt(int min, int max);

    /*Setters*/
    void setPosition(sf::Vector2f spawn_position);
    void setItemType(ItemType item);

    /*Update Functions*/
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget& target);
};
#endif
