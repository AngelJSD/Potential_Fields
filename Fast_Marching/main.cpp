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

vector<cCell> visited, path, obstacles;

cFastMarching fastMarching;

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

    for(int i=0; i<obstacles.size(); ++i){

        glColor3f(0.0,0.0,0.5);
        fillCell(obstacles[i].i,obstacles[i].j);
    }

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
		for(int i=0; i<fastMarching.path.size(); ++i){
			//cout<<fastMarching.path.size()<<" "<<i<<endl;
            if(fastMarching.path[i]->obstacle){

                fastMarching.m_grid.init();
                fastMarching.FM(inix, iniy);
                fastMarching.m_grid.print();
                fastMarching.genPath(goalx,goaly);
                visited = fastMarching.visited;
                //path = fastMarching.path;
                break;
            }
            else
                fillCell(fastMarching.path[i]->i,fastMarching.path[i]->j);
		}
	}
    
    //fillCell(x,y);
    //cout<<"here"<<endl;
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

void mouseClicks(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        fastMarching.m_grid.setObstacle(y/(500/COLUMNS),x/(500/COLUMNS));
        obstacles.push_back(fastMarching.m_grid.grid[y/(500/COLUMNS)][x/(500/COLUMNS)]);
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        
        fastMarching.FM(inix, iniy);
        fastMarching.m_grid.print();
        fastMarching.genPath(goalx,goaly);
        visited = fastMarching.visited;
        //path = fastMarching.path;
    }
}

int main(int argc, char** argv) {

	inix=5;
    iniy=5;
    goalx=15;
    goaly=17;
    //cFastMarching fastMarching(COLUMNS, ROWS, inix, iniy);
    fastMarching = cFastMarching (COLUMNS, ROWS);
	

	it=0;
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Grid");
    glutMouseFunc(mouseClicks);
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
