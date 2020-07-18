#ifndef H_PAINT_DATA_H
#define H_PAINT_DATA_H

#include "SFML/Graphics.hpp"
#include "State.h"
#include "MenuBar.h"

enum ButtonState {
  RELEASED = 0,
  PRESSED  = 1
};

struct PaintData {
  PaintData(int width, int height)
    : menuBar(sf::Vector2f((float)width, (float)height))
  {
    eraserSize           = 20;
    connectPixels        = false;
    isDrawing            = false;
    isColorPicking       = false;
    isColorPicked        = false;
    state                = State::EMPTY_STATE;
    oldState             = State::EMPTY_STATE;
    newState             = State::MOUSE_CURSOR;
    mouseLeftButtonState = ButtonState::RELEASED;
    drawColour           = sf::Color::Black;
    sprite.setOrigin({ (float)menuBar.getBarWidth(), 0 });
    sprite.setPosition({ (float)menuBar.getBarWidth(), 0 });
    mouse.setSize(sf::Vector2f(0, 0));
    pickerImage.loadFromFile("./texture/color_pick.png");
    pickerTexture.loadFromImage(pickerImage);
    colorPicker.setTexture(&pickerTexture);
    colorPicker.setSize({ 0,0 });
  };

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
  State              oldState;
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
