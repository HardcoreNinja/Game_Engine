#include "Header.h"
#include "State.h"
/*Initializers*/
void State::initView()
{
	this->defaultWindowView = this->window->getDefaultView();
	this->defaultWindowView.setCenter(this->window->getDefaultView().getCenter());

	this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
	this->view.setCenter(static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2.f);
}

/*Constuctor & Destructor*/
State::State(GameInfo* game_info)
{
	this->states = game_info->states;
	this->gameInfo = game_info;
	this->graphicsSettings = game_info->graphicsSettings;
	this->window = game_info->window;
	this->sfmlEvent = game_info->sfmlEvent;
	this->supportedKeys = game_info->supportedKeys;
	this->keyTime = 0;
	this->maxKeyTime = 100;
	this->isQuit = false;
	this->mouseReleased = false;
	this->tileSize = 40.f;
	this->isPaused = false;
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
	this->gameInfo->graphicsSettings->resolution = sf::VideoMode(this->window->getSize().x, this->window->getSize().y);
	this->graphicsSettings->saveToFile();

	this->createWindow();
}
void State::updateSFMLEvents()
{
	while (this->window->pollEvent(*this->sfmlEvent))
	{
		if (this->sfmlEvent->type == sf::Event::Closed)
			this->window->close();

		if (this->sfmlEvent->type == sf::Event::MouseButtonPressed)
		{
			std::cout << "Mouse Pressed!\n";
			this->mouseReleased = false;
		}
		if (this->sfmlEvent->type == sf::Event::MouseButtonReleased)
		{
			std::cout << "Mouse Released!\n";
			this->mouseReleased = true;
		}
		if (this->sfmlEvent->type == sf::Event::Resized)
		{
			std::cout << "New Resized Window Size: " << this->window->getSize().x << "x" << this->window->getSize().y << '\n';
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
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

	/*Mouse Position View*/
	if (view)
		this->window->setView(*view);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	/*Mouse Position GUI*/
	if (default_window_view)
		this->window->setView(*default_window_view);
	this->mousePositionGUI = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	/*Mouse Position Tile w/ View as Base*/
	this->mousePositionTile = sf::Vector2u(
		static_cast<unsigned>(this->mousePositionView.x) / static_cast<unsigned>(this->tileSize),
		static_cast<unsigned>(this->mousePositionView.y) / static_cast<unsigned>(this->tileSize)
	);

	this->window->setView(this->window->getDefaultView());
}
void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->maxKeyTime)
		this->keyTime += static_cast<int>(2.f * dt * (1.f / dt));

	/*Test Debug
	std::cout << this->keyTime << '\n';
	*/
}

/*Reinitialize Functions*/
void State::createWindow()
{
	auto style = this->gameInfo->graphicsSettings->isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	{
		this->window->create(
			this->gameInfo->graphicsSettings->resolution,     //Window Resolution
			this->gameInfo->graphicsSettings->title,          //Window Title
			style,                                            //Fullscreen Style or not
			this->gameInfo->graphicsSettings->contextSettings //Anti Aliasing Level
		);
	}
	this->window->setFramerateLimit(this->gameInfo->graphicsSettings->frameRateLimit); //Framerate Limit
	this->window->setVerticalSyncEnabled(this->gameInfo->graphicsSettings->isVSync);   //VSync Enabled

	this->reinitializeStates();
}
void State::reinitializeStates()
{
	for (auto& element : *this->states)
	{
		element->reinitializeState();
	}

	this->initView();
}

/*Resize View*/
void State::resizeView()
{
	float aspectRatio = static_cast<float>(this->window->getSize().x) / static_cast<float>(this->window->getSize().y);

	//this->defaultWindowView.setSize(static_cast<float>(this->window->getSize().x) * aspectRatio, static_cast<float>(this->window->getSize().y) * aspectRatio);

	this->view.setSize(static_cast<float>(this->window->getSize().x) * aspectRatio, static_cast<float>(this->window->getSize().y) * aspectRatio);
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
