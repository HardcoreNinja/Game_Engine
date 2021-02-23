#ifndef TILEMAP_H
#define TILEMAP_H

namespace TILEMAP 
{
	/*Class Forward Declarations*/
	class sf::Texture;
	class sf::RenderTarget;

	enum TileType {Default = 0, Grass, Water, Road, Building};
	class Tile
	{
	private:
		sf::RectangleShape shape;
		bool collision;
		unsigned short tileType;

	public:
		/*Constuctor & Destructor*/
		Tile(
			float tile_size, 
			float pos_x, float pos_y, 
			sf::Texture& texture, 
			sf::IntRect& texture_intrect, 
			bool tile_collision, 
			unsigned short type = 0
		);
		virtual ~Tile();

		/*Getters*/
		const sf::Vector2f& getPosition() const;
		const std::string getAsString() const;

		/*Render Functions*/
		void render(sf::RenderTarget& target);
	};

	class TileMap
	{
	private:
		float tileSizeF;
		unsigned tileSizeU;
		unsigned tileLayers;
		sf::Vector2u mapSizeU;
		std::vector<std::vector<std::vector<std::unique_ptr<TILEMAP::Tile>>>> tileMap;
		sf::IntRect textureIntRect;
		std::string textureFilePath;
		sf::Texture texture;
		
	public:
		/*Constuctor & Destructor*/
		TileMap(float tile_size, unsigned map_width, unsigned map_height, std::string tilesheet_file_path);
		virtual ~TileMap();

		/*Add & Remove Tile Functions*/
		void addTile(
		const unsigned pos_x, const unsigned pos_y,
			const unsigned tile_layer,
			const bool& collision, 
			const unsigned short& tile_type
		);

		/*Render Functions*/
		void render(sf::RenderTarget& target);
	};
}
#endif
