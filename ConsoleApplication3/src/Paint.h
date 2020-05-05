#ifndef H_PAINT_H
#define H_PAINT_H

#include <SFML/Graphics.hpp>
#include "MenuBar.h"

class Paint {
  public:
    Paint(unsigned int, unsigned int, std::string);
    ~Paint();

    void run();
    void setMenuBar(MenuBar&);

  protected:
    sf::RenderWindow m_window;

     
  private:

  private:
    std::string  m_title;
    MenuBar*     m_menuBar;
};

#endif // !H_PAINT_H