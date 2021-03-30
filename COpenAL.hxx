
#ifndef COPENAL_HXX
#define COPENAL_HXX



// Include
#include <AL/al.h>
#include <AL/alut.h>


// Set Namespace
using namespace std;


class COpenAL {
 public:
 	// Con- and destructors
	COpenAL();
	~COpenAL();
	
	// Public access modifiers
	//
	
	// Public utility functions
	void doAlutInit(int *, char **&);
	void doAlutExit ();
	
 private:
	// Private access modifiers
	//
	
	// Private utility functions
	//
	
	// Private variables
	//
};



#endif
