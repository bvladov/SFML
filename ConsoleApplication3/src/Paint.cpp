#include "Paint.h"
#include <assert.h>
using std::cout;
using std::endl;

Paint::Paint(unsigned int height, unsigned int width, std::string windowTitle)
  : m_window(sf::VideoMode(width,  height), windowTitle)
  , m_menuBar(new MenuBar(m_window))
{
  m_title = windowTitle;
  m_window.setFramerateLimit(60);
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
    while (m_window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        m_window.close();
        cout << "Closing\n";
        break;
      case sf::Event::MouseButtonPressed:
        //keyPressed = true;
        cout << "KeyPressed\n";
        break;
      case sf::Event::MouseButtonReleased:
        //keyPressed = false;
        cout << "KeyReleased\n";
        break;
      }

    }

    m_window.clear(sf::Color::White);
    //draw(window, scene);
    //window.draw(m_menuItem);
    m_menuBar->interact(m_window);
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
