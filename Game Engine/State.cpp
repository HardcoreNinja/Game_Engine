#include "Header.h"
#include "State.h"

/*Constuctor / Destructor*/
State::State(GameInfo* game_info)
{
	this->states = game_info->states;
	this->gameInfo = game_info;
	this->window = game_info->window;
	this->graphicsSettings = game_info->graphicsSettings;
	this->supportedKeys = game_info->supportedKeys;
	this->keyTime = 0;
	this->maxKeyTime = 100;
	this->isQuit = false;
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
void State::updateMousePosition(sf::View* view)
{
	this->mousePositionDesktop = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

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
