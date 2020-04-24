#include <iostream>
#include <SFML/Graphics.hpp>


class MenuItem
{
public:
		MenuItem();
		MenuItem& operator=(const MenuItem&);
		~MenuItem();


		void setIcon(std::string);
		void clearIcon();
		bool isClicked() const;
		void draw(sf::RenderWindow& window);

		void render();
		void run();

private:
		void init();

		sf::RenderWindow sf_window;
		sf::Event sf_event;

		bool m_isClicked;
		sf::Texture m_icon;
};

MenuItem::MenuItem() : m_icon()
{
}

MenuItem& MenuItem::operator=(const MenuItem& other)
{
		if (this != &other)
		{
				m_icon = other.m_icon;
				m_isClicked = other.m_isClicked;
		}

		return *this;
}

MenuItem::~MenuItem()
{
		clearIcon();
}

void MenuItem::setIcon(std::string filename)
{
		m_icon.loadFromFile(filename);
}

void MenuItem::clearIcon()
{
		m_icon.~Texture();
}
bool MenuItem::isClicked() const
{
		return m_isClicked;
}

void MenuItem::draw(sf::RenderWindow& window)
{

}