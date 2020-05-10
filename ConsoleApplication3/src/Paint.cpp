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
  //m_window.setFramerateLimit(144);
  m_state      = State::EMPTY_STATE;
  m_drawColour = sf::Color::Black;
  m_scene.reserve(height * width);
}

Paint::~Paint()
{
  m_window.close();
}

void Paint::run()
{
  while (m_window.isOpen())
  {
    m_window.clear(sf::Color::White);

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

    cout << (int)m_state << '\n';
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
  sf::RectangleShape pixel;
  pixel.setPosition(sf::Vector2f(pos));
  pixel.setFillColor(color);
  if (m_scene.empty() || m_connectPixels == false)
  {
    pixel.setSize({ 2,2 });
  }
  else
  {
    pixel.setSize({ getDistance(pixel, m_scene.back()), 2 });

    float angle = 180 - atan2(m_scene.back().getPosition().y - pixel.getPosition().y
                            , pixel.getPosition().x - m_scene.back().getPosition().x) * 180 / 3.1415 ;

    pixel.setRotation(angle);
  }

  m_scene.push_back(pixel);
}

float Paint::getDistance(const sf::RectangleShape& a, const sf::RectangleShape& b)
{
  return sqrt( (b.getPosition().x - a.getPosition().x) * (b.getPosition().x - a.getPosition().x)
             + (b.getPosition().y - a.getPosition().y) * (b.getPosition().y - a.getPosition().y));
}

void Paint::draw()
{
  for (size_t i = 0; i < m_scene.size(); i++)
  {
    m_window.draw(m_scene[i]);
  }
}

void Paint::drawLogic()
{
  if (m_mouseLeftButtonState == ButtonState::RELEASED || sf::Mouse::getPosition(m_window).x < m_menuBar.getBarWidth())
  {
    m_connectPixels = false;
  }

  if (sf::Mouse::getPosition(m_window).x > m_menuBar.getBarWidth()
   && sf::Mouse::isButtonPressed(sf::Mouse::Left)
   && sf::Mouse::getPosition(m_window).x != (m_scene.empty() ? -1 : m_scene.back().getPosition().x)
   && sf::Mouse::getPosition(m_window).y != (m_scene.empty() ? -1 : m_scene.back().getPosition().y))
  {
    putPixel(sf::Mouse::getPosition(m_window), m_drawColour);
    m_connectPixels = true;
  }
}

void Paint::eraseLogic()
{
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    for (auto& pixel : m_scene)
    {
      if (pixel.getPosition().x == sf::Mouse::getPosition(m_window).x
        && pixel.getPosition().y == sf::Mouse::getPosition(m_window).y)
      {
        cout << "erased" << endl;
        pixel.setFillColor(sf::Color::White);
      }
    }
  }
}
