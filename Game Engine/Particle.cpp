#include "Header.h"
#include "Particle.h"

/*Initializers*/
void Particle::initVariables(sf::RenderWindow& window)
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	if (!this->texture.loadFromFile("Resources/Images/Particles/rain.png"))
		throw("ERROR::PARTICLES::FAILED_TO_LOAD::rain.png");
	this->sprite.setTexture(this->texture);
	this->intRect = sf::IntRect(0, 0, 2, 10);
	this->sprite.setTextureRect(this->intRect);
	this->sprite.setPosition(static_cast<float>(this->getRandomInt(0, window.getSize().x)), 0.f);
}
void Particle::initShader()
{
	if(!this->shader.loadFromFile("Shaders/Particle/Rain/fragment.frag", sf::Shader::Fragment))
		throw ("ERROR::PARTICLE::COULD_NOT_LOAD_SHADER");
}

/*Constructor & Destructor*/
Particle::Particle(sf::RenderWindow& window)
{
	this->initVariables(window);
	this->initShader();
}
Particle::~Particle()
{
}

/*Getters*/
sf::Vector2f Particle::getPosition()
{
	return this->sprite.getPosition();
}
int Particle::getRandomInt(int min, int max)
{
	return rand() % max + min;
}

/*Update Functions*/
void Particle::update(const float& dt)
{
	this->sprite.move(5.f, 1024.f * dt);
}

/*Render Functions*/
void Particle::render(sf::RenderTarget& target, sf::RenderWindow& window, CurrentTileMap currentTileMap)
{
	if ((this->sprite.getPosition().y < window.getSize().y) && currentTileMap != CurrentTileMap::HOUSE_A)
	{
		this->shader.setUniform("u_time", this->shaderClock.getElapsedTime().asSeconds());
		target.draw(this->sprite, &this->shader);
	}
}
