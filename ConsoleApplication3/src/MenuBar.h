#ifndef H_MENUBAR_H
#define H_MENUBAR_H

#include <iostream>
#include  "MenuItem.h"

class MenuBar
{
public:
	MenuBar();
	~MenuBar();

	void draw();
	void addItem(std::string);


private:


private:
	sf::RectangleShape    m_menuBar;
	std::vector<MenuItem> m_items;
	int                   m_nbItems;
};

#endif // !H_MENUBAR_H