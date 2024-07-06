#pragma once
#include "SFML/Graphics.hpp"
#include "ball.h"
#include "paddle.h"
#include "score.h"
#include "particle.h"

enum class MenuOption { Start, Options, Exit, Pause, Resume, None };

class Menu {
public:
  MenuOption mainMenu(sf::RenderWindow& window, sf::Font font);
  MenuOption pauseMenu(sf::RenderWindow& window, sf::Font font);
  MenuOption gameScreen(sf::RenderWindow& window, sf::Font& font, float, float);
};
