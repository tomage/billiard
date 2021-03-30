
#ifndef OPENGL_HPP
#define OPENGL_HPP

// Include
#include <GL/glut.h>
#include <string>

class OpenGL {
public:
  // Con- and destructors
  OpenGL(const char *);
  ~OpenGL();

  // Public access modifiers
  void setVisible(bool);

  // Public utility functions
  void doGlutInit(int *, char **&);
  void doGlutInitDisplayMode(int);
  void doGlutInitWindowSize(int, int);
  void doGlutCreateWindow();
  void doGlutDisplayFunc(void (&)());
  void doGlutKeyboardFunc(void (&)(unsigned char, int, int));
  void doGlutSpecialFunc(void (&)(int, int, int));
  void doGlutMouseFunc(void (&)(int, int, int, int));
  void doGlutMotionFunc(void (&)(int, int));
  void doGlutPassiveMotionFunc(void (&)(int, int));
  void doGlutReshapeFunc(void (&)(int, int));
  void doGlutIdleFunc(void (&func)());
  void doGlutMainLoop();
  void doGlutDestroyWindow();

  // Public variables
  int iScreenWidth;
  int iScreenHeight;
  int iWindowWidth;
  int iWindowHeight;
  int iMouseButton;
  int iMouseState;

private:
  // Private access modifiers
  //

  // Private utility functions
  //

  // Private variables
  std::string sWindowTitle;
  int iGLwin;
};

#endif
