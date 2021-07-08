#ifndef MAINMENU_H
#define MAINMENU_H
#include "State.h"
#include "Settings.h"
#include "Editor.h"
#include "NewCharacterScreen.h"
#include "GameState.h"
#include "Player.h"
#include "NPC.h"

/*Class Forward Declarations*/
class Settings;
class Editor;
class NewCharacterScreen;
class GameState;
class Player;
class NPC;
class Projectile;
class sf::RenderTarget;

class MainMenu :
    public State
{
private:
    /*Player Details*/
    PlayerDetails playerDetails;

    /*Projectile Details*/
    ProjectileDetails projectileDetails;

    /*Background Rectangle*/
    sf::RectangleShape background;

    /*NPC Variables*/
    std::unique_ptr<NPC> npc;
    std::vector<std::unique_ptr<NPC>>::const_iterator npcItr;
    std::vector<std::unique_ptr<NPC>> npcVector;

    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();
    void initShader();
    void initRenderTexture();
    void initTileMap();
    void initNPC();

public:
    /*Constuctor & Destructor*/
    MainMenu(GameInfo* game_info);
    virtual ~MainMenu();

    /*Update Functions*/
    void updateButtons();
    void updateNPCLoop(const float& dt);
    void updateNPCCollisions();
    virtual void updateUserInput(const float& dt);
    virtual void update(const float& dt);

    /*Getters*/
     int getRandomInt(int min, int max);

    /*Reinitialize Functions*/
    void reinitializeState();

    /*Save & Load Functions*/
    void loadPlayerDetailsFromFile();
    void loadProjectileDetailsFromFile();

    /*Render Functions*/
    void renderBackground(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void renderNPCs(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    virtual void render(sf::RenderTarget* target);
};
#endif
