#include <assert.h>
#include "Paint.h"
#include "Algorithms.h"

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
  m_newState   = State::MOUSE_CURSOR;
  m_drawColour = sf::Color::Black;
  m_sprite.setOrigin({ (float)m_menuBar.getBarWidth(), 0 });
  m_sprite.setPosition({ (float)m_menuBar.getBarWidth(), 0 });
  m_mouse.setSize(sf::Vector2f(0, 0)); 
  m_eraserSize = 20;
  m_window.setMouseCursorVisible(false);
  //m_window.setFramerateLimit(144);
}

Paint::~Paint()
{
  m_window.close();
}

void Paint::run()
{
  setMouseCursor();

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
        case sf::Event::MouseMoved:
          updateCursorPos(event.mouseMove.x, event.mouseMove.y);
          break;
      }
    }

    switch (m_state)
    {
    case State::PENCIL:
      drawLogic();
      break;
    case State::LINE:
      //m_connectPixels = true;
      break;
    case State::ERASE:
      eraseLogic();
      break;
    case State::FILL:
      fillLogic();
      break;
    default://State::MOUSE_CURSOR
      break;
    }
    draw();
    m_newState = m_menuBar.interact(m_window, m_state);
    if (m_newState != m_state)
    {
      setMouseCursor();
    }

    m_state = m_newState;

    m_menuBar.draw(m_window);
    m_window.display();
  }
}

void Paint::putPixel(sf::Vector2i pos, sf::Color color)
{
  if (m_connectPixels == false)
  {
    m_image.setPixel(pos.x, pos.y, color);
  }
  else
  {
    BresenhamLine(pos, m_prevPixel, color, m_image);
  }
  m_prevPixel = pos;
}

void Paint::resetMouseCursor()
{
  m_mouse.setTexture(nullptr);
  m_mouse.setSize(sf::Vector2f(0, 0));
  m_mouse.setOutlineThickness(0);
}

void Paint::updateCursorPos(int x, int y)
{
  switch (m_state)
  {
  case State::ERASE:
    m_mouse.setPosition(sf::Vector2f(x - m_eraserSize, y - m_eraserSize));
    break;
  case State::PENCIL:
    m_mouse.setPosition(sf::Vector2f(x, y - 32));
    break;
  default:
    m_mouse.setPosition(sf::Vector2f(x, y));
  }
}

void Paint::setMouseCursor()
{
  resetMouseCursor();
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(m_window);

  switch (m_newState)
  {
  case State::PENCIL:
  {
    sf::Texture* icon = new sf::Texture;
    icon->loadFromFile(std::string("./texture/cursor_pencil.png"));
    icon->setSmooth(true);
    m_mouse.setSize(sf::Vector2f(32, 32));
    cout << m_mouse.getSize().x << ' ' << m_mouse.getSize().y << "\n";
    m_mouse.setTexture(icon);
    break;
  }
  case State::LINE:
    break;
  case State::ERASE:
  {
    m_mouse.setSize(sf::Vector2f(m_eraserSize * 2, m_eraserSize * 2));
    m_mouse.setOutlineThickness(1);
    m_mouse.setOutlineColor(m_drawColour);
    m_mouse.setFillColor(sf::Color::White);
    break;
  }
  case State::FILL:
  {
    sf::Texture* icon = new sf::Texture;
    icon->loadFromFile(std::string("./texture/cursor_fill.png"));
    icon->setSmooth(true);
    m_mouse.setSize(sf::Vector2f(32, 32));
    cout << m_mouse.getSize().x << ' ' << m_mouse.getSize().y << "\n";
    m_mouse.setTexture(icon);
    break;
  }
  default:
  {
    sf::Texture* icon = new sf::Texture;
    icon->loadFromFile(std::string("./texture/cursor_arrow.png"));
    icon->setSmooth(true);
    m_mouse.setSize(sf::Vector2f(32, 32));
    cout << m_mouse.getSize().x << ' ' << m_mouse.getSize().y << "\n";
    m_mouse.setTexture(icon);
    break;
  }
  }
}

void Paint::draw()
{
  m_texture.loadFromImage(m_image);
  m_sprite.setTexture(m_texture);
  m_window.draw(m_sprite);
  m_window.draw(m_mouse);
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
   && (mouseCoords.x != m_prevPixel.x
   || mouseCoords.y != m_prevPixel.y))
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

void Paint::fillLogic()
{
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(m_window);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    cout << m_window.getPosition().x + m_menuBar.getBarWidth() << endl;
    cout << mouseCoords.x << endl;
    floodFill(mouseCoords
      , m_drawColour
      , m_image
      , sf::Vector2u(m_menuBar.getBarWidth(), 0)
      , { m_window.getSize().x, m_window.getSize().y });
  }
}