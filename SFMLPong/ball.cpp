#include "ball.h"
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

Ball::Ball(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f vel) : 
  Entity(pos, size, vel) {
  m_shape.setFillColor(sf::Color::Red);
  m_shape.setRadius(size.x);
  m_shape.setPosition(pos);
  m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
}

// checks if the object is within bounds of the other object
bool Ball::checkCollision(const Entity& object) const {
  const sf::Vector2f ball = getPosition();
  const sf::Vector2f ballSize = getSize();
  const sf::Vector2f paddle = object.getPosition();
  const sf::Vector2f padSize = object.getSize();
  return (ball.x - ballSize.x < paddle.x + padSize.x && 
          ball.x + ballSize.x > paddle.x &&
          ball.y < paddle.y + padSize.y && 
          ball.y + ballSize.y > paddle.y);
}

// checks if object hits the quarter end portion of the object
bool Ball::bounceEdge(const Entity& object) const {
  const sf::Vector2f ball = getPosition();
  const sf::Vector2f ballSize = getSize();
  const sf::Vector2f paddle = object.getPosition();
  const sf::Vector2f padSize = object.getSize();
  return ((ball.y < paddle.y + padSize.y * 0.25 && 
           ball.y > paddle.y) ||
          (ball.y > paddle.y + padSize.y * 0.75 && 
           ball.y < paddle.y + padSize.y));
}

bool Ball::collision(const Entity& p1, const Entity& p2) {
  setPosition(m_shape.getPosition());
  const sf::Vector2f player = p1.getPosition();
  const sf::Vector2f opponent = p2.getPosition();
  const sf::Vector2f pos = getPosition();
  const float dt = dtUpdate();
  sf::Vector2f vel = getVelocity();
  bool bounce = false;

  if (checkCollision(p1)) {
    bounce = true;
    if (bounceEdge(p1)) {
      vel.y *= 1.1;
      setVelocity(vel);
    }
    else {
      vel.x *= 2;
      setVelocity(vel);
    }
    vel.x *= -1;
    setVelocity(vel);
  }
  else if (checkCollision(p2)) {
    bounce = true;
    if (bounceEdge(p2)) {
      vel.y *= 1.1;
      setVelocity(vel);
    }
    else {
      vel.x *= 2;
      setVelocity(vel);
    }
    vel.x *= -1; 
    setVelocity(vel);
  }

  // if ball hits top or bottom
  if (pos.y - getSize().y < 0 || pos.y + getSize().y > 800) {
    bounce = true;
    vel.y *= -1;
    setVelocity(vel);
  }
  
  m_shape.move(vel * dt);
  return bounce;
}

void Ball::reset() {
  m_shape.setPosition(sf::Vector2f(400, 400));
  std::random_device seed;
  std::mt19937 gen{ seed() };
  std::uniform_int_distribution<> dist{ 15, 30 };
  int randX = dist(gen);
  if (randX > 22)
    randX *= -1;

  int randY = rand() % 30 + 15;
  if (randY > 22)
    randY *= -1;

  srand(time(0));

  float dt = dtUpdate();
  sf::Vector2f vel = getVelocity();
  vel.x = randX*10;
  vel.y = randY*10;
  setVelocity(vel);
  m_shape.move(vel * dt);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.texture = NULL;
  target.draw(m_shape, states);
}
