#ifndef H_PAINT_H
#define H_PAINT_H

#include "SFML/Window/ContextSettings.hpp"
#include "MenuBar.h"
#include "State.h"

enum ButtonState {
  RELEASED = 0,
  PRESSED  = 1,
};

//Main entry point class for the application
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
    void fillLogic();
    void draw();
    void setMouseCursor();
    void resetMouseCursor();
    void updateCursorPos(int x, int y);

    sf::Image          m_image;
    sf::Texture        m_texture;
    sf::Sprite         m_sprite;
    std::string        m_title;
    MenuBar            m_menuBar;
    State              m_state;
    State              m_newState;
    sf::Color          m_drawColour;
    bool               m_connectPixels;
    bool               m_mouseLeftButtonState;
    sf::Vector2i       m_prevPixel;
    int                m_eraserSize;
    sf::RectangleShape m_mouse;
};

#endif // !H_PAINT_H