//
//  texture.h
//  interface
//
//  Created by Yoz Work on 11/5/12.
//
//

#ifndef __interface__texture__
#define __interface__texture__

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int load_png_as_texture(char* filename);

#endif /* defined(__interface__texture__) */
