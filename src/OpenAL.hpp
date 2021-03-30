
#ifndef OPENAL_HPP
#define OPENAL_HPP

// Include
#include <AL/al.h>
#include <AL/alut.h>

class OpenAL {
public:
  // Con- and destructors
  OpenAL();
  ~OpenAL();

  // Public access modifiers
  //

  // Public utility functions
  void doAlutInit(int *, char **&);
  void doAlutExit();

private:
  // Private access modifiers
  //

  // Private utility functions
  //

  // Private variables
  //
};

#endif
