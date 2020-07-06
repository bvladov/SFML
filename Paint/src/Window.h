#ifndef H_WINDOW_H
#define H_WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

class Window
{
public:
  Window(const std::string title, int width, int height);
  ~Window();

  void update();
  void draw(sf::Drawable& drawable);

private:
  void createWindow();
  void closeWindow();

  sf::RenderWindow m_window;
  std::string      m_title;
  int m_width;
  int m_height;
};

#endif // !H_WINDOW_H
