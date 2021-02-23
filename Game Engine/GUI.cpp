#include "Header.h"
#include "GUI.h"
/*Buttons===========================================================================================================================================*/
/*Constructor/Destructor*/
GUI::Button::Button(
	float pos_x, float pos_y,
	float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
	: buttonState(BTN_IDLE), id(id)
{
	this->shape.setPosition(sf::Vector2f(pos_x, pos_y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOrigin(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = sf::Color::White;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}
GUI::Button::~Button()
{
}

/*Getters*/
const bool GUI::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}
const std::string GUI::Button::getText() const
{
	return this->text.getString();
}
const short unsigned& GUI::Button::getID() const
{
	return this->id;
}

/*Setters*/
void GUI::Button::setText(const std::string text)
{
	this->text.setString(text);
}
void GUI::Button::setID(const short unsigned id)
{
	this->id = id;
}

/*Update Functions*/
void GUI::Button::update(const sf::Vector2f& mousePos)
{
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

/*Render Functions*/
void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

/*DROPDOWN LIST =============================================================================================*/
/*Constructor/Destructor*/
GUI::DropdownList::DropdownList(
	float pos_x, float pos_y,
	float width, float height,
	sf::Font& font_reference, std::string list[], unsigned int character_size,
	int& key_time, int& max_key_time,
	unsigned numofElements, unsigned default_index
)
	: font(font_reference), showList(false), keyTime(key_time), maxKeyTime(max_key_time)
{
	this->activeElement = new GUI::Button(
		pos_x, pos_y, width, height,
		&this->font, list[default_index], character_size,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);

	for (size_t i = 0; i < numofElements; i++)
	{
		this->buttons.push_back(
			std::make_unique<GUI::Button>(
				pos_x, pos_y + ((i + 1) * height), width, height,
				&this->font, list[i], character_size,
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				i // <-Button.m_id is index number of vector...
			)
		);
	}
}
GUI::DropdownList::~DropdownList()
{
	delete this->activeElement;
}

/*Getters*/
const bool GUI::DropdownList::getKeyTime()
{
	if (this->keyTime >= this->maxKeyTime)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}
const unsigned short& GUI::DropdownList::getActiveElementID() const
{
	return this->activeElement->getID();
}
const bool& GUI::DropdownList::getShowList() const
{
	return this->showList;
}

/*Setters*/
const void GUI::DropdownList::setActiveElementID(const short unsigned id) const
{
	this->activeElement->setID(id);
	this->activeElement->setText(this->buttons[id]->getText());
}

/*Update Functions*/
void GUI::DropdownList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->maxKeyTime)
		this->keyTime += static_cast<int>(2.f * dt * (1.f / dt));
}
void GUI::DropdownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeyTime(dt);

	this->activeElement->update(mousePos);

	//Show & Hide List
	if (this->activeElement->isPressed() && this->getKeyTime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->buttons)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeyTime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setID(i->getID());
			}
		}
	}

}

/*Render Functions*/
void GUI::DropdownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->buttons)
		{
			i->render(target);
		}
	}
}