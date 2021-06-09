#include "Header.h"
#include "Editor.h"
/*Initializers*/
void Editor::initVariables()
{
	this->collision = false;
	this->doorName = "NULL";
	this->tileType = TILEMAP::TileType::Default;
	this->maxTileType = TILEMAP::TileType::Path_Finder_Markings;
	this->cameraSpeed = 1280.f;
	this->tileRotationDegrees = 0;
	this->maxTileRotationDegrees = 360;
	this->tileLayers = 0;
	this->maxTileLayers = 3;
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
		this->tileSize,                                //Tile Size
		37, 25,                                        //Map Width & Height (in Squares)
		this->tileSize, this->tileSize,                //Texture Width & Height
		"Resources/Images/Tiles/PipoyaMasterLevel.png" //Tile Sheet File Path
		);
}
void Editor::initTextureSelector()
{
	/*Texture Selector Box*/
	this->textureSelector = std::make_unique<TILEMAP::TextureSelector>(
		"Config/texture_selector_data_file.ini", //Texture Selector Date File Path
		this->tileSize,                          //Tile Size
		0.f, 0.f,                                //Texture Selector Position
		256.f, 512.f,                            //Bounds Size         
		this->tileMap->getTexture(),             //Tile Map Texture
		this->font,                              //Hide Button Font
		this->keyTime, this->maxKeyTime          //Key Time Variables
		);

	/*Green Selector That Follows Mouse*/
	this->selectorRect.setSize(sf::Vector2f(this->tileSize, this->tileSize));
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setTextureRect(this->tileMap->getTextureIntRect());
	this->selectorRect.setTexture(this->tileMap->getTexture());

	/*Gray Side Bar*/
	this->sideBar.setSize(sf::Vector2f(40.f, static_cast<float>(this->window->getSize().y)));
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 255));
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
void Editor::initLatestTileMap()
{
	this->tileMap->loadFromFile("Config/tile_map.ini", "Resources/Images/Tiles/PipoyaMasterLevel.png");
}

/*Constructor & Destructor*/
Editor::Editor(GameInfo* game_info)
	: State(game_info)
{
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initTileMap();
	this->initTextureSelector();
	this->initPauseMenu();
	this->initLatestTileMap();
}
Editor::~Editor()
{
}

/*Update Functions*/
void Editor::updateTileType()
{
	if (this->tileType < this->maxTileType)
		this->tileType += 1;
	else if (this->tileType == this->maxTileType)
		this->tileType = 0;
}
void Editor::updateTileRotation()
{
	if (this->tileRotationDegrees < this->maxTileRotationDegrees)
		this->tileRotationDegrees += 90;
	else if (this->tileRotationDegrees == this->maxTileRotationDegrees)
		this->tileRotationDegrees = 0;
}
void Editor::updateTileLayers()
{
	if (this->tileLayers < this->maxTileLayers)
		this->tileLayers += 1;
	else if (this->tileLayers == this->maxTileLayers)
		this->tileLayers = 0;
}
void Editor::updateCursorText()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BACKSPACE"))) && this->getKeyTime())
	{
		if (this->doorName.size() > 0)
		{
			this->doorName.pop_back();
		}
	}

	if (this->sfmlEvent->type == sf::Event::TextEntered && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))) && this->getKeyTime())
	{
		if (this->sfmlEvent->text.unicode < 128 && this->sfmlEvent->text.unicode != 8 && this->sfmlEvent->text.unicode != 27 && this->doorName.size() <= 20)
		{
			this->doorName.push_back(static_cast<char>(this->sfmlEvent->text.unicode));
		}
	}

	this->text.setPosition((static_cast<float>(this->mousePositionGUI.x) + 100.f), (static_cast<float>(this->mousePositionGUI.y) - 50.f));

	std::stringstream ss;

	ss << "Mouse Position Window: " << this->mousePositionWindow.x << " x " << this->mousePositionWindow.y << '\n'
		<< "Mouse Position View: " << this->mousePositionView.x << " x " << this->mousePositionView.y << '\n'
		<< "Mouse Position Tile: " << this->mousePositionTile.x << " x " << this->mousePositionTile.y << '\n'
		<< "Tile Map Int Rec (left & top): " << this->tileMap->getTextureIntRect().left << " x " << this->tileMap->getTextureIntRect().top << '\n'
		<< "Collision Bool: " << this->collision << '\n'
		<< "Door Name: " << this->doorName << '\n'
		<< "Tile Type: " << this->tileType << '\n'
		<< "Rotation Degrees: " << this->tileRotationDegrees << '\n'
		<< "Tile Layer: " << this->tileLayers << '\n';

	this->text.setString(ss.str());
}
void Editor::updateSelectorRect()
{
	if (!this->textureSelector->getIsActive())
	{
		this->selectorRect.setTextureRect(this->tileMap->getTextureIntRect());
		this->selectorRect.setTexture(this->tileMap->getTexture());
		this->selectorRect.setRotation(this->tileRotationDegrees);

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
		this->tileMap->loadFromFile("Config/tile_map.ini", "Resources/Images/Tiles/MasterTileSheet.png");

	if (this->pauseMenu->isButtonPressed("EXIT") && this->getKeyTime())
	{
		this->tileSize = 32.f;
		this->tileMap->setTileSizeF(this->tileSize);
		this->tileMap->saveToFile("Config/tile_map.ini");
		this->textureSelector->saveToFile("Config/texture_selector_data_file.ini");
		this->endState();
	}
}
void Editor::updateTextureSelector(const float& dt)
{
	this->textureSelector->update(static_cast<sf::Vector2i>(this->mousePositionGUI), dt);
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
				this->tileLayers,          //Tile Layer
				this->collision,           //Collision
				this->doorName,            //Door Name
				this->tileType,            //Tile Type
				this->tileRotationDegrees  //Tile Rotation
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
			this->tileLayers           //Tile Layer
		);
	}
}
void Editor::updateUserInput(const float& dt)
{
	/*Pause Game*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE_GAME"))) && this->getKeyTime())
		if (!this->isPaused)
			this->pause();
		else
			this->unpause();

	if (!this->isPaused)
	{
		/*Camera Controls*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_UP"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
			this->view.move(sf::Vector2f(0.f, -this->cameraSpeed * dt));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_DOWN"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
			this->view.move(sf::Vector2f(0.f, this->cameraSpeed * dt));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_LEFT"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
			this->view.move(sf::Vector2f(-this->cameraSpeed * dt, 0.f));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_RIGHT"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
			this->view.move(sf::Vector2f(this->cameraSpeed * dt, 0.f));

		/*Collision Toggle*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("COLLISION_TOGGLE"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))) && this->getKeyTime())
			if (this->collision)
				this->collision = false;
			else
				this->collision = true;

		/*Tile Type*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TILE_TYPE"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))) && this->getKeyTime())
			this->updateTileType();

		/*Rotate Tile*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ROTATE_TILE"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))) && this->getKeyTime())
			this->updateTileRotation();

		/*Tile Layers*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TILE_LAYERS"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))) && this->getKeyTime())
			this->updateTileLayers();

		/*Scroll Texture Selector Up*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SCROLL_UP"))))
			this->textureSelector->scrollUp();
		else if (this->sfmlEvent->type == sf::Event::MouseWheelScrolled && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
		{
			if (this->sfmlEvent->mouseWheelScroll.delta > 0)
			{
				std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
				this->textureSelector->scrollUp();
				this->sfmlEvent->mouseWheelScroll.delta = 0;
				std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
			}
		}

		/*Scroll Texture Selector Down*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SCROLL_DOWN"))))
			this->textureSelector->scrollDown();
		else if (this->sfmlEvent->type == sf::Event::MouseWheelScrolled && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
		{
			std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
			if (sfmlEvent->mouseWheelScroll.delta < 0)
				this->textureSelector->scrollDown();
			this->sfmlEvent->mouseWheelScroll.delta = 0;
			std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
		}

		/*Scroll Texture Selector Left*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SCROLL_LEFT"))))
			this->textureSelector->scrollLeft();
		else if (this->sfmlEvent->type == sf::Event::MouseWheelScrolled && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
		{
			if (this->sfmlEvent->mouseWheelScroll.delta < 0)
			{
				std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
				this->textureSelector->scrollLeft();
				this->sfmlEvent->mouseWheelScroll.delta = 0;
				std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
			}
		}

		/*Scroll Texture Selector Right*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SCROLL_RIGHT"))))
			this->textureSelector->scrollRight();
		else if (this->sfmlEvent->type == sf::Event::MouseWheelScrolled && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))))
		{
			if (this->sfmlEvent->mouseWheelScroll.delta > 0)
			{
				std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
				this->textureSelector->scrollRight();
				this->sfmlEvent->mouseWheelScroll.delta = 0;
				std::cout << "Scroll Wheel Delta: " << this->sfmlEvent->mouseWheelScroll.delta << '\n';
			}
		}

		/*Double & Halve Tile Size*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("P"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))) && this->getKeyTime())
		{
			this->tileSize = this->tileSize * 2.f;
			this->tileMap->doubleTileSize();
			this->textureSelector->doubleSelectorSize();
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());
			this->selectorRect.setSize(sf::Vector2f(this->textureSelector->getTextureIntRect().width, this->textureSelector->getTextureIntRect().height));
			this->selectorRect.setTextureRect(this->textureSelector->getTextureIntRect());
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("O"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT_SHIFT"))) && this->getKeyTime())
		{
			this->tileSize = this->tileSize / 2.f;
			this->tileMap->halveTileSize();
			this->textureSelector->halveSelectorSize();
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());
			this->selectorRect.setSize(sf::Vector2f(this->textureSelector->getTextureIntRect().width, this->textureSelector->getTextureIntRect().height));
			this->selectorRect.setTextureRect(this->textureSelector->getTextureIntRect());
		}
	}
}
void Editor::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateMousePosition(&this->view, &this->defaultWindowView);
	this->updateUserInput(dt);

	if (this->isPaused) //Paused
	{
		this->pauseMenu->update(static_cast<sf::Vector2f>(this->mousePositionGUI));
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

/*Reinitialize Functions*/
void Editor::reinitializeState()
{
	std::cout << "Reinitializing Editor!\n";
	this->tileMap->saveToFile("Config/tile_map.ini");
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initTileMap();
	this->initTextureSelector();
	this->initPauseMenu();
	this->initLatestTileMap();
}

/*Render Functions*/
void Editor::renderCursorText(sf::RenderTarget& target)
{
		target.draw(this->text);
}
void Editor::renderSelectorRect(sf::RenderTarget& target)
{
	/*View*/
	this->window->setView(this->view);

	if (!this->textureSelector->getIsActive())
		target.draw(this->selectorRect);
}
void Editor::renderTextureSelector(sf::RenderTarget& target)
{
	this->textureSelector->render(target, this->defaultWindowView);
}
void Editor::renderPauseMenu(sf::RenderTarget& target)
{
	this->pauseMenu->render(target);
}
void Editor::renderTileMap(sf::RenderTarget& target)
{
	this->tileMap->render(target, this->view);
}
void Editor::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	/*Items Rendered with Camera View*/
	target->setView(this->view);
	this->renderTileMap(*target);

	/*Items Rendered with Default Window View*/
	this->window->setView(this->defaultWindowView);
	target->draw(this->sideBar);

	/*Items Rendered with Camera View*/
	target->setView(this->view);
	this->renderTextureSelector(*target);
	this->renderSelectorRect(*target);

	/*Items Rendered with Default Window View*/
	this->window->setView(this->defaultWindowView);
	this->renderCursorText(*target);
	if(this->isPaused)
	this->renderPauseMenu(*target);
}
