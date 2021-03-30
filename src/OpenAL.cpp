
// Header
#include "OpenAL.hpp"

// Con- and destructors ==================================================== //

OpenAL::OpenAL() {
  // Nothing...
}

OpenAL::~OpenAL() {
  // Nothing...
}

// Public access modifiers ================================================= //

//

// Public utility functions ================================================ //

void OpenAL::doAlutInit(int *i, char **&c) { alutInit(i, c); }

void OpenAL::doAlutExit() { alutExit(); }

// Private access modifiers ================================================ //

//

// Private utility functions =============================================== //

//
