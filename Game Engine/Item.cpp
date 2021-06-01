#include "Header.h"
#include "Item.h"

/*Initializers*/
void Item::initVariables()
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	/*Consumable Type*/
	this->itemDetails.itemType = static_cast<ItemType>(this->getRandomInt(0, 2));
}
void Item::initSpriteRect()
{
	this->spriteRect.setSize(sf::Vector2f(32.f, 32.f)); 
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Red);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);
}
void Item::initSprite()
{
	this->spriteIntRect = sf::IntRect(0, 0, 32, 32); 
	this->setItemType(this->itemDetails.itemType);
	this->sprite.setTextureRect(this->spriteIntRect); 
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
}
void Item::initText()
{
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
		throw ("ERROR::ITEM::FAILED_TO_LOAD:BreatheFire.ttf");

	/*Text Shape*/
	this->textShape.setSize(sf::Vector2f(100.f, 25.f));
	this->textShape.setOrigin(this->textShape.getGlobalBounds().width / 2.f, this->textShape.getGlobalBounds().height / 2.f);
	this->textShape.setFillColor(sf::Color(0, 0, 0, 150));

	/*Text*/
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(15);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setPosition(sf::Vector2f(this->textShape.getPosition().x, this->textShape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
}

/*Constructor & Destructor*/
Item::Item()
{
	this->initVariables();
	this->initSpriteRect();
	this->initSprite();
	this->initText();
}
Item::~Item()
{
}

/*Getters*/
ItemDetails Item::getItemDetails()
{
	return this->itemDetails;
}
int Item::getRandomInt(int min, int max)
{
	return rand() % max + min;
}

/*Setters*/
void Item::setPosition(sf::Vector2f spawn_position)
{
	this->spriteRect.setPosition(spawn_position);
}
void Item::setItemType(ItemType item)
{
	switch (item)
	{
	case ItemType::HP_Potion:
		if (!this->texture.loadFromFile("Resources/Images/Items/Consumables/hp.png"))
			throw("ERROR::ITEM::FAILED_TO_LOAD::Consumables/hp.png");
		this->sprite.setTexture(this->texture);
		this->itemDetails.hp = 25.f;
		this->text.setString("Health Potion");
		break;
	case ItemType::Stamina_Potion:
		if (!this->texture.loadFromFile("Resources/Images/Items/Consumables/stamina.png"))
			throw("ERROR::ITEM::FAILED_TO_LOAD::Consumables/stamina.png");
		this->sprite.setTexture(this->texture);
		this->itemDetails.stamina = 25.f;
		this->text.setString("Stamina Potion");
		break;
	case ItemType::Mana_Potion:
		if (!this->texture.loadFromFile("Resources/Images/Items/Consumables/mana.png"))
			throw("ERROR::ITEM::FAILED_TO_LOAD::Consumables/mana.png");
		this->sprite.setTexture(this->texture);
		this->itemDetails.mana = 25.f;
		this->text.setString("Mana Potion");
		break;
	default:
		std::cout << "ERROR::ITEM::void Item::setItemType(ItemType consumable)::Invalid Switch Entry!\n";
	}
}

/*Update Functions*/
void Item::update(const float& dt)
{
	/*Set Sprite Position to Sprite Rect*/
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
	this->textShape.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 50.f));
	this->text.setPosition(sf::Vector2f(this->textShape.getPosition().x, this->textShape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
}

/*Render Functions*/
void Item::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
	target.draw(this->textShape);
	target.draw(this->text);
}
