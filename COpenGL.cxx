
// Header
#include "COpenGL.hxx"

// Con- and destructors ==================================================== //

COpenGL::COpenGL(const char *c) {
  sWindowTitle = c;
  iMouseButton = -1;
  iMouseState = -1;
}

COpenGL::~COpenGL() {
  // Nothing...
}

// Public access modifiers ================================================= //

void COpenGL::setVisible(bool b) {
  // Nothing...
}

// Public utility functions ================================================ //

void COpenGL::doGlutInit(int *i, char **&c) { glutInit(i, c); }

void COpenGL::doGlutCreateWindow() {
  iGLwin = glutCreateWindow(sWindowTitle.c_str());
}

void COpenGL::doGlutInitDisplayMode(int i) { glutInitDisplayMode(i); }

void COpenGL::doGlutInitWindowSize(int i, int j) {
  iScreenWidth = i;
  iScreenHeight = j;
  glutInitWindowSize(i, j);
}

void COpenGL::doGlutDisplayFunc(void (&func)()) { glutDisplayFunc(func); }

void COpenGL::doGlutKeyboardFunc(void (&func)(unsigned char, int, int)) {
  glutKeyboardFunc(func);
}

void COpenGL::doGlutSpecialFunc(void (&func)(int, int, int)) {
  glutSpecialFunc(func);
}

void COpenGL::doGlutMouseFunc(void (&func)(int, int, int, int)) {
  glutMouseFunc(func);
}

void COpenGL::doGlutMotionFunc(void (&func)(int, int)) { glutMotionFunc(func); }

void COpenGL::doGlutPassiveMotionFunc(void (&func)(int, int)) {
  glutPassiveMotionFunc(func);
}

void COpenGL::doGlutReshapeFunc(void (&func)(int, int)) {
  glutReshapeFunc(func);
}

void COpenGL::doGlutIdleFunc(void (&func)()) { glutIdleFunc(func); }

void COpenGL::doGlutMainLoop() { glutMainLoop(); }

void COpenGL::doGlutDestroyWindow() { glutDestroyWindow(iGLwin); }

// Private access modifiers ================================================ //

//

// Private utility functions =============================================== //

//
