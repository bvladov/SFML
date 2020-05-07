#ifndef H_PAINT_H
#define H_PAINT_H

#include "MenuBar.h"
#include "State.h"


class Paint {
  public:
    Paint(unsigned int height, unsigned int width, std::string windowTitle);
    ~Paint();

    void run();
    void setMenuBar(MenuBar& menuBar);

  private:
    sf::RenderWindow m_window;
    void putPixel(sf::Vector2i pos, sf::Color color, bool connect);
    void pencilLogic();
    void draw();
    float getDistance(const sf::RectangleShape& a, const sf::RectangleShape& b);

    std::vector<sf::RectangleShape> m_scene;
    std::string                     m_title;
    MenuBar*                        m_menuBar;
    State                           m_state;
    sf::Color                       m_drawColour;

};

#endif // !H_PAINT_H