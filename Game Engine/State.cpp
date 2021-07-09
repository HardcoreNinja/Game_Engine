#include "Header.h"
#include "State.h"
/*Initializers*/
void State::initVariables(GameInfo* game_info)
{
	this->gameInfo = game_info;
	this->keyTime = 0.f;
	this->maxKeyTime = 37.5f;
	this->isQuit = false;
	this->mouseReleased = false;
	this->tileSize = 32.f;
	this->isPaused = false;
}
void State::initShader()
{
	if (!this->shader.loadFromFile("Shaders/Player/vertex.vert", "Shaders/Player/fragment.frag"))
		std::cout << "Error Loading Shader!\n";
}
void State::initView()
{
	this->defaultWindowView = this->gameInfo->window->getDefaultView();
	this->defaultWindowView.setCenter(this->gameInfo->window->getDefaultView().getCenter());

	this->view.setSize(std::floor(static_cast<float>(this->gameInfo->window->getSize().x)), std::floor(static_cast<float>(this->gameInfo->window->getSize().y)));
	this->view.setCenter(std::floor(static_cast<float>(this->gameInfo->window->getSize().x) / 2.f), std::floor(static_cast<float>(this->gameInfo->window->getSize().y) / 2.f));
}

/*Constuctor & Destructor*/
State::State(GameInfo* game_info)
{
	this->initVariables(game_info);
	this->initShader();
	this->initView();
}
State::~State()
{
}

/*Getters*/
const bool& State::getKeyTime()
{
	if (this->keyTime >= this->maxKeyTime)
	{
		this->keyTime = 0;
		return true;
	}
	else
		return false;
}
const bool& State::getisQuit()
{
	return this->isQuit;
}

/*Setters*/
void State::endState()
{
	this->isQuit = true;
}

/*Update Functions*/
void State::updateGraphicsSettings()
{
	this->gameInfo->graphicsSettings->resolution = sf::VideoMode(this->gameInfo->window->getSize().x, this->gameInfo->window->getSize().y);
	this->gameInfo->graphicsSettings->saveToFile();

	this->createWindow();
}
void State::updateSFMLEvents()
{
	while (this->gameInfo->window->pollEvent(*this->gameInfo->sfmlEvent))
	{
		if (this->gameInfo->sfmlEvent->type == sf::Event::Closed)
			this->gameInfo->window->close();

		else if (this->gameInfo->sfmlEvent->type == sf::Event::MouseButtonPressed)
		{
			std::cout << "Mouse Pressed!\n";
			this->mouseReleased = false;

			this->gameInfo->window->setMouseCursor(*this->gameInfo->cursorDown);
		}
		else if (this->gameInfo->sfmlEvent->type == sf::Event::MouseButtonReleased)
		{
			std::cout << "Mouse Released!\n";
			this->mouseReleased = true;
			this->gameInfo->window->setMouseCursor(*this->gameInfo->cursor);
		}
		else if (this->gameInfo->sfmlEvent->type == sf::Event::Resized)
		{
			std::cout << "New Resized Window Size: " << this->gameInfo->window->getSize().x << "x" << this->gameInfo->window->getSize().y << '\n';
			this->resizeView();
			this->updateGraphicsSettings();
		}
	}
}
void State::updateMousePosition(sf::View* view, sf::View* default_window_view)
{
	/*Mouse Position Desktop*/
	this->mousePositionDesktop = sf::Mouse::getPosition();

	/*Mouse Position Window*/
	this->mousePositionWindow = sf::Mouse::getPosition(*this->gameInfo->window);

	/*Mouse Position View*/
	if (view)
		this->gameInfo->window->setView(*view);
	this->mousePositionView = this->gameInfo->window->mapPixelToCoords(sf::Mouse::getPosition(*this->gameInfo->window));

	/*Mouse Position GUI*/
	if (default_window_view)
		this->gameInfo->window->setView(*default_window_view);
	this->mousePositionGUI = this->gameInfo->window->mapPixelToCoords(sf::Mouse::getPosition(*this->gameInfo->window));

	/*Mouse Position Tile w/ View as Base*/
	this->mousePositionTile = sf::Vector2u(
		static_cast<unsigned>(this->mousePositionView.x) / static_cast<unsigned>(this->tileSize),
		static_cast<unsigned>(this->mousePositionView.y) / static_cast<unsigned>(this->tileSize)
	);

	this->gameInfo->window->setView(this->gameInfo->window->getDefaultView());
}
void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->maxKeyTime)
		this->keyTime += 256.f * dt;

	/*Test Debug
	std::cout << this->keyTime << '\n';
	*/
}

/*Reinitialize Functions*/
void State::createWindow()
{
	auto style = this->gameInfo->graphicsSettings->isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	{
		this->gameInfo->window->create(
			this->gameInfo->graphicsSettings->resolution,     //Window Resolution
			this->gameInfo->graphicsSettings->title,          //Window Title
			style,                                            //Fullscreen Style or not
			this->gameInfo->graphicsSettings->contextSettings //Anti Aliasing Level
		);
	}
	this->gameInfo->window->setFramerateLimit(this->gameInfo->graphicsSettings->frameRateLimit); //Framerate Limit
	this->gameInfo->window->setVerticalSyncEnabled(this->gameInfo->graphicsSettings->isVSync);   //VSync Enabled

	this->reinitializeStates();
}
void State::reinitializeStates()
{
	for (auto& element : *this->gameInfo->states)
	{
		element->reinitializeState();
	}

	this->initView();
}

/*Resize View*/
void State::resizeView()
{
	float aspectRatio = static_cast<float>(this->gameInfo->window->getSize().x) / static_cast<float>(this->gameInfo->window->getSize().y);

	//this->defaultWindowView.setSize(static_cast<float>(this->gameInfo->window->getSize().x) * aspectRatio, static_cast<float>(this->gameInfo->window->getSize().y) * aspectRatio);

	this->view.setSize(std::floor(static_cast<float>(this->gameInfo->window->getSize().x) * aspectRatio), std::floor(static_cast<float>(this->gameInfo->window->getSize().y) * aspectRatio));
	this->view.setCenter((std::floor(static_cast<float>(this->gameInfo->window->getSize().x) * aspectRatio) / 2.f), std::floor((static_cast<float>(this->gameInfo->window->getSize().y) * aspectRatio) / 2.f));
}

/*Pause Menu Functions*/
void State::pause()
{
	this->isPaused = true;
}
void State::unpause()
{
	this->isPaused = false;
}
