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
  m_btnMaxY = m_menuBar.getSize().y * 0.98f;
  m_btnMinY = m_menuBar.getSize().y * 0.02f;

  defaultSetup();
}

MenuBar::~MenuBar()
{

}

void MenuBar::defaultSetup()
{
  int x = m_menuBar.getSize().x;
  int y = m_menuBar.getSize().y;

  addItem("Arrow",  "./texture/arrow.png");
  addItem("Line",   "./texture/line.png");
  addItem("Pencil", "./texture/pencil.png");
}

void MenuBar::draw(sf::RenderWindow& window)
{
  window.draw(m_menuBar);
  
  for (size_t i = 0; i < m_items.size(); i++)
  {
    m_items[i].draw(window);
  }
}

void MenuBar::interact(sf::RenderWindow& window)
{
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
  for (size_t i = 0; i < m_items.size(); i++)
  {
    m_items[i].interact(mouseCoords);
  }
}

void MenuBar::addItem(std::string title, std::string iconPath)
{
  float x = m_menuBar.getSize().x;
  float y = m_menuBar.getSize().y;

  MenuItem item(title
             , { x - m_btnMinX * 2 , y / 15}                            // size
             , { m_btnMinX         ,  m_btnMinY + m_numItems * y / 13 } // position
             , iconPath);

  m_items.push_back(item);
  ++m_numItems;
}
