//
//  util.cpp
//  interface
//
//  Created by Philip Rosedale on 8/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "world.h"
#include "glm/glm.hpp"

float randFloat () {
    return (rand()%10000)/10000.f;
}

void makeCubes(float location[3], float scale, int * index, 
               float * cubes_position, float * cubes_scale, float * cubes_color) {
    int i;
    float spot[3];
    //std::cout << "loc: " << location[0] << "," 
    //<< location[1] << "," << location[2] << "\n";
    if ((*index >= MAX_CUBES) || (scale < SMALLEST_CUBE)) return;
    if (scale < 3 && (randFloat() < .1)) {  
        //  Make a cube
        for (i = 0; i < 3; i++) cubes_position[*index*3 + i] = location[i]+scale/2.0;
        float color = randFloat();
        cubes_scale[*index] = scale;
        cubes_color[*index*3] = color;
        cubes_color[*index*3 + 1] = color;
        cubes_color[*index*3 + 2] = color;
        *index += 1;
        //std::cout << "Loc: " << location[0] << "," << location[1] 
        //<< "," << location[2] << " scale " << scale << "\n";
    } else {
        for (i = 0; i < 8; i++) {
            spot[0] = location[0] + (i%2)*scale/2.0;
            spot[1] = location[1] + ((i/2)%2)*scale/2.0;
            spot[2] = location[2] + ((i/4)%2)*scale/2.0;
            //std::cout << "called with " << spot[0] << "," << spot[1] << "," << spot[2] << "\n";
            makeCubes(spot, scale/2.0, index, cubes_position, cubes_scale, cubes_color);
        }
    }
}

void render_vector(glm::vec3 * vec)
{
    //  Show edge of world 
    glDisable(GL_LIGHTING);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    //  Draw axes
    glColor3f(1,0,0);
    glVertex3f(-1,0,0);
    glVertex3f(1,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-1,0);
    glVertex3f(0, 1, 0);
    glColor3f(0,0,1);
    glVertex3f(0,0,-1);
    glVertex3f(0, 0, 1);
    // Draw vector
    glColor3f(1,1,1);
    glVertex3f(0,0,0);
    glVertex3f(vec->x, vec->y, vec->z);
    // Draw marker dots for magnitude    
    glEnd();
    float particle_attenuation_quadratic[] =  { 0.0f, 0.0f, 2.0f }; // larger Z = smaller particles
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, particle_attenuation_quadratic );
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(vec->x,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,vec->y,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,vec->z);
    glEnd();

}

void render_world_box()
{
    //  Show edge of world 
    glDisable(GL_LIGHTING);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(WORLD_SIZE,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0, WORLD_SIZE, 0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0, 0, WORLD_SIZE);
    glEnd();
}

void outstring(char * string, int length) {
    char out[length];
    memcpy(out, string, length); 
    std::cout << out << "\n";
}

double diffclock(timeval clock1,timeval clock2)
{
	double diffms = (clock2.tv_sec - clock1.tv_sec) * 1000.0;
    diffms += (clock2.tv_usec - clock1.tv_usec) / 1000.0;   // us to ms
    
	return diffms;
}

void drawtext(int x, int y, float scale, float rotate, float thick, int mono, char *string, 
              float r=1.0, float g=1.0, float b=1.0)
{
    //
    //  Draws text on screen as stroked so it can be resized
    //
    int len, i;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(r,g,b);
    glRotated(180+rotate,0,0,1);
    glRotated(180,0,1,0);
    glLineWidth(thick);
    glScalef(scale, scale, 1.0);
    len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
        if (!mono) glutStrokeCharacter(GLUT_STROKE_ROMAN, int(string[i]));
        else glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, int(string[i]));
	}
    glPopMatrix();

}


void drawvec3(int x, int y, float scale, float rotate, float thick, int mono, glm::vec3 vec, 
              float r=1.0, float g=1.0, float b=1.0)
{
    //
    //  Draws text on screen as stroked so it can be resized
    //
    char vectext[20];
    sprintf(vectext,"%3.1f,%3.1f,%3.1f", vec.x, vec.y, vec.z);
    int len, i;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(r,g,b);
    glRotated(180+rotate,0,0,1);
    glRotated(180,0,1,0);
    glLineWidth(thick);
    glScalef(scale, scale, 1.0);
    len = (int) strlen(vectext);
	for (i = 0; i < len; i++)
	{
        if (!mono) glutStrokeCharacter(GLUT_STROKE_ROMAN, int(vectext[i]));
        else glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, int(vectext[i]));
	}
    glPopMatrix();
    
} 
