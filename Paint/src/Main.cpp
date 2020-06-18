#include <iostream>
#include <winsqlite/winsqlite3.h>
#include <string>
#include "Paint.h"

#define WIDTH  1000
#define HEIGHT 1000

int main()
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  Paint paint(WIDTH, HEIGHT, "Paint", settings);
  
  paint.run();

  return 0;
}