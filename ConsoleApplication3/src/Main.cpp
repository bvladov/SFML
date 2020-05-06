#include <iostream>
#include <winsqlite/winsqlite3.h>
#include <string>
#include "Paint.h"
using namespace std;
#define WIDTH  1024
#define HEIGHT 768

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
  Paint paint(HEIGHT, WIDTH, "Paint");
  
  paint.run();

  return 0;
}