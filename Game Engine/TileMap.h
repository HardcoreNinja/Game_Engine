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

	/*Tile Types*/
	enum TileType 
	{
		Default = 0, 
		Chest, 
		Door, 
		Wall, 
		Enemy_Spawn_Point, 
		Path_Finder_Markings, 
		Invisible_Wall
	};

	class Tile
	{
	private:
		sf::RectangleShape shape;
		unsigned short shapeRotation;
		bool collision;
		std::string doorName;
		unsigned short tileType;
		float tileSize;

	public:
		/*Constuctor & Destructor*/
		Tile(
			float tile_size, 
			float pos_x, float pos_y, 
			const sf::Texture& texture, 
			const sf::IntRect& texture_intrect, 
			bool tile_collision,
			std::string door_name,
			unsigned short type = 0,
			unsigned short shape_rotation = 0
		);
		virtual ~Tile();

		/*Getters*/
		const std::string_view getDoorName() const;
		const sf::Vector2f& getPosition() const;
		const std::string getAsString() const;
		sf::RectangleShape& getShape();
		bool getCollision() const;
		unsigned short getTileType() const;
		float getTileSize();


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
		std::tuple<bool, unsigned short, std::string_view> getCollision(sf::RectangleShape player_rect);
		std::vector<sf::Vector2f> getEnemySpawnPositions();
		std::vector<sf::Vector2f> getPathFinderMarkings();

		/*Setters*/
		void setTextureIntRect(sf::IntRect texture_int_rect);
		void setTileSizeF(float tile_size);

		/*Double & Halve Tile Size Functions*/
		void doubleTileSize();
		void halveTileSize();

		/*Add & Remove Tile Functions*/
		void addTile(
		const unsigned pos_x, const unsigned pos_y,
			const unsigned tile_layer,
			const bool& collision,
			const std::string& door_name,
			const unsigned short& tile_type,
			unsigned short& rotation_degrees
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
		void render(sf::RenderTarget& target, const sf::View& view);
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
		float keyTime;
		float maxKeyTime;

		/*Scroll Incrementers*/
		int horizontalScrollIncrementer;
		int verticalScrollIncrementer;

	public:
		/*Constuctor & Destructor*/
		TextureSelector(
			std::string texture_selector_data_file_path,
			float tile_size,
			float pos_x, float pos_y,
			float bounds_width, float bounds_height,
			const sf::Texture* texture_Sheet,
			sf::Font& hide_button_font,
			float key_time, float max_key_time
			);
		virtual ~TextureSelector();

		/*Getters*/
		const sf::IntRect& getTextureIntRect();
		const bool& getIsActive();
		bool getKeyTime();

		/*Update Functions*/
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2i& mouse_position_window, const float& dt);

		/*Scroll Functions*/
		void scrollUp();
		void scrollDown();
		void scrollLeft();
		void scrollRight();

		/*Double & Halve Texture Selector Functions*/
		void doubleSelectorSize();
		void halveSelectorSize();

		/*Save & Load Functions*/
		void saveToFile(std::string file_path);
		void loadFromFile(std::string file_path);

		/*Render Functions*/
		void render(sf::RenderTarget& target, const sf::View& view);
	};
}
#endif
