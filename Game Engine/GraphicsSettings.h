#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

/*Class Forward Declarations*/
class sf::VideoMode;

class GraphicsSettings
{
private:
	/*Initializers*/
	void initVariables();
public:
	/*Constuctor / Destructor*/
	GraphicsSettings();
	virtual ~GraphicsSettings();

	/*Graphics Variables*/
	std::string title;
	sf::VideoMode resolution;
	bool isFullscreen;
	bool isVSync;
	unsigned int frameRateLimit;
	sf::ContextSettings contextSettings;

	/*Save & Load Functions*/
	void saveToFile();
	void loadFromFile();
};
#endif
