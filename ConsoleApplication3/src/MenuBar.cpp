#include "MenuBar.h"

MenuBar::MenuBar()
{
	
}

MenuBar::~MenuBar()
{

}

void MenuBar::draw(sf::RenderWindow& window)
{
  window.draw(m_menuBar);
	
	for (size_t i = 0; i < m_items.size(); i++)
	{
		m_items[i].draw(window);
	}
}

void MenuBar::addItem(std::string title, sf::Vector2f size)
{
	MenuItem item(title, size);
	m_items.push_back(item);
}
