#ifndef H_MENUBAR_H
#define H_MENUBAR_H

#include <iostream>
#include "MenuButton.h"

class MenuBar : public MenuObject
{
public:
  MenuBar(sf::RenderWindow& window);
  virtual ~MenuBar();

  void draw(sf::RenderWindow& window);
  void addItem(std::string title, std::string iconPath, State state);
  State interact(sf::RenderWindow& window, State oldState);
  const int getBarWidth() const;

private:
  void defaultButtonsSetup();

  std::vector<MenuButton> m_buttons;

  float                   m_btnMaxX;
  float                   m_btnMinX;
  float                   m_btnMaxY;
  float                   m_btnMinY;
  int                     m_numItems;
  int                     m_barWidth;
};

#endif // !H_MENUBAR_H