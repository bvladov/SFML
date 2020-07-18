#ifndef H_WINDOW_H
#define H_WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "PaintData.h"

//Wrapper class around sf::Renderwindow
class Window
{
public:
  Window(unsigned int      width
       , unsigned int      height
       , const std::string title
       , struct PaintData* paintData);
  ~Window();

  bool isOpen();
  void update();
  void display();
  void draw(sf::Drawable& drawable);
  sf::RenderWindow& getWindow();
  sf::Vector2u      getSize();
  sf::Vector2i      getPosition();
  sf::Vector2i      getMouseCoords();

private:
  void createWindow();
  void closeWindow();
  void updateCursorPos(int x, int y);

  sf::RenderWindow  m_window;
  struct PaintData* m_paintData;
  std::string       m_title;
  unsigned int      m_width;
  unsigned int      m_height;
  bool              m_isOpen;
};

#endif // !H_WINDOW_H
