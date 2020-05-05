#include "MenuBar.h"

MenuBar::MenuBar(sf::RenderWindow& window)
{
	MenuItem first("First", window);
	m_menuBar.setSize({ 50,50 });
	m_menuBar.setFillColor(sf::Color::White);
	m_items.push_back(first);
}

MenuBar::~MenuBar()
{

}

void MenuBar::draw(sf::RenderWindow& window)
{
  //window.draw(m_menuBar);
	
	for (size_t i = 0; i < m_items.size(); i++)
	{
		m_items[i].draw(window);
	}
}