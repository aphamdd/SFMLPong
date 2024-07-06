#pragma once
#include "SFML/Graphics.hpp"

class Score : public sf::Drawable {
public:
  Score(sf::Font& font, float x, float y);
  void update();

private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = NULL;
    target.draw(m_text, states);
  }

private:
  int m_score;
  sf::Text m_text;
};
