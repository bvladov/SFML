#include "MenuItem.h"
#include <assert.h>

MenuItem::MenuItem(std::string title, sf::Vector2f size, sf::Vector2f position, std::string iconPath)
  : m_title(title), m_isClicked(false), m_isHovered(false),  m_scale(1)
{
  m_menuItem.setSize(size);
  m_menuItem.setPosition(position);
  m_icon = new sf::Texture();
  setIcon(iconPath);
  m_menuItem.setTexture(m_icon);
}

MenuItem& MenuItem::operator=(const MenuItem& other)
{
  if (this != &other)
  {
    m_icon = other.m_icon;
    m_isClicked = other.m_isClicked;
    m_menuItem = other.m_menuItem;
    m_title = other.m_title;
    m_scale = other.m_scale;
  }

  return *this;
}

MenuItem::MenuItem(const MenuItem& other)
{
  m_icon      = other.m_icon;
  m_isClicked = other.m_isClicked;
  m_menuItem  = other.m_menuItem;
  m_title     = other.m_title;
  m_scale     = other.m_scale;
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

void MenuItem::interact(sf::Vector2i& mouseCoords)
{
  if (mouseCoords.x >= m_menuItem.getPosition().x &&
      mouseCoords.x <= m_menuItem.getPosition().x + m_menuItem.getSize().x &&
      mouseCoords.y >= m_menuItem.getPosition().y &&
      mouseCoords.y <= m_menuItem.getPosition().y + m_menuItem.getSize().y)
  {
    std::cout << m_scale << '\n';
    hover();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_isClicked)
    {
      std::cout << "clicking" << std::endl;
      click();
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
  m_isHovered = false;
}

void MenuItem::draw(sf::RenderWindow& window)
{
  window.draw(m_menuItem);
}