#include "Header.h"
#include "TileMap.h"
/*TILE=======================================================================================================================================================*/
/*Constructor & Destructor*/
TILEMAP::Tile::Tile(
	float tile_size, 
	float pos_x, float pos_y, 
	const sf::Texture& texture, 
	const sf::IntRect& texture_intrect, 
	bool tile_collision, 
	unsigned short type,
	unsigned short shape_rotation
)
	: collision(tile_collision), tileType(type), shapeRotation(shape_rotation), tileSize(tile_size)
{
	this->shape.setSize(sf::Vector2f(tile_size, tile_size));
	this->shape.setPosition(sf::Vector2f(static_cast<float>(pos_x) * tile_size, static_cast<float>(pos_y) * tile_size));
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_intrect);
	this->shape.setOutlineColor(sf::Color::Transparent);
	this->shape.setOutlineThickness(1.f);
	this->shape.setRotation(this->shapeRotation);

	/*Color Codes for Collision & Tile Types
	if (this->collision)
	{
		this->shape.setFillColor(sf::Color::Red);
	}

	switch (this->tileType)
	{
	case TILEMAP::TileType::Default:
		this->shape.setOutlineColor(sf::Color::Transparent);
		break;
	case TILEMAP::TileType::Chest:
		this->shape.setOutlineColor(sf::Color::Yellow);
		break;
	case TILEMAP::TileType::Door:
		this->shape.setOutlineColor(sf::Color::Blue);
		break;
	case TILEMAP::TileType::Wall:
		this->shape.setOutlineColor(sf::Color::Magenta);
		break;
	}*/
}
TILEMAP::Tile::~Tile()
{
}

/*Getters*/
const sf::Vector2f& TILEMAP::Tile::getPosition() const
{
	return this->shape.getPosition();
}
const std::string TILEMAP::Tile::getAsString() const
{
	std::stringstream ss; 

	ss << this->shape.getTextureRect().left << " "
		<< this->shape.getTextureRect().top << " "
		<< this->collision << " "
		<< this->tileType << " "
		<< this->shapeRotation;

	return ss.str();
}
sf::RectangleShape& TILEMAP::Tile::getShape()
{
	return this->shape;
}
bool TILEMAP::Tile::getCollision() const
{
	return this->collision;
}
unsigned short TILEMAP::Tile::getTileType() const
{
	return this->tileType;
}
float TILEMAP::Tile::getTileSize()
{
	return this->tileSize;
}

/*Render Functions*/
void TILEMAP::Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

/*TILE_MAP=======================================================================================================================================================*/
/*Constuctor & Destructor*/
TILEMAP::TileMap::TileMap(
	float tile_size, 
	unsigned map_width, unsigned map_height, 
	int texture_width, int texture_height, 
	std::string tile_sheet_file_path
)
{
	this->tileSizeF = tile_size;
	this->tileSizeU = static_cast<unsigned>(tileSizeF);
	this->mapSizeU.x = map_width;
	this->mapSizeU.y = map_height;
	this->textureIntRect = sf::IntRect(0, 0, texture_width, texture_height);
	this->textureFilePath = tile_sheet_file_path;
	this->tileLayers = 4;

	if (!this->texture.loadFromFile(tile_sheet_file_path))
	{
		throw("ERROR::TILE_MAP::FAILED_TO_LOAD::this->texture");
	}

	this->tileMap.resize(this->tileLayers);
	for (size_t tile_layers = 0; tile_layers < this->tileLayers; tile_layers++)
	{
		this->tileMap[tile_layers].resize(this->mapSizeU.x);
		for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
		{
			this->tileMap[tile_layers][pos_x].resize(this->mapSizeU.y);
		}
	}
}
TILEMAP::TileMap::~TileMap()
{
}

/*Getters*/
const sf::Texture* TILEMAP::TileMap::getTexture()
{
	return &this->texture;
}
const sf::IntRect& TILEMAP::TileMap::getTextureIntRect()
{
	return this->textureIntRect;
}
std::tuple<bool, unsigned short> TILEMAP::TileMap::getCollision(sf::RectangleShape player_rect)
{
	for(int tile_layer = 0; tile_layer != this->tileMap.size(); tile_layer++)
		for(int pos_x = 0; pos_x != this->tileMap[tile_layer].size(); pos_x++)
			for (int pos_y = 0; pos_y != this->tileMap[tile_layer][pos_x].size(); pos_y++)
			{
				if (this->tileMap[tile_layer][pos_x][pos_y] != NULL)
				{
					if (tile_layer > 0)
					{
						if (this->tileMap[tile_layer][pos_x][pos_y]->getShape().getGlobalBounds().intersects(player_rect.getGlobalBounds()))
						{
							//std::cout << "Collision Enabled: " << this->tileMap[x][y][tileLayer]->getCollision() << " " << "Tile Type: " << this->tileMap[x][y][tileLayer]->getTileType() << '\n';
							return std::make_tuple(this->tileMap[tile_layer][pos_x][pos_y]->getCollision(), this->tileMap[tile_layer][pos_x][pos_y]->getTileType());
						}
					}
				}
			}
}
std::vector<sf::Vector2f> TILEMAP::TileMap::getEnemySpawnPositions()
{
	std::vector<sf::Vector2f> enemySpawnPositions; 
	for (int tile_layer = 0; tile_layer != this->tileMap.size(); tile_layer++)
		for (int pos_x = 0; pos_x != this->tileMap[tile_layer].size(); pos_x++)
			for (int pos_y = 0; pos_y != this->tileMap[tile_layer][pos_x].size(); pos_y++)
			{
				if (this->tileMap[tile_layer][pos_x][pos_y] != NULL)
				{
					if (tile_layer == 0)
					{
						if (this->tileMap[tile_layer][pos_x][pos_y]->getTileType() == TILEMAP::TileType::Default)
						{
							std::cout << "Enemy Spawn Positions: " << this->tileMap[tile_layer][pos_x][pos_y]->getPosition().x << " x " << this->tileMap[tile_layer][pos_x][pos_y]->getPosition().y << '\n';
							enemySpawnPositions.push_back(this->tileMap[tile_layer][pos_x][pos_y]->getPosition());
						}

					}
				}
			}

	return enemySpawnPositions;
}

/*Setters*/
void TILEMAP::TileMap::setTextureIntRect(sf::IntRect texture_int_rect)
{
	this->textureIntRect = texture_int_rect;
}
void TILEMAP::TileMap::setTileSizeF(float tile_size)
{
	this->tileSizeF = tile_size;
}

/*Double & Halve Tile Size Functions*/
void TILEMAP::TileMap::doubleTileSize()
{
	this->tileSizeF = this->tileSizeF * 2.f;
	this->tileSizeU = this->tileSizeU * 2;
}
void TILEMAP::TileMap::halveTileSize()
{
	this->tileSizeF = this->tileSizeF / 2.f;
	this->tileSizeU = this->tileSizeU / 2;
}

/*Add & Remove Tile Functions*/
void TILEMAP::TileMap::addTile(
	const unsigned pos_x, const unsigned pos_y, 
	const unsigned tile_layer,
	const bool& tile_collision, 
	const unsigned short& tile_type,
	unsigned short& rotation_degrees)
{
	if (pos_x < this->mapSizeU.x && pos_x >= 0 &&
		pos_y < this->mapSizeU.y && pos_y >= 0 &&
		tile_layer < this->tileLayers && tile_layer >=0)
	{
		if (this->tileMap[tile_layer][pos_x][pos_y] == NULL)
		{
			this->tileMap[tile_layer][pos_x][pos_y] = std::make_unique<TILEMAP::Tile>(
				this->tileSizeF,
				pos_x, pos_y,
				this->texture,
				sf::IntRect(this->textureIntRect.left, this->textureIntRect.top, this->tileSizeF, this->tileSizeF),
				tile_collision,
				tile_type,
				rotation_degrees
				);
		}
	}
}
void TILEMAP::TileMap::removeTile(const unsigned pos_x, const unsigned pos_y, const unsigned tile_layer)
{
	if (pos_x < this->mapSizeU.x && pos_x >= 0 &&
		pos_y < this->mapSizeU.y && pos_y >= 0 &&
		tile_layer < this->tileLayers && tile_layer >= 0)
	{
		if (this->tileMap[tile_layer][pos_x][pos_y] != NULL)
		{
			this->tileMap[tile_layer][pos_x][pos_y].reset();
		}
	}
}

/*Clear Memory Functions*/
void TILEMAP::TileMap::clearMemory()
{
	for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
	{
		for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
		{
			for (size_t pos_y = 0; pos_y < this->mapSizeU.y; pos_y++)
			{
				this->tileMap[tile_layer][pos_x][pos_y].reset();
			}
			this->tileMap[tile_layer][pos_x].clear();
		}
		this->tileMap[tile_layer].clear();
	}
	this->tileMap.clear();
}

/*Save & Load Functions*/
void TILEMAP::TileMap::saveToFile(std::string file_path)
{
	std::ofstream ofs;
	ofs.open(file_path);

	if (ofs.is_open())
	{
		ofs << this->mapSizeU.x << " " << this->mapSizeU.y << '\n';
		ofs << this->tileSizeU << '\n';
		ofs << this->tileLayers << '\n';
		ofs << this->textureFilePath << '\n';

		this->tileMap.push_back(std::vector<std::vector<std::unique_ptr<TILEMAP::Tile>>>());

		for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
		{
			for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
			{
				for (size_t pos_y = 0; pos_y < this->mapSizeU.y; pos_y++)
				{
					if (this->tileMap[tile_layer][pos_x][pos_y])
						ofs << tile_layer << " " 
						<< pos_x << " " << pos_y << " " 
						<< this->tileMap[tile_layer][pos_x][pos_y]->getTileSize() << " "
						<< this->tileMap[tile_layer][pos_x][pos_y]->getAsString() << " ";
				}
			}
		}
	}
	else
		throw("ERROR::TILEMAP::TILE_MAP::FAILED_TO_SAVE::ofs");

	ofs.close();
	std::cout << "Saved Tile Map\n";
}
void TILEMAP::TileMap::loadFromFile(std::string tile_map_file_path, std::string texture_sheet_file_path)
{
	std::ifstream ifs;
	ifs.open(tile_map_file_path);

	if (ifs.is_open())
	{
		sf::Vector2u mapSizeU;
		unsigned mapTileSize = 0;
		float tileSize = 0;
		unsigned tileLayers = 0;
		std::string textureFilePath = "";
		unsigned tile_layer = 0;
		unsigned pos_x = 0;
		unsigned pos_y = 0;
		unsigned tile = 0;
		unsigned intRectLeft = 0;
		unsigned intRectTop = 0;
		bool collision = false;
		short type = 0;
		unsigned short shapeRotation;

		ifs >> mapSizeU.x >> mapSizeU.y;
		ifs >> mapTileSize;
		ifs >> tileLayers;
		ifs >> textureFilePath;

		this->mapSizeU = sf::Vector2u(mapSizeU.x, mapSizeU.y);
		this->tileSizeU = mapTileSize;
		//this->tileSizeF = static_cast<float>(mapTileSize);
		this->tileLayers = tileLayers;
		this->textureFilePath = textureFilePath;

		this->clearMemory();

		
		this->tileMap.resize(this->tileLayers);
		for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
		{
			this->tileMap[tile_layer].resize(this->mapSizeU.x);
			for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
			{
				this->tileMap[tile_layer][pos_x].resize(this->mapSizeU.y);
			}
		}

		if(!this->texture.loadFromFile(texture_sheet_file_path))
			throw("ERROR::TILEMAP::TILE_MAP::FAILED_TO_SAVE::texture_sheet_file_path");

		while (ifs >> tile_layer >> pos_x >> pos_y >> tileSize >> intRectLeft >> intRectTop >> collision >> type >> shapeRotation)
		{
			this->tileMap[tile_layer][pos_x][pos_y] = std::make_unique <TILEMAP::Tile>(
				tileSize,
				pos_x, pos_y,
				this->texture,
				sf::IntRect(intRectLeft, intRectTop, tileSize, tileSize),
				collision,
				type,
				shapeRotation
				);
		}
	}
	else
		throw("ERROR::TILEMAP::TILE_MAP::FAILED_TO_LOAD::tile_map_file_path");

	ifs.close();
	std::cout << "Loaded Tile Map\n";
}

/*Render Functions*/
void TILEMAP::TileMap::render(sf::RenderTarget& target, const sf::View& view)
{
	float viewSizeOffset = 256.f;

	sf::Vector2f viewSize = view.getSize();
	viewSize.x = viewSize.x + viewSizeOffset;
	viewSize.y = viewSize.y + viewSizeOffset;

	sf::FloatRect viewPort{
		view.getCenter().x - viewSize.x / 2.f,
		view.getCenter().y - viewSize.y / 2.f,
		viewSize.x, viewSize.y
	};

	sf::FloatRect tileRect{
		0,0,
		this->tileSizeF, this->tileSizeF
	};

	for (auto& tile_layer : this->tileMap)
	{
		for (auto& pos_x : tile_layer)
		{
			for (auto& pos_y : pos_x)
			{
				if (pos_y != NULL)
				{
					tileRect.left = pos_y->getPosition().x;
					tileRect.top = pos_y->getPosition().y;
					if(tileRect.intersects(viewPort))
						pos_y->render(target);
				}
			}
		}
	}
}

/*TEXTURE_SELECTOR=======================================================================================================================================================*/
/*Constructor & Destructor*/
TILEMAP::TextureSelector::TextureSelector(
	std::string texture_selector_data_file_path,
	float tile_size,
	float pos_x, float pos_y,
	float bounds_width, float bounds_height,
	const sf::Texture* texture_Sheet,
	sf::Font& hide_button_font,
	int key_time, int max_key_time
) : keyTime(key_time), maxKeyTime(max_key_time)
{
	/*Load Texture Selector Data File*/
	this->loadFromFile(texture_selector_data_file_path);

	/*Tile Size*/
	this->tileSize = tile_size;

	/*X Position Offset*/
	float xOffset = 40.f;
	float hideButtonOffset = 20.f;
	
	/*Bounds*/
	this->bounds.setPosition(sf::Vector2f(pos_x + xOffset, pos_y));
	this->bounds.setSize(sf::Vector2f(bounds_width, bounds_height));
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineColor(sf::Color::White);
	this->bounds.setOutlineThickness(1.f);

	/*Sprite Sheet*/
	this->spriteSheet.setPosition(sf::Vector2f(this->bounds.getPosition().x, this->bounds.getPosition().y));
	this->spriteSheet.setTexture(*texture_Sheet);
	this->spriteSheet.setTextureRect(sf::IntRect(
		(static_cast<int>(this->tileSize) * this->horizontalScrollIncrementer), (static_cast<int>(this->tileSize) * this->verticalScrollIncrementer),
		static_cast<int>(bounds_width), static_cast<int>(bounds_height)
	)
	);

	this->textureIntRect.width = static_cast<int>(tile_size);
	this->textureIntRect.height = static_cast<int>(tile_size);

	/*Selector*/
	this->selector.setPosition(sf::Vector2f(pos_x + xOffset, pos_y));
	this->selector.setSize(sf::Vector2f(tile_size, tile_size));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineColor(sf::Color::Red);
	this->selector.setOutlineThickness(1.f);

	/*Hide Buttons*/
	this->hideButton = std::make_unique<GUI::Button>(
		pos_x + hideButtonOffset, pos_y + hideButtonOffset,                              //Button Rect Position
		40.f, 40.f,                                                                      //Button Rect Size
		&hide_button_font, "TS", 16,                                                     //Button Font, Text, and Character Size
		sf::Color::White, sf::Color::White, sf::Color::White,                            //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), //Button Rect Fill Color
		sf::Color::White, sf::Color::White, sf::Color::White                             //Button Rect Outline Color
		);

	/*Flags*/
	this->isHidden = true;
	this->isActive = false;
}
TILEMAP::TextureSelector::~TextureSelector()
{
}

/*Getters*/
const sf::IntRect& TILEMAP::TextureSelector::getTextureIntRect()
{
	return this->textureIntRect;
}
const bool& TILEMAP::TextureSelector::getIsActive()
{
	return this->isActive;
}
bool TILEMAP::TextureSelector::getKeyTime()
{
	if (this->keyTime >= this->maxKeyTime)
	{
		this->keyTime = 0;

		return true;
	}
	else
		return false;
}

/*Update Functions*/
void TILEMAP::TextureSelector::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->maxKeyTime)
		this->keyTime += static_cast<int>(2.f * dt * (1.f / dt));
}
void TILEMAP::TextureSelector::update(const sf::Vector2i& mouse_position_window, const float& dt)
{
	/*Key Time*/
	this->updateKeyTime(dt);

	/*Hide Button*/
	this->hideButton->update(static_cast<sf::Vector2f>(mouse_position_window));
	if (this->hideButton->isPressed() && this->getKeyTime())
	{
		if (this->isHidden)
			this->isHidden = false;
		else
			this->isHidden = true;
	}

	/*Check if mouse is within bounds if it's not hidden*/
	if (!this->isHidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position_window)))
			this->isActive = true;
		else
			this->isActive = false;

		if (this->isActive)
		{
			this->mousePositionTile.x = (mouse_position_window.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->tileSize);
			this->mousePositionTile.y = (mouse_position_window.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->tileSize);

			this->selector.setPosition(sf::Vector2f(
				this->bounds.getPosition().x + this->mousePositionTile.x * this->tileSize,
				this->bounds.getPosition().y + this->mousePositionTile.y * this->tileSize
			)
			);

			this->textureIntRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x) + (static_cast<int>(this->tileSize) * this->horizontalScrollIncrementer);
			this->textureIntRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y) + (static_cast<int>(this->tileSize) * this->verticalScrollIncrementer);
		}
	}
}

/*Scroll Functions*/
void TILEMAP::TextureSelector::scrollUp()
{
	if (this->verticalScrollIncrementer != 0)
		this->verticalScrollIncrementer -= 1;

	this->spriteSheet.setTextureRect(sf::IntRect(
		(static_cast<int>(this->tileSize) * this->horizontalScrollIncrementer), (static_cast<int>(this->tileSize) * this->verticalScrollIncrementer),
		static_cast<int>(this->bounds.getSize().x), static_cast<int>(this->bounds.getSize().y)
	)
	);
}
void TILEMAP::TextureSelector::scrollDown()
{
	if(this->verticalScrollIncrementer != 117)
	this->verticalScrollIncrementer += 1;

	this->spriteSheet.setTextureRect(sf::IntRect(
		(static_cast<int>(this->tileSize) * this->horizontalScrollIncrementer), (static_cast<int>(this->tileSize) * this->verticalScrollIncrementer),
		static_cast<int>(this->bounds.getSize().x), static_cast<int>(this->bounds.getSize().y)
	)
	);
}
void TILEMAP::TextureSelector::scrollLeft()
{
	if (this->horizontalScrollIncrementer != 0)
		this->horizontalScrollIncrementer -= 1;

	this->spriteSheet.setTextureRect(sf::IntRect(
		(static_cast<int>(this->tileSize) * this->horizontalScrollIncrementer), (static_cast<int>(this->tileSize) * this->verticalScrollIncrementer),
		static_cast<int>(this->bounds.getSize().x), static_cast<int>(this->bounds.getSize().y)
	)
	);
}
void TILEMAP::TextureSelector::scrollRight()
{
	if (this->horizontalScrollIncrementer != 64)
		this->horizontalScrollIncrementer += 1;

	this->spriteSheet.setTextureRect(sf::IntRect(
		(static_cast<int>(this->tileSize) * this->horizontalScrollIncrementer), (static_cast<int>(this->tileSize) * this->verticalScrollIncrementer),
		static_cast<int>(this->bounds.getSize().x), static_cast<int>(this->bounds.getSize().y)
	)
	);
}

/*Double & Halve Texture Selector Functions*/
void TILEMAP::TextureSelector::doubleSelectorSize()
{
	this->selector.setSize(sf::Vector2f(this->selector.getSize().x * 2.f, this->selector.getSize().y * 2.f));
	this->textureIntRect.width = this->textureIntRect.width * 2;
	this->textureIntRect.height = this->textureIntRect.height * 2;
}
void TILEMAP::TextureSelector::halveSelectorSize()
{
	this->selector.setSize(sf::Vector2f(this->selector.getSize().x / 2.f, this->selector.getSize().y / 2.f));
	this->textureIntRect.width = this->textureIntRect.width / 2;
	this->textureIntRect.height = this->textureIntRect.height / 2;
}

/*Save & Load Functions*/
void TILEMAP::TextureSelector::saveToFile(std::string file_path)
{
	std::ofstream ofs;
	ofs.open(file_path);

	if (ofs.is_open())
	{
		ofs << this->horizontalScrollIncrementer << " " << this->verticalScrollIncrementer << '\n';
	}
	else
		throw("ERROR::TILEMAP::TEXTURE_SELECTOR::FAILED_TO_SAVE::ofs");

	ofs.close();
	std::cout << "Saved Texture Selector Data File \n";
}
void TILEMAP::TextureSelector::loadFromFile(std::string file_path)
{
	std::ifstream ifs;
	ifs.open(file_path);

	if (ifs.is_open())
	{
		int hScrollIncrementer;
		int vScrollIncrementer;

		ifs >> hScrollIncrementer >> vScrollIncrementer;

		std::cout << "Horizontal: " << hScrollIncrementer << " " << "Vertical: " << vScrollIncrementer << '\n';

		this->horizontalScrollIncrementer = hScrollIncrementer;
		this->verticalScrollIncrementer = vScrollIncrementer;
	}
	else
		throw("ERROR::TILEMAP::TEXTURE_SELECTOR::FAILED_TO_LOAD::ifs");

	ifs.close();
	std::cout << "Loaded Texture Selector Data File \n";
}

/*Render Functions*/
void TILEMAP::TextureSelector::render(sf::RenderTarget& target, const sf::View& view)
{
	/*View*/
	target.setView(view);

	this->hideButton->render(target);
	
	if (!isHidden)
	{
		target.draw(this->bounds);
		target.draw(this->spriteSheet);

		if(this->isActive)
		target.draw(this->selector);
	}
}
