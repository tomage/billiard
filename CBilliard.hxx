
#ifndef CBilliard_HXX
#define CBilliard_HXX


// Include
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "COpenGL.hxx"
#include "COpenAL.hxx"
#include "CVector.hxx"
#include "CMatrix.hxx"
#include <cmath>


// Set Namespace
using namespace std;

// Billiard user-defined-type
struct udtBall {
	
	CMatrix x;
	CMatrix v;
	CMatrix coll;
	
	double red;
	double green;
	double blue;
	
	bool bActive;
	bool bFirstPlayer;
	
	double dHoleTime, dCollisionTime, dWallTime;
	
	udtBall () {
		x = CMatrix(3,1);	// Location
		v = CMatrix(3,1);	// Velocity
		coll = CMatrix(3,1);	// Collision vector
		red = 0.0; green = 0.0; blue = 0.0;
		
		bActive = false;
		bFirstPlayer = true;
		
		dHoleTime = -1.0;
		dCollisionTime = -1.0;
		dWallTime = -1.0;
	}
};

class CState {
  public:
	// Con- and destructors
	CState() {
		iNoBalls = 16;
		uBalls = new udtBall *[iNoBalls-1];
		for (int i = 0; i < iNoBalls; i++)
			uBalls[i] = new udtBall();
		iNoBalls = 16;
		
		uBalls[ 0]->red = 1.0; uBalls[ 0]->green = 1.0, uBalls[ 0]->blue = 1.0;	// CUE
		uBalls[ 5]->red = 0.0; uBalls[ 5]->green = 0.0, uBalls[ 5]->blue = 0.0;	// BLACK
		
		uBalls[ 1]->red = 1.0; uBalls[ 1]->green = 0.0, uBalls[ 1]->blue = 0.0;
		uBalls[ 2]->red = 0.0; uBalls[ 2]->green = 1.0, uBalls[ 2]->blue = 0.0;
		uBalls[ 3]->red = 0.0; uBalls[ 3]->green = 0.0, uBalls[ 3]->blue = 1.0;
		uBalls[ 4]->red = 1.0; uBalls[ 4]->green = 1.0, uBalls[ 4]->blue = 0.0;
		uBalls[ 6]->red = 1.0; uBalls[ 6]->green = 0.0, uBalls[ 6]->blue = 1.0;
		uBalls[ 7]->red = 0.0; uBalls[ 7]->green = 1.0, uBalls[ 7]->blue = 1.0;
		uBalls[ 8]->red = 0.0; uBalls[ 8]->green = 0.0, uBalls[ 8]->blue = 0.5;
		
		uBalls[ 9]->red = 0.5; uBalls[ 9]->green = 0.0, uBalls[ 9]->blue = 0.0;
		uBalls[10]->red = 0.0; uBalls[10]->green = 0.5, uBalls[10]->blue = 0.0;
		uBalls[11]->red = 0.0; uBalls[11]->green = 0.0, uBalls[11]->blue = 0.5;
		uBalls[12]->red = 0.5; uBalls[12]->green = 0.5, uBalls[12]->blue = 0.0;
		uBalls[13]->red = 0.5; uBalls[13]->green = 0.0, uBalls[13]->blue = 0.5;
		uBalls[14]->red = 0.0; uBalls[14]->green = 0.5, uBalls[14]->blue = 0.5;
		uBalls[15]->red = 0.0; uBalls[15]->green = 0.0, uBalls[15]->blue = 0.25;
		uCueBall = uBalls[0];	// Set first ball as cue ball
		
		for (int i = iNoBalls/2; i < iNoBalls; i++)
			uBalls[i]->bFirstPlayer = false;
		
		// No next state
		next = 0;
		time = 0;
		endtime = 0;
	}
	~CState();
	
	// Public access modifiers
	//
	
	// Public utility functions
	//
	
	// Public variables
	CState * next;
	int iNoBalls;
	udtBall ** uBalls;	// List of balls
	udtBall * uCueBall;	// Cue ball - refers to item in uBalls
	double time;	// Start time of state
	double endtime; // End time of state
	
  private:
	// Private access modifiers
	//
	
	// Private utility functions
	//
	
	// Private variables
	//
};

class CBilliard {
  public:
	// Con- and destructors
	CBilliard();
	~CBilliard();
	
	// Public access modifiers
	//
	
	// Public utility functions
	void init ();
	void setGlutFunctions (COpenGL *cogl);
	
	// Public variables
	//
	
	static COpenGL *myOpenGL;
	static COpenAL *myOpenAL;
	
  private:
	// Private access modifiers
	//
	
	// Private utility functions
	static CMatrix getX(double, udtBall*);
	static CMatrix getV(double, udtBall*);
	static double energy(double);
	static double energy(double, CState*);
	
	static double getCollisionTime(udtBall *,  udtBall *, double, double);
	static double getWallTime(int, udtBall *);
	static void getNextState();
	static void gotoNextState();
	static void displayFunction ();
	static void keyboardFunction (unsigned char, int, int);
	static void specialFunction (int, int, int);
	static void mouseFunction (int, int, int, int);
		
	static void motionFunction (int, int);
	static void passiveMotionFunction (int, int);
	static void reshapeFunction (int, int);
	static void idleFunction ();
	static void mouseMove (int, int, int, int);
	
	// Private variables
	static CState * states;		// Head pointer to state list
	static CState * current;	// Currently selected state
	static CState * drawState;	// Draw state
	static double time; // Currently selected time to display
	static double finaltime;
	static CMatrix * holes;
	
	static double dTABLE_SIZEX;
	static double dTABLE_SIZEY;
	static double dGAME_SPEED;
	static double dBALL_SIZE;
	static double dHOLE_SIZE;
	static double dPHYSICS_K;
	static double dENERGY_ZERO;
	
	static double timeStep;
	static double dMouseX;
	static double dMouseY;
	static bool bAim;
	static bool bPause;
	static bool bLookAtCue;
	static bool bLookTop;
	static bool bLookCenter;
	static CMatrix aim;
	
	static ALuint buffer[2];
	static ALuint source[2];
};


#endif
