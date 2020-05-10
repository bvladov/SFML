#ifndef H_MENUBUTTON_H
#define H_MENUBUTTON_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "MenuObject.h"
#include "State.h"

class MenuButton : public MenuObject
{
public:
    MenuButton(sf::Vector2f size, sf::Vector2f position, State state, std::string iconPath, std::string title = "");
    MenuButton(const MenuButton& other);
    virtual ~MenuButton();

    void setIcon(std::string filename);
    void clearIcon();
    virtual State interact(sf::RenderWindow& window, State oldState);
    virtual void draw(sf::RenderWindow& window);

private:
    std::shared_ptr<sf::Texture> m_icon;
};

#endif // !H_MENUBUTTON_H