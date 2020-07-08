#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const std::string title, PaintData* paintData)
  : m_window(sf::VideoMode(width, height), title)
  , m_paintData(paintData)
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
  m_window.setMouseCursorVisible(false);
  m_isOpen = true;
}

void Window::closeWindow()
{
  m_window.close();
  m_isOpen = false;
}

void Window::update()
{
  m_window.clear();

  sf::Event event;
  while (m_window.pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      closeWindow();
      break;
    case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        m_paintData->mouseLeftButtonState = ButtonState::PRESSED;
        if (sf::Mouse::getPosition(m_window).x > m_paintData->menuBar.getBarWidth())
        {
          m_paintData->isDrawing       = true;
          m_paintData->imageSnapshot   = m_paintData->image;
          m_paintData->lineStartCoords = m_paintData->prevLine = sf::Mouse::getPosition(m_window);
        }
        if (!m_paintData->isColorPicking && m_paintData->state == State::COLOR_PICKER)
        {
          m_paintData->isColorPicking = false;
          m_paintData->isColorPicked  = false;
          m_paintData->colorPicker.setSize({ 512,511 });
          m_paintData->colorPicker.setPosition(sf::Vector2f(getMouseCoords().x + 0.5, getMouseCoords().y + 0.5));
        }
      }
      break;
    case sf::Event::MouseButtonReleased:
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        m_paintData->mouseLeftButtonState = ButtonState::RELEASED;
        if (sf::Mouse::getPosition(m_window).x > m_paintData->menuBar.getBarWidth())
        {
          m_paintData->isDrawing = false;
          m_paintData->isColorPicked = false;
        }
      }
      if (m_paintData->state == State::COLOR_PICKER && !m_paintData->isColorPicking)
      {
        m_paintData->isColorPicking = true;
      }
      break;
    case sf::Event::MouseMoved:
      updateCursorPos(event.mouseMove.x, event.mouseMove.y);
      break;
    }
  }
}

void Window::updateCursorPos(int x, int y)
{
  switch (m_paintData->state)
  {
  case State::ERASE:
    m_paintData->mouse.setPosition(sf::Vector2f(x - m_paintData->eraserSize, y - m_paintData->eraserSize));
    break;
  case State::PENCIL:
    m_paintData->mouse.setPosition(sf::Vector2f(x, y - 32));
    break;
  default:
    m_paintData->mouse.setPosition(sf::Vector2f(x, y));
  }
}

void Window::draw(sf::Drawable& drawable)
{
  m_window.draw(drawable);
}

sf::RenderWindow& Window::getWindow()
{
  return m_window;
}

bool Window::isOpen()
{
  return m_isOpen;
}

void Window::display()
{
  m_window.display();
}

sf::Vector2u Window::getSize()
{
  return m_window.getSize();
}

sf::Vector2i Window::getPosition()
{
  return m_window.getPosition();
}

sf::Vector2i Window::getMouseCoords()
{
  return sf::Mouse::getPosition(m_window);
}