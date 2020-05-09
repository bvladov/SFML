#include <iostream>
#include <winsqlite/winsqlite3.h>
#include <string>
#include "Paint.h"
using namespace std;
#define WIDTH  900
#define HEIGHT 900

int main()
{
  Paint paint(HEIGHT, WIDTH, "Paint");
  
  paint.run();

  return 0;
}