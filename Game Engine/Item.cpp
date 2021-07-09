#include "Header.h"
#include "Item.h"

/*Initializers*/
void Item::initVariables()
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	/*Consumable Type*/
	this->itemDetails.itemType = static_cast<ItemType>(this->getRandomInt(0, 3));

	/*Show Item Text Bool*/
	this->showItemText = false;
}
void Item::initKeybinds(std::map<std::string, int>* supported_keys)
{
	std::ifstream ifs("Config/item_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = supported_keys->at(keyboardKey);
	}
	ifs.close();

	//Debug Tester
	for (auto i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void Item::initSpriteRect()
{
this->spriteRect.setSize(sf::Vector2f(32.f, 32.f));
this->spriteRect.setOutlineThickness(1.f);
this->spriteRect.setOutlineColor(sf::Color::Transparent);
this->spriteRect.setFillColor(sf::Color::Transparent);
this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);

/*Alert Circle*/
this->alertCircle = sf::CircleShape(50);
this->alertCircle.setOutlineThickness(1.f);
this->alertCircle.setOutlineColor(sf::Color::Magenta);
this->alertCircle.setFillColor(sf::Color::Transparent);
this->alertCircle.setOrigin(this->alertCircle.getGlobalBounds().width / 2.f, this->alertCircle.getGlobalBounds().height / 2.f);
this->alertCircle.setPosition(this->spriteRect.getPosition());
}
void Item::initSprite()
{
	this->itemDetails.itemIntRect = sf::IntRect(0, 0, 32, 32);
	this->setItemType(this->itemDetails.itemType);
	this->itemDetails.itemSprite.setTextureRect(this->itemDetails.itemIntRect);
	this->itemDetails.itemSprite.setOrigin(this->itemDetails.itemSprite.getGlobalBounds().width / 2.f, this->itemDetails.itemSprite.getGlobalBounds().height / 2.f);
	this->itemDetails.itemSprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
}
void Item::initText()
{
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
		throw ("ERROR::ITEM::FAILED_TO_LOAD:BreatheFire.ttf");

	/*Text Shape*/
	this->textShape.setSize(sf::Vector2f(125.f, 25.f));
	this->textShape.setOrigin(this->textShape.getGlobalBounds().width / 2.f, this->textShape.getGlobalBounds().height / 2.f);
	this->textShape.setFillColor(sf::Color(0, 0, 0, 150));

	/*Text*/
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(15);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setPosition(sf::Vector2f(this->textShape.getPosition().x, this->textShape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
}
void Item::initAudio()
{
	switch (this->itemDetails.itemType)
	{
	case ItemType::HP_Potion:
		this->audioMap["ITEM_POTION"]->play();
		break;
	case ItemType::Stamina_Potion:
		this->audioMap["ITEM_POTION"]->play();
		break;
	case ItemType::Mana_Potion:
		this->audioMap["ITEM_POTION"]->play();
		break;
	default:
		std::cout << "ERROR::ITEM::void Item::setItemType(ItemType consumable)::Invalid Switch Entry!\n";
	}
}

/*Constructor & Destructor*/
Item::Item(std::map<std::string, int>* supported_keys, std::map<std::string, std::unique_ptr<Audio>>& audio_map)
	:Entity(audio_map)
{
	this->initVariables();
	this->initKeybinds(supported_keys);
	this->initSpriteRect();
	this->initSprite();
	this->initText();
	this->initAudio();
}
Item::~Item()
{
}

/*Getters*/
sf::RectangleShape Item::getSpriteRect()
{
	return this->spriteRect;
}
sf::CircleShape Item::getAlertCircle()
{
	return this->alertCircle;
}
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
		if (!this->itemDetails.itemTexture.loadFromFile("Resources/Images/Items/Consumables/hp.png"))
			throw("ERROR::ITEM::FAILED_TO_LOAD::Consumables/hp.png");
		this->itemDetails.itemSprite.setTexture(this->itemDetails.itemTexture);
		this->itemDetails.hp = 25.f;
		this->text.setString("Health Potion (P)");
		break;
	case ItemType::Stamina_Potion:
		if (!this->itemDetails.itemTexture.loadFromFile("Resources/Images/Items/Consumables/stamina.png"))
			throw("ERROR::ITEM::FAILED_TO_LOAD::Consumables/stamina.png");
		this->itemDetails.itemSprite.setTexture(this->itemDetails.itemTexture);
		this->itemDetails.stamina = 25.f;
		this->text.setString("Stamina Potion (P)");
		break;
	case ItemType::Mana_Potion:
		if (!this->itemDetails.itemTexture.loadFromFile("Resources/Images/Items/Consumables/mana.png"))
			throw("ERROR::ITEM::FAILED_TO_LOAD::Consumables/mana.png");
		this->itemDetails.itemSprite.setTexture(this->itemDetails.itemTexture);
		this->itemDetails.mana = 25.f;
		this->text.setString("Mana Potion (P)");
		break;
	default:
		std::cout << "ERROR::ITEM::void Item::setItemType(ItemType consumable)::Invalid Switch Entry!\n";
	}
}

/*Update Functions*/
void Item::updateUserInput(sf::RectangleShape player_rect, const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOW_ITEM_TITLES"))) || this->alertCircle.getGlobalBounds().intersects(player_rect.getGlobalBounds()))
		this->showItemText = true;
	else
		this->showItemText = false;
}
void Item::update(sf::RectangleShape player_rect, const float& dt)
{
	/*User Input*/
	this->updateUserInput(player_rect, dt);

	/*Alert Circle*/
	this->alertCircle.setPosition(this->spriteRect.getPosition());

	/*Set Sprite Position to Sprite Rect*/
	this->itemDetails.itemSprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
	this->textShape.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 50.f));
	this->text.setPosition(sf::Vector2f(this->textShape.getPosition().x, this->textShape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
}

/*Render Functions*/
void Item::render(sf::RenderTarget& target, sf::Vector2f player_center, sf::Shader* shader)
{
	target.draw(this->spriteRect);

	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPosition", player_center);
		target.draw(this->itemDetails.itemSprite, shader);
	}
	else if (!shader)
		target.draw(this->itemDetails.itemSprite);

	//target.draw(this->alertCircle);

	if (this->showItemText)
	{
		target.draw(this->textShape);
		target.draw(this->text);
	}
}
