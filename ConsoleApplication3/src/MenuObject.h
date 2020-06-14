#ifndef H_MENUOBJECT_H
#define H_MENUOBJECT_H

#include "SFML/Graphics.hpp"
#include "State.h"

//Class that represents a square menu object
class MenuObject
{
public:
  MenuObject(sf::Vector2f size, sf::Vector2f position, State state, std::string title = "");
  MenuObject(const MenuObject& other);
  MenuObject& operator=(const MenuObject& other);
  virtual ~MenuObject();

  virtual State interact(sf::RenderWindow& window, State oldState) = 0;
  virtual void draw(sf::RenderWindow& window) = 0;
  virtual void clickLogic();
  virtual void unclickLogic();
  virtual void resetLogic();
  virtual void hoverLogic();
  sf::Vector2f getPosition() const;
  sf::Vector2f getSize()     const;
  State        getState()    const;

  std::string  m_title;
  bool         m_isClicked;
  bool         m_isHovered;

private:
  void copyFrom(const MenuObject& other);
  virtual void setScale(float factor);

  bool isClicked() const;
  bool isHovered() const;

  float              m_scale;
  State              m_state;

protected:
  sf::RectangleShape m_menuObject;
};

#endif // !H_MENUOBJECT_H
