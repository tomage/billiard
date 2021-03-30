# Billiard makefile

COMPILER = c++
CCFLAGS = -c -g3

all:	main.o CBilliard.o COpenGL.o COpenAL.o CVector.o CMatrix.o
	${COMPILER} -o billiard.out main.o CBilliard.o COpenGL.o COpenAL.o CVector.o CMatrix.o -lGL -lglut -lopenal -lalut -lgmp -lm # -lcore++

main.o:		main.cpp 
	${COMPILER} ${CCFLAGS} main.cpp

CBilliard.o:	CBilliard.cxx
	${COMPILER} ${CCFLAGS} CBilliard.cxx

COpenGL.o:	COpenGL.cxx
	${COMPILER} ${CCFLAGS} COpenGL.cxx

COpenAL.o:	COpenAL.cxx
	${COMPILER} ${CCFLAGS} COpenAL.cxx
	
CVector.o:	CVector.cxx
	${COMPILER} ${CCFLAGS} CVector.cxx
	
CMatrix.o:	CMatrix.cxx
	${COMPILER} ${CCFLAGS} CMatrix.cxx

clean:
	rm *.o*
