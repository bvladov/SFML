#include "MenuItem.h"

MenuItem::MenuItem(std::string title, sf::RenderWindow& window) : m_icon()
{
	m_title = title;
	m_isClicked = false;
	m_menuItem.setSize({ 50,50 });
	m_menuItem.setFillColor(sf::Color::White);
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

MenuItem::MenuItem(const MenuItem& other)
{
	m_icon      = other.m_icon;
	m_isClicked = other.m_isClicked;
	m_menuItem  = other.m_menuItem;
	m_title     = other.m_title;
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
	window.draw(m_menuItem);
}