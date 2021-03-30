
// Header
#include "COpenAL.hxx"

// Con- and destructors ==================================================== //

COpenAL::COpenAL() {
  // Nothing...
}

COpenAL::~COpenAL() {
  // Nothing...
}

// Public access modifiers ================================================= //

//

// Public utility functions ================================================ //

void COpenAL::doAlutInit(int *i, char **&c) { alutInit(i, c); }

void COpenAL::doAlutExit() { alutExit(); }

// Private access modifiers ================================================ //

//

// Private utility functions =============================================== //

//
