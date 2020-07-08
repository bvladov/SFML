#ifndef H_PAINT_H
#define H_PAINT_H

#include "Window.h"
#include "PaintData.h"

//Main entry point class for the application
class Paint {
  public:
    Paint(unsigned int width, unsigned int height, std::string windowTitle);
    ~Paint();

    void run();
    MenuBar*    getMenuBar();
    sf::RenderWindow& getWindow();

  private:
    //sf::RenderWindow m_window;
    Window m_window;
    void putPixel(sf::Vector2i pos, sf::Color color);
    void pencilLogic();
    void lineLogic();
    void eraseLogic();
    void fillLogic();
    void colorPickLogic();
    void draw();
    void setMouseCursor();
    void resetMouseCursor();
    void initData();

    PaintData m_data;

    //sf::Image          m_image;
    //sf::Image          m_imageSnapshot;
    //sf::Texture        m_texture;
    //sf::Sprite         m_sprite;
    //std::string        m_title;
    //MenuBar            m_menuBar;
    //State              m_state;
    //State              m_newState;
    //sf::Color          m_drawColour;
    //bool               m_connectPixels;
    //bool               m_mouseLeftButtonState;
    //sf::Vector2i       m_prevPixel;
    //int                m_eraserSize;
    //sf::RectangleShape m_mouse;
    //bool               m_isDrawing;
    //sf::Vector2i       m_lineStartCoords;
    //sf::Vector2i       m_prevLine;
    //sf::RectangleShape m_colorPicker;
    //sf::Image          m_pickerImage;
    //sf::Texture        m_pickerTexture;
    //bool               m_isColorPicking;
    //bool               m_isColorPicked;
};

#endif // !H_PAINT_H