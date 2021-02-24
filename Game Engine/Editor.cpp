#include "Header.h"
#include "Editor.h"
/*Initializers*/
void Editor::initVariables()
{
	this->collision = false;
	this->tileType = TILEMAP::TileType::Default;
	this->cameraSpeed = 10.f;
}
void Editor::initView()
{
	this->view.setSize(static_cast<float>(this->graphicsSettings->resolution.width), static_cast<float>(this->graphicsSettings->resolution.height));
	this->view.setCenter(static_cast<float>(this->graphicsSettings->resolution.width) / 2.f, static_cast<float>(this->graphicsSettings->resolution.height) / 2.f);
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
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(sf::Vector2f(static_cast<float>(this->mousePositionWindow.x), static_cast<float>(this->mousePositionWindow.y)));
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
	/*Texture Selector Box*/
	this->textureSelector = std::make_unique<TILEMAP::TextureSelector>(
		0.f, 0.f,                       //Texture Selector Position
		432.f, 240.f,                   //Bounds Size
		this->tileSize,                 //Tile Size
		this->tileMap->getTexture(),    //Tile Map Texture
		this->font,                     //Hide Button Font
		this->keyTime, this->maxKeyTime //Key Time Variables
		);

	/*Green Selector That Follows Mouse*/
	this->selectorRect.setSize(sf::Vector2f(this->tileSize, this->tileSize));
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setTextureRect(this->tileMap->getTextureIntRect());
	this->selectorRect.setTexture(this->tileMap->getTexture());

	/*Gray Side Bar*/
	this->sideBar.setSize(sf::Vector2f(48.f, static_cast<float>(this->window->getSize().y)));
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineColor(sf::Color::White);
	this->sideBar.setOutlineThickness(1.f);
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
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTileMap();
	this->initTextureSelector();
	this->initPauseMenu();
}
Editor::~Editor()
{
}

/*Update Functions*/
void Editor::updateCursorText()
{
	this->text.setPosition((static_cast<float>(this->mousePositionWindow.x) + 100.f), (static_cast<float>(this->mousePositionWindow.y) - 50.f));

	std::stringstream ss;

	ss << "Mouse Position View: " << this->mousePositionView.x << " x " << this->mousePositionView.y << '\n'
		<< "Mouse Position Tile: " << this->mousePositionTile.x << " x " << this->mousePositionTile.y << '\n'
		<< "Tile Map Int Rec (left & top): " << this->tileMap->getTextureIntRect().left << " x " << this->tileMap->getTextureIntRect().top << '\n'
		<< "Collision Bool: " << this->collision << '\n'
		<< "Tile Type: " << this->tileType << '\n';

	this->text.setString(ss.str());
}
void Editor::updateSelectorRect()
{
	if (!this->textureSelector->getIsActive())
	{
		this->selectorRect.setTextureRect(this->tileMap->getTextureIntRect());
		this->selectorRect.setTexture(this->tileMap->getTexture());

		//Debug Test
		//std::cout << "Selector Int Rect: " << this->tileMap->getTextureIntRect().left << " X " << this->tileMap->getTextureIntRect().top << '\n';
		
		this->selectorRect.setPosition(sf::Vector2f(
			static_cast<float>(this->mousePositionTile.x * this->tileSize),
			static_cast<float>(this->mousePositionTile.y * this->tileSize)
		)
		);
	}
}
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
	this->textureSelector->update(static_cast<sf::Vector2i>(this->mousePositionView), dt);
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
				this->collision,           //Collision
				this->tileType             //Tile Type
			);
		}
		else if(!this->sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePositionWindow)))
		{
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());

			//Debug Test
			//std::cout << this->textureSelector->getTextureIntRect().left << " x " << this->textureSelector->getTextureIntRect().top << '\n';
			//std::cout << this->textureSelector->getTextureIntRect().width << " x " << this->textureSelector->getTextureIntRect().height << '\n';
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
void Editor::updateUserInput(const float& dt)
{
	/*Camera Controls*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_UP"))))
		this->view.move(sf::Vector2f(0.f, -this->cameraSpeed * dt * (1.f / dt)));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_DOWN"))))
		this->view.move(sf::Vector2f(0.f, this->cameraSpeed * dt * (1.f / dt)));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_LEFT"))))
		this->view.move(sf::Vector2f(-this->cameraSpeed * dt * (1.f / dt), 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_RIGHT"))))
		this->view.move(sf::Vector2f(this->cameraSpeed * dt * (1.f / dt), 0.f));

	/*Collision Toggle*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("COLLISION_TOGGLE"))) && this->getKeyTime())
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;

	/*Increase Tile Type*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeyTime())
		this->tileType += 1;

	/*Decrease Tile Type*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeyTime() && this->tileType != 0)
		this->tileType -= 1;

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
	this->updateMousePosition(&this->view);
	this->updateUserInput(dt);

	if (this->isPaused) //Paused
	{
		this->pauseMenu->update(static_cast<sf::Vector2f>(this->mousePositionView));
		this->updatePauseMenuButtons();
	}
	else               //Unpaused
	{
		this->updateCursorText();
		this->updateSelectorRect();
		this->updateTextureSelector(dt);
		this->updateTileMap();	
	}
}

/*Render Functions*/
void Editor::renderCursorText(sf::RenderTarget& target)
{
		target.draw(this->text);
}
void Editor::renderSelectorRect(sf::RenderTarget& target)
{
	if (!this->textureSelector->getIsActive())
		target.draw(this->selectorRect);
}
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
void Editor::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->setView(this->view);
	this->renderTiles(*target);
	this->renderTextureSelector(*target);
	this->renderSelectorRect(*target);
	this->renderCursorText(*target);
	target->draw(this->sideBar);

	if(this->isPaused)
	this->renderPauseMenu(*target);
}
