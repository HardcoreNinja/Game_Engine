#ifndef GUI_H
#define GUI_H
namespace GUI
{
	enum ButtonState {BTN_IDLE, BTN_HOVER, BTN_ACTIVE};
	class Button
	{
	private:

		/*Shape & Text*/
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		/*Button State & ID*/
		short unsigned buttonState;
		short unsigned id;

		/*Rectangle Colors*/
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		/*Text Colors*/
		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

	public:
		/*Constuctor / Destructor*/
		Button(
			float pos_x, float pos_y,
			float width, float height,
			sf::Font* font, std::string text,
			unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent,
			sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0
		);

		virtual ~Button();

		/*Getters*/
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getID() const;

		/*Setters*/
		void setText(const std::string text);
		void setID(const short unsigned id);


		/*Update Functions*/
		void update(const sf::Vector2f& mousePos);

		/*Render*/
		void render(sf::RenderTarget& target);
	};

	class DropdownList
	{
	private:
	    /*Button Variables*/
		GUI::Button* activeElement;
		std::vector<std::unique_ptr<GUI::Button>> buttons;
		
		/*Font Variables*/
		sf::Font& font;

		/*Key Time Variables*/
		float keyTime;
		float maxKeyTime;

		/*Flags*/
		bool showList;

	public:
		/*Constuctor / Destructor*/
		DropdownList(
			float pos_x, float pos_y,
			float width, float height,
			sf::Font& font, std::string list[], unsigned int character_size,
			float& key_time, float& max_key_time,
			unsigned numofElements, unsigned default_index = 0
		);

		virtual ~DropdownList();

		/*Getters*/
		const bool getKeyTime();
		const unsigned short& getActiveElementID() const;
		const bool& getShowList()const;


		/*Setter*/
		const void setActiveElementID(const short unsigned id) const;

		/*Update Functions*/
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);

		/*Render Functions*/
		void render(sf::RenderTarget& target);
	};
}
#endif
