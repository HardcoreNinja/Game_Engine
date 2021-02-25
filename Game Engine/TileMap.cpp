#include "Header.h"
#include "TileMap.h"
/*TILE=======================================================================================================================================================*/
/*Constuctor & Destructor*/
TILEMAP::Tile::Tile(
	float tile_size, 
	float pos_x, float pos_y, 
	const sf::Texture& texture, 
	const sf::IntRect& texture_intrect, 
	bool tile_collision, 
	unsigned short type,
	unsigned short shape_rotation
)
	: collision(tile_collision), tileType(type), shapeRotation(shape_rotation)
{
	this->shape.setSize(sf::Vector2f(tile_size, tile_size));
	this->shape.setPosition(sf::Vector2f(static_cast<float>(pos_x) * tile_size, static_cast<float>(pos_y) * tile_size));
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_intrect);
	this->shape.setOutlineColor(sf::Color::Transparent);
	this->shape.setOutlineThickness(1.f);
	this->shape.setRotation(this->shapeRotation);
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
	this->tileLayers = 3;

	if (!this->texture.loadFromFile(tile_sheet_file_path))
	{
		throw("ERROR::TILE_MAP::FAILED_TO_LOAD::this->texture");
	}

	this->tileMap.resize(this->mapSizeU.x);
	for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
	{
		this->tileMap[pos_x].resize(this->mapSizeU.y);
		for (size_t pos_y = 0; pos_y < this->mapSizeU.y; pos_y++)
		{
			this->tileMap[pos_x][pos_y].resize(this->tileLayers);
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

/*Setters*/
void TILEMAP::TileMap::setTextureIntRect(sf::IntRect texture_int_rect)
{
	this->textureIntRect = texture_int_rect;
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
		if (this->tileMap[pos_x][pos_y][tile_layer] == NULL)
		{
			this->tileMap[pos_x][pos_y][tile_layer] = std::make_unique<TILEMAP::Tile>(
				this->tileSizeF,
				pos_x, pos_y,
				this->texture,
				this->textureIntRect,
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
		if (this->tileMap[pos_x][pos_y][tile_layer] != NULL)
		{
			this->tileMap[pos_x][pos_y][tile_layer].reset();
		}
	}
}

/*Clear Memory Functions*/
void TILEMAP::TileMap::clearMemory()
{
	for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
	{
		for (size_t pos_y = 0; pos_y < this->mapSizeU.y; pos_y++)
		{
			for (size_t tile = 0; tile < this->tileLayers; tile++)
			{
				this->tileMap[pos_x][pos_y][tile].reset();
			}
			this->tileMap[pos_x][pos_y].clear();
		}
		this->tileMap[pos_x].clear();
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

		for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
		{
			for (size_t pos_y = 0; pos_y < this->mapSizeU.y; pos_y++)
			{
				for (size_t tile = 0; tile < this->tileLayers; tile++)
				{
					if (this->tileMap[pos_x][pos_y][tile])
						ofs << pos_x << " " << pos_y << " " << tile << " " << this->tileMap[pos_x][pos_y][tile]->getAsString() << " ";
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
		unsigned tileSize = 0;
		unsigned tileLayers = 0;
		std::string textureFilePath = "";
		unsigned pos_x = 0;
		unsigned pos_y = 0;
		unsigned tile = 0;
		unsigned intRectLeft = 0;
		unsigned intRectTop = 0;
		bool collision = false;
		short type = 0;
		unsigned short shapeRotation;

		ifs >> mapSizeU.x >> mapSizeU.y;
		ifs >> tileSize;
		ifs >> tileLayers;
		ifs >> textureFilePath;

		this->mapSizeU = sf::Vector2u(mapSizeU.x, mapSizeU.y);
		this->tileSizeU = tileSize;
		this->tileSizeF = static_cast<float>(tileSize);
		this->tileLayers = tileLayers;
		this->textureFilePath = textureFilePath;

		this->clearMemory();

		
		this->tileMap.resize(this->mapSizeU.x);
		for (size_t pos_x = 0; pos_x < this->mapSizeU.x; pos_x++)
		{
			this->tileMap[pos_x].resize(this->mapSizeU.y);
			for (size_t pos_y = 0; pos_y < this->mapSizeU.y; pos_y++)
			{
				this->tileMap[pos_x][pos_y].resize(this->tileLayers);
			}
		}

		if(!this->texture.loadFromFile(texture_sheet_file_path))
			throw("ERROR::TILEMAP::TILE_MAP::FAILED_TO_SAVE::texture_sheet_file_path");

		while (ifs >> pos_x >> pos_y >> tile >> intRectLeft >> intRectTop >> collision >> type >> shapeRotation)
		{
			this->tileMap[pos_x][pos_y][tile] = std::make_unique <TILEMAP::Tile>(
				this->tileSizeF,
				pos_x, pos_y,
				this->texture,
				sf::IntRect(intRectLeft, intRectTop, this->tileSizeU, this->tileSizeU),
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
void TILEMAP::TileMap::render(sf::RenderTarget& target)
{
	for (auto& pos_x : this->tileMap)
	{
		for (auto& pos_y : pos_x)
		{
			for (auto& tile : pos_y)
			{
				if (tile != NULL)
					tile->render(target);
			}
		}
	}
}

/*TEXTURE_SELECTOR=======================================================================================================================================================*/
/*Constuctor & Destructor*/
TILEMAP::TextureSelector::TextureSelector(
	float pos_x, float pos_y,
	float bounds_width, float bounds_height,
	float tile_size,
	const sf::Texture* texture_Sheet,
	sf::Font& hide_button_font,
	int key_time, int max_key_time
) : keyTime(key_time), maxKeyTime(max_key_time)
{
	/*X Position Offset*/
	float xOffset = 48.f;
	float hideButtonOffset = 24.f;
	

	/*Bounds*/
	this->bounds.setPosition(sf::Vector2f(pos_x + xOffset, pos_y));
	this->bounds.setSize(sf::Vector2f(bounds_width, bounds_height));
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineColor(sf::Color::White);
	this->bounds.setOutlineThickness(1.f);

	/*Sprite Sheet*/
	this->spriteSheet.setPosition(sf::Vector2f(this->bounds.getPosition().x, this->bounds.getPosition().y));
	this->spriteSheet.setTexture(*texture_Sheet);
	this->spriteSheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(bounds_width), static_cast<int>(bounds_height)));

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
		48.f, 48.f,                                                                      //Button Rect Size
		&hide_button_font, "TS", 16,                                                     //Button Font, Text, and Character Size
		sf::Color::White, sf::Color::White, sf::Color::White,                            //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), //Button Rect Fill Color
		sf::Color::White, sf::Color::White, sf::Color::White                             //Button Rect Outline Color
		);

	/*Tile Size*/
	this->tileSize = tile_size;

	/*Flags*/
	this->isHidden = false;
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
	this->hideButton->update(static_cast<sf::Vector2f>( mouse_position_window));
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

			this->textureIntRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureIntRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
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
