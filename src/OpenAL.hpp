
#ifndef OPENAL_HPP
#define OPENAL_HPP

#include <AL/al.h>
#include <iostream>
#include <map>

class OpenAL {
public:
  // Con- and destructors
  OpenAL(int *argc, char **&argv);
  ~OpenAL();

  // Public utility functions
  void init();
  void doAlutInit(int *, char **&);
  void doAlutExit();
  void add(const char name[], const char filename[]);
  void play(const char name[]);

private:
  std::map<std::string, ALuint> buffers;
  std::map<std::string, ALuint> sources;
};

#endif
