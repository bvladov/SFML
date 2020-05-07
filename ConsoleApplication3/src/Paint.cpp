#include <assert.h>
#include "Paint.h"
#include "State.h"

#define DELTA 60

using std::cout;
using std::endl;

Paint::Paint(unsigned int height, unsigned int width, std::string windowTitle)
  : m_window(sf::VideoMode(width,  height), windowTitle)
  , m_menuBar(new MenuBar(m_window))
{
  //m_window.setFramerateLimit(144);
  m_title      = windowTitle;
  m_state      = State::MOUSE_CURSOR;
  m_drawColour = sf::Color::Black;
  m_scene.reserve(height * width);
}

Paint::~Paint()
{
  delete m_menuBar;
  m_window.close();
}

void Paint::run()
{
  while (m_window.isOpen())
  {
    sf::Event event;
    m_window.clear(sf::Color::White);
    while (m_window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        m_window.close();
        cout << "Closing\n";
        break;
      }
    }
    
    m_menuBar->interact(m_window, m_state);
    switch (m_state)
    {
    case State::MOUSE_CURSOR:
      break;
    case State::PENCIL:
      pencilLogic();
      break;
    case State::LINE:
      break;
    }

    m_menuBar->draw(m_window);
    m_window.display();
  }
}

void Paint::setMenuBar(MenuBar& menuBar)
{
  delete m_menuBar;
  m_menuBar = nullptr;
  m_menuBar = &menuBar;
}

void Paint::putPixel(sf::Vector2i pos, sf::Color color, bool connect)
{
  sf::RectangleShape pixel;
  pixel.setPosition(sf::Vector2f(pos));
  pixel.setFillColor(color);
  if (m_scene.empty())
  {
    pixel.setSize({ 2,2 });
  }
  else
  {
    pixel.setSize({ getDistance(pixel, m_scene.back()), 2 });

    float angle = 180 - atan2(m_scene.back().getPosition().y - pixel.getPosition().y
                            , pixel.getPosition().x - m_scene.back().getPosition().x) * 180 / 3.1415 ;
    cout << "angle = " << -angle << endl;

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

void Paint::pencilLogic()
{
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
   && sf::Mouse::getPosition(m_window).x > m_menuBar->getBarWidth()
   && sf::Mouse::getPosition(m_window).x != (m_scene.empty() ? -1 : m_scene.back().getPosition().x) 
   && sf::Mouse::getPosition(m_window).y != (m_scene.empty() ? -1 : m_scene.back().getPosition().y))
  {
    putPixel(sf::Mouse::getPosition(m_window), m_drawColour, true);
  }

  draw();
}