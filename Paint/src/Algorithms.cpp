#include <queue>
#include  "Algorithms.h"

sf::Vector2f getRectangleCenter(const sf::RectangleShape& rect)
{
  return { rect.getPosition().x - rect.getOrigin().x + rect.getSize().x / 2
         , rect.getPosition().y - rect.getOrigin().y + rect.getSize().y / 2 };
}

void BresenhamLine(sf::Vector2i a, sf::Vector2i b, sf::Color color, sf::Image& image)
{
  int x1 = a.x;
  int x2 = b.x;
  int y1 = a.y;
  int y2 = b.y;
  int dx = fabs(x1 - x2);
  int dy = fabs(y1 - y2);

  bool reverse = dx < dy;

  int d;
  if (reverse)
  {
    d = x1;
    x1 = y1;
    y1 = d;

    d = x2;
    x2 = y2;
    y2 = d;

    d = dx;
    dx = dy;
    dy = d;
  }

  int incUp = -2 * dx + 2 * dy;
  int incDN = 2 * dy;

  int incx = x1 <= x2 ? 1 : -1;
  int incy = y1 <= y2 ? 1 : -1;
  d = -dx + 2 * dy;
  int x = x1;
  int y = y1;
  int n = dx + 1;
  while (n--)
  {
    if (reverse)
    {
      image.setPixel(y, x, color);
    }
    else
    {
      image.setPixel(x, y, color);
    }

    x = x + incx;
    if (d > 0)
    {
      d = d + incUp;
      y = y + incy;
    }
    else
    {
      d = d + incDN;
    }
  }
}

//Distance between 2 points represented as rectangles
float getDistance(const sf::RectangleShape& a, const sf::RectangleShape& b)
{
  return sqrt(squared(b.getPosition().x - a.getPosition().x)
            + squared(b.getPosition().y - a.getPosition().y));
}

void floodFill(const sf::Vector2i pos, sf::Color color, sf::Image& image, sf::Vector2u lowBounds, sf::Vector2u highBounds)
{
  std::queue<sf::Vector2i> q;
  q.push({ pos.x, pos.y });
  sf::Vector2i top;
  while (!q.empty())
  {
    top = q.front();
    q.pop();
    if (lowBounds.x <= top.x
     && lowBounds.y <= top.y
     && top.x < highBounds.x
     && top.y < highBounds.y
     && image.getPixel(top.x, top.y) != color)
    {
      image.setPixel(top.x, top.y, color);
      q.push({ top.x - 1, top.y });
      q.push({ top.x + 1, top.y });
      q.push({ top.x, top.y - 1 });
      q.push({ top.x, top.y + 1 });
    }
  }
}