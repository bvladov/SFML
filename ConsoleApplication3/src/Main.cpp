#include <iostream>
#include <winsqlite/winsqlite3.h>
#include <string>
#include "Paint.h"
using namespace std;
#define WIDTH  1024
#define HEIGHT 1024



//void logic(sf::Event& event, sf::RenderWindow& window, vector<sf::RectangleShape>& scene)
//{
//    putPixel(sf::Vector2f(sf::Mouse::getPosition(window)), sf::Uint8(100), window, scene);
//}

int main()
{
  Paint paint(HEIGHT, WIDTH, "Paint");
  
  paint.run();

  return 0;
}