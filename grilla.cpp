#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#define windowWidth 500
#define windowHeight 500
#define REFRESH 30

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f,1.0f,1.0f); // White (RGB)
    int xsize=0,ysize=0;
    for(int j=0;j<50;j++)
    {

        xsize=0;
        for(int i=0;i<50;i++)
        {
             glBegin(GL_POLYGON);
               glVertex3f(-50.0+xsize, -50.0+ysize, 0.0);
               glVertex3f(-40.0+xsize, -50.0+ysize, 0.0);
               glVertex3f(-40.0+xsize, -40.0+ysize, 0.0);
               glVertex3f(-50.0+xsize, -40.0+ysize, 0.0);
            glEnd();
         xsize+=2.0;
     }
     ysize+=2.0;
     }
     glFlush();

}

void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(REFRESH, timer, 0); // next Timer call milliseconds later
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(windowWidth, windowHeight);   // Set the window's initial width & height
	glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode (GL_PROJECTION);
    glLoadIdentity();


    glutTimerFunc(0, timer, 0);
    glutInitWindowPosition(0, windowWidth); // Position the window's initial top-left corner
    glutDisplayFunc(display);

	glutMainLoop();
}
