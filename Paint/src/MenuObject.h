#ifndef H_MENUOBJECT_H
#define H_MENUOBJECT_H

#include "SFML/Graphics.hpp"
#include "State.h"

//Abstract class to represent a square menu object
class MenuObject
{
public:
  MenuObject(sf::Vector2f size
           , sf::Vector2f position
           , State        state
           , std::string  title = "");
  MenuObject(const MenuObject& other);
  MenuObject& operator=(const MenuObject& other);
  virtual ~MenuObject();

  virtual State interact(sf::RenderWindow& window, State oldState) = 0;
  virtual void  draw(sf::RenderWindow& window) = 0;
  virtual void  click();
  virtual void  unclick();
  virtual void  reset();
  virtual void  hover();
  sf::Vector2f  getPosition() const;
  sf::Vector2f  getSize()     const;
  State         getState()    const;

  std::string   m_title;
  bool          m_isClicked;
  bool          m_isHovered;

private:
  virtual void setScale(float factor);
  void         copyFrom(const MenuObject& other);

  bool         isClicked() const;
  bool         isHovered() const;

  float        m_scale;
  State        m_state;

protected:
  sf::RectangleShape m_menuObject;
};

#endif // !H_MENUOBJECT_H
