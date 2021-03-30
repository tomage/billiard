
#ifndef COPENGL_HXX
#define COPENGL_HXX



// Include
#include <GL/glut.h>
#include <string>


// Set Namespace
using namespace std;


class COpenGL {
 public:
 	// Con- and destructors
	COpenGL(const char*);
	~COpenGL();
	
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
	string sWindowTitle;
	int iGLwin;
};



#endif
