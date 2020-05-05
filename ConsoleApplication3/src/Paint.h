#ifndef H_PAINT_H
#define H_PAINT_H

#include <SFML/Graphics.hpp>
#include "MenuBar.h"

class Paint {
  public:
    Paint(sf::Vector2f);
    ~Paint();

  protected:
    sf::RenderWindow m_window;


  private:
    void setMenuBar(MenuBar&);

  private:
    sf::Vector2f m_coords;
    std::string  m_title;
    MenuBar*     m_menuBar;
};

#endif // !H_PAINT_H