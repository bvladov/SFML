#ifndef H_PAINT_DATA_H
#define H_PAINT_DATA_H

#include "SFML/Graphics.hpp"
#include "State.h"
#include "MenuBar.h"

enum ButtonState {
  RELEASED = 0,
  PRESSED = 1,
};

struct PaintData {
  PaintData(int width, int height)
    : menuBar(sf::Vector2f(width, height))
  {};

  MenuBar            menuBar;
  sf::Image          image;
  sf::Image          imageSnapshot;
  sf::Image          pickerImage;
  sf::Texture        texture;
  sf::Texture        pickerTexture;
  sf::Sprite         sprite;
  sf::RectangleShape mouse;
  sf::RectangleShape colorPicker;
  sf::Color          drawColour;
  sf::Vector2i       prevPixel;
  sf::Vector2i       lineStartCoords;
  sf::Vector2i       prevLine;
  State              state;
  State              newState;
  int                eraserSize;
  bool               connectPixels;
  bool               mouseLeftButtonState;
  bool               isDrawing;
  bool               isColorPicking;
  bool               isColorPicked;
  std::string        title;
};

#endif // !H_PAINT_DATA_H
