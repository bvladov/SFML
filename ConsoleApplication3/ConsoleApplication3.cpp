#include <iostream>
#include <winsqlite/winsqlite3.h>
#include <string>
#include "MenuItem.h"
using namespace std;
#define WIDTH  800
#define HEIGHT 600

void putPixel(sf::Vector2f pos, sf::Uint8 color, sf::RenderWindow& window)
{
    sf::RectangleShape pixel;
    pixel.setSize(sf::Vector2f(1,1));
    pixel.setPosition(pos);
    pixel.setFillColor(sf::Color::White);
    window.draw(pixel);
    cout << "New rectangle at (" << pos.x << "," << pos.y << ")" << endl;
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

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                cout << "Closing" << endl;
                break;
            case sf::Event::MouseButtonPressed:
                putPixel(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), sf::Uint8(100), window);
                break;
            }
            window.display();
        }
        
        
    }

    return 0;
}