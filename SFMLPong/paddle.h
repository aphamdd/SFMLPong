#pragma once
#include "SFML/Graphics.hpp"
#include "entity.h"

class Paddle : public Entity {
public:
  Paddle(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f vel);
 
  void update() override;
  void cpuUpdate(const Entity& ball);

private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::RectangleShape m_shape;
};
