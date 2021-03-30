
// Header
#include "main.h"

int main(int argc, char **argv) {

  // Create instance of the main classes
  COpenGL *myOpenGL = new COpenGL("Billiard");
  COpenAL *myOpenAL = new COpenAL();
  CBilliard *myBilliard = new CBilliard();

  /* Set up OpenGL */

  // Initialize some glut stuff
  myOpenGL->doGlutInit(&argc, argv);
  myOpenGL->doGlutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  myOpenGL->doGlutInitWindowSize(600, 600);

  // Create the glut window
  myOpenGL->doGlutCreateWindow();

  // And display the window
  myOpenGL->setVisible(true);

  /* ============= */

  /* Set up OpenAL */

  // initialise openAL
  myOpenAL->doAlutInit(&argc, argv);

  /* ============= */

  /* Set up Billiard */

  // Give billiard handle to most important stuff
  myBilliard->myOpenGL = myOpenGL;
  myBilliard->myOpenAL = myOpenAL;

  // Initiailze snake3D - Mostly OpenGL and OpenAL setup
  myBilliard->init();

  // Set some glut functions
  myBilliard->setGlutFunctions(myOpenGL);

  /* ============== */

  // And set the glut loop going
  myBilliard->myOpenGL->doGlutMainLoop();

  return 0;
}
