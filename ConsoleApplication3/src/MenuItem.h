#ifndef H_MENUITEM_H
#define H_MENUIEM_H

#include <iostream>
#include <SFML/Graphics.hpp>

class MenuItem
{
public:
		MenuItem(std::string, sf::RenderWindow& window);
		MenuItem(const MenuItem&);
		MenuItem& operator=(const MenuItem&);
		~MenuItem();


		void setIcon(std::string);
		void clearIcon();
		bool isClicked() const;
		void draw(sf::RenderWindow&);

		void render();
		void run();

private:
		void init();

		sf::RenderWindow   sf_window;
		sf::Event          sf_event;
		sf::Texture        m_icon;

		bool               m_isClicked;
		std::string        m_title;
		sf::RectangleShape m_menuItem;
};

#endif // !H_MENUITEM_H