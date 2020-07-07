#include <assert.h>
#include "Paint.h"
#include "Algorithms.h"

#define DELTA 60

using std::cout;
using std::endl;

Paint::Paint(unsigned int width, unsigned int height, std::string windowTitle)
  : m_data(width, height)
  , m_window(width, height, windowTitle, &m_data)
{
  m_data.image.create(width, height, sf::Color::White);
  initData();
}

void Paint::initData()
{
  m_data.connectPixels = false;
  m_data.mouseLeftButtonState = ButtonState::RELEASED;
  m_data.isDrawing = false;
  m_data.isColorPicking = false;
  m_data.state = State::EMPTY_STATE;
  m_data.newState = State::MOUSE_CURSOR;
  m_data.drawColour = sf::Color::Black;
  m_data.sprite.setOrigin({ (float)m_data.menuBar.getBarWidth(), 0 });
  m_data.sprite.setPosition({ (float)m_data.menuBar.getBarWidth(), 0 });
  m_data.mouse.setSize(sf::Vector2f(0, 0));
  m_data.eraserSize = 20;
  m_data.pickerImage.loadFromFile("./texture/color_pick.png");
  m_data.pickerTexture.loadFromImage(m_data.pickerImage);
  m_data.colorPicker.setTexture(&m_data.pickerTexture);
  m_data.colorPicker.setSize({ 0,0 });
}

Paint::~Paint()
{

}

void Paint::run()
{
  setMouseCursor();

  while (m_window.isOpen())
  {
    m_window.update();

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
    draw();
    m_data.newState = m_data.menuBar.interact(getWindow(), m_data.state);
    if (m_data.newState != m_data.state)
    {
      setMouseCursor();
    }

    m_data.state = m_data.newState;

    m_window.display();
  }
}

void Paint::putPixel(sf::Vector2i pos, sf::Color color)
{
  if (m_data.connectPixels == false)
  {
    m_data.image.setPixel(pos.x, pos.y, color);
  }
  else
  {
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

void Paint::setMouseCursor()
{
  resetMouseCursor();
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(getWindow());

  switch (m_data.newState)
  {
  case State::PENCIL:
  {
    sf::Texture* icon = new sf::Texture;
    icon->loadFromFile(std::string("./texture/cursor_pencil.png"));
    icon->setSmooth(true);
    m_data.mouse.setSize(sf::Vector2f(32, 32));
    cout << m_data.mouse.getSize().x << ' ' << m_data.mouse.getSize().y << "\n";
    m_data.mouse.setTexture(icon);
    break;
  }
  //case State::LINE:
  //  break;
  case State::ERASE:
  {
    m_data.mouse.setSize(sf::Vector2f(m_data.eraserSize * 2, m_data.eraserSize * 2));
    m_data.mouse.setOutlineThickness(1);
    m_data.mouse.setOutlineColor(m_data.drawColour);
    m_data.mouse.setFillColor(sf::Color::White);
    break;
  }
  case State::FILL:
  {
    sf::Texture* icon = new sf::Texture;
    icon->loadFromFile(std::string("./texture/cursor_fill.png"));
    icon->setSmooth(true);
    m_data.mouse.setSize(sf::Vector2f(32, 32));
    cout << m_data.mouse.getSize().x << ' ' << m_data.mouse.getSize().y << "\n";
    m_data.mouse.setTexture(icon);
    break;
  }
  default:
  {
    sf::Texture* icon = new sf::Texture;
    icon->loadFromFile(std::string("./texture/cursor_arrow.png"));
    icon->setSmooth(true);
    m_data.mouse.setSize(sf::Vector2f(32, 32));
    cout << m_data.mouse.getSize().x << ' ' << m_data.mouse.getSize().y << "\n";
    m_data.mouse.setTexture(icon);
    break;
  }
  }
}

void Paint::draw()
{
  m_data.texture.loadFromImage(m_data.image);
  m_data.sprite.setTexture(m_data.texture);
  m_window.draw(m_data.sprite);
  m_data.menuBar.draw(getWindow());
  m_window.draw(m_data.colorPicker);
  m_window.draw(m_data.mouse);
}

void Paint::pencilLogic()
{
  sf::Vector2i mouseCoords = sf::Mouse::getPosition(getWindow());

  if (m_data.mouseLeftButtonState == ButtonState::RELEASED
   || mouseCoords.x < m_data.menuBar.getBarWidth()
   || mouseCoords.x >= m_window.getSize().x
   || mouseCoords.y >= m_window.getSize().y)
  {
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
        if (m_data.image.getPixel(mouseCoords.x + i, mouseCoords.y + j) == m_data.drawColour)
        {
          m_data.image.setPixel(mouseCoords.x + i, mouseCoords.y + j, sf::Color::White);
        }
      }
    }
  }
}

void Paint::fillLogic()
{
  sf::Vector2i mouseCoords = m_window.getMouseCoords();
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    cout << m_window.getPosition().x + m_data.menuBar.getBarWidth() << endl;
    cout << mouseCoords.x << endl;
    floodFill(mouseCoords
      , m_data.drawColour
      , m_data.image
      , sf::Vector2u(m_data.menuBar.getBarWidth(), 0)
      , { m_window.getSize().x, m_window.getSize().y });
  }
}

void Paint::colorPickLogic()
{
  sf::Vector2i mouseCoords = m_window.getMouseCoords();
  if (!m_data.isColorPicking)
  {
    m_data.colorPicker.setPosition(sf::Vector2f(mouseCoords));

  }
  else
  {
    if (mouseCoords.x >= m_data.colorPicker.getPosition().x
     && mouseCoords.y >= m_data.colorPicker.getPosition().y
     && mouseCoords.x <= m_data.colorPicker.getPosition().x + m_data.colorPicker.getSize().x
     && mouseCoords.y <= m_data.colorPicker.getPosition().x + m_data.colorPicker.getSize().y
     && m_data.isColorPicked)
    {
      m_data.colorPicker.setSize({ 0,0 });
      printf("(r,g,b) = (%d,%d,%d)\n", m_data.pickerImage.getPixel(mouseCoords.x, mouseCoords.y).a, m_data.pickerImage.getPixel(mouseCoords.x, mouseCoords.y).b,
        m_data.pickerImage.getPixel(mouseCoords.x, mouseCoords.y).a);
    }
  }

}

bool Paint::getLMBstate()
{
  return m_data.mouseLeftButtonState;
}

void Paint::setLMBstate(ButtonState newState)
{
  m_data.mouseLeftButtonState = newState;
}

bool Paint::isDrawing()
{
  return m_data.isDrawing;
}

bool Paint::isColorPicked()
{
  return m_data.isColorPicked;
}

bool Paint::isColorPicking()
{
  return m_data.isColorPicking;
}

MenuBar* Paint::getMenuBar()
{
  return &m_data.menuBar;
}

void Paint::setDrawing(bool newState)
{
  m_data.isDrawing = newState;
}

sf::RenderWindow& Paint::getWindow()
{
  return m_window.getWindow();
}