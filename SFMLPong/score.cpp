#include "score.h"

Score::Score(sf::Font &font, float x, float y) {
  m_text.setFont(font);
  m_text.setCharacterSize(50);
  m_text.setStyle(sf::Text::Regular);
  m_text.setPosition(sf::Vector2f(x, y));
  m_text.setFillColor(sf::Color::White);
  m_score = -1;
  update();
}

void Score::update() { 
  m_score += 1;
  m_text.setString(std::to_string(m_score)); 
}
