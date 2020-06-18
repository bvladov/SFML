#ifndef H_ALGORITHMS_H
#define H_ALGORITHMS_H

#include "SFML/Graphics.hpp"
#define squared(a) a*a

sf::Vector2f getRectangleCenter(const sf::RectangleShape& rect);
void BresenhamLine(sf::Vector2i a, sf::Vector2i b, sf::Color color, sf::Image& image);
float getDistance(const sf::RectangleShape& a, const sf::RectangleShape& b);
void floodFill(const sf::Vector2i pos, sf::Color color, sf::Image& image, sf::Vector2u lowBounds, sf::Vector2u highBounds);

#endif //!H_ALGORITHMS_H