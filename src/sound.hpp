
#ifndef SOUND_HPP
#define SOUND_HPP

#include "OpenAL.hpp"

class Sound {
public:
  Sound(OpenAL *system);
  ~Sound();
  void add(const char name[], const char filename[]);
  void play(const char name[]);

private:
  OpenAL *system;
};

#endif
