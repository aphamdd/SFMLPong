#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace std;

class Entity : public sf::Drawable, public sf::Transformable {
public:
  Entity(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f vel) :
    m_pos(pos),
    m_size(size),
    m_vel(vel)
  {}

  float dtUpdate() { return dtClock.restart().asSeconds(); }
  virtual void update() {};
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

  virtual void setPosition(const sf::Vector2f pos) { m_pos = pos; }
  virtual void setVelocity(const sf::Vector2f vel) { m_vel = vel; }
  virtual sf::Vector2f getPosition() const { return m_pos; }
  virtual const sf::Vector2f getSize() const { return m_size; }
  virtual sf::Vector2f getVelocity() const { return m_vel; }

private:
  sf::Clock dtClock;
  sf::Vector2f m_pos;
  sf::Vector2f m_size;
  sf::Vector2f m_vel;
};