#include "Window.h"

Window::Window(const std::string title, int width, int height)
  : m_window(sf::VideoMode(width, height), title)
{
  m_title  = title;
  m_width  = width;
  m_height = height;
  createWindow();
}

Window::~Window()
{
  closeWindow();
}

void Window::createWindow()
{
  m_window.create({ m_width, m_height }, m_title);
}

void Window::closeWindow()
{
  m_window.close();
}

void Window::update()
{

}

void Window::draw(sf::Drawable& drawable)
{
  m_window.draw(drawable);
}