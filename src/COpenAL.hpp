
#ifndef COPENAL_HPP
#define COPENAL_HPP

// Include
#include <AL/al.h>
#include <AL/alut.h>

class COpenAL {
public:
  // Con- and destructors
  COpenAL();
  ~COpenAL();

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
