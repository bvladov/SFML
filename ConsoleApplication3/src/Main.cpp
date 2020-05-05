#include <iostream>
#include <winsqlite/winsqlite3.h>
#include <string>
#include "MenuBar.h"
using namespace std;
#define WIDTH  800
#define HEIGHT 600

void putPixel(sf::Vector2f pos, sf::Uint8 color, sf::RenderWindow& window, vector<sf::RectangleShape>& scene)
{
  sf::RectangleShape pixel;
  pixel.setSize(sf::Vector2f(1,1));
  pixel.setPosition(pos);
  pixel.setFillColor(sf::Color::White);
  scene.push_back(pixel);
  cout << "New rectangle at (" << pos.x << "," << pos.y << ")" << endl;

}

void draw(sf::RenderWindow& window, vector<sf::RectangleShape>& scene)
{
  for (size_t i = 0; i < scene.size(); i++)
  {
    window.draw(scene[i]);
  }
}

void logic(sf::Event& event, sf::RenderWindow& window, vector<sf::RectangleShape>& scene)
{
    putPixel(sf::Vector2f(sf::Mouse::getPosition(window)), sf::Uint8(100), window, scene);
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Title");
  sf::Event event;
  sf::Texture texture;
  //int pixels[WIDTH][HEIGHT];
  //texture.create(WIDTH, HEIGHT);
  int x = 10;
  int y = 10;
  bool keyPressed = false;
  vector<sf::RectangleShape> scene;
  MenuBar bar(window);

  sf::RectangleShape m_menuItem;
  
	m_menuItem.setSize({ 50,50 });
	m_menuItem.setFillColor(sf::Color::White);

  while (window.isOpen())
  {
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        cout << "Closing\n";
        break;
      case sf::Event::MouseButtonPressed:
        keyPressed = true;
        cout << "KeyPressed\n";
        break;
      case sf::Event::MouseButtonReleased:
        keyPressed = false;
        cout << "KeyReleased\n";
        break;
      }

    }

    //if (keyPressed)
    //{
    //  logic(event, window, scene);
    //}
    window.clear();
    //draw(window, scene);
    //window.draw(m_menuItem);
    bar.draw(window);
    window.display();
  }

  return 0;
}