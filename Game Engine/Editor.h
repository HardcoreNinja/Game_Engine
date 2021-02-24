#ifndef EDITOR_H
#define EDITOR_H
#include "State.h"
#include "TileMap.h"

/*Class Forward Declarations*/
class Tile;
class TileMap;
class sf::RenderTarget;

class Editor :
    public State
{
private:
    /*Tile Map*/
    std::unique_ptr<TILEMAP::TileMap> tileMap;

    /*Tile Map Flags*/
    bool collision;
    unsigned short tileType;

    /*Texture Selector Variables*/
    std::unique_ptr<TILEMAP::TextureSelector> textureSelector;
    sf::RectangleShape selectorRect;

    /*Texture Selector Side Bar*/
    sf::RectangleShape sideBar;

    /*Initializers*/
    void initVariables();
    void initKeybinds();
    void initFonts();
    void initTileMap();
    void initTextureSelector();
    void initPauseMenu();

public:
    /*Constuctor & Destructor*/
    Editor(GameInfo* game_info);
    virtual ~Editor();

    /*Update Functions*/
    void updateCursorText();
    void updateSelectorRect();
    void updatePauseMenuButtons();
    void updateTextureSelector(const float& dt);
    void updateTileMap();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Render Functions*/
    void renderCursorText(sf::RenderTarget& target);
    void renderSelectorRect(sf::RenderTarget& target);
    void renderTextureSelector(sf::RenderTarget& target);
    void renderPauseMenu(sf::RenderTarget& target);
    void renderTiles(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
