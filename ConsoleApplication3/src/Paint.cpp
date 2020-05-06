#include <assert.h>
#include "Paint.h"
#include "State.h"
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

void Paint::putPixel(sf::Vector2i pos, sf::Color color)
{
  sf::RectangleShape pixel;
  pixel.setSize({ 2,2 });
  pixel.setPosition(sf::Vector2f(pos));
  pixel.setFillColor(color);
  m_scene.push_back(pixel);
  std::cout << "New rectangle at (" << pos.x << "," << pos.y << ")" << std::endl;
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
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    putPixel(sf::Mouse::getPosition(m_window), m_drawColour);
  }

  draw();
}