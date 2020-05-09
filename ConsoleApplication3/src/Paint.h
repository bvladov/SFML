#ifndef H_PAINT_H
#define H_PAINT_H

#include "SFML/Window/ContextSettings.hpp"
#include "MenuBar.h"
#include "State.h"

enum ButtonState {
  PRESSED  = 0,
  RELEASED = 1
};

class Paint {
  public:
    Paint(unsigned int width, unsigned int height, std::string windowTitle, sf::ContextSettings settings = sf::ContextSettings());
    ~Paint();

    void run();
    void setMenuBar(MenuBar& menuBar);

  private:
    sf::RenderWindow m_window;
    void putPixel(sf::Vector2i pos, sf::Color color);
    void drawLogic();
    void eraseLogic();
    void draw();
    float getDistance(const sf::RectangleShape& a, const sf::RectangleShape& b);

    std::vector<sf::RectangleShape> m_scene;
    std::string                     m_title;
    MenuBar*                        m_menuBar;
    State                           m_state;
    sf::Color                       m_drawColour;
    bool                            m_connectPixels;
    bool                            m_mouseLeftButtonState;
};

#endif // !H_PAINT_H