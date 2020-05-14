#include "MenuBar.h"

MenuBar::MenuBar(sf::RenderWindow& window) : m_numItems(0),
  MenuObject({ (float)window.getSize().x / 15, (float)window.getSize().y }
           , { 0,0 }
           , State::EMPTY_STATE)
{
  m_menuObject.setOutlineThickness(3);
  m_menuObject.setOutlineColor(sf::Color::Black);
  m_menuObject.setFillColor(sf::Color(100, 150, 255)); //Light blue-ish

  m_btnMaxX = (m_menuObject.getSize().x - m_menuObject.getOutlineThickness()) * 0.95f;
  m_btnMinX = (m_menuObject.getSize().x - m_menuObject.getOutlineThickness()) * 0.05f;
  m_btnMaxY = m_menuObject.getSize().y * 0.98f;
  m_btnMinY =  m_menuObject.getSize().y * 0.02f;

  m_barWidth = m_menuObject.getSize().x + m_menuObject.getOutlineThickness();

  defaultButtonsSetup();
}

MenuBar::~MenuBar()
{

}

void MenuBar::defaultButtonsSetup()
{
  int x = m_menuObject.getSize().x;
  int y = m_menuObject.getSize().y;

  addItem("Cursor", "./texture/arrow.png"  , State::MOUSE_CURSOR);
  addItem("Pencil", "./texture/pencil1.png", State::PENCIL);
  addItem("Line"  , "./texture/line.png"   , State::LINE);
  addItem("Erase" , "./texture/eraser.png" , State::ERASE);
  addItem("Fill" , "./texture/fill.png"    , State::FILL);
}

void MenuBar::draw(sf::RenderWindow& window)
{
  window.draw(m_menuObject);
  
  for (size_t i = 0; i < m_buttons.size(); i++)
  {
    m_buttons[i].draw(window);
  }
}

State MenuBar::interact(sf::RenderWindow& window, State oldState)
{
  State newState;

  for (size_t i = 0; i < m_buttons.size(); i++)
  {
    newState = m_buttons[i].interact(window, oldState);
    //std::cout << (int)newState << std::endl;
    if (newState != State::EMPTY_STATE)
    {
      return newState;
    }
  }
  return oldState;
}

void MenuBar::addItem(std::string title, std::string iconPath, State state)
{
  float x = m_menuObject.getSize().x;
  float y = m_menuObject.getSize().y;

  MenuButton button({ x - m_btnMinX * 2 , y / 15}                            // size
                  , { m_btnMinX         ,  m_btnMinY + m_numItems * y / 13 } // position
                  , state
                  , iconPath
                  , title);

  m_buttons.push_back(button);
  ++m_numItems;
}

const int MenuBar::getBarWidth() const
{
  return m_barWidth;
}