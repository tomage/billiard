#include "sound.hpp"
#include "OpenAL.hpp"
#include <iostream>

Sound::Sound(OpenAL *system) {
  this->system = system;
  system->init();
}

Sound::~Sound() { delete system; }

void Sound::add(const char name[], const char filename[]) {
  std::cout << "[sound] add(): " << name << std::endl;
  system->add(name, filename);
}

void Sound::play(const char name[]) {
  // std::cout << "[sound] play(): " << name << std::endl;
  system->play(name);
}
