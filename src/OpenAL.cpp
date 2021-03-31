
// Header
#include "OpenAL.hpp"
#include <AL/al.h>
#include <AL/alut.h>

// Con- and destructors ==================================================== //

OpenAL::OpenAL(int *argc, char **&argv) { doAlutInit(argc, argv); }

OpenAL::~OpenAL() { doAlutExit(); }

// Public utility functions ================================================ //

void OpenAL::init() {
  ALfloat alfVector[] = {0.0, 0.0, 0.0};
  ALfloat listenerOri[] = {0.0, 0.0, 1.0, 0.0, 1.0, 0.0};
  alListenerfv(AL_POSITION, alfVector);
  alListenerfv(AL_VELOCITY, alfVector);
  alListenerfv(AL_ORIENTATION, listenerOri);
}

void OpenAL::add(const char name[], const char filename[]) {
  std::cout << "[OpenAL] add(): " << name << std::endl;
  ALfloat alfVector[] = {0.0, 0.0, 0.0};

  alGenBuffers(1, &buffers[name]);
  alGenSources(1, &sources[name]);

  buffers[name] = alutCreateBufferFromFile((const char *)filename);

  alSourcef(sources[name], AL_PITCH, 1.0f);
  alSourcef(sources[name], AL_GAIN, 1.0f);
  alSourcefv(sources[name], AL_POSITION, alfVector);
  alSourcefv(sources[name], AL_VELOCITY, alfVector);
  alSourcei(sources[name], AL_BUFFER, buffers[name]);
}
void OpenAL::play(const char name[]) {
  // std::cout << "[OpenAL] play(): " << name << std::endl;
  alSourcePlay(sources[name]);
}

void OpenAL::doAlutInit(int *i, char **&c) { alutInit(i, c); }

void OpenAL::doAlutExit() { alutExit(); }
