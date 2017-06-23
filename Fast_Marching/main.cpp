#include <cstdlib>
#include <iostream>
#include <random>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "grilla_FM.hpp"
#include "fastMarching.hpp"

#define COLUMNS 20
#define ROWS 20
#define FPS 40

using namespace std;

int it, inix, iniy, goalx, goaly;

vector<cCell> visited, path;

void init(){

    glClearColor(0.0,0.0,0.0,1.0);
}

void cell(int x, int y){

    glLineWidth(1.0);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void fillCell(int x, int y){

    glRectd(y,(COLUMNS-1)-x,y+1,(COLUMNS-1)-x+1);
}

void drawGrid(){

    glColor3f(1.0,0.0,0.0);
    fillCell(inix,iniy);
    glColor3f(0.0,1.0,0.0);
    fillCell(goalx,goaly);

    for(int i=0; i<ROWS; ++i){
        
        for(int j=0; j<COLUMNS; ++j){

            cell(i,j);
        }
    }
    
}

void display_callback(){

    int x,y;
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    if(it<visited.size()){
		 fillCell(visited[it].i,visited[it].j);
		 ++it;
	}
	else{
		for(int i=0; i<path.size(); ++i){
			fillCell(path[i].i,path[i].j);
		}
	}
    //fillCell(x,y);
    cout<<"here"<<endl;
    glutSwapBuffers();
}

void reshape_callback(int w, int h){

    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int){

    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}

int main(int argc, char** argv) {

	inix=5;
    iniy=5;
    goalx=15;
    goaly=17;
    cFastMarching fastMarching(COLUMNS, ROWS, inix, iniy);
	fastMarching.m_grid.print();
	fastMarching.genPath(goalx,goaly);
	visited = fastMarching.visited;
	path = fastMarching.path;

	it=0;
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Grid");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    init();
    glutMainLoop();

	return 0;
}
/*
int main (){

	cGrid grid(5,5);
	cFastMarching fastMarching(10, 10, 2, 2); //cambiar grid por w,h o constructor vacio
	//fastMarching = cFastMarching(grid, 2, 2);
	fastMarching.m_grid.print();
	fastMarching.genPath(6,6);

	return 0;
}*/
