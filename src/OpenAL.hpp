
#ifndef OPENAL_HPP
#define OPENAL_HPP

class OpenAL {
public:
  // Con- and destructors
  OpenAL(int *argc, char **&argv);
  ~OpenAL();

  // Public utility functions
  void doAlutInit(int *, char **&);
  void doAlutExit();
};

#endif
