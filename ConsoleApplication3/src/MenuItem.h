#ifndef H_MENUITEM_H
#define H_MENUIEM_H

#include <iostream>
#include <SFML/Graphics.hpp>

class MenuItem
{
public:
    MenuItem(std::string title, sf::Vector2f size, sf::Vector2f position, std::string iconPath);
    MenuItem(const MenuItem&);
    MenuItem& operator=(const MenuItem& other);
    ~MenuItem();

    void setIcon(std::string filename);
    void clearIcon();
    void draw(sf::RenderWindow& window);
    void interact(sf::Vector2i& mouseCoords);

    sf::RectangleShape m_menuItem;

private:
    bool isClicked() const;
    bool isHovered() const;

    void setScale(float factor);
    void hover();
    void click();
    void unclick();
    void reset();

    sf::RenderWindow   sf_window;
    sf::Event          sf_event;
    sf::Texture*       m_icon;

    bool               m_isClicked;
    bool               m_isHovered;
    std::string        m_title;
    float              m_scale;
};

#endif // !H_MENUITEM_H