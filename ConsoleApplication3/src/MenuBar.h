#ifndef H_MENUBAR_H
#define H_MENUBAR_H

#include <iostream>
#include  "MenuItem.h"

class MenuBar
{
public:
  MenuBar(sf::RenderWindow& window);
  ~MenuBar();

  void draw(sf::RenderWindow& window);
  void addItem(std::string title, std::string iconPath, State state);
  void interact(sf::RenderWindow& window, State& oldState);

private:
  void defaultSetup();

private:
  sf::RectangleShape    m_menuBar;
  std::vector<MenuItem> m_items;
  int                   m_numItems;
  float                 m_btnMaxX;
  float                 m_btnMinX;
  float                 m_btnMaxY;
  float                 m_btnMinY;
};

#endif // !H_MENUBAR_H