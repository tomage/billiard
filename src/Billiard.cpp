
// Header
#include "Billiard.hpp"
#include <AL/alut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>

// Con- and destructors ==================================================== //

Billiard::Billiard(OpenGL *myOpenGL, OpenAL *myOpenAL) {

  this->myOpenGL = myOpenGL;
  this->myOpenAL = myOpenAL;

  // Get seed
  srand(std::time(NULL));

  dTABLE_SIZEX = 222.0;
  dTABLE_SIZEY = dTABLE_SIZEX / 2;
  dGAME_SPEED = 3.0 / 25.0;
  dBALL_SIZE = 3.0;
  dHOLE_SIZE = dBALL_SIZE * 1.4;
  dPHYSICS_K = 1.0 / 1.5;
  dENERGY_ZERO = 0.01;

  double dHoleVariance = 0.7;
  holes = new Matrix[6];
  holes[0] = Matrix(3, 1);
  holes[0].setEntry(0, 0, dTABLE_SIZEX / 2 - dHOLE_SIZE * dHoleVariance);
  holes[0].setEntry(1, 0, dTABLE_SIZEY / 2 - dHOLE_SIZE * dHoleVariance);
  holes[1] = Matrix(3, 1);
  holes[1].setEntry(0, 0, dTABLE_SIZEX / 2 - dHOLE_SIZE * dHoleVariance);
  holes[1].setEntry(1, 0, -dTABLE_SIZEY / 2 + dHOLE_SIZE * dHoleVariance);
  holes[2] = Matrix(3, 1);
  holes[2].setEntry(0, 0, -dTABLE_SIZEX / 2 + dHOLE_SIZE * dHoleVariance);
  holes[2].setEntry(1, 0, dTABLE_SIZEY / 2 - dHOLE_SIZE * dHoleVariance);
  holes[3] = Matrix(3, 1);
  holes[3].setEntry(0, 0, -dTABLE_SIZEX / 2 + dHOLE_SIZE * dHoleVariance);
  holes[3].setEntry(1, 0, -dTABLE_SIZEY / 2 + dHOLE_SIZE * dHoleVariance);
  holes[4] = Matrix(3, 1);
  holes[4].setEntry(1, 0,
                    dTABLE_SIZEY / 2 - dHOLE_SIZE * dHoleVariance *
                                           dHoleVariance * dHoleVariance *
                                           dHoleVariance);
  holes[5] = Matrix(3, 1);
  holes[5].setEntry(1, 0,
                    -dTABLE_SIZEY / 2 + dHOLE_SIZE * dHoleVariance *
                                            dHoleVariance * dHoleVariance *
                                            dHoleVariance);

  timeStep = 0.03;
  dMouseX = 0.0;
  dMouseY = 0.0;
  bAim = false;
  bPause = false;
  bLookAtCue = false;

  aim = Matrix(3, 0); // Set up aim along the x axis...
  aim.setEntry(0, 0, 1);
  aim.setEntry(1, 0, 0);
  aim.setEntry(2, 0, 0);

  states = new CState();
  current = states;
  drawState = current;
  finaltime = 0.1;
  current->endtime = 0;

  double d = dBALL_SIZE * 2.08;
  double dx = sqrt(d * d - d * d / 4);

  for (int i = 0; i < current->iNoBalls; i++) {
    current->uBalls[i]->bActive = true;
    current->uBalls[i]->x.setEntry(0, 0, 0.0);
    current->uBalls[i]->x.setEntry(1, 0, 0.0);
    current->uBalls[i]->x.setEntry(2, 0, dBALL_SIZE);
  }

  // Position balls
  current->uCueBall->x.setEntry(0, 0, -dTABLE_SIZEX / 4.0);
  current->uCueBall->x.setEntry(1, 0, 0.0);

  current->uBalls[1]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * (-2));
  current->uBalls[1]->x.setEntry(1, 0, d / 2 * (0));

  current->uBalls[9]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * (-1));
  current->uBalls[9]->x.setEntry(1, 0, d / 2 * (-1));
  current->uBalls[2]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * (-1));
  current->uBalls[2]->x.setEntry(1, 0, d / 2 * (1));

  current->uBalls[10]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 0);
  current->uBalls[10]->x.setEntry(1, 0, d / 2 * (-2));
  current->uBalls[5]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 0);
  current->uBalls[5]->x.setEntry(1, 0, d / 2 * (0));
  current->uBalls[11]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 0);
  current->uBalls[11]->x.setEntry(1, 0, d / 2 * (2));

  current->uBalls[3]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 1);
  current->uBalls[3]->x.setEntry(1, 0, d / 2 * (-3));
  current->uBalls[12]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 1);
  current->uBalls[12]->x.setEntry(1, 0, d / 2 * (-1));
  current->uBalls[4]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 1);
  current->uBalls[4]->x.setEntry(1, 0, d / 2 * (1));
  current->uBalls[13]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 1);
  current->uBalls[13]->x.setEntry(1, 0, d / 2 * (3));

  current->uBalls[6]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 2);
  current->uBalls[6]->x.setEntry(1, 0, d / 2 * (-4));
  current->uBalls[14]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 2);
  current->uBalls[14]->x.setEntry(1, 0, d / 2 * (-2));
  current->uBalls[7]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 2);
  current->uBalls[7]->x.setEntry(1, 0, d / 2 * (0));
  current->uBalls[15]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 2);
  current->uBalls[15]->x.setEntry(1, 0, d / 2 * (2));
  current->uBalls[8]->x.setEntry(0, 0, dTABLE_SIZEX / 4.0 + dx * 2);
  current->uBalls[8]->x.setEntry(1, 0, d / 2 * (4));

  // Randomize xy pos a bit..
  double randfact = (d - dBALL_SIZE * 2) * 0.4;
  for (int i = 0; i < current->iNoBalls; i++) {
    current->uBalls[i]->x.setEntry(0, 0,
                                   current->uBalls[i]->x.getEntry(0, 0) +
                                       (double)rand() / (double)RAND_MAX /
                                           dBALL_SIZE * randfact);
    current->uBalls[i]->x.setEntry(1, 0,
                                   current->uBalls[i]->x.getEntry(1, 0) +
                                       (double)rand() / (double)RAND_MAX /
                                           dBALL_SIZE * randfact);
  }
}

Billiard::~Billiard() {
  // Nothing...
}

// Public access modifiers ================================================= //

//

// Public utility functions ================================================ //

void Billiard::init() {

  // Initialize OpenGL stuff
  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  if (false) { // FOG ?
    float fogColor[] = {0.1, 0.1, 0.3, 0.4};
    glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, 1.0);
    glFogf(GL_FOG_START, 1);
    glFogf(GL_FOG_END, 80);
    glFogfv(GL_FOG_COLOR, fogColor);
  }

  // Initialize OpenAL stuff
  ALfloat alfVector[] = {0.0, 0.0, 0.0};
  ALfloat listenerOri[] = {0.0, 0.0, 1.0, 0.0, 1.0, 0.0};
  alListenerfv(AL_POSITION, alfVector);
  alListenerfv(AL_VELOCITY, alfVector);
  alListenerfv(AL_ORIENTATION, listenerOri);

  alGenBuffers(2, buffer); // Generate buffers, or else no sound will happen!
  alGenSources(2, source);

  buffer[0] = alutCreateBufferFromFile((const char *)"click.wav");
  buffer[1] = alutCreateBufferFromFile((const char *)"doink.wav");

  alSourcef(source[0], AL_PITCH, 1.0f);
  alSourcef(source[0], AL_GAIN, 1.0f);
  alSourcefv(source[0], AL_POSITION, alfVector);
  alSourcefv(source[0], AL_VELOCITY, alfVector);
  alSourcei(source[0], AL_BUFFER, buffer[0]);

  alSourcef(source[1], AL_PITCH, 1.0f);
  alSourcef(source[1], AL_GAIN, 1.0f);
  alSourcefv(source[1], AL_POSITION, alfVector);
  alSourcefv(source[1], AL_VELOCITY, alfVector);
  alSourcei(source[1], AL_BUFFER, buffer[1]);

  // Set GLUT functions
  myOpenGL->doGlutDisplayFunc(displayFunction);
  myOpenGL->doGlutKeyboardFunc(keyboardFunction);
  myOpenGL->doGlutSpecialFunc(specialFunction);
  myOpenGL->doGlutMouseFunc(mouseFunction);
  myOpenGL->doGlutMotionFunc(motionFunction);
  myOpenGL->doGlutPassiveMotionFunc(passiveMotionFunction);
  myOpenGL->doGlutReshapeFunc(reshapeFunction);
  myOpenGL->doGlutIdleFunc(idleFunction);
}

void Billiard::run() { myOpenGL->doGlutMainLoop(); }

// Private access modifiers ================================================ //

//

// Private utility functions =============================================== //

Matrix Billiard::getX(double t, udtBall *b) {
  Matrix temp = Matrix(3, 1);
  // 	std::cout << "getX(): t = " << t << std::endl;
  temp.setEntry(0, 0,
                b->v.getEntry(0, 0) / dPHYSICS_K * (1 - exp(-dPHYSICS_K * t)));
  temp.setEntry(1, 0,
                b->v.getEntry(1, 0) / dPHYSICS_K * (1 - exp(-dPHYSICS_K * t)));
  temp.setEntry(2, 0,
                b->v.getEntry(2, 0) / dPHYSICS_K * (1 - exp(-dPHYSICS_K * t)));
  // 	std::cout << "Temp addition: " << std::endl; temp.print();
  return temp;
}

Matrix Billiard::getV(double t, udtBall *b) {
  Matrix temp = Matrix(3, 1);
  // 	std::cout << "getV(): t = " << t << std::endl;
  temp.setEntry(0, 0, b->v.getEntry(0, 0) * exp(-dPHYSICS_K * t));
  temp.setEntry(1, 0, b->v.getEntry(1, 0) * exp(-dPHYSICS_K * t));
  temp.setEntry(2, 0, b->v.getEntry(2, 0) * exp(-dPHYSICS_K * t));
  return temp;
}

double Billiard::energy(double t) {

  double retX = 0.0;
  double retY = 0.0;
  double retZ = 0.0;
  for (int i = 0; i < drawState->iNoBalls; i++) {
    retX += getV(t - drawState->time, drawState->uBalls[i]).getEntry(0, 0);
    retY += getV(t - drawState->time, drawState->uBalls[i]).getEntry(1, 0);
    retZ += getV(t - drawState->time, drawState->uBalls[i]).getEntry(2, 0);
  }
  return sqrt(retX * retX + retY * retY + retZ * retZ);
}
double Billiard::energy(double t, CState *state) {

  double retX = 0.0;
  double retY = 0.0;
  double retZ = 0.0;
  for (int i = 0; i < state->iNoBalls; i++) {
    retX += getV(t - state->time, state->uBalls[i]).getEntry(0, 0);
    retY += getV(t - state->time, state->uBalls[i]).getEntry(1, 0);
    retZ += getV(t - state->time, state->uBalls[i]).getEntry(2, 0);
  }
  return sqrt(retX * retX + retY * retY + retZ * retZ);
}

double fsqrt(double n) {
  return sqrt(n);
  if (n == 0.0)
    return 0.0;
  double X;
  double NewX;
  X = n;
  for (int i = 0; i < 80; i++) {
    NewX = 0.5 * (X + n / X);
    X = NewX;
  }
  return X;
}
double flog(double x) {
  return log(x);
  double ret = 0.0;
  double power = x - 1.0;
  for (int i = 1; i < 200; i += 1) {
    power = -power * (x - 1.0);
    // 		ret += power / i;
  }
  return ret;
}
double flog(double x, double N) {
  double ret = 0.0;
  double power = x - 1.0;
  for (int i = 1; i < N; i += 1) {
    power = -power * (x - 1.0);
    ret += power / i;
  }
  return ret;
}

double Billiard::getCollisionTime(udtBall *a, udtBall *b, double r1,
                                  double r2) {
  // Returns time of collision
  // This is a pretty complex solution to detect collision with two balls when
  // either of them is stationary or moving. Need positions and velocity
  // vectors. Is probably too heavy for checking all collisions, so better use
  // some simpler methors before to check their interactivity. NB: This model
  // assumes a friction model of static only .... NEED MORE DESCRIPTION HERE...

  double k = dPHYSICS_K;

  double x1 = a->x.getEntry(0, 0), y1 = a->x.getEntry(1, 0),
         z1 = a->x.getEntry(2, 0);
  double x2 = b->x.getEntry(0, 0), y2 = b->x.getEntry(1, 0),
         z2 = b->x.getEntry(2, 0);
  double vx1 = a->v.getEntry(0, 0), vy1 = a->v.getEntry(1, 0),
         vz1 = a->v.getEntry(2, 0);
  double vx2 = b->v.getEntry(0, 0), vy2 = b->v.getEntry(1, 0),
         vz2 = b->v.getEntry(2, 0);

  double A = (vx2 - vx1) * (vx2 - vx1) + (vy2 - vy1) * (vy2 - vy1) +
             (vz2 - vz1) * (vz2 - vz1);
  double B = -2.0 * (k * (x2 - x1) * (vx2 - vx1) + (vx2 - vx1) * (vx2 - vx1) +
                     k * (y2 - y1) * (vy2 - vy1) + (vy2 - vy1) * (vy2 - vy1) +
                     k * (z2 - z1) * (vz2 - vz1) + (vz2 - vz1) * (vz2 - vz1));
  double C = k * k * (x2 - x1) * (x2 - x1) + (vx2 - vx1) * (vx2 - vx1) +
             2 * k * (x2 - x1) * (vx2 - vx1) + k * k * (y2 - y1) * (y2 - y1) +
             (vy2 - vy1) * (vy2 - vy1) + 2 * k * (y2 - y1) * (vy2 - vy1) +
             k * k * (z2 - z1) * (z2 - z1) + (vz2 - vz1) * (vz2 - vz1) +
             2 * k * (z2 - z1) * (vz2 - vz1);
  C -= (r1 + r2) * (r1 + r2) *
       (k * k); // Remember to subtract the right hand side of the equation:
                // Ax^2 + Bx + C - R < 0

  double root_;

  // Check if A = 0 (not quadric eqn)
  if (A == (double)0.0) {
    if (B == (double)0.0) {
      return (double)-1.0;
    }
    root_ = -C / B;
  } else {
    // Check if we have a valid solutions (not imaginary):
    double sq = B * B - (double)4.0 * A * C;

    if (sq < (double)0.0) {
      return (double)-1.0;
    }

    // Get our roots
    double rootA = (-B + fsqrt(sq)) / (A * 2);
    double rootB = (-B - fsqrt(sq)) / (A * 2);

    if (rootA < rootB) // If rootA gives longer collision time than rootB
      root_ = rootB;
    else
      root_ = rootA;

    // Check if they are valid
    if (root_ <= (double)0.0) {
      return -1.0;
    }
  }

  // Use inverse of starting function to calculate time at collision
  return -flog(root_) / k;
}

double Billiard::getWallTime(int iWall, udtBall *b) {
  // iWall can be: 0: left, 1: right, 2: top, 3: bottom
  Matrix temp = Matrix(3, 1);

  double k = dPHYSICS_K;
  double r = dBALL_SIZE;
  double w, x, v;

  if (iWall == 0) { // Left
    w = dTABLE_SIZEY / 2 - r;
    x = b->x.getEntry(1, 0);
    v = b->v.getEntry(1, 0);
  } else if (iWall == 1) { // Right
    w = -dTABLE_SIZEY / 2 + r;
    x = b->x.getEntry(1, 0);
    v = b->v.getEntry(1, 0);
  } else if (iWall == 2) { // Top
    w = dTABLE_SIZEX / 2 - r;
    x = b->x.getEntry(0, 0);
    v = b->v.getEntry(0, 0);
  } else if (iWall == 3) { // Bottom
    w = -dTABLE_SIZEX / 2 + r;
    x = b->x.getEntry(0, 0);
    v = b->v.getEntry(0, 0);
  } else {
    return -1;
  }
  if (v == 0)
    return -1;
  double m = 1 - k * (w - x) / v;
  if (m <= 0 || m >= 1)
    return (double)(-1.0);
  double ret = -flog(m) / k;
  return ret;
}

void Billiard::getNextState() {

  if (energy(current->time, current) < dENERGY_ZERO) {
    bPause = false;
    return;
  }

  CState *next = new CState();

  // Some shortcuts ;)
  udtBall **cb = current->uBalls;
  udtBall **nb = next->uBalls;

  double dFullTime =
      -log((double)0.01) / dPHYSICS_K; // Full time of movement - afterwards,
                                       // particle will stop no matter...
  double dLeastTime = dFullTime;
  double dCollision = -1.0;

  // Set active
  for (int i = 0; i < current->iNoBalls; i++) {
    nb[i]->bActive = cb[i]->bActive;
  }

  // Check if ball drops into a hole!
  for (int i = 0; i < current->iNoBalls; i++) {
    if (cb[i]->bActive) {
      for (int j = 0; j < 6; j++) {
        udtBall *ballhole = new udtBall();
        ballhole->x.setEntry(0, 0, holes[j].getEntry(0, 0));
        ballhole->x.setEntry(1, 0, holes[j].getEntry(1, 0));
        ballhole->x.setEntry(2, 0, holes[j].getEntry(2, 0));
        dCollision = getCollisionTime(cb[i], ballhole, 0, dHOLE_SIZE);
        if (dCollision > 0 && dLeastTime > dCollision) {
          dLeastTime = dCollision;
          cb[i]->dHoleTime = dCollision;
        }
      }
    }
  }

  // Check for ball collisions
  for (int i = 0; i < current->iNoBalls; i++) {
    for (int j = i + 1; j < current->iNoBalls; j++) {
      if (i != j && cb[i]->bActive && cb[j]->bActive) {
        dCollision = getCollisionTime(cb[i], cb[j], dBALL_SIZE, dBALL_SIZE);
        if (dCollision > 0 && dLeastTime > dCollision) {
          dLeastTime = dCollision;
          cb[i]->dCollisionTime = dCollision;
          cb[j]->dCollisionTime = dCollision;
        }
      }
    }
  }

  double dLossFactor = 0.85;

  // Check for wall collisions
  for (int i = 0; i < current->iNoBalls; i++) {
    if (cb[i]->bActive) {
      // Top wall
      double dWT0 = getWallTime(0, cb[i]);
      // 		std::cout << "a "; cb[i]->coll.print();
      double margin = 0.0;
      if (dWT0 > margin && dWT0 != -1) {
        if (dWT0 < dLeastTime) {
          dLeastTime = dWT0;
          cb[i]->dWallTime = dWT0;
          Matrix m = getV(dWT0, cb[i]);
          m.setEntry(1, 0, -m.getEntry(1, 0) * dLossFactor);
          cb[i]->coll = m;
        }
      }
      double dWT1 = getWallTime(1, cb[i]);
      if (dWT1 > margin && dWT1 != -1) {
        if (dWT1 < dLeastTime) {
          dLeastTime = dWT1;
          cb[i]->dWallTime = dWT1;
          Matrix m = getV(dWT1, cb[i]);
          m.setEntry(1, 0, -m.getEntry(1, 0) * dLossFactor);
          cb[i]->coll = m;
        }
      }
      double dWT2 = getWallTime(2, cb[i]);
      if (dWT2 > margin && dWT2 != -1) {
        if (dWT2 < dLeastTime) {
          dLeastTime = dWT2;
          cb[i]->dWallTime = dWT2;
          Matrix m = getV(dWT2, cb[i]);
          m.setEntry(0, 0, -m.getEntry(0, 0) * dLossFactor);
          cb[i]->coll = m;
        }
      }
      double dWT3 = getWallTime(3, cb[i]);
      if (dWT3 > margin && dWT3 != -1) {
        if (dWT3 < dLeastTime) {
          dLeastTime = dWT3;
          cb[i]->dWallTime = dWT3;
          Matrix m = getV(dWT3, cb[i]);
          m.setEntry(0, 0, -m.getEntry(0, 0) * dLossFactor);
          cb[i]->coll = m;
        }
      }
    }
  }

  // If not collision, move all balls toward 1% of the initial velocity applied
  // to cueBall
  if (dLeastTime == dFullTime) {
    // Calculate ball positions when v < 1%xv_0. Happenes at t = -ln(1%)/k
    for (int i = 0; i < current->iNoBalls; i++) {
      if (cb[i]->bActive) {
        nb[i]->x = cb[i]->x + getX(dFullTime, cb[i]);
      }
    }
  } else {
    // Now, move all balls forward in time, of dLeastTime time units
    for (int i = 0; i < current->iNoBalls; i++) {
      if (cb[i]->bActive) {
        nb[i]->x = cb[i]->x + getX(dLeastTime, cb[i]);
        double margin = 0.9999;
        if (nb[i]->x.getEntry(1, 0) < -dTABLE_SIZEY / 2.0 + dBALL_SIZE)
          nb[i]->x.setEntry(1, 0, -dTABLE_SIZEY / 2.0 * margin + dBALL_SIZE);
        if (nb[i]->x.getEntry(1, 0) > dTABLE_SIZEY / 2.0 - dBALL_SIZE)
          nb[i]->x.setEntry(1, 0, dTABLE_SIZEY / 2.0 * margin - dBALL_SIZE);
        if (nb[i]->x.getEntry(0, 0) < -dTABLE_SIZEX / 2.0 + dBALL_SIZE)
          nb[i]->x.setEntry(0, 0, -dTABLE_SIZEX / 2.0 * margin + dBALL_SIZE);
        if (nb[i]->x.getEntry(0, 0) > dTABLE_SIZEX / 2.0 - dBALL_SIZE)
          nb[i]->x.setEntry(0, 0, dTABLE_SIZEX / 2.0 * margin - dBALL_SIZE);
        // Leave the velocities alone, since they are 0 anyway...
      }
    }

    // First set a scaled vector to indicate collisions for all balls
    int iNoColl = 0;
    for (int i = 0; i < current->iNoBalls; i++) {
      if (cb[i]->bActive) {
        if (cb[i]->dHoleTime == dLeastTime) {
          nb[i]->bActive = false;
          if (i == 0)
            bLookAtCue = false;
        } else if (cb[i]->dWallTime > 0) {
          cb[i]->coll = cb[i]->coll * getV(dLeastTime, cb[i]).len() /
                        cb[i]->coll.len() * dLossFactor;
        } else if (cb[i]->dCollisionTime == dLeastTime) {
          iNoColl++;
          for (int j = i; j < current->iNoBalls; j++) {
            if (cb[i]->bActive) {
              if (cb[j]->dCollisionTime == dLeastTime && i != j) {

                // Get velocities of balls at collision
                Matrix v1 = getV(dLeastTime, cb[i]);
                Matrix v2 = getV(dLeastTime, cb[j]);

                // Get vectors pointing from ball to ball
                Matrix vec1 = Matrix(1, 3);
                vec1.setEntry(
                    0, 0, nb[j]->x.getEntry(0, 0) - nb[i]->x.getEntry(0, 0));
                vec1.setEntry(
                    0, 1, nb[j]->x.getEntry(1, 0) - nb[i]->x.getEntry(1, 0));
                vec1.setEntry(
                    0, 2, nb[j]->x.getEntry(2, 0) - nb[i]->x.getEntry(2, 0));
                vec1 = vec1 / vec1.len(); // Normalize

                Matrix vec2 = Matrix(1, 3);
                vec2.setEntry(
                    0, 0, nb[i]->x.getEntry(0, 0) - nb[j]->x.getEntry(0, 0));
                vec2.setEntry(
                    0, 1, nb[i]->x.getEntry(1, 0) - nb[j]->x.getEntry(1, 0));
                vec2.setEntry(
                    0, 2, nb[i]->x.getEntry(2, 0) - nb[j]->x.getEntry(2, 0));
                vec2 = vec2 / vec2.len(); // Normalize

                // Calculate the parallel exchanging forces
                Matrix p1 = vec1.transpose() * (vec1 * v1).getEntry(0, 0);
                Matrix p2 = vec2.transpose() * (vec2 * v2).getEntry(0, 0);

                // Calculate original normal forces
                Matrix n1 = v1 - p1;
                Matrix n2 = v2 - p2;

                // Now add together the original normal force, and the exchange
                // of the parallel forces
                cb[i]->coll = v1 - p1 + p2;
                cb[j]->coll = v2 - p2 + p1;
              }
            }
          }
        }
      }
    }

    // Set velocities
    for (int i = 0; i < current->iNoBalls; i++) {
      if (cb[i]->bActive) {
        nb[i]->v.setEntry(0, 0, cb[i]->v.getEntry(0, 0));
        nb[i]->v.setEntry(1, 0, cb[i]->v.getEntry(1, 0));
        nb[i]->v.setEntry(2, 0, cb[i]->v.getEntry(2, 0));
        nb[i]->v = getV(dLeastTime, cb[i]);
      }
    }

    // Now calculate all vectors from collisions
    for (int i = 0; i < current->iNoBalls; i++) {
      if (cb[i]->bActive) {
        if (cb[i]->dCollisionTime == dLeastTime ||
            cb[i]->dWallTime == dLeastTime) {
          nb[i]->v = cb[i]->coll;
        }
      }
    }
  }

  // Set next state tp 'next'
  if (dLeastTime == dFullTime) {
    finaltime = current->time + dFullTime;
  }
  current->endtime = current->time + dLeastTime;
  next->time = current->endtime; // Set end time of collision
  next->endtime = next->time;
  current->next = next;

  // Go to next state
  gotoNextState();
}

void Billiard::gotoNextState() {
  if (current->next != 0)
    current = current->next;
}

void Billiard::displayFunction() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
  glLoadIdentity();            // Reset The Projection Matrix
  gluPerspective(60.0f, (GLfloat)100 / (GLfloat)100, 0.1f, 250.0f);
  glMatrixMode(GL_MODELVIEW); // Select The Projection Matrix

  GLfloat light_pos[] = {0.0, 0.0, 30.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

  // Find the state to draw by the time
  drawState = states; // Set to the head state
  while (true) {
    if (drawState->next == 0)
      break;
    if (drawState->endtime >= time)
      break;
    drawState = drawState->next;
  }

  glPushMatrix();

  for (int i = 0; i < 6; i++) {
    glPushMatrix();
    glScaled(1.0, 1.0, 0.2);
    glColor3d(0.0, 0.0, 0.0);
    glTranslated(holes[i].getEntry(0, 0), holes[i].getEntry(1, 0),
                 holes[i].getEntry(2, 0));
    glutSolidSphere(dHOLE_SIZE, 20, 20);
    glPopMatrix();
  }

  for (int i = 0; i < drawState->iNoBalls; i++) {
    if (drawState->uBalls[i]->bActive || false) {
      glPushMatrix();
      udtBall *b = drawState->uBalls[i];

      Matrix pos = b->x + getX(time - drawState->time, b);

      glTranslated(pos.getEntry(0, 0), pos.getEntry(1, 0), 0);

      // "Shadow"
      glDisable(GL_LIGHTING);
      glPushMatrix();
      glTranslated(pos.getEntry(0, 0) * 0.03, pos.getEntry(1, 0) * 0.03,
                   -dBALL_SIZE * 0.02);
      glScaled(1.0, 1.0, 0.1);
      glColor4d(b->red * 0.1, b->green * 0.1, b->blue * 0.1, 0.5);
      glutSolidSphere(dBALL_SIZE, 20, 10);
      glPopMatrix();
      glEnable(GL_LIGHTING);

      // Draw small mark for player 2 balls...
      if (!b->bFirstPlayer) {
        glPushMatrix();
        glTranslated(0.0, 0.0, dBALL_SIZE * 2);
        glScaled(1.0, 1.0, 1.0);
        glColor3d(0.9, 0.9, 0.9);
        glutSolidSphere(dBALL_SIZE / 4, 10, 10);
        glPopMatrix();
      }

      // Transalte to cull ball location
      glTranslated(0.0, 0.0, pos.getEntry(2, 0));
      glColor3d(b->red, b->green, b->blue);
      glutSolidSphere(dBALL_SIZE, 20, 20);

      if (false) {
        double dFullTime = -log((double)0.01) / dPHYSICS_K;
        Matrix vel = getX(dFullTime, b) - getX(time - drawState->time, b);
        glColor3d(1.0, 0.0, 0.0);
        glLineWidth(2.0);
        glBegin(GL_LINE);
        glVertex3d(0.0, 0.0, dBALL_SIZE);
        glVertex3d(vel.getEntry(0, 0), vel.getEntry(1, 0),
                   vel.getEntry(2, 0) + dBALL_SIZE);
        glEnd();

        Matrix posnext = getX(drawState->endtime - drawState->time, b) -
                         getX(time - drawState->time, b);
        glColor3d(0.0, 1.0, 0.0);
        glLineWidth(4.0);
        glBegin(GL_LINE);
        glVertex3d(0.0, 0.0, dBALL_SIZE);
        glVertex3d(posnext.getEntry(0, 0), posnext.getEntry(1, 0),
                   posnext.getEntry(2, 0) + dBALL_SIZE);
        glEnd();
      }
      glPopMatrix();
    }
  }

  glColor3f(0.2, 0.5, 0.2);
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-1 * dTABLE_SIZEX / 2, -1 * dTABLE_SIZEY / 2, 0.0);
  glVertex3f(1 * dTABLE_SIZEX / 2, -1 * dTABLE_SIZEY / 2, 0.0);
  glVertex3f(1 * dTABLE_SIZEX / 2, 1 * dTABLE_SIZEY / 2, 0.0);
  glVertex3f(-1 * dTABLE_SIZEX / 2, 1 * dTABLE_SIZEY / 2, 0.0);
  glEnd();

  glPopMatrix();

  udtBall *cb = drawState->uCueBall;
  Matrix cbpos = cb->x + getX(time - drawState->time, cb);

  // Check if to look at cue ball
  if (bLookAtCue) {
    if (drawState->uCueBall->bActive) {
      glLoadIdentity();
      if (bLookTop) {
        double distance = 50;
        gluLookAt(cbpos.getEntry(0, 0) - aim.getEntry(0, 0) * distance,
                  cbpos.getEntry(1, 0) - aim.getEntry(1, 0) * distance,
                  cbpos.getEntry(2, 0) - aim.getEntry(2, 0) * distance +
                      distance / 2,
                  cbpos.getEntry(0, 0), cbpos.getEntry(1, 0),
                  cbpos.getEntry(2, 0), 0.0, 0.0, 1.0);
      } else if (bLookCenter) {
        gluLookAt(0.0, 0.0, 40.0, cbpos.getEntry(0, 0), cbpos.getEntry(1, 0),
                  cbpos.getEntry(2, 0), 0.0, 0.0, 1.0);
      }
    }
  }

  glutSwapBuffers();
}

void Billiard::keyboardFunction(unsigned char key, int, int) {

  double *dP = new double[9];
  Matrix add;
  for (int i = 0; i < 9; i++)
    dP[i] = 0;

  switch (key) {
  case '1': // Default camera view
    bLookAtCue = false;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, dTABLE_SIZEX, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    break;
  case '2': // Cue ball overview (close)
    bLookAtCue = true;
    bLookTop = true;
    bLookCenter = false;
    break;
  case '3': // Cue ball overview (close)
    bLookAtCue = true;
    bLookTop = false;
    bLookCenter = true;
    break;
  case 'p': // Apply force 'up', or in +x direction, to cue ball
  case 'P':
    bPause = !bPause;
    std::cout << std::endl << " - Pause: " << bPause << std::endl << std::endl;
    break;
  case 'i': // Apply force 'up', or in +x direction, to cue ball
  case 'I':
    current->uCueBall->v.setEntry(0, 0, (double)900.0);
    current->uCueBall->v.setEntry(1, 0, (double)0.0);
    break;
  case 'y': // Apply force 'up', or in +x direction, to cue ball
  case 'Y':
    current->uCueBall->v.setEntry(0, 0, (double)150.0);
    current->uCueBall->v.setEntry(1, 0, (double)5.0);
    break;
  case 'u': // Apply force 'up', or in +x direction, to cue ball
  case 'U':
    current->uCueBall->v.setEntry(0, 0, (double)-50.0);
    current->uCueBall->v.setEntry(1, 0, (double)200.0);
    break;
  case 'e': // Apply force 'up', or in +x direction, to cue ball
  case 'E':
    current->uCueBall->v.setEntry(
        0, 0, current->uCueBall->v.getEntry(0, 0) + (double)0.5);
    current->uCueBall->v.setEntry(
        1, 0, current->uCueBall->v.getEntry(1, 0) + (double)-0.5);
    break;
  case 'n': // Get next state
  case 'N':
    bPause = true;
    getNextState();
    break;
  case 'g': // Goto next state
  case 'G':
    timeStep *= 1.1;
    std::cout << "Timestep: " << timeStep << std::endl;
    break;
  case 'b': // Goto next state
  case 'B':
    timeStep /= 1.1;
    std::cout << "Timestep: " << timeStep << std::endl;
    break;
  case 'f': // Reset
  case 'F':
    time += timeStep;
    if (time > current->time)
      time = current->time;
    std::cout << "Time: " << time << " current time: " << current->time
              << " energy: " << energy(time) << std::endl;
    break;
  case 'v': // Reset
  case 'V':
    time -= timeStep;
    if (time < 0)
      time = 0;
    std::cout << "Time: " << time << " current time: " << current->time
              << " energy: " << energy(time) << std::endl;
    break;
  case 't': // Reset
  case 'T':
    std::cout << " states:\t " << states << "\t endtime:\t " << states->endtime
              << std::endl;
    std::cout << "current:\t " << current << "\t   time:\t " << current->time
              << "\t endtime:\t " << current->endtime << std::endl;
    std::cout << "   draw:\t " << drawState << "\t   time:\t "
              << drawState->time << "\t endtime:\t " << drawState->endtime
              << std::endl;
    break;
  case 'z':
  case 'Z':
    drawState->uCueBall->bActive = true;
    drawState->uCueBall->dHoleTime = -1.0;
    drawState->uCueBall->dCollisionTime = -1.0;
    drawState->uCueBall->dWallTime = -1.0;
    drawState->uCueBall->x.setEntry(0, 0, -dTABLE_SIZEX / 4.0);
    drawState->uCueBall->x.setEntry(1, 0, 0.0);
    drawState->uCueBall->x.setEntry(2, 0, dBALL_SIZE);
    drawState->uCueBall->v.setEntry(0, 0, 0.0);
    drawState->uCueBall->v.setEntry(1, 0, 0.0);
    drawState->uCueBall->v.setEntry(2, 0, 0.0);
    drawState->uCueBall->coll.setEntry(0, 0, 0.0);
    drawState->uCueBall->coll.setEntry(1, 0, 0.0);
    drawState->uCueBall->coll.setEntry(2, 0, 0.0);
    current->uCueBall->bActive = true;
    current->uCueBall->dHoleTime = -1.0;
    current->uCueBall->dCollisionTime = -1.0;
    current->uCueBall->dWallTime = -1.0;
    current->uCueBall->x.setEntry(0, 0, -dTABLE_SIZEX / 4.0);
    current->uCueBall->x.setEntry(1, 0, 0.0);
    current->uCueBall->x.setEntry(2, 0, dBALL_SIZE);
    current->uCueBall->v.setEntry(0, 0, 0.0);
    current->uCueBall->v.setEntry(1, 0, 0.0);
    current->uCueBall->v.setEntry(2, 0, 0.0);
    current->uCueBall->coll.setEntry(0, 0, 0.0);
    current->uCueBall->coll.setEntry(1, 0, 0.0);
    current->uCueBall->coll.setEntry(2, 0, 0.0);
    break;
  case 'r': // Reset
  case 'R':
    Billiard(myOpenGL, myOpenAL);
    break;
  case 27: // Quit
    myOpenAL->doAlutExit();
    myOpenGL->doGlutDestroyWindow();
    exit(0);
    break;
  default:
    std::cout << "  Press r to reset" << std::endl;
    std::cout << "  Press ESC to quit" << std::endl;
    break;
  }
}

void Billiard::specialFunction(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_RIGHT:
    keyboardFunction('w', x, y);
    break;
  case GLUT_KEY_LEFT:;
    keyboardFunction('w', x, y);
    break;
  case GLUT_KEY_UP:
    keyboardFunction('w', x, y);
    break;
  case GLUT_KEY_DOWN:
    keyboardFunction('w', x, y);
    break;
  }
}

void Billiard::mouseFunction(int iButton, int iState, int x, int y) {
  myOpenGL->iMouseButton = iButton;
  myOpenGL->iMouseState = iState;
  mouseMove(myOpenGL->iMouseButton, myOpenGL->iMouseState, x, y);
}

void Billiard::motionFunction(int x, int y) {
  mouseMove(myOpenGL->iMouseButton, myOpenGL->iMouseState, x, y);
}

void Billiard::passiveMotionFunction(int x, int y) {
  if (bAim)
    mouseMove(GLUT_RIGHT_BUTTON, GLUT_DOWN, x, y);
  else
    mouseMove(-1, -1, x, y);
}

void Billiard::reshapeFunction(int w, int h) {
  if (h > w) {
    myOpenGL->iScreenWidth = w;
    myOpenGL->iScreenHeight = w;
  } else {
    myOpenGL->iScreenWidth = h;
    myOpenGL->iScreenHeight = h;
  }
  myOpenGL->iWindowWidth = w;
  myOpenGL->iWindowHeight = h;
  glViewport(0, myOpenGL->iWindowHeight - myOpenGL->iScreenHeight,
             (GLsizei)myOpenGL->iScreenWidth, (GLsizei)myOpenGL->iScreenHeight);
  // 	glMatrixMode(GL_PROJECTION);
  // 	glLoadIdentity() ;
  // 	gluPerspective(60.0,(GLfloat)w/(GLfloat)h,0.9, 200.0) ;
  // 	glMatrixMode(GL_MODELVIEW);
  // 	glLoadIdentity() ;
  //  	glTranslatef(-myOpenGL->iScreenWidth/2, -myOpenGL->iScreenHeight/2, 0.0)
  //  ;
}

void Billiard::idleFunction() {
  passiveMotionFunction((int)dMouseX, (int)dMouseY);
  // 	std::cout << "fint: " << finaltime << "  ct: " << current->time <<
  // std::endl;

  if (!bPause) {
    time += timeStep;
    if (time > current->endtime)
      time = current->endtime;

    if (drawState->endtime - time < timeStep / 2 &&
        (drawState != states || time > timeStep / 2) &&
        (drawState->next != current ||
         timeStep / 2 < current->endtime - time)) {
      bool bWall = false;

      for (int i = 0; i < drawState->iNoBalls; i++) {
        if (drawState->uBalls[i]->bActive) {
          if (drawState->uBalls[i]->dWallTime > 0) {
            bWall = true;
            break;
          }
        }
      }
      //	alSourcef(source[0], AL_GAIN, drawState->uBalls[i]->v.len());
      if (bWall) {
        alSourcePlay(source[1]);
      } else {
        alSourcePlay(source[0]);
      }
    }
  }

  if (current->time > finaltime) {
    // Get next state
    getNextState();
  }

  // Redraw the scene
  glutPostRedisplay();
}

void Billiard::mouseMove(int iButton, int iState, int x, int y) {

  dMouseX = x;
  dMouseY = y;

  // Fix the coords..
  x -= myOpenGL->iScreenWidth / 2;
  // y -= myOpenGL->iScreenHeight / 2;
  double X = x * 0.2;
  double Y = y * 1;

  double theta;
  if (aim.getEntry(1, 0) < 0)
    theta = -acos(aim.getEntry(0, 0));
  else
    theta = acos(aim.getEntry(0, 0));

  if (iButton == GLUT_RIGHT_BUTTON && iState == GLUT_DOWN) {
    bAim = true;

    theta -= (float)X / 10.0 / myOpenGL->iScreenWidth;
    // Turn x diff into rotation of aim
    aim.setEntry(0, 0, cos(theta));
    aim.setEntry(1, 0, sin(theta));
    aim.setEntry(2, 0, 0);
  }
  if (iButton == GLUT_RIGHT_BUTTON && iState == GLUT_UP) {
    bAim = false;
  }
  if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_UP) {
    bAim = false;

    current->uCueBall->v.setEntry(0, 0, aim.getEntry(0, 0) * Y);
    current->uCueBall->v.setEntry(1, 0, aim.getEntry(1, 0) * Y);
    current->uCueBall->v.setEntry(2, 0, aim.getEntry(2, 0) * Y);

    getNextState();
  }
}

OpenGL *Billiard::myOpenGL;
OpenAL *Billiard::myOpenAL;

CState *Billiard::states;
CState *Billiard::current;
CState *Billiard::drawState;
double Billiard::time;
double Billiard::finaltime;
Matrix *Billiard::holes;

double Billiard::dTABLE_SIZEX;
double Billiard::dTABLE_SIZEY;
double Billiard::dGAME_SPEED;
double Billiard::dBALL_SIZE;
double Billiard::dHOLE_SIZE;
double Billiard::dPHYSICS_K;
double Billiard::dENERGY_ZERO;
double Billiard::timeStep;
double Billiard::dMouseX;
double Billiard::dMouseY;
bool Billiard::bAim;
bool Billiard::bPause;
bool Billiard::bLookAtCue;
bool Billiard::bLookTop;
bool Billiard::bLookCenter;
Matrix Billiard::aim;

ALuint Billiard::buffer[2];
ALuint Billiard::source[2];
