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
		&this->font, "Back", 50,//Button Font, Text, and Character Size
		sf::Color(70, 70, 70, 200), sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50),//Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));    //Button Rect Fill Color (Outline Color Optional)
}
void Editor::initTileMap()
{
	this->tileMap = std::make_unique<TILEMAP::TileMap>(
		this->tileSize,
		10, 10,
		"Resources/Images/Tiles/grass.png"
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
}
Editor::~Editor()
{
}

/*Update Functions*/
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
	/*Add Tile*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->tileMap->addTile(
			this->mousePositionTile.x, //Mouse Position Tile X
			this->mousePositionTile.y, //Mouse Position Tile Y
			0,                         //Tile Layer
			false,                     //Collision
			0                          //Tile Type
		);

	/*Remove Tile*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->tileMap->removeTile(
			this->mousePositionTile.x, //Mouse Position Tile X
			this->mousePositionTile.y, //Mouse Position Tile Y
			0                          //Tile Layer
		);
	}

	/*Quit Game*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT_GAME"))))
		this->endState();
}
void Editor::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateButtons();
	this->updateMousePosition();
	this->updateUserInput(dt);
}

/*Render Functions*/
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
	this->renderButtons(*target);
	this->renderTiles(*target);
}
