#ifndef H_MENUBAR_H
#define H_MENUBAR_H

#include <iostream>
#include  "MenuItem.h"

class MenuBar
{
public:
	MenuBar();
	~MenuBar();

	void draw(sf::RenderWindow&);
	void addItem(std::string, sf::Vector2f);


private:


private:
	sf::RectangleShape    m_menuBar;
	std::vector<MenuItem> m_items;
	int                   m_nbItems;
};

#endif // !H_MENUBAR_H