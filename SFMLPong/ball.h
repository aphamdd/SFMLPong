#pragma once
#include "SFML/Graphics.hpp"
#include "entity.h"
#include <vector>

class Ball : public Entity {
public:
  Ball(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f vel);

  bool collision(const Entity& p1, const Entity& p2);
  void reset();

private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  bool checkCollision(const Entity&) const;
  bool bounceEdge(const Entity&) const;

private:
  sf::CircleShape m_shape;
};