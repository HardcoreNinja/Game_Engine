#include "Header.h"
#include "TileMap.h"
/*TILE=======================================================================================================================================================*/
/*Constuctor & Destructor*/
TILEMAP::Tile::Tile(
	float tile_size, 
	float pos_x, float pos_y, 
	sf::Texture& texture, 
	sf::IntRect& texture_intrect, 
	bool tile_collision, 
	unsigned short type
)
	: collision(tile_collision), tileType(type)
{
	this->shape.setSize(sf::Vector2f(tile_size, tile_size));
	this->shape.setPosition(sf::Vector2f(static_cast<float>(pos_x) * tile_size, static_cast<float>(pos_y) * tile_size));
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_intrect);
	this->shape.setOutlineColor(sf::Color::Green);
	this->shape.setOutlineThickness(1.f);
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
		<< this->tileType;

	return ss.str();
}

/*Render Functions*/
void TILEMAP::Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

/*TILE_MAP=======================================================================================================================================================*/

/*Constuctor & Destructor*/
TILEMAP::TileMap::TileMap(float tile_size, unsigned map_width, unsigned map_height, std::string tilesheet_file_path)
{
	this->tileSizeF = tile_size;
	this->tileSizeU = static_cast<unsigned>(tileSizeF);
	this->mapSizeU.x = map_width;
	this->mapSizeU.y = map_height;
	this->textureIntRect = sf::IntRect(0, 0, static_cast<int>(tileSizeU), static_cast<int>(tileSizeU));
	this->textureFilePath = tilesheet_file_path;
	this->tileLayers = 1;

	if (!this->texture.loadFromFile(tilesheet_file_path))
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

/*Add & Remove Tile Functions*/
void TILEMAP::TileMap::addTile(
	const unsigned pos_x, const unsigned pos_y, 
	const unsigned tile, 
	const bool& tile_collision, 
	const unsigned short& tile_type)
{
	if (pos_x < this->mapSizeU.x && pos_x >= 0 &&
		pos_y < this->mapSizeU.y && pos_y >= 0 &&
		tile < this->tileLayers && tile >=0)
	{
		if (this->tileMap[pos_x][pos_y][tile] == NULL)
		{
			this->tileMap[pos_x][pos_y][tile] = std::make_unique<TILEMAP::Tile>(
				this->tileSizeF,
				pos_x, pos_y,
				this->texture,
				this->textureIntRect,
				tile_collision,
				tile_type
				);
		}
	}
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

