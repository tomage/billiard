
// Header
#include "OpenGL.hpp"

// Con- and destructors ==================================================== //

OpenGL::OpenGL(const char *c) {
  sWindowTitle = c;
  iMouseButton = -1;
  iMouseState = -1;
}

OpenGL::~OpenGL() {
  // Nothing...
}

// Public access modifiers ================================================= //

void OpenGL::setVisible(bool) {
  // Nothing...
}

// Public utility functions ================================================ //

void OpenGL::doGlutInit(int *i, char **&c) { glutInit(i, c); }

void OpenGL::doGlutCreateWindow() {
  iGLwin = glutCreateWindow(sWindowTitle.c_str());
}

void OpenGL::doGlutInitDisplayMode(int i) { glutInitDisplayMode(i); }

void OpenGL::doGlutInitWindowSize(int i, int j) {
  iScreenWidth = i;
  iScreenHeight = j;
  glutInitWindowSize(i, j);
}

void OpenGL::doGlutDisplayFunc(void (&func)()) { glutDisplayFunc(func); }

void OpenGL::doGlutKeyboardFunc(void (&func)(unsigned char, int, int)) {
  glutKeyboardFunc(func);
}

void OpenGL::doGlutSpecialFunc(void (&func)(int, int, int)) {
  glutSpecialFunc(func);
}

void OpenGL::doGlutMouseFunc(void (&func)(int, int, int, int)) {
  glutMouseFunc(func);
}

void OpenGL::doGlutMotionFunc(void (&func)(int, int)) { glutMotionFunc(func); }

void OpenGL::doGlutPassiveMotionFunc(void (&func)(int, int)) {
  glutPassiveMotionFunc(func);
}

void OpenGL::doGlutReshapeFunc(void (&func)(int, int)) {
  glutReshapeFunc(func);
}

void OpenGL::doGlutIdleFunc(void (&func)()) { glutIdleFunc(func); }

void OpenGL::doGlutMainLoop() { glutMainLoop(); }

void OpenGL::doGlutDestroyWindow() { glutDestroyWindow(iGLwin); }

// Private access modifiers ================================================ //

//

// Private utility functions =============================================== //

//
