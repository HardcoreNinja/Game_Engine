#include "Header.h"
#include "Inventory.h"

/*Initializers*/
void Inventory::initVariables()
{
	this->showInventory = false;
	this->usedItem = false; 
	this->inventoryDetails.hpTextureFilePath = "Resources/Images/Items/Consumables/hp.png";
	this->inventoryDetails.staminaTextureFilePath = "Resources/Images/Items/Consumables/stamina.png";
	this->inventoryDetails.manaTextureFilePath = "Resources/Images/Items/Consumables/mana.png";
}
void Inventory::initFont()
{
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
		throw ("ERROR::INVENTORY::FAILED_TO_LOAD:BreatheFire.ttf");
}
void Inventory::initKeybinds(std::map<std::string, int>* supported_keys)
{
	std::ifstream ifs("Config/inventory_keybinds.ini");

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
void Inventory::initBackground(sf::RenderWindow& window)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	this->background.setOutlineThickness(1.f);
	this->background.setOutlineColor(sf::Color(58, 55, 55, 255));

	this->backgroundIntRect = sf::IntRect(0, 0, static_cast<int>(this->background.getSize().x), static_cast<int>(this->background.getSize().y));
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Inventory/background_texture.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/background_texture.png");
	this->backgroundTexture.setRepeated(true);
	this->background.setTextureRect(this->backgroundIntRect); 
	this->background.setTexture(&this->backgroundTexture);
}
void Inventory::initCells(sf::RenderWindow& window)
{
	/*Cell Container*/
	this->cellContainer.setSize(sf::Vector2f(640.f, 384.f));
	this->cellContainer.setOutlineThickness(1.f);
	this->cellContainer.setOutlineColor(sf::Color::Transparent);
	this->cellContainer.setFillColor(sf::Color::Transparent);
	this->cellContainer.setOrigin(this->cellContainer.getGlobalBounds().width / 2.f, this->cellContainer.getGlobalBounds().height / 2.f); 
	this->cellContainer.setPosition(this->background.getSize().x / 2.f, this->background.getSize().y - 256.f); 

	/*Cells*/
	int cellsX = 10;
	int cellsY = 6;
	float cellSize = 64.f;
	this->cellIntRect = sf::IntRect(0, 0, 32, 32);
	if (!this->inactiveCellTexture.loadFromFile("Resources/Images/Inventory/inactive_cell_32.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/inactive_cell_32.png");

	if (!this->activeCellTexture.loadFromFile("Resources/Images/Inventory/active_cell_32.png"))
		throw("ERROR::INVENTORY::FAILED_TO_LOAD::Inventory/active_cell_32.png");

	for (int y = 0; y < cellsY; y++)
	{
		for (int x = 0; x < cellsX; x++)
		{
			this->cell = std::make_unique<sf::RectangleShape>();
			this->cell->setSize(sf::Vector2f(cellSize, cellSize));
			this->cell->setTextureRect(this->cellIntRect);
			this->cell->setTexture(&this->inactiveCellTexture);
			this->cell->setPosition(
				this->cellContainer.getPosition().x - this->cellContainer.getSize().x / 2.f + (x * cellSize),
				this->cellContainer.getPosition().y - this->cellContainer.getSize().y / 2.f + (y * cellSize)
			);
			this->cellVector.push_back(std::move(this->cell));
		}
	}
}

/*Constructor & Destructor*/
Inventory::Inventory(std::map<std::string, int>* supported_keys, sf::RenderWindow& window, std::map<std::string, std::unique_ptr<Audio>>& audio_map)
	: audioMap(audio_map)
{
	this->initVariables();
	this->initFont();
	this->initKeybinds(supported_keys);
	this->initBackground(window);
	this->initCells(window);
}
Inventory::~Inventory()
{
}

/*Getters*/
bool Inventory::getShowInventory()
{
	return this->showInventory;
}
bool Inventory::getUsedItem()
{
	return this->usedItem;
}
ItemDetails Inventory::getUsedItemDetails()
{
	return this->inventoryDetails.usedItemDetails;
}

/*Setters*/
void Inventory::setItemToInventory(ItemDetails item_details)
{
	switch (item_details.itemType)
	{
	case ItemType::HP_Potion:
		if (this->inventoryDetails.numberOfHealthPotions == 0)
			this->inventoryDetails.itemDetailsVector.push_back(item_details);
		this->inventoryDetails.numberOfHealthPotions += 1; 
		this->inventoryDetails.totalInventory += 1;
		break;
	case ItemType::Stamina_Potion:
		if (this->inventoryDetails.numberOfStaminaPotions == 0)
			this->inventoryDetails.itemDetailsVector.push_back(item_details);
		this->inventoryDetails.numberOfStaminaPotions += 1;
		this->inventoryDetails.totalInventory += 1;
		break;
	case ItemType::Mana_Potion:
		if (this->inventoryDetails.numberOfManaPotions == 0)
			this->inventoryDetails.itemDetailsVector.push_back(item_details);
		this->inventoryDetails.numberOfManaPotions += 1;
		this->inventoryDetails.totalInventory += 1;
		break;
	default:
		std::cout << "ERROR::ITEM::void Item::setItemType(ItemType consumable)::Invalid Switch Entry!\n";
	}
}
void Inventory::setUsedItem(bool used_item)
{
	this->usedItem = used_item;
}

/*Update Functions*/
void Inventory::updateUseItem(const sf::Event& sfml_events, const sf::Vector2i& mouse_window, const bool& key_time, const float& dt)
{
	for (int i = 0; i < this->inventoryDetails.itemDetailsVector.size(); i++)
	{
		if (this->cellVector[i]->getGlobalBounds().contains(static_cast<float>(mouse_window.x), static_cast<float>(mouse_window.y)) && (sfml_events.mouseButton.button == sf::Mouse::Left && key_time))
		{
			switch (this->inventoryDetails.itemDetailsVector[i].itemType)
			{
			case ItemType::HP_Potion:
				this->usedItem = true;
				this->inventoryDetails.usedItemDetails = this->inventoryDetails.itemDetailsVector[i];
				this->inventoryDetails.numberOfHealthPotions -= 1;
				if (this->inventoryDetails.numberOfHealthPotions == 0)
				{
					this->inventoryDetails.itemDetailsVector.erase(this->inventoryDetails.itemDetailsVector.begin() + i);
					this->inventoryDetails.itemDetailsVector.shrink_to_fit();
				}
				this->audioMap["INVENTORY_USE_POTION"]->play();
				break;
			case ItemType::Stamina_Potion:
				this->usedItem = true;
				this->inventoryDetails.usedItemDetails = this->inventoryDetails.itemDetailsVector[i];
				this->inventoryDetails.numberOfStaminaPotions -= 1;
				if (this->inventoryDetails.numberOfStaminaPotions == 0)
				{
					this->inventoryDetails.itemDetailsVector.erase(this->inventoryDetails.itemDetailsVector.begin() + i);
					this->inventoryDetails.itemDetailsVector.shrink_to_fit();
				}
				this->audioMap["INVENTORY_USE_POTION"]->play();
				break;
			case ItemType::Mana_Potion:
				this->usedItem = true;
				this->inventoryDetails.usedItemDetails = this->inventoryDetails.itemDetailsVector[i];
				this->inventoryDetails.numberOfManaPotions -= 1;
				if (this->inventoryDetails.numberOfManaPotions == 0)
				{
					this->inventoryDetails.itemDetailsVector.erase(this->inventoryDetails.itemDetailsVector.begin() + i);
					this->inventoryDetails.itemDetailsVector.shrink_to_fit();
				}
				this->audioMap["INVENTORY_USE_POTION"]->play();
				break;
			default:
				std::cout << "ERROR::ITEM::void Item::setItemType(ItemType consumable)::Invalid Switch Entry!\n";
			}
		}
	}
}
void Inventory::updateItems()
{
		for (int i = 0; i < this->inventoryDetails.itemDetailsVector.size(); i++)
		{
			switch (this->inventoryDetails.itemDetailsVector[i].itemType)
			{
			case ItemType::HP_Potion:
				if (!this->inventoryDetails.itemDetailsVector[i].itemTexture.loadFromFile(this->inventoryDetails.hpTextureFilePath))
					throw("ERROR::INVENTORY::FAILED_TO_LOAD::Consumables/hp.png");
				this->inventoryDetails.itemDetailsVector[i].itemSprite.setTexture((this->inventoryDetails.itemDetailsVector[i].itemTexture));
				this->inventoryDetails.itemDetailsVector[i].itemCountText.setString("x" + std::to_string(this->inventoryDetails.numberOfHealthPotions));
				break;
			case ItemType::Stamina_Potion:
				if (!this->inventoryDetails.itemDetailsVector[i].itemTexture.loadFromFile(this->inventoryDetails.staminaTextureFilePath))
					throw("ERROR::INVENTORY::FAILED_TO_LOAD::Consumables/stamina.png");
				this->inventoryDetails.itemDetailsVector[i].itemSprite.setTexture((this->inventoryDetails.itemDetailsVector[i].itemTexture));
				this->inventoryDetails.itemDetailsVector[i].itemCountText.setString("x" + std::to_string(this->inventoryDetails.numberOfStaminaPotions));
				break;
			case ItemType::Mana_Potion:
				if (!this->inventoryDetails.itemDetailsVector[i].itemTexture.loadFromFile(this->inventoryDetails.manaTextureFilePath))
					throw("ERROR::INVENTORY::FAILED_TO_LOAD::Consumables/mana.png");
				this->inventoryDetails.itemDetailsVector[i].itemSprite.setTexture((this->inventoryDetails.itemDetailsVector[i].itemTexture));
				this->inventoryDetails.itemDetailsVector[i].itemCountText.setString("x" + std::to_string(this->inventoryDetails.numberOfManaPotions));
				break;
			default:
				std::cout << "ERROR::ITEM::void Item::setItemType(ItemType consumable)::Invalid Switch Entry!\n";
			}

			/*Item Counter Text*/
			this->inventoryDetails.itemDetailsVector[i].itemCountText.setFont(this->font);
			this->inventoryDetails.itemDetailsVector[i].itemCountText.setCharacterSize(16);
			this->inventoryDetails.itemDetailsVector[i].itemCountText.setOrigin(
				this->inventoryDetails.itemDetailsVector[i].itemCountText.getGlobalBounds().width / 2.f,
				this->inventoryDetails.itemDetailsVector[i].itemCountText.getGlobalBounds().height / 2.f);
			this->inventoryDetails.itemDetailsVector[i].itemCountText.setPosition(
				this->cellVector[i]->getPosition().x + this->cellVector[i]->getSize().x - 15.f,
				this->cellVector[i]->getPosition().y + this->cellVector[i]->getSize().y - 15.f);

			/*Item Sprite*/
			this->inventoryDetails.itemDetailsVector[i].itemSprite.setTextureRect(this->inventoryDetails.itemDetailsVector[i].itemIntRect);
			this->inventoryDetails.itemDetailsVector[i].itemSprite.setPosition(
				this->cellVector[i]->getPosition().x + this->cellVector[i]->getSize().x / 2.f,
				this->cellVector[i]->getPosition().y + this->cellVector[i]->getSize().y / 2.f
			);
		}
}
void Inventory::updateUserInput(const sf::Vector2i& mouse_window, const bool& key_time, const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOW_INVENTORY"))) && key_time)
	{
		if (!this->showInventory)
			this->showInventory = true;
		else if (this->showInventory)
			this->showInventory = false;
	}	

	int counter = 0;
	for (this->cellItr = this->cellVector.begin(); this->cellItr != this->cellVector.end(); this->cellItr++)
	{
		if (this->cellVector[counter]->getGlobalBounds().contains(static_cast<float>(mouse_window.x), static_cast<float>(mouse_window.y)))
			this->cellVector[counter]->setTexture(&this->activeCellTexture);
		else if (!this->cellVector[counter]->getGlobalBounds().contains(static_cast<float>(mouse_window.x), static_cast<float>(mouse_window.y)))
			this->cellVector[counter]->setTexture(&this->inactiveCellTexture);

		counter++;		
	}
}
void Inventory::update(const sf::Event& sfml_events, const sf::Vector2i& mouse_window, const bool& key_time, const float& dt)
{
	this->updateUserInput(mouse_window, key_time, dt);
	this->updateItems();
	this->updateUseItem(sfml_events, mouse_window, key_time, dt);
}

/*Save & Load Functions*/
void Inventory::saveToFile()
{
	std::ofstream ofs("Config/inventory_details.ini");
	if (ofs.is_open())
	{
		ofs << this->inventoryDetails.totalInventory << '\n';

		ofs << this->inventoryDetails.numberOfHealthPotions << '\n';
		ofs << this->inventoryDetails.numberOfStaminaPotions << '\n';
		ofs << this->inventoryDetails.numberOfManaPotions << '\n';

		for (auto& element : this->inventoryDetails.itemDetailsVector)
		{
			ofs << static_cast<int>(element.itemType) << " " 
				<< element.itemIntRect.left << " "
				<< element.itemIntRect.top << " "
				<< element.itemIntRect.width << " "
				<< element.itemIntRect.height << " "
				<< element.hp << " " 
				<< element.stamina << " " 
				<< element.mana << '\n';
		}
	}

	ofs.close();
}
void Inventory::loadToFile()
{
	int itemType = 0;
	int intRect_Left; 
	int intRect_Top; 
	int intRect_Width; 
	int intRect_Height;
	float hp = 0.f;
	float stamina = 0.f;
	float mana = 0.f;
	ItemDetails itemDetails; 

	std::ifstream ifs("Config/inventory_details.ini");

	if (ifs.is_open())
	{
		ifs >> this->inventoryDetails.totalInventory;

		ifs >> this->inventoryDetails.numberOfHealthPotions;
		ifs >> this->inventoryDetails.numberOfStaminaPotions;
		ifs >> this->inventoryDetails.numberOfManaPotions;

		while (ifs >> itemType >> intRect_Left  >> intRect_Top >> intRect_Width >> intRect_Height >> hp >> stamina >> mana)
		{
				itemDetails.itemType = static_cast<ItemType>(itemType); 
				itemDetails.itemIntRect = sf::IntRect(intRect_Left, intRect_Top, intRect_Width, intRect_Height);
				itemDetails.hp = hp; 
				itemDetails.stamina = stamina; 
				itemDetails.mana = mana; 

				this->inventoryDetails.itemDetailsVector.push_back(itemDetails);
		}
	}
	ifs.close();

	for (auto& element : this->inventoryDetails.itemDetailsVector)
	{
		switch (element.itemType)
		{
		case ItemType::HP_Potion:
			if (!element.itemTexture.loadFromFile(this->inventoryDetails.hpTextureFilePath))
				throw("ERROR::INVENTORY::FAILED_TO_LOAD::Consumables/hp.png");
			element.itemSprite.setTexture(element.itemTexture);
			element.itemSprite.setTextureRect(element.itemIntRect);
			element.itemSprite.setOrigin(element.itemSprite.getGlobalBounds().width / 2.f, element.itemSprite.getGlobalBounds().height / 2.f);
			break;
		case ItemType::Stamina_Potion:
			if (!element.itemTexture.loadFromFile(this->inventoryDetails.staminaTextureFilePath))
				throw("ERROR::INVENTORY::FAILED_TO_LOAD::Consumables/stamina.png");
			element.itemSprite.setTexture(element.itemTexture);
			element.itemSprite.setTextureRect(element.itemIntRect);
			element.itemSprite.setOrigin(element.itemSprite.getGlobalBounds().width / 2.f, element.itemSprite.getGlobalBounds().height / 2.f);
			break;
		case ItemType::Mana_Potion:
			if (!element.itemTexture.loadFromFile(this->inventoryDetails.manaTextureFilePath))
				throw("ERROR::INVENTORY::FAILED_TO_LOAD::Consumables/mana.png");
			element.itemSprite.setTexture(element.itemTexture);
			element.itemSprite.setTextureRect(element.itemIntRect);
			element.itemSprite.setOrigin(element.itemSprite.getGlobalBounds().width / 2.f, element.itemSprite.getGlobalBounds().height / 2.f);
			break;
		default:
			std::cout << "ERROR::ITEM::void Item::setItemType(ItemType consumable)::Invalid Switch Entry!\n";
		}
	}
}

/*Render Functions*/
void Inventory::render(sf::RenderTarget& target)
{
	if (this->showInventory)
	{
		target.draw(this->background);
		target.draw(this->cellContainer);


		/*Draw Inventory Cells*/
		for (int i = 0; i < this->cellVector.size(); i++)
		target.draw(*this->cellVector[i]);

		/*Draw Items*/
		for (int i = 0; i < this->inventoryDetails.itemDetailsVector.size(); i++)
		{
			target.draw(this->inventoryDetails.itemDetailsVector[i].itemSprite);
			target.draw(this->inventoryDetails.itemDetailsVector[i].itemCountText);
		}
	}
}