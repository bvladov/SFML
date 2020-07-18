#include <iostream>
#include <string>
#include "Paint.h"

#define WIDTH  1000
#define HEIGHT 1000

int main()
{
  Paint paint(WIDTH, HEIGHT, "Paint");
  
  paint.run();

  return 0;
}