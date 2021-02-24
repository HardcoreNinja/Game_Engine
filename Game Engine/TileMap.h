#ifndef TILEMAP_H
#define TILEMAP_H
#include "GUI.h"

namespace TILEMAP 
{
	/*Class Forward Declarations*/
	class Button;
	class sf::Texture;
	class sf::RectangleShape;
	class sf::RenderTarget;

	/*Tile*/
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
			const sf::Texture& texture, 
			const sf::IntRect& texture_intrect, 
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

	/*Tile Map*/
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
		TileMap(
			float tile_size,
			unsigned map_width, unsigned map_height,
			int texture_width, int texture_height,
			std::string tile_sheet_file_path
		);
		virtual ~TileMap();

		/*Getters*/
		const sf::Texture* getTexture();
		const sf::IntRect& getTextureIntRect();

		/*Setters*/
		void setTextureIntRect(sf::IntRect texture_int_rect);

		/*Add & Remove Tile Functions*/
		void addTile(
		const unsigned pos_x, const unsigned pos_y,
			const unsigned tile_layer,
			const bool& collision, 
			const unsigned short& tile_type
		);

		void removeTile(
			const unsigned pos_x, const unsigned pos_y,
			const unsigned tile_layer
		);

		/*Clear Memory Functions*/
		void clearMemory();

		/*Save & Load Functions*/
		void saveToFile(std::string file_path);
		void loadFromFile(std::string file_path, std::string texture_sheet_file_path);

		/*Render Functions*/
		void render(sf::RenderTarget& target);
	};

	/*Texture Selector*/
	class TextureSelector
	{
	private:
		/*Texture Selector Variables*/
		sf::RectangleShape bounds;
		sf::Sprite spriteSheet;
		sf::IntRect textureIntRect;
		sf::Vector2u mousePositionTile;
		sf::RectangleShape selector;

		/*Tile Variables*/
		float tileSize;

		/*Hide Button*/
		std::unique_ptr<GUI::Button> hideButton;

		/*Flags*/
		bool isHidden;
		bool isActive;

		/*Key Time Variables*/
		int keyTime;
		int maxKeyTime;

	public:
		/*Constuctor & Destructor*/
		TextureSelector(
			float pos_x, float pos_y,
			float bounds_width, float bounds_height,
			float tile_size,
			const sf::Texture* texture_Sheet,
			sf::Font& hide_button_font,
			int key_time, int max_key_time
			);
		virtual ~TextureSelector();

		/*Getters*/
		const sf::IntRect& getTextureIntRect();
		const bool& getIsActive();
		bool getKeyTime();

		/*Update Functions*/
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2i& mouse_position_window, const float& dt);

		/*Render Functions*/
		void render(sf::RenderTarget& target, const sf::View& view);

	};
}
#endif
