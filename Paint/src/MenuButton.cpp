#include "MenuButton.h"
#include "Algorithms.h"
#include <assert.h>

MenuButton::MenuButton(sf::Vector2f size
                     , sf::Vector2f position
                     , State        state
                     , std::string  iconPath
                     , std::string  title)
  : MenuObject(size, position, state, title), m_icon(std::make_shared<sf::Texture>())
{
  setIcon(iconPath);
  m_menuObject.setTexture(m_icon.get());
  m_menuObject.setOrigin(getRectangleCenter(m_menuObject));
  m_menuObject.setPosition(m_menuObject.getOrigin().x  + position.x
                         , m_menuObject.getOrigin().y  + position.y);
}

MenuButton::MenuButton(const MenuButton& other) : MenuObject(other)
{
  m_icon = other.m_icon;
}

MenuButton::~MenuButton()
{

}

void MenuButton::setIcon(std::string filename)
{
  m_icon->loadFromFile(filename);
}

//Detect if the button is hovered or pressed and return a new state
State MenuButton::interact(sf::RenderWindow& window, State oldState)
{
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);

  //if mouse is over the button
  if (mouseCoords.x >= getPosition().x &&
      mouseCoords.x <= getPosition().x + getSize().x &&
      mouseCoords.y >= getPosition().y &&
      mouseCoords.y <= getPosition().y + getSize().y)
  {
    hover();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_isClicked)
    {
      click();
      return getState();
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      unclick();
    }
  }
  else
  {
    reset();
  }

  return State::EMPTY_STATE;
}

//Draw the button to the window
void MenuButton::draw(sf::RenderWindow& window)
{
  window.draw(m_menuObject);
}