#include "Window.h"

Window::Window(unsigned int      width
             , unsigned int      height
             , const std::string title
             , PaintData*        paintData)
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

//Calls sf::RenderWindow::create to create a window and hides the default mouse cursor
//so that custom ones could be used
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

//Method to process window events
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
      std::cout << (m_paintData->state == State::COLOR_PICKER) << std::endl;
      std::cout << "isPicking: " << (m_paintData->isColorPicking) << std::endl;
      std::cout << "isPicked: "  << (m_paintData->isColorPicked) << std::endl;
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        m_paintData->mouseLeftButtonState = ButtonState::PRESSED;
        if (m_paintData->state == State::LINE)
        {
          //If the button was pressed in the drawing field
          if (sf::Mouse::getPosition(m_window).x > m_paintData->menuBar.getBarWidth())
          {
            m_paintData->isDrawing = true;
            //Save a snapshot of the current drawing and the starting cooordinates when the user starts drawing a line
            //Snapshot is needed to avoid creating a new line with each change of mouse coordinates
            m_paintData->imageSnapshot = m_paintData->image;
            m_paintData->lineStartCoords = m_paintData->prevLine = sf::Mouse::getPosition(m_window);
          }
        }
        if (m_paintData->state == State::COLOR_PICKER && !m_paintData->isColorPicking)
        {
          std::cout << "open color pick img " << std::endl;
          m_paintData->isColorPicking = true;
          m_paintData->isColorPicked  = false;
          //Size of colorPicker image
          m_paintData->colorPicker.setSize({ 512,511 });
          //Set the position right next to the mouse pointer soit doesnt detect the mouse press as if a color was picked
          m_paintData->colorPicker.setPosition(sf::Vector2f(getMouseCoords().x + 1, getMouseCoords().y + 1));
        }
      }
      break;
    case sf::Event::MouseButtonReleased:
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        m_paintData->mouseLeftButtonState = ButtonState::RELEASED;
        if (m_paintData->state == State::LINE)
        {
          //If the button was pressed in the drawing field
          if (sf::Mouse::getPosition(m_window).x > m_paintData->menuBar.getBarWidth())
          {
            m_paintData->isDrawing = false;
            //m_paintData->isColorPicked = false;
          }
        }
      }
      //if (m_paintData->state == State::COLOR_PICKER && m_paintData->isColorPicking)
      //{
      //  m_paintData->isColorPicking = false;
      //}
      break;
    case sf::Event::MouseMoved:
      //Move the custom cursor over the mouse's actual position
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
    //Set eraser's center is over the mouse's tip
    m_paintData->mouse.setPosition(sf::Vector2f(x - m_paintData->eraserSize, y - m_paintData->eraserSize));
    break;
  case State::PENCIL:
    //Offset y coordinate due to the position of the pencil tip in the pencil image
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

//Gets mouse coordinates relative to the window
sf::Vector2i Window::getMouseCoords()
{
  return sf::Mouse::getPosition(m_window);
}