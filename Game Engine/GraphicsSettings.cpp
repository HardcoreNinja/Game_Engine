#include "Header.h"
#include "GraphicsSettings.h"

/*Initializers*/
void GraphicsSettings::initVariables()
{
	this->title = "DEFAULT TITLE";
	this->resolution = sf::VideoMode(800, 600);
	this->isFullscreen = false;
	this->isVSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
}

/*Constuctor & Destructor*/
GraphicsSettings::GraphicsSettings()
{
	this->initVariables();
}
GraphicsSettings::~GraphicsSettings()
{
}

/*Save & Load Functions*/
void GraphicsSettings::saveToFile()
{
	std::ofstream ofs("Config/graphics_settings.ini");

	if (ofs.is_open())
	{
		ofs << this->title << '\n';
		ofs << this->resolution.width << " " << this->resolution.height << '\n';
		ofs << this->isFullscreen << '\n';
		ofs << this->isVSync << '\n';
		ofs << this->frameRateLimit << '\n';
		ofs << this->contextSettings.antialiasingLevel << '\n';
	}
	ofs.close();
}
void GraphicsSettings::loadFromFile()
{
	std::ifstream ifs("Config/graphics_settings.ini");

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->isFullscreen;
		ifs >> this->isVSync;
		ifs >> this->frameRateLimit;
		ifs >> this->contextSettings.antialiasingLevel;
	}
	ifs.close();
}
