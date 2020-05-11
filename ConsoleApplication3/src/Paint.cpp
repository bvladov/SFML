#include <assert.h>
#include "Paint.h"
#include "State.h"

#define DELTA 60

using std::cout;
using std::endl;

Paint::Paint(unsigned int width, unsigned int height, std::string windowTitle, sf::ContextSettings settings)
  : m_window(sf::VideoMode(width,height), windowTitle, sf::Style::Default, settings)
  , m_connectPixels(false)
  , m_menuBar(m_window)
  , m_title(windowTitle)
  , m_mouseLeftButtonState(ButtonState::RELEASED)
{
  m_image.create(width, height, sf::Color::White);
  m_state      = State::EMPTY_STATE;
  m_drawColour = sf::Color::Black;
  m_sprite.setOrigin({ (float)m_menuBar.getBarWidth(), 0 });
  m_sprite.setPosition({ (float)m_menuBar.getBarWidth(), 0 });
  //m_sprite.setTextureRect({ m_menuBar.getBarWidth(),0, (int)width, (int)height });
  //m_window.setFramerateLimit(144);
  m_eraserSize = 20;
}

Paint::~Paint()
{
  m_window.close();
}

void Paint::run()
{
  while (m_window.isOpen())
  {
    m_window.clear();

    sf::Event event;
    while (m_window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          m_window.close();
          cout << "Closing\n";
          break;
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left)
          {
            m_mouseLeftButtonState = ButtonState::PRESSED;
          }
          break;
        case sf::Event::MouseButtonReleased:
          if (event.mouseButton.button == sf::Mouse::Left)
          {
            m_mouseLeftButtonState = ButtonState::RELEASED;
          }
          break;
      }
    }

    switch (m_state)
    {
    case State::MOUSE_CURSOR:
      break;
    case State::PENCIL:

      drawLogic();
      break;
    case State::LINE:
      //m_connectPixels = true;
      break;
    case State::ERASE:
      eraseLogic();
      break;
    }
    draw();

    m_state = m_menuBar.interact(m_window, m_state);
    m_menuBar.draw(m_window);
    m_window.display();
  }
}

void Paint::setMenuBar(MenuBar& menuBar)
{

}

void Paint::putPixel(sf::Vector2i pos, sf::Color color)
{
  if (m_connectPixels == false)
  {
    m_image.setPixel(pos.x, pos.y, color);
  }
  else
  {
    BresenhamLine(pos, m_prevPixel, color);
  }
  m_prevPixel = pos;
}

float Paint::getDistance(const sf::RectangleShape& a, const sf::RectangleShape& b)
{
  return sqrt( (b.getPosition().x - a.getPosition().x) * (b.getPosition().x - a.getPosition().x)
             + (b.getPosition().y - a.getPosition().y) * (b.getPosition().y - a.getPosition().y));
}

void Paint::draw()
{
  m_texture.loadFromImage(m_image);
  m_sprite.setTexture(m_texture);
  m_window.draw(m_sprite);
}

void Paint::drawLogic()
{
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(m_window);

  if (m_mouseLeftButtonState == ButtonState::RELEASED 
   || mouseCoords.x < m_menuBar.getBarWidth()
   || mouseCoords.x >= m_window.getSize().x
   || mouseCoords.y >= m_window.getSize().y)
  {
    m_connectPixels = false;
  }

   if(sf::Mouse::isButtonPressed(sf::Mouse::Left)
   && mouseCoords.x < m_window.getSize().x
   && mouseCoords.y < m_window.getSize().y
   && mouseCoords.x > m_menuBar.getBarWidth()
   && mouseCoords.x != m_prevPixel.x
   && mouseCoords.y != m_prevPixel.y)
  {
    putPixel(mouseCoords, m_drawColour);
    m_connectPixels = true;
  }
}

void Paint::eraseLogic()
{
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(m_window);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
      && mouseCoords.x < (m_window.getSize().x - m_eraserSize) && mouseCoords.x > m_eraserSize
      && mouseCoords.y < (m_window.getSize().y - m_eraserSize) && mouseCoords.y > m_eraserSize
      && mouseCoords.x >= (m_menuBar.getBarWidth() + m_eraserSize))
      //&& mouseCoords.x != m_prevPixel.x
      //&& mouseCoords.y != m_prevPixel.y)
  {
    for (int i = -m_eraserSize; i <= m_eraserSize; i++)
    {
      for (int j = -m_eraserSize; j <= m_eraserSize; j++)
      {
        if (m_image.getPixel(mouseCoords.x + i, mouseCoords.y + j) == m_drawColour)
        {
          m_image.setPixel(mouseCoords.x + i, mouseCoords.y + j, sf::Color::White);
        }
      }
    }
  }
}

void Paint::BresenhamLine(sf::Vector2i a, sf::Vector2i b, sf::Color color)
{
  int x1 = a.x;
  int x2 = b.x;
  int y1 = a.y;
  int y2 = b.y;
  int dx = fabs(x1 - x2);
  int dy = fabs(y1 - y2);

  bool reverse = dx < dy;

  int d;
  if (reverse)
  {
    d  = x1;
    x1 = y1;
    y1 = d;
    
    d  = x2;
    x2 = y2;
    y2 = d;

    d  = dx;
    dx = dy;
    dy = d;
  }

  int incUp = -2 * dx + 2 * dy;
  int incDN = 2 * dy;

  int incx = x1 <= x2 ? 1 : -1;
  int incy = y1 <= y2 ? 1 : -1;
  d = -dx + 2 * dy;
  int x = x1;
  int y = y1;
  int n = dx + 1;
  while (n--)
  {
    if (reverse)
    {
      m_image.setPixel(y, x, color);
    }
    else
    {
      m_image.setPixel(x, y, color);
    }

    x = x + incx;
    if (d > 0)
    {
      d = d + incUp;
      y = y + incy;
    }
    else
    {
      d = d + incDN;
    }
  }
}