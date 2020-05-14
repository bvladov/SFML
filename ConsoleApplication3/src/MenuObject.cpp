#include "MenuObject.h"

MenuObject::MenuObject(sf::Vector2f size, sf::Vector2f position, State state, std::string title)
  : m_title(title), m_isClicked(false), m_isHovered(false), m_scale(1)
{
  m_menuObject.setSize(size);
  m_menuObject.setOrigin(position);
  m_menuObject.setPosition(position);
  m_state = state;
}

MenuObject& MenuObject::operator=(const MenuObject& other)
{
  if (this != &other)
  {
    copyFrom(other);
  }

  return *this;
}

MenuObject::MenuObject(const MenuObject& other)
{
  copyFrom(other);
}

MenuObject::~MenuObject()
{

}

void MenuObject::copyFrom(const MenuObject& other)
{
  m_isClicked = other.m_isClicked;
  m_menuObject = other.m_menuObject;
  m_title = other.m_title;
  m_state = other.m_state;
}

void MenuObject::setScale(float factor)
{
  m_scale = factor;
  if (m_scale > 1)  m_scale = 1;
  m_menuObject.setScale(m_scale, m_scale);
}

void MenuObject::hoverLogic()
{
  m_isHovered = true;
  m_menuObject.setOutlineThickness(2);
  m_menuObject.setOutlineColor(sf::Color::Black);
  m_menuObject.setFillColor(sf::Color::Cyan);
}

bool MenuObject::isClicked() const
{
  return isHovered() && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool MenuObject::isHovered() const
{
  return sf::Mouse::getPosition().x >= m_menuObject.getPosition().x
      && sf::Mouse::getPosition().x <= m_menuObject.getPosition().x + m_menuObject.getSize().x 
      && sf::Mouse::getPosition().y >= m_menuObject.getPosition().y 
      && sf::Mouse::getPosition().y <= m_menuObject.getPosition().y + m_menuObject.getSize().y;
}

void MenuObject::clickLogic()
{
  m_isClicked = true;
  setScale(0.8f);
}

void MenuObject::unclickLogic()
{
  if (m_isClicked)
  {
    m_isClicked = false;
    setScale(1 / m_scale);
  }
}

void MenuObject::resetLogic()
{
  unclickLogic();
  m_menuObject.setOutlineThickness(0);
  m_menuObject.setFillColor(sf::Color::White);
  m_isHovered = false;
}

sf::Vector2f MenuObject::getPosition() const
{
  return { m_menuObject.getPosition().x - m_menuObject.getOrigin().x
         , m_menuObject.getPosition().y - m_menuObject.getOrigin().y };
}

sf::Vector2f MenuObject::getSize() const
{
  return m_menuObject.getSize();
}
State MenuObject::getState() const
{
  return m_state;
}
