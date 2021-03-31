
// Header
#include "OpenAL.hpp"
#include <AL/alut.h>

// Con- and destructors ==================================================== //

OpenAL::OpenAL(int *argc, char **&argv) { doAlutInit(argc, argv); }

OpenAL::~OpenAL() {}

// Public utility functions ================================================ //

void OpenAL::doAlutInit(int *i, char **&c) { alutInit(i, c); }

void OpenAL::doAlutExit() { alutExit(); }
