#include <assert.h>
#include "Paint.h"
#include "Algorithms.h"

Paint::Paint(unsigned int width
           , unsigned int height
           , std::string  windowTitle)
  : m_data(width, height)
  , m_window(width, height, windowTitle, &m_data)
{
  m_data.image.create(width, height, sf::Color::White);
}

Paint::~Paint()
{

}

void Paint::run()
{
  //Set initial custom mouse cursor
  setMouseCursor();

  while (m_window.isOpen())
  {
    m_data.newState = m_data.menuBar.interact(getWindow(), m_data.state);
    //If state has changed, change the mouse cursor
    if (m_data.newState != m_data.state)
    {
      //oldState variable is used to return to the previous state after the user chooses the new color in the color picker
      m_data.oldState = m_data.state;
      setMouseCursor();
    }

    m_data.state = m_data.newState;

    if (m_data.state != State::COLOR_PICKER)
    {
      m_data.isColorPicking = false;
      m_data.isColorPicked  = false;
      m_data.colorPicker.setSize({ 0,0 });
    }

    switch (m_data.state)
    {
    case State::PENCIL:
      pencilLogic();
      break;
    case State::LINE:
      lineLogic();
      break;
    case State::ERASE:
      eraseLogic();
      break;
    case State::FILL:
      fillLogic();
      break;
    case State::COLOR_PICKER:
      colorPickLogic();
      break;
    default://State::MOUSE_CURSOR
      break;
    }

    m_window.update();
    draw();
    m_window.display();
  }
}

//Method to set a color for a given pixel in the drawing field
void Paint::putPixel(sf::Vector2i pos, sf::Color color)
{
  if (m_data.connectPixels == false) //Edge case when mouse went outside of the window
  {
    m_data.image.setPixel(pos.x, pos.y, color);
  }
  else
  {
    //Draw lines between new pixel and the previous pixel because
    //fast mouse movement leads to some pixels being skipped and not colored
    BresenhamLine(pos, m_data.prevPixel, color, m_data.image);
  }
  m_data.prevPixel = pos;
}

void Paint::resetMouseCursor()
{
  m_data.mouse.setTexture(nullptr);
  m_data.mouse.setSize(sf::Vector2f(0, 0));
  m_data.mouse.setOutlineThickness(0);
}

//Set the custom mouse cursor depending on the current state
void Paint::setMouseCursor()
{
  resetMouseCursor();
  sf::Vector2i mouseCoords = m_window.getMouseCoords();

  switch (m_data.newState)
  {
    case State::PENCIL:
    {
      sf::Texture* icon = new sf::Texture;
      icon->loadFromFile(std::string("./texture/cursor_pencil.png"));
      icon->setSmooth(true);
      m_data.mouse.setSize(sf::Vector2f(32, 32));
      m_data.mouse.setTexture(icon);
      //Change the mouse position because the pencil tip is at the bottom
      m_data.mouse.setPosition(sf::Vector2f(mouseCoords.x, mouseCoords.y - 32));
      break;
    }
    //case State::LINE:
    //  break;
    case State::ERASE:
    {
      m_data.mouse.setSize(sf::Vector2f(m_data.eraserSize * 2, m_data.eraserSize * 2));
      m_data.mouse.setOutlineThickness(1);
      m_data.mouse.setOutlineColor(sf::Color::Black);
      m_data.mouse.setFillColor(sf::Color::White);
      //Center the eraser rectangle over the mouse cursor
      m_data.mouse.setPosition(sf::Vector2f(mouseCoords.x - m_data.eraserSize, mouseCoords.y - m_data.eraserSize));
      break;
    }
    case State::FILL:
    {
      sf::Texture* icon = new sf::Texture;
      icon->loadFromFile(std::string("./texture/cursor_fill.png"));
      icon->setSmooth(true);
      m_data.mouse.setSize(sf::Vector2f(32, 32));
      m_data.mouse.setTexture(icon);
      break;
    }
    default:
    {
      sf::Texture* icon = new sf::Texture;
      icon->loadFromFile(std::string("./texture/cursor_arrow.png"));
      icon->setSmooth(true);
      m_data.mouse.setSize(sf::Vector2f(32, 32));
      m_data.mouse.setTexture(icon);
      m_data.mouse.setPosition(sf::Vector2f(mouseCoords.x, mouseCoords.y));
      break;
    }
  }
}

//Draw all objects to the window
void Paint::draw()
{
  m_data.texture.loadFromImage(m_data.image);
  m_data.sprite.setTexture(m_data.texture);
  m_window.draw(m_data.sprite);
  m_data.menuBar.draw(getWindow());
  m_window.draw(m_data.colorPicker);
  m_window.draw(m_data.mouse);
}

//Colors the pixels which the mouse went over
void Paint::pencilLogic()
{
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(getWindow());

  if (m_data.mouseLeftButtonState == ButtonState::RELEASED
   || mouseCoords.x < m_data.menuBar.getBarWidth()
   || mouseCoords.x >= m_window.getSize().x
   || mouseCoords.y >= m_window.getSize().y)
  {
    //Edge case when mouse goes outside of the window
    m_data.connectPixels = false;
  }

   if(sf::Mouse::isButtonPressed(sf::Mouse::Left)
   &&  mouseCoords.x  < m_window.getSize().x
   &&  mouseCoords.y  < m_window.getSize().y
   &&  mouseCoords.x  > m_data.menuBar.getBarWidth()
   && (mouseCoords.x != m_data.prevPixel.x
   ||  mouseCoords.y != m_data.prevPixel.y))
  {
    putPixel(mouseCoords, m_data.drawColour);
    m_data.connectPixels = true;
  }
}

//Draws a line from the coordinates where the LMB was first pressed to where it is released
void Paint::lineLogic()
{
  if (m_data.isDrawing)
  {
    m_data.image = m_data.imageSnapshot;
    sf::Vector2i mouseCoords = sf::Mouse::getPosition(getWindow());
    if (mouseCoords.x < m_window.getSize().x
    && mouseCoords.y  < m_window.getSize().y
    && mouseCoords.x  > m_data.menuBar.getBarWidth())
    {
      BresenhamLine(m_data.lineStartCoords, mouseCoords, m_data.drawColour, m_data.image);
    }
    m_data.prevLine = mouseCoords;
  }
}

//Sets color to white to all the pixels inside the eraser rectangle
void Paint::eraseLogic()
{
  sf::Vector2i mouseCoords = m_window.getMouseCoords();

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
      && mouseCoords.x < (m_window.getSize().x - m_data.eraserSize) && mouseCoords.x > m_data.eraserSize
      && mouseCoords.y < (m_window.getSize().y - m_data.eraserSize) && mouseCoords.y > m_data.eraserSize
      && mouseCoords.x >= (m_data.menuBar.getBarWidth() + m_data.eraserSize))
  {
    for (int i = -m_data.eraserSize; i <= m_data.eraserSize; i++)
    {
      for (int j = -m_data.eraserSize; j <= m_data.eraserSize; j++)
      {
        if (m_data.image.getPixel(mouseCoords.x + i, mouseCoords.y + j) != sf::Color::White)
        {
          m_data.image.setPixel(mouseCoords.x + i, mouseCoords.y + j, sf::Color::White);
        }
      }
    }
  }
}

//Uses flood fill iterative algorithm to color the pixels in drawColour color
void Paint::fillLogic()
{
  sf::Vector2i mouseCoords = m_window.getMouseCoords();
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    floodFill(mouseCoords
      , m_data.drawColour
      , m_data.image
      , sf::Vector2u(m_data.menuBar.getBarWidth(), 0)
      , { m_window.getSize().x, m_window.getSize().y });
  }
}

void Paint::colorPickLogic()
{
  //std::cout << m_data.isColorPicked << m_data.isColorPicking  << std::endl;
  sf::Vector2i mouseCoords = m_window.getMouseCoords();
  //if (m_data.isColorPicked)
  //{
  //  m_data.colorPicker.setSize({ 0,0 });
  //  m_data.isColorPicking = false;
  //  m_data.isColorPicked  = false;
  //}
  //else
  {
    if (mouseCoords.x >= (int)m_data.colorPicker.getPosition().x
     && mouseCoords.y >= (int)m_data.colorPicker.getPosition().y
     && mouseCoords.x <= (int)(m_data.colorPicker.getPosition().x + m_data.colorPicker.getSize().x)
     && mouseCoords.y <= (int)(m_data.colorPicker.getPosition().y + m_data.colorPicker.getSize().y)
     && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
     && m_data.isColorPicking)
    {
      //Get the color from the color picker image
      m_data.drawColour = m_data.pickerImage.getPixel(mouseCoords.x - (int)m_data.colorPicker.getPosition().x
                                                    , mouseCoords.y - (int)m_data.colorPicker.getPosition().y);

      m_data.isColorPicking = false;
      m_data.isColorPicked  = true;
      //Change state back to what it was before going into color pick state
      m_data.state = m_data.newState = m_data.oldState;
      setMouseCursor();
      std::cout << "picked" << std::endl;
    }
  }
}

MenuBar* Paint::getMenuBar()
{
  return &m_data.menuBar;
}

sf::RenderWindow& Paint::getWindow()
{
  return m_window.getWindow();
}