#include "MenuBar.h"

//TODO: improve button layout when resizing window
MenuBar::MenuBar(sf::Vector2f windowSize) : m_numItems(0),
  MenuObject({ windowSize.x / 15, windowSize.y }
           , { 0,0 }
           , State::EMPTY_STATE)
{
  m_menuObject.setOutlineThickness(3);
  m_menuObject.setOutlineColor(sf::Color::Black);
  m_menuObject.setFillColor(sf::Color(100, 150, 255)); //Light blue-ish

  m_btnMaxX = (m_menuObject.getSize().x - m_menuObject.getOutlineThickness()) * 0.95f;
  m_btnMinX = (m_menuObject.getSize().x - m_menuObject.getOutlineThickness()) * 0.05f;
  m_btnMaxY =  m_menuObject.getSize().y * 0.98f;
  m_btnMinY =  m_menuObject.getSize().y * 0.02f;

  m_barWidth = m_menuObject.getSize().x + m_menuObject.getOutlineThickness();

  defaultButtonsSetup();
}

MenuBar::~MenuBar()
{

}

//Add the default buttons
void MenuBar::defaultButtonsSetup()
{
  int x = m_menuObject.getSize().x;
  int y = m_menuObject.getSize().y;

  addItem("Cursor"      , State::MOUSE_CURSOR, "./texture/arrow.png");
  addItem("Pencil"      , State::PENCIL      , "./texture/pencil1.png");
  addItem("Line"        , State::LINE        , "./texture/line.png");
  addItem("Erase"       , State::ERASE       , "./texture/eraser.png");
  addItem("Fill"        , State::FILL        , "./texture/fill.png");
  addItem("ColorPicker" , State::COLOR_PICKER, "./texture/color_pick.png");
}

//Draw the menu bar first then draw all the buttons
void MenuBar::draw(sf::RenderWindow& window)
{
  window.draw(m_menuObject);
  
  for (size_t i = 0; i < m_buttons.size(); i++)
  {
    m_buttons[i].draw(window);
  }
}

//Calls interact method of each button to detect a change of state
State MenuBar::interact(sf::RenderWindow& window, State oldState)
{
  State newState;

  for (size_t i = 0; i < m_buttons.size(); i++)
  {
    newState = m_buttons[i].interact(window, oldState);
    if (newState != State::EMPTY_STATE)
    {
      return newState;
    }
  }
  return oldState;
}

//Adds a button to the menu bar
void MenuBar::addItem(std::string title, State state, std::string iconPath)
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