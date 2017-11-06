#if defined(WIN32)
#include <windows.h>
#endif

#if defined(__APPLE__)
// this is a little outrageous, but it suppresses dozens of warnings
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif