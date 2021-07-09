#include "Header.h"
#include "NewCharacterScreen.h"

/*Initializers*/
void NewCharacterScreen::initVariables(sf::RenderTexture* render_texture, sf::Sprite* render_sprite)
{
	this->mainMenuRenderTexture = render_texture;
	this->mainMenuRenderSprite = render_sprite;
	this->male1Female0 = true;
	this->textureSwitchCounter = 1;
	this->displayNameWarning = false;
}
void NewCharacterScreen::initVariables()
{
	this->male1Female0 = true;
	this->textureSwitchCounter = 1;
	this->displayNameWarning = false;
}
void NewCharacterScreen::initOverlay()
{
	this->overlay.setSize(
		sf::Vector2f(
			static_cast<float>(this->gameInfo->window->getSize().x),
			static_cast<float>(this->gameInfo->window->getSize().y)
		)
	);

	this->overlay.setFillColor(sf::Color(0, 0, 0, 150));
}
void NewCharacterScreen::initKeybinds()
{
	std::ifstream ifs("Config/newcharacterscreen_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = this->gameInfo->supportedKeys->at(keyboardKey);
	}
	ifs.close();

	//Debug Tester
	for (auto i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void NewCharacterScreen::initText()
{
	/*Menu Text*/
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
	{
		throw ("ERROR::NEW_CHARACTER_SCREEN::FAILED_TO_LOAD::BreatheFire.ttf");
	}

	/*Title Text*/
	this->titleShape.setPosition(sf::Vector2f(static_cast<float>(this->gameInfo->window->getSize().x) / 2.f, 30.f));
	this->titleShape.setSize(sf::Vector2f(200.f, 50.f));
	this->titleShape.setOrigin(this->titleShape.getGlobalBounds().width / 2.f, this->titleShape.getGlobalBounds().height / 2.f);

	this->text.setFont(font);
	this->text.setString("Choose a Hero");
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setPosition(sf::Vector2f(this->titleShape.getPosition().x, this->titleShape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));

	/*Name Text*/
	this->nameText.setFont(font);
	this->nameText.setFillColor(sf::Color::White);
	this->nameText.setCharacterSize(30);
	//this->nameText.setOrigin(this->nameText.getGlobalBounds().width / 2.f, this->nameText.getGlobalBounds().height / 2.f);

	/*Name Warning Text*/
	this->nameWarningText.setFont(font);
	this->nameWarningText.setString("You forgot to name your Hero!");
	this->nameWarningText.setFillColor(sf::Color::Red);
	this->nameWarningText.setCharacterSize(15);
	this->nameWarningText.setPosition(0.f, 250.f);
}
void NewCharacterScreen::initButtons()
{
	this->buttons["BACK"] = std::make_unique<GUI::Button>(
		120.f, 550.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Back", 50,  //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["START_GAME"] = std::make_unique<GUI::Button>(
		120.f, 450.f,                  //Button Rect Position
		200.f, 50.f,                   // Button Rect Size
		&this->font, "Start Game", 50,       //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["<"] = std::make_unique<GUI::Button>(
		static_cast<float>(this->gameInfo->window->getSize().x) / 2.f - 25.f, static_cast<float>(this->gameInfo->window->getSize().y) / 2 + 25.f,                  //Button Rect Position
		50.f, 50.f,                   // Button Rect Size
		&this->font, "<", 50,       //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons[">"] = std::make_unique<GUI::Button>(
		static_cast<float>(this->gameInfo->window->getSize().x) / 2.f + 25.f, static_cast<float>(this->gameInfo->window->getSize().y) / 2 + 25.f,                  //Button Rect Position
		50.f, 50.f,                   // Button Rect Size
		&this->font, ">", 50,       //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

	this->buttons["M/F"] = std::make_unique<GUI::Button>(
		static_cast<float>(this->gameInfo->window->getSize().x) / 2.f, static_cast<float>(this->gameInfo->window->getSize().y) / 2 + 100.f,                  //Button Rect Position
		50.f, 50.f,                   // Button Rect Size
		&this->font, "M/F", 50,       //Button Font, Text, and Character Size
		sf::Color::White, sf::Color(250, 150, 150, 250), sf::Color(20, 20, 20, 50), //Text Color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));     //Button Rect Fill Color (Outline Color Optional)

}
void NewCharacterScreen::initSprite()
{
	int intRect_Left = 32;
	int intRec_Top = 32;
	int intRect_Width = 32;
	int intRect_Height = 32;

	this->spriteIntRect = sf::IntRect(intRect_Left * 1, intRec_Top * 0, intRect_Width, intRect_Height);
	if (!this->texture.loadFromFile("Resources/Images/Characters/Male/1.png"))
		throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/1.png");
	sprite.setTexture(this->texture);
	sprite.setTextureRect(this->spriteIntRect);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
	sprite.setPosition(static_cast<float>(this->gameInfo->window->getSize().x) / 2.f, static_cast<float>(this->gameInfo->window->getSize().y) / 2.f);
}

/*Constructor & Destructor*/
NewCharacterScreen::NewCharacterScreen(
	GameInfo* game_info,
	std::vector<std::unique_ptr<NPC>>::const_iterator& npc_itr,
	std::vector<std::unique_ptr<NPC>>& npc_vector,
	std::unique_ptr<TILEMAP::TileMap>& tile_map,
	sf::RenderTexture* render_texture,
	sf::Sprite* render_sprite
)
	: State(game_info), mainMenuNPCItr(npc_itr), mainMenuNPCVector(npc_vector), mainMenuTileMap(tile_map)
{
	this->initVariables(render_texture, render_sprite);
	this->initOverlay();
	this->initKeybinds();
	this->initText();
	this->initButtons();
	this->initSprite();
}
NewCharacterScreen::~NewCharacterScreen()
{
}

/*Update Functions*/
void NewCharacterScreen::updateTexture()
{
	if(this->male1Female0)
		switch (this->textureSwitchCounter)
		{
		case 1:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/1.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/1.png");
			sprite.setTexture(this->texture);
			break;
		case 2:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/2.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/2.png");
			sprite.setTexture(this->texture);
			break;
		case 3:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/3.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/3.png");
			sprite.setTexture(this->texture);
			break;
		case 4:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/4.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/4.png");
			sprite.setTexture(this->texture);
			break;
		case 5:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/5.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/5.png");
			sprite.setTexture(this->texture);
			break;
		case 6:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/6.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/6.png");
			sprite.setTexture(this->texture);
			break;
		case 7:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/7.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/7.png");
			sprite.setTexture(this->texture);
			break;
		case 8:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/8.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/8.png");
			sprite.setTexture(this->texture);
			break;
		case 9:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/9.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/9.png");
			sprite.setTexture(this->texture);
			break;
		case 10:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/10.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/10.png");
			sprite.setTexture(this->texture);
			break;
		case 11:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/11.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/11.png");
			sprite.setTexture(this->texture);
			break;
		case 12:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/12.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/12.png");
			sprite.setTexture(this->texture);
			break;
		case 13:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/13.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/13.png");
			sprite.setTexture(this->texture);
			break;
		case 14:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/14.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/14.png");
			sprite.setTexture(this->texture);
			break;
		case 15:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/15.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/15.png");
			sprite.setTexture(this->texture);
			break;
		case 16:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/16.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/16.png");
			sprite.setTexture(this->texture);
			break;
		case 17:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/17.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/17.png");
			sprite.setTexture(this->texture);
			break;
		case 18:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/18.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/18.png");
			sprite.setTexture(this->texture);
			break;
		case 19:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/19.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/19.png");
			sprite.setTexture(this->texture);
			break;
		case 20:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/20.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/20.png");
			sprite.setTexture(this->texture);
			break;
		case 21:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/21.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/21.png");
			sprite.setTexture(this->texture);
			break;
		case 22:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/22.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/22.png");
			sprite.setTexture(this->texture);
			break;
		case 23:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/23.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/23.png");
			sprite.setTexture(this->texture);
			break;
		case 24:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/24.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/24.png");
			sprite.setTexture(this->texture);
			break;
		case 25:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/25.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/25.png");
			sprite.setTexture(this->texture);
			break;
		case 26:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/26.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/26.png");
			sprite.setTexture(this->texture);
			break;
		case 27:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/27.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/27.png");
			sprite.setTexture(this->texture);
			break;
		case 28:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/28.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/28.png");
			sprite.setTexture(this->texture);
			break;
		case 29:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/29.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/9.png");
			sprite.setTexture(this->texture);
			break;
		case 30:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/30.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/30.png");
			sprite.setTexture(this->texture);
			break;
		case 31:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/31.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/31.png");
			sprite.setTexture(this->texture);
			break;
		case 32:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/32.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/32.png");
			sprite.setTexture(this->texture);
			break;
		case 33:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/33.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/33.png");
			sprite.setTexture(this->texture);
			break;
		case 34:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/34.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/34.png");
			sprite.setTexture(this->texture);
			break;
		case 35:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/35.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/35.png");
			sprite.setTexture(this->texture);
			break;
		case 36:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/36.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/36.png");
			sprite.setTexture(this->texture);
			break;
		case 37:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/37.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/37.png");
			sprite.setTexture(this->texture);
			break;
		case 38:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/38.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/38.png");
			sprite.setTexture(this->texture);
			break;
		case 39:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/39.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/39.png");
			sprite.setTexture(this->texture);
			break;
		case 40:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/40.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/40.png");
			sprite.setTexture(this->texture);
			break;
		case 41:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/41.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/41.png");
			sprite.setTexture(this->texture);
			break;
		case 42:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/42.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/42.png");
			sprite.setTexture(this->texture);
			break;
		case 43:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/43.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/43.png");
			sprite.setTexture(this->texture);
			break;
		case 44:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/44.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/44.png");
			sprite.setTexture(this->texture);
			break;
		case 45:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/45.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/45.png");
			sprite.setTexture(this->texture);
			break;
		case 46:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/46.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/46.png");
			sprite.setTexture(this->texture);
			break;
		case 47:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/47.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/47.png");
			sprite.setTexture(this->texture);
			break;
		case 48:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/48.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/48.png");
			sprite.setTexture(this->texture);
			break;
		case 49:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/49.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/49.png");
			sprite.setTexture(this->texture);
			break;
		case 50:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/50.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/50.png");
			sprite.setTexture(this->texture);
			break;
		case 51:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/51.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/51.png");
			sprite.setTexture(this->texture);
			break;
		case 52:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/52.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/52.png");
			sprite.setTexture(this->texture);
			break;
		case 53:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/53.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/53.png");
			sprite.setTexture(this->texture);
			break;
		case 54:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/54.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/54.png");
			sprite.setTexture(this->texture);
			break;
		case 55:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/55.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/55.png");
			sprite.setTexture(this->texture);
			break;
		case 56:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/56.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/56.png");
			sprite.setTexture(this->texture);
			break;
		case 57:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/57.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/57.png");
			sprite.setTexture(this->texture);
			break;
		case 58:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/58.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/58.png");
			sprite.setTexture(this->texture);
			break;
		case 59:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/59.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/59.png");
			sprite.setTexture(this->texture);
			break;
		case 60:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/60.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/60.png");
			sprite.setTexture(this->texture);
			break;
		case 61:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/61.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/61.png");
			sprite.setTexture(this->texture);
			break;
		case 62:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/62.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/62.png");
			sprite.setTexture(this->texture);
			break;
		case 63:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/63.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/63.png");
			sprite.setTexture(this->texture);
			break;
		case 64:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/64.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/64.png");
			sprite.setTexture(this->texture);
			break;
		case 65:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/65.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/65.png");
			sprite.setTexture(this->texture);
			break;
		case 66:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/66.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/66.png");
			sprite.setTexture(this->texture);
			break;
		case 67:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/67.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/67.png");
			sprite.setTexture(this->texture);
			break;
		case 68:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/68.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/68.png");
			sprite.setTexture(this->texture);
			break;
		case 69:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/69.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/69.png");
			sprite.setTexture(this->texture);
			break;
		default:
			std::cout << "ERROR::NEWCHARACTERSCREEN::void updateTexture()::Invalid Switch Entry!\n";
		}
	else if (!this->male1Female0)
		switch (this->textureSwitchCounter)
		{
		case 1:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/1.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/1.png");
			this->sprite.setTexture(this->texture);
			break;
		case 2:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/2.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/2.png");
			this->sprite.setTexture(this->texture);
			break;
		case 3:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/3.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/3.png");
			this->sprite.setTexture(this->texture);
			break;
		case 4:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/4.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/4.png");
			this->sprite.setTexture(this->texture);
			break;
		case 5:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/5.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/5.png");
			this->sprite.setTexture(this->texture);
			break;
		case 6:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/6.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/6.png");
			this->sprite.setTexture(this->texture);
			break;
		case 7:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/7.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/7.png");
			this->sprite.setTexture(this->texture);
			break;
		case 8:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/8.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/8.png");
			this->sprite.setTexture(this->texture);
			break;
		case 9:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/9.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 10:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/10.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/10.png");
			this->sprite.setTexture(this->texture);
			break;
		case 11:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/11.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/11.png");
			this->sprite.setTexture(this->texture);
			break;
		case 12:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/12.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/12.png");
			this->sprite.setTexture(this->texture);
			break;
		case 13:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/13.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/13.png");
			this->sprite.setTexture(this->texture);
			break;
		case 14:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/14.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/14.png");
			this->sprite.setTexture(this->texture);
			break;
		case 15:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/15.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/15.png");
			this->sprite.setTexture(this->texture);
			break;
		case 16:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/16.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/16.png");
			this->sprite.setTexture(this->texture);
			break;
		case 17:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/17.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/17.png");
			this->sprite.setTexture(this->texture);
			break;
		case 18:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/18.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/18.png");
			this->sprite.setTexture(this->texture);
			break;
		case 19:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/19.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/19.png");
			this->sprite.setTexture(this->texture);
			break;
		case 20:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/20.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/20.png");
			this->sprite.setTexture(this->texture);
			break;
		case 21:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/21.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/21.png");
			this->sprite.setTexture(this->texture);
			break;
		case 22:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/22.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/22.png");
			this->sprite.setTexture(this->texture);
			break;
		case 23:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/23.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/23.png");
			this->sprite.setTexture(this->texture);
			break;
		case 24:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/24.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/24.png");
			this->sprite.setTexture(this->texture);
			break;
		case 25:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/25.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/25.png");
			this->sprite.setTexture(this->texture);
			break;
		case 26:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/26.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/26.png");
			this->sprite.setTexture(this->texture);
			break;
		case 27:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/27.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/27.png");
			this->sprite.setTexture(this->texture);
			break;
		case 28:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/28.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/28.png");
			this->sprite.setTexture(this->texture);
			break;
		case 29:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/29.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 30:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/30.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/30.png");
			this->sprite.setTexture(this->texture);
			break;
		case 31:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/31.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/31.png");
			this->sprite.setTexture(this->texture);
			break;
		case 32:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/32.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/32.png");
			this->sprite.setTexture(this->texture);
			break;
		case 33:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/33.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/33.png");
			this->sprite.setTexture(this->texture);
			break;
		case 34:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/34.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/34.png");
			this->sprite.setTexture(this->texture);
			break;
		case 35:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/35.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/35.png");
			this->sprite.setTexture(this->texture);
			break;
		case 36:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/36.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/36.png");
			this->sprite.setTexture(this->texture);
			break;
		case 37:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/37.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/37.png");
			this->sprite.setTexture(this->texture);
			break;
		case 38:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/38.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/38.png");
			this->sprite.setTexture(this->texture);
			break;
		case 39:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/39.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/39.png");
			this->sprite.setTexture(this->texture);
			break;
		case 40:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/40.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/40.png");
			this->sprite.setTexture(this->texture);
			break;
		case 41:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/41.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/41.png");
			this->sprite.setTexture(this->texture);
			break;
		case 42:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/42.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/42.png");
			this->sprite.setTexture(this->texture);
			break;
		case 43:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/43.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/43.png");
			this->sprite.setTexture(this->texture);
			break;
		case 44:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/44.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/44.png");
			this->sprite.setTexture(this->texture);
			break;
		case 45:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/45.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/45.png");
			this->sprite.setTexture(this->texture);
			break;
		case 46:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/46.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/46.png");
			this->sprite.setTexture(this->texture);
			break;
		case 47:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/47.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/47.png");
			this->sprite.setTexture(this->texture);
			break;
		case 48:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/48.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/48.png");
			this->sprite.setTexture(this->texture);
			break;
		case 49:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/49.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/49.png");
			this->sprite.setTexture(this->texture);
			break;
		case 50:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/50.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/50.png");
			this->sprite.setTexture(this->texture);
			break;
		case 51:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/51.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/51.png");
			this->sprite.setTexture(this->texture);
			break;
		case 52:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/52.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/52.png");
			this->sprite.setTexture(this->texture);
			break;
		case 53:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/53.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/53.png");
			this->sprite.setTexture(this->texture);
			break;
		case 54:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/54.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/54.png");
			this->sprite.setTexture(this->texture);
			break;
		case 55:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/55.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/55.png");
			this->sprite.setTexture(this->texture);
			break;
		case 56:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/56.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/56.png");
			this->sprite.setTexture(this->texture);
			break;
		case 57:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/57.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/57.png");
			this->sprite.setTexture(this->texture);
			break;
		case 58:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/58.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/58.png");
			this->sprite.setTexture(this->texture);
			break;
		case 59:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/59.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/59.png");
			this->sprite.setTexture(this->texture);
			break;
		case 60:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/60.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/60.png");
			this->sprite.setTexture(this->texture);
			break;
		case 61:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/61.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/61.png");
			this->sprite.setTexture(this->texture);
			break;
		case 62:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/62.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/62.png");
			this->sprite.setTexture(this->texture);
			break;
		case 63:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/63.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/63.png");
			this->sprite.setTexture(this->texture);
			break;
		case 64:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/64.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/64.png");
			this->sprite.setTexture(this->texture);
			break;
		case 65:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/65.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/65.png");
			this->sprite.setTexture(this->texture);
			break;
		case 66:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/66.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/66.png");
			this->sprite.setTexture(this->texture);
			break;
		case 67:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/67.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/67.png");
			this->sprite.setTexture(this->texture);
			break;
		case 68:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/68.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/68.png");
			this->sprite.setTexture(this->texture);
			break;
		case 69:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/69.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/69.png");
			this->sprite.setTexture(this->texture);
			break;
		case 70:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/70.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/70.png");
			this->sprite.setTexture(this->texture);
			break;
		case 71:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/71.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/71.png");
			this->sprite.setTexture(this->texture);
			break;
		case 72:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/72.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/72.png");
			this->sprite.setTexture(this->texture);
			break;
		case 73:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/73.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/73.png");
			this->sprite.setTexture(this->texture);
			break;
		case 74:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/74.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/74.png");
			this->sprite.setTexture(this->texture);
			break;
		case 75:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/75.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/75.png");
			this->sprite.setTexture(this->texture);
			break;
		case 76:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/76.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/76.png");
			this->sprite.setTexture(this->texture);
			break;
		case 77:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/77.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/77.png");
			this->sprite.setTexture(this->texture);
			break;
		case 78:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/78.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/78.png");
			this->sprite.setTexture(this->texture);
			break;
		case 79:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/79.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/79.png");
			this->sprite.setTexture(this->texture);
			break;
		case 80:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/80.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/80.png");
			this->sprite.setTexture(this->texture);
			break;
		case 81:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/81.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/81.png");
			this->sprite.setTexture(this->texture);
			break;
		case 82:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/82.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/82.png");
			this->sprite.setTexture(this->texture);
			break;
		case 83:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/83.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/83.png");
			this->sprite.setTexture(this->texture);
			break;
		case 84:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/84.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/84.png");
			this->sprite.setTexture(this->texture);
			break;
		case 85:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/85.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/85.png");
			this->sprite.setTexture(this->texture);
			break;
		case 86:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/86.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/86.png");
			this->sprite.setTexture(this->texture);
			break;
		case 87:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/87.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/87.png");
			this->sprite.setTexture(this->texture);
			break;
		case 88:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/88.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/88.png");
			this->sprite.setTexture(this->texture);
			break;
		case 89:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/89.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 90:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/90.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/10.png");
			this->sprite.setTexture(this->texture);
			break;
		case 91:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/91.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/91.png");
			this->sprite.setTexture(this->texture);
			break;
		default:
			std::cout << "ERROR::NEWCHARACTERSCREEN::void updateTexture()::Invalid Switch Entry!\n";
		}
}
void NewCharacterScreen::updateAnimation()
{

	int intRectTop_Down = 0;
	int intRectLeft_Start = 0;
	int intRectLeft_End = 64;
	int intRectLeft_FrameSize = 32;

	float deltaTime = this->animationClock.getElapsedTime().asSeconds();
	float switchTime = .1f;

	if (this->male1Female0)
	{
		if (deltaTime > switchTime)
		{
			this->spriteIntRect.top = intRectTop_Down;

			if (this->spriteIntRect.left == intRectLeft_End)
				this->spriteIntRect.left = intRectLeft_Start;
			else
			{
				this->spriteIntRect.left += intRectLeft_FrameSize;
				sprite.setTextureRect(this->spriteIntRect);
				this->animationClock.restart();
			}
		}
	}
	else if (!this->male1Female0)
	{
		if (deltaTime > switchTime)
		{
			this->spriteIntRect.top = intRectTop_Down;

			if (this->spriteIntRect.left == intRectLeft_End)
				this->spriteIntRect.left = intRectLeft_Start;
			else
			{
				this->spriteIntRect.left += intRectLeft_FrameSize;
				this->sprite.setTextureRect(this->spriteIntRect);
				this->animationClock.restart();
			}
		}
	}

}
void NewCharacterScreen::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mousePositionView);

	/*Start Game*/
	if (this->buttons["START_GAME"]->isPressed() && this->getKeyTime())
	{
		if (this->nameString.size() <= 0)
			this->displayNameWarning = true;
		else
		{
			/*Fade Out Main Menu Music*/
			this->gameInfo->audioMap["MAIN_MENU"]->setFadeOut(true);

			/*New Character Details*/
			this->playerDetails.name = this->nameString;
			this->playerDetails.textureSwitchCounter = this->textureSwitchCounter;
			this->playerDetails.male1Female0 = this->male1Female0;

			/*Current Tile Map*/
			this->playerDetails.currentTileMap = CurrentTileMap::LEVEL_A;

			/*Position & Direction*/
			this->playerDetails.position = sf::Vector2f(207.f, 176.f);
			this->playerDetails.oldDirection = Direction::Down;

			/*Movement Variables*/
			this->playerDetails.velocity = sf::Vector2f(0.f, 0.f);;
			this->playerDetails.maxVelocity = 1024.f;
			this->playerDetails.acceleration = 26.f;
			this->playerDetails.deceleration = 19.f;

			/*Level*/
			this->playerDetails.level = 1;

			/*HP*/
			this->playerDetails.currentHP = 100.f;
			this->playerDetails.maxHP = 100.f;

			/*Stamina*/
			this->playerDetails.currentStamina = 100.f;
			this->playerDetails.maxStamina = 100.f;
			this->playerDetails.staminaDrainFactor = 0.05;
			this->playerDetails.staminaFillFactor = 0.05;

			/*Mana*/
			this->playerDetails.currentMana = 100.f;
			this->playerDetails.maxMana = 100.f;

			/*Projectile Type*/
			this->projectileDetails.projectileType = ProjectileTypes::Black_Tornado;

			/*Projectile Movement Variables*/
			this->projectileDetails.velocity = sf::Vector2f(0.f, 0.f);
			this->projectileDetails.maxVelocity = 1024.f;
			this->projectileDetails.acceleration = 128.f;
			this->projectileDetails.deceleration = 13.f;

			/*Mana*/
			this->projectileDetails.manaDrainFactor = 5.f;

			/*Projectile Destroy Variables*/
			this->projectileDetails.lifeTimeCounter = 0;
			this->projectileDetails.maxLifeTimeCounter = 100;

			this->gameInfo->states->push_back(std::make_unique<GameState>(this->gameInfo, this->playerDetails, this->projectileDetails, false));
		}
	}

	/*Back to Main Menu*/
	if (this->buttons["BACK"]->isPressed() && this->getKeyTime())
		this->endState();

	/*Increment & Decrement Texture*/
	if (this->male1Female0)
	{
		/*Increment Texture*/
		if (this->buttons[">"]->isPressed() && this->getKeyTime())
		{
			if (this->textureSwitchCounter != 69)
			{
				this->textureSwitchCounter += 1;
				std::cout << this->textureSwitchCounter << '\n';
				this->updateAnimation();
			}
			else if (this->textureSwitchCounter == 69)
			{
				this->textureSwitchCounter = 1;
				std::cout << this->textureSwitchCounter << '\n';
				this->updateAnimation();
			}
		}

		/*Decrement Texture*/
		if (this->buttons["<"]->isPressed() && this->getKeyTime())
		{
			if (this->textureSwitchCounter != 1)
			{
				this->textureSwitchCounter -= 1;
				this->updateAnimation();
			}
			else if (this->textureSwitchCounter == 1)
			{
				this->textureSwitchCounter = 69;
				this->updateAnimation();
			}
		}
	}
	else if (!this->male1Female0)
	{
		/*Increment Texture*/
		if (this->buttons[">"]->isPressed() && this->getKeyTime())
		{
			if (this->textureSwitchCounter != 91)
			{
				this->textureSwitchCounter += 1;
				std::cout << this->textureSwitchCounter << '\n';
				this->updateAnimation();
			}
			else if (this->textureSwitchCounter == 91)
			{
				this->textureSwitchCounter = 1;
				std::cout << this->textureSwitchCounter << '\n';
				this->updateAnimation();
			}
		}

		/*Decrement Texture*/
		if (this->buttons["<"]->isPressed() && this->getKeyTime())
		{
			if (this->textureSwitchCounter != 1)
			{
				this->textureSwitchCounter -= 1;
				this->updateAnimation();
			}
			else if (this->textureSwitchCounter == 1)
			{
				this->textureSwitchCounter = 91;
				this->updateAnimation();
			}
		}
	}

		/*Gender Toggle*/
		if (this->buttons["M/F"]->isPressed() && this->getKeyTime())
		{
			if (this->male1Female0 == true)
				this->male1Female0 = false;
			else if (this->male1Female0 == false)
				this->male1Female0 = true;
		}

}
void NewCharacterScreen::updateUserInput(const float& dt)
{
	/*Start Game*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("START_GAME"))) && this->getKeyTime())
	{
		if (this->nameString.size() <= 0)
			this->displayNameWarning = true;
		else
		{
			/*Fade Out Main Menu Music*/
			this->gameInfo->audioMap["MAIN_MENU"]->setFadeOut(true);

			/*New Character Details*/
			this->playerDetails.name = this->nameString;
			this->playerDetails.textureSwitchCounter = this->textureSwitchCounter;
			this->playerDetails.male1Female0 = this->male1Female0;

			/*Current Tile Map*/
			this->playerDetails.currentTileMap = CurrentTileMap::LEVEL_A;

			/*Position & Direction*/
			this->playerDetails.position = sf::Vector2f(207.f, 176.f);
			this->playerDetails.oldDirection = Direction::Down;

			/*Movement Variables*/
			this->playerDetails.velocity = sf::Vector2f(0.f, 0.f);;
			this->playerDetails.maxVelocity = 1024.f;
			this->playerDetails.acceleration = 26.f;
			this->playerDetails.deceleration = 19.f;

			/*Level*/
			this->playerDetails.level = 1;

			/*HP*/
			this->playerDetails.currentHP = 100.f;
			this->playerDetails.maxHP = 100.f;

			/*Stamina*/
			this->playerDetails.currentStamina = 100.f;
			this->playerDetails.maxStamina = 100.f;
			this->playerDetails.staminaDrainFactor = 0.05;
			this->playerDetails.staminaFillFactor = 0.05;

			/*Mana*/
			this->playerDetails.currentMana = 100.f;
			this->playerDetails.maxMana = 100.f;

			/*Projectile Type*/
			this->projectileDetails.projectileType = ProjectileTypes::Black_Tornado;

			/*Projectile Movement Variables*/
			this->projectileDetails.velocity = sf::Vector2f(0.f, 0.f);
			this->projectileDetails.maxVelocity = 1024.f;
			this->projectileDetails.acceleration = 128.f;
			this->projectileDetails.deceleration = 13.f;

			/*Mana*/
			this->projectileDetails.manaDrainFactor = 5.f;

			/*Projectile Destroy Variables*/
			this->projectileDetails.lifeTimeCounter = 0;
			this->projectileDetails.maxLifeTimeCounter = 100;

			this->gameInfo->states->push_back(std::make_unique<GameState>(this->gameInfo, this->playerDetails, this->projectileDetails, false));
		}
	}

	/*Back to Main Menu*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BACK"))) && this->getKeyTime())
		this->endState();
}  
void NewCharacterScreen::updateNameText()
{
	std::stringstream ss;

		this->nameText.setPosition(0.f, 200.f);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BACKSPACE"))) && this->getKeyTime())
		{
			if (this->nameString.size() > 0)
			{
				this->nameString.pop_back();
				this->nameText.setString(ss.str());
			}
		}

		if (this->gameInfo->sfmlEvent->type == sf::Event::TextEntered && this->getKeyTime())
		{
			if (this->gameInfo->sfmlEvent->text.unicode < 128 && this->gameInfo->sfmlEvent->text.unicode != 8 && this->gameInfo->sfmlEvent->text.unicode != 27 && this->nameString.size() <= 9)
			{
				this->nameString.push_back(static_cast<char>(this->gameInfo->sfmlEvent->text.unicode));	
			}
		}

		ss << "Character Name: " << this->nameString;

		this->nameText.setString(ss.str());
}
void NewCharacterScreen::updateNPCLoop(const float& dt)
{
	int counter = 0;
	for (this->mainMenuNPCItr = this->mainMenuNPCVector.begin(); this->mainMenuNPCItr != this->mainMenuNPCVector.end(); this->mainMenuNPCItr++)
	{
		this->mainMenuNPCVector[counter]->update(dt);
		counter++;
	}
}
void NewCharacterScreen::updateNPCCollisions()
{
	/*NPC/Wall*/
	int counter = 0;
	for (this->mainMenuNPCItr = this->mainMenuNPCVector.begin(); this->mainMenuNPCItr != this->mainMenuNPCVector.end(); this->mainMenuNPCItr++)
	{
		this->mainMenuNPCVector[counter]->tileCollision(this->mainMenuTileMap->getCollision(this->mainMenuNPCVector[counter]->getSpriteRect()));
		counter++;
	}
}
void NewCharacterScreen::update(const float& dt)
{
	this->updateSFMLEvents();
	this->updateKeyTime(dt);
	this->updateMousePosition();
	this->updateTexture();
	this->updateAnimation();
	this->updateButtons();
	this->updateUserInput(dt);
	this->updateNameText();
	this->updateNPCLoop(dt);
	this->updateNPCCollisions();

	/*Name Warning Text Toggle*/
	if (this->displayNameWarning == true)
	{
		if (this->nameString.size() > 0)
			this->displayNameWarning = false;
	}
}

/*Reinitialize Functions*/
void NewCharacterScreen::reinitializeState()
{
	std::cout << "Reinitializing NewCharacterScreen!\n";
	this->initVariables();
	this->initOverlay();
	this->initKeybinds();
	this->initText();
	this->initButtons();
	this->initSprite();
}

/*Render Functions*/
void NewCharacterScreen::renderOverlay(sf::RenderTarget& target)
{
	target.draw(this->overlay);
}
void NewCharacterScreen::renderTileMap(sf::RenderTarget& target)
{
	this->mainMenuTileMap->render(target, this->view, this->mainMenuTileMap->getEnterTilePosition(), &this->shader);
}
void NewCharacterScreen::renderNPCs(sf::RenderTarget& target)
{
	int counter = 0;
	for (this->mainMenuNPCItr = this->mainMenuNPCVector.begin(); this->mainMenuNPCItr != this->mainMenuNPCVector.end(); this->mainMenuNPCItr++)
	{
		this->mainMenuNPCVector[counter]->render(target);

		counter++;
	}
}
void NewCharacterScreen::renderSprite(sf::RenderTarget& target)
{
	target.draw(sprite);
}
void NewCharacterScreen::renderText(sf::RenderTarget& target)
{
	target.draw(this->text);
	//target.draw(this->nameTextShape);
	target.draw(this->nameText);

	if (this->displayNameWarning)
		target.draw(this->nameWarningText);
}
void NewCharacterScreen::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}
void NewCharacterScreen::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameInfo->window;

	this->mainMenuRenderTexture->clear();
	this->renderTileMap(*this->mainMenuRenderTexture);
	this->renderNPCs(*this->mainMenuRenderTexture);
	this->renderOverlay(*this->mainMenuRenderTexture);
	this->renderTexture.display();
	target->draw(*this->mainMenuRenderSprite);

	this->renderSprite(*target);
	this->renderText(*target);
	this->renderButtons(*target);
}
