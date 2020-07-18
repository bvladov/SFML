#ifndef H_PAINT_H
#define H_PAINT_H

#include "Window.h"
#include "PaintData.h"

//Main entry point class for the application
class Paint {
  public:
    Paint(unsigned int width
        , unsigned int height
        , std::string  windowTitle);
    ~Paint();

    sf::RenderWindow& getWindow();
    MenuBar*          getMenuBar();
    void              run();

  private:
    void putPixel(sf::Vector2i pos, sf::Color color);
    void pencilLogic();
    void lineLogic();
    void eraseLogic();
    void fillLogic();
    void colorPickLogic();
    void draw();
    void setMouseCursor();
    void resetMouseCursor();

    Window    m_window;
    PaintData m_data;
};

#endif // !H_PAINT_H