#ifndef CS354_COMMON_HPP
#define CS354_COMMON_HPP

#include <stdint.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#ifdef _WIN32
# include <windows.h>
#endif
#ifdef __MAC__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# ifdef CS354_GENERIC_IMPL
#  include <GLUT/glut.h>
# endif
#else
# include <GL/gl.h>
# include <GL/glu.h>
# ifdef CS354_GENERIC_IMPL
#  include <GL/glut.h>
# endif
# include <GL/glext.h>
#endif

#endif
