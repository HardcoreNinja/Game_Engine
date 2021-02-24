#include "Header.h"
#include "Editor.h"
/*Initializers*/
void Editor::initVariables()
{
}
void Editor::initBackground()
{
	this->backgroundRect.setSize(
		sf::Vector2f(
			static_cast<float>(this->graphicsSettings->resolution.width),
			static_cast<float>(this->graphicsSettings->resolution.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/mainmenu_background.jpg"))
		throw("ERROR::MAIN_MENU::FAILED_TO_LOAD::mainmenu_background.jpg");

	this->backgroundRect.setTexture(&this->backgroundTexture);
}
void Editor::initKeybinds()
{
	std::ifstream ifs("Config/editor_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = this->supportedKeys->at(keyboardKey);
	}
	ifs.close();

	//Debug Tester
	for (auto i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void Editor::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/Dosis.ttf"))
	{
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD:Dosis.ttf");
	}

	this->text.setFont(this->font);
}
void Editor::initButtons()
{
	this->buttons["BACK"] = std::make_unique<GUI::Button>(
		100.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   //Button Rect Size
		&this->font, "Back", 50,       //Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}
void Editor::initTileMap()
{
	this->tileMap = std::make_unique<TILEMAP::TileMap>(
		this->tileSize,
		10, 10,
		this->tileSize, this->tileSize,
		"Resources/Images/Tiles/grass-dirt-sand-water-mountains-trees.png"
		);
}
void Editor::initTextureSelector()
{
	this->sideBar.setSize(sf::Vector2f(48.f, static_cast<float>(this->window->getSize().y)));
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineColor(sf::Color::White);
	this->sideBar.setOutlineThickness(1.f);

	this->textureSelector = std::make_unique<TILEMAP::TextureSelector>(
		0.f, 0.f,                       //Texture Selector Position
		432.f, 240.f,                   //Bounds Size
		this->tileSize,                 //Tile Size
		this->tileMap->getTexture(),    //Tile Map Texture
		this->font,                     //Hide Button Font
		this->keyTime, this->maxKeyTime //Key Time Variables
		);
}
void Editor::initPauseMenu()
{
	this->pauseMenu = std::make_unique<PauseMenu>(
		*this->window, //Pause Menu Render Window
		this->font    //Pause Menu Font;
		);

	this->pauseMenu->addButton(
		"EXIT",                                                 //Key
		static_cast<float>(this->window->getSize().y) - 100.f,  // Pos_Y
		"Exit"                                                  // Button Text
	);

	this->pauseMenu->addButton(
		"SAVE",                                              //Key
		static_cast<float>(this->window->getSize().y)/ 2.f,  // Pos_Y
		"Save"                                               // Button Text
	);

	this->pauseMenu->addButton(
		"LOAD",                                                         //Key
		(static_cast<float>(this->window->getSize().y) / 2.f) + 100.f,  // Pos_Y
		"Load"                                                          // Button Text
	);
}

/*Constuctor & Destructor*/
Editor::Editor(GameInfo* game_info)
	: State(game_info)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initTileMap();
	this->initTextureSelector();
	this->initPauseMenu();
}
Editor::~Editor()
{
}

/*Update Functions*/
void Editor::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("Config/tile_map.ini");

	if (this->pauseMenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("Config/tile_map.ini", "Resources/Images/Tiles/grass-dirt-sand-water-mountains-trees.png");

	if (this->pauseMenu->isButtonPressed("EXIT") && this->getKeyTime())
		this->endState();
}
void Editor::updateTextureSelector(const float& dt)
{
	this->textureSelector->update(this->mousePositionWindow, dt);
}
void Editor::updateTileMap()
{
	/*Add Tile*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->textureSelector->getIsActive() &&
			!this->sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePositionWindow)))
		{
			this->tileMap->addTile(
				this->mousePositionTile.x, //Mouse Position Tile X
				this->mousePositionTile.y, //Mouse Position Tile Y
				0,                         //Tile Layer
				false,                     //Collision
				0                          //Tile Type
			);
		}
		else if(!this->sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePositionWindow)))
		{
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());

			//Debug Test
			std::cout << this->textureSelector->getTextureIntRect().left << " x " << this->textureSelector->getTextureIntRect().top << '\n';
			std::cout << this->textureSelector->getTextureIntRect().width << " x " << this->textureSelector->getTextureIntRect().height << '\n';
		}
	}

	/*Remove Tile*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->tileMap->removeTile(
			this->mousePositionTile.x, //Mouse Position Tile X
			this->mousePositionTile.y, //Mouse Position Tile Y
			0                          //Tile Layer
		);
	}
}
void Editor::updateButtons()
{
		for (auto& i : this->buttons)
			i.second->update(this->mousePositionView);

	//Back to Main Menu
	if (this->buttons["BACK"]->isPressed() && this->getKeyTime())
		this->endState();	
}
void Editor::updateUserInput(const float& dt)
{
	/*Quit Game*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE_GAME"))) && this->getKeyTime())
		if (!this->isPaused)
			this->pause();
		else
			this->unpause();
}
void Editor::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateMousePosition();
	this->updateUserInput(dt);

	if (this->isPaused) //Paused
	{
		this->pauseMenu->update(static_cast<sf::Vector2f>(mousePositionWindow));
		this->updatePauseMenuButtons();
	}
	else               //Unpaused
	{
		this->updateButtons();
		this->updateTextureSelector(dt);
		this->updateTileMap();	
	}
}


/*Render Functions*/
void Editor::renderTextureSelector(sf::RenderTarget& target)
{
	this->textureSelector->render(target);
}
void Editor::renderPauseMenu(sf::RenderTarget& target)
{
	this->pauseMenu->render(target);
}
void Editor::renderTiles(sf::RenderTarget& target)
{
	this->tileMap->render(target);
}
void Editor::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}
void Editor::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->backgroundRect);
	this->renderTiles(*target);
	this->renderTextureSelector(*target);
	target->draw(this->sideBar);
	this->renderButtons(*target);

	if(this->isPaused)
	this->renderPauseMenu(*target);
}
