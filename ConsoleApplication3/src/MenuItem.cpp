#include "MenuItem.h"
#include <assert.h>

MenuItem::MenuItem(std::string title, sf::Vector2f size, sf::Vector2f position, std::string iconPath, State state)
  : m_title(title), m_isClicked(false), m_isHovered(false),  m_scale(1)
{
  m_menuItem.setSize(size);
  m_menuItem.setPosition(position);
  m_icon = new sf::Texture();
  setIcon(iconPath);
  m_menuItem.setTexture(m_icon);
  m_state = state;
}

MenuItem& MenuItem::operator=(const MenuItem& other)
{
  if (this != &other)
  {
    copyFrom(other);
  }

  return *this;
}

MenuItem::MenuItem(const MenuItem& other)
{
  copyFrom(other);
}

void MenuItem::copyFrom(const MenuItem& other)
{
  m_icon      = other.m_icon;
  m_isClicked = other.m_isClicked;
  m_menuItem  = other.m_menuItem;
  m_title     = other.m_title;
  m_scale     = other.m_scale;
  m_state     = other.m_state;
}


MenuItem::~MenuItem()
{
  clearIcon();
}

void MenuItem::setIcon(std::string filename)
{
  assert(m_icon != nullptr);
  m_icon->loadFromFile(filename);
}

void MenuItem::clearIcon()
{

}

bool MenuItem::isClicked() const
{
  return m_isClicked;
}

bool MenuItem::isHovered() const
{
  return m_isHovered;
}

State MenuItem::interact(sf::Vector2i& mouseCoords)
{
  if (mouseCoords.x >= m_menuItem.getPosition().x &&
      mouseCoords.x <= m_menuItem.getPosition().x + m_menuItem.getSize().x &&
      mouseCoords.y >= m_menuItem.getPosition().y &&
      mouseCoords.y <= m_menuItem.getPosition().y + m_menuItem.getSize().y)
  {
    hover();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_isClicked)
    {
      click();
      return m_state;
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

  return State::UNCHANGED;
}

void MenuItem::setScale(float factor)
{
  m_scale = factor;
  if (m_scale > 1)  m_scale = 1;
  m_menuItem.setScale(m_scale, m_scale);
}

void MenuItem::hover()
{
  m_isHovered = true;
  m_menuItem.setOutlineThickness(2);
  m_menuItem.setOutlineColor(sf::Color::Black);
  m_menuItem.setFillColor(sf::Color::Cyan);
}

void MenuItem::click()
{
  m_isClicked = true;
  setScale(0.8f);
}

void MenuItem::unclick()
{
  if (m_isClicked)
  {
    std::cout << m_title << "::unclicking" << std::endl;
    m_isClicked = false;
    setScale(1 / m_scale);
  }
}

void MenuItem::reset()
{
  unclick();
  m_menuItem.setOutlineThickness(0);
  m_menuItem.setFillColor(sf::Color::White);
  m_isHovered = false;
}

void MenuItem::draw(sf::RenderWindow& window)
{
  window.draw(m_menuItem);
}