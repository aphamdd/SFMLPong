// SFML Install instructions
// make sure when creating the project to not check
// "solution in the same folder" as the project
// https://www.youtube.com/watch?v=lFzpkvrscs4

// Extra Credit: 
// Add particle effects on collision
// Glow effects
// Textures

#include <iostream>
#include "menu.h"
using namespace std;

int main() {
  const int fps = 3000;
  const float winX = 800, winY = 800;
  sf::RenderWindow window(sf::VideoMode(winX, winY), "SFML Pong", sf::Style::Default);
  window.setFramerateLimit(fps);

  sf::Font font;
  if (!font.loadFromFile("./Fonts/Retale-Regular.ttf"))
    throw("COULDN'T LOAD FONT");
  
  Menu menu;

  while (window.isOpen()) {
    MenuOption select = menu.mainMenu(window, font);
    switch (select) {

    case MenuOption::Start:
      select = menu.gameScreen(window, font, winX, winY);
      break;
    case MenuOption::Options:
      break;
    case MenuOption::Exit:
      window.close();
      break;
    default:
      break;
    }
  }
  return 0;
}
// this line (window.draw(particles)) doesnt actually render the particles yet,
// it enters the draw function inside the particle class
// and then it calls its own draw function to actually render.
// I have 0 idea how it even enters its own draw function first
//
// OK, so actually the particles object is my own type ParticleSystem. Typically
// I call window.draw() and I pass in a DRAWABLE object. Now note that
// the ParticleSystem object is also a Drawable object since it inherited.
// So thats why its able to call window.draw(particles) and use my own draw function, 
// it makes it look cleaner instead of something like window.draw(ball.getShape()) using a getter function.