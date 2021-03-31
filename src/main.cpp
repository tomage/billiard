
#include "Billiard.hpp"
#include "OpenAL.hpp"
#include "OpenGL.hpp"
#include "sound.hpp"

int main(int argc, char **argv) {

  // Setup video and audio
  OpenGL *myOpenGL = new OpenGL("Billiard", &argc, argv);
  OpenAL *myOpenAL = new OpenAL(&argc, argv);

  Sound *sound = new Sound(myOpenAL);

  // Setup the billiard
  Billiard *myBilliard = new Billiard(myOpenGL, sound);
  myBilliard->init();

  // Run it!
  myBilliard->run();

  return 0;
}
