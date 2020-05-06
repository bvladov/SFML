#include "MenuBar.h"

MenuBar::MenuBar(sf::RenderWindow& window) : m_numItems(0)
{
  m_menuBar.setSize( { (float)window.getSize().x/15
                     , (float)window.getSize().y } );
  m_menuBar.setOutlineThickness(3);
  m_menuBar.setOutlineColor(sf::Color::Black);
  m_menuBar.setFillColor(sf::Color(100, 150, 255)); //Light blue-ish

  m_btnMaxX = (m_menuBar.getSize().x - m_menuBar.getOutlineThickness()) * 0.95f;
  m_btnMinX = (m_menuBar.getSize().x - m_menuBar.getOutlineThickness()) * 0.05f;
  m_btnMaxY =  m_menuBar.getSize().y * 0.98f;
  m_btnMinY =  m_menuBar.getSize().y * 0.02f;

  defaultSetup();
}

MenuBar::~MenuBar()
{

}

void MenuBar::defaultSetup()
{
  int x = m_menuBar.getSize().x;
  int y = m_menuBar.getSize().y;

  addItem("Cursor", "./texture/arrow.png" , State::MOUSE_CURSOR);
  addItem("Pencil", "./texture/pencil1.png", State::PENCIL);
  addItem("Line"  , "./texture/line.png"  , State::LINE);
}

void MenuBar::draw(sf::RenderWindow& window)
{
  window.draw(m_menuBar);
  
  for (size_t i = 0; i < m_items.size(); i++)
  {
    m_items[i].draw(window);
  }
}

void MenuBar::interact(sf::RenderWindow& window,  State& oldState)
{
  State newState;

  sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
  for (size_t i = 0; i < m_items.size(); i++)
  {
    newState = m_items[i].interact(mouseCoords);
    if (newState != State::UNCHANGED)
    {
      //std::cout << newState << std::endl;
      oldState = newState;
      return;
    }
  }

}

void MenuBar::addItem(std::string title, std::string iconPath, State state)
{
  float x = m_menuBar.getSize().x;
  float y = m_menuBar.getSize().y;

  MenuItem item(title
             , { x - m_btnMinX * 2 , y / 15}                            // size
             , { m_btnMinX         ,  m_btnMinY + m_numItems * y / 13 } // position
             , iconPath
             , state);

  m_items.push_back(item);
  ++m_numItems;
}
