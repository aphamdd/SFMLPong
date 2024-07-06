#include "menu.h"

MenuOption Menu::mainMenu(sf::RenderWindow& window, sf::Font font) {
  if (!font.loadFromFile("./Fonts/Retale-Regular.ttf"))
    throw("COULDN'T LOAD FONT");

  // Set up text items
  sf::Text title("Pong Game", font, 50);
  title.setPosition(250, 100);

  sf::Text startGame("Start Game", font, 30);
  startGame.setPosition(320, 250);

  sf::Text options("Options", font, 30);
  options.setPosition(320, 300);

  sf::Text exit("Exit", font, 30);
  exit.setPosition(320, 350);

  // Handle user input and draw the menu
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          return MenuOption::Exit;
        }
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          if (startGame.getGlobalBounds().contains(mousePos.x, mousePos.y))
            return MenuOption::Start;
          if (options.getGlobalBounds().contains(mousePos.x, mousePos.y))
            return MenuOption::Options;
          if (exit.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
            return MenuOption::Exit;
        }
      }
    }

    // Clear window
    window.clear(sf::Color::Black);

    // Draw menu items
    window.draw(title);
    window.draw(startGame);
    window.draw(options);
    window.draw(exit);

    // Display window contents
    window.display();
  }

  return MenuOption::None;
}

MenuOption Menu::gameScreen(sf::RenderWindow& window, sf::Font& font, float winX, float winY) {
  const sf::Vector2f 
    paddleSize = { 10, 100 },
    p1Pos = { 0, (winX/2) - (paddleSize.y/2) }, 
    p2Pos = { winX-paddleSize.x, (winY/2)-(paddleSize.y/2) },
    paddleVelocity = { NULL, 500 };
  const int actualBallSize = 8;
  const sf::Vector2f 
    ballPos = { winX/2, winY/2 }, 
    ballSize = { actualBallSize, actualBallSize },
    ballVelocity = { -500, 100 };
  Ball ball(ballPos, ballSize, ballVelocity);
  Paddle player(p1Pos, paddleSize, paddleVelocity);
  Paddle opponent(p2Pos, paddleSize, paddleVelocity);
  Score p1Score(font, (winX*.30), winY*.1);
  Score p2Score(font, (winX*.70), winY*.1);
  ParticleSystem particles(100);
  ParticleSystem bounceParticles(1);
  sf::Clock clock;
  sf::VertexArray fieldLine(sf::Lines, 2);
  MenuOption select = MenuOption::None;

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed)
        if (event.key.code == sf::Keyboard::Space)
          ball.reset();
      if (event.type == sf::Event::KeyPressed)
        if (event.key.code == sf::Keyboard::Escape)
          select = pauseMenu(window, font);
    }
    
    switch (select) {
    case MenuOption::Exit:
      return MenuOption::Exit;
    default:
      bool bounce = false;
      // Update pong sprites
      bounce = ball.collision(player, opponent);
      player.update();
      opponent.cpuUpdate(ball);

      // Particles
      sf::Time elapsed = clock.restart();
      particles.setEmitter(ball.getPosition());
      particles.update(elapsed);
      if (bounce)
        bounceParticles.setEmitter(ball.getPosition());
      sf::Time e = sf::microseconds(1000);
      bounceParticles.update(e);

      // Field line
      fieldLine[0].position = sf::Vector2f((winX / 2), 0.f);
      fieldLine[1].position = sf::Vector2f((winX / 2), winY);

      // Score Tracking
      if (ball.getPosition().x < (winX - winX) - 10) {
        p2Score.update();
        ball.reset();
      }
      else if (ball.getPosition().x > winX + 10) {
        p1Score.update();
        ball.reset();
      }
    }

    // rendering
    window.clear(sf::Color::Black);
    window.draw(fieldLine);
    window.draw(p1Score);
    window.draw(p2Score);
    window.draw(player);
    window.draw(opponent);
    window.draw(ball);
    window.draw(particles);
    window.draw(bounceParticles);
    window.display();
  }
  return MenuOption::None;
}

MenuOption Menu::pauseMenu(sf::RenderWindow& window, sf::Font font) {
  if (!font.loadFromFile("./Fonts/Retale-Regular.ttf"))
    throw("COULDN'T LOAD FONT");

  // Set up text items
  sf::Text title("Pause", font, 50);
  title.setPosition(250, 100);

  sf::Text resume("Resume", font, 30);
  resume.setPosition(320, 250);

  sf::Text options("Options", font, 30);
  options.setPosition(320, 300);

  sf::Text exit("Exit", font, 30);
  exit.setPosition(320, 350);

  // Handle user input and draw the menu
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          return MenuOption::Exit;
        }
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          if (resume.getGlobalBounds().contains(mousePos.x, mousePos.y))
            return MenuOption::Resume;
          if (options.getGlobalBounds().contains(mousePos.x, mousePos.y))
            return MenuOption::Options;
          if (exit.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
            return MenuOption::Exit;
        }
      }
    }

    // Clear window
    window.clear(sf::Color::Black);

    // Draw menu items
    window.draw(title);
    window.draw(resume);
    window.draw(options);
    window.draw(exit);

    // Display window contents
    window.display();
  }

  return MenuOption::None;
}
