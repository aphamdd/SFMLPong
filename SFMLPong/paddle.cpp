#include "paddle.h"
#include <iostream>
using namespace std;

Paddle::Paddle(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f vel) :
  Entity(pos, size, vel) {
  m_shape.setFillColor(sf::Color::Green);
  m_shape.setSize(size);
  m_shape.setPosition(pos);
}

void Paddle::update() {
  setPosition(m_shape.getPosition());
  const float dt = dtUpdate();
  const sf::Vector2f vel = getVelocity();
  sf::Vector2f pos = getPosition();

  if (pos.y < 0) {
    pos.y = 0;
    setPosition(pos);
    m_shape.setPosition(pos);
  }
  else if (pos.y + getSize().y > 800) {
    pos.y = 800-getSize().y;
    setPosition(pos);
    m_shape.setPosition(pos);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    if (pos.y >= 0)
      m_shape.move(-vel * dt);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
    if (pos.y + getSize().y <= 800)
      m_shape.move(vel * dt);
  }
}

void Paddle::cpuUpdate(const Entity& b) {
  setPosition(m_shape.getPosition());
  const float dt = dtUpdate();
  const sf::Vector2f ball = b.getPosition();
  const sf::Vector2f vel = getVelocity();
  sf::Vector2f pos = getPosition();

  if (pos.y < 0) {
    pos.y = 0;
    setPosition(pos);
    m_shape.setPosition(pos);
  }
  else if (pos.y + getSize().y > 800) {
    pos.y = 800-getSize().y;
    setPosition(pos);
    m_shape.setPosition(pos);
  }

  if (ball.y >= pos.y && pos.y + getSize().y <= 800)
    m_shape.move(vel * dt);
  else if (ball.y <= pos.y && pos.y >= 0)
    m_shape.move(-vel * dt);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.texture = NULL;
  target.draw(m_shape, states);
}
