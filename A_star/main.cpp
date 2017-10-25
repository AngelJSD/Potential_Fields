#include <cstdlib>
#include <iostream>
#include <random>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "grilla_A_star.hpp"
#include "aStar.hpp"

#define COLUMNS 120
#define ROWS 120
#define FPS 60

using namespace std;

int it, inix, iniy, goalx, goaly, countClicks, screenHeight;
bool iniSeted, goalSeted, clickRightDown, pathFound;

vector<cCell> visited, path, obstacles;

cAstar aStar;

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

    if(iniSeted){
        glColor3f(0.0,1.0,0.0);
        fillCell(inix,iniy);
    }
    if(goalSeted){
        glColor3f(1.0,0.0,0.0);
        fillCell(goalx,goaly);
    }

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
		for(int i=0; i<aStar.path.size(); ++i){
			//cout<<fastMarching.path.size()<<" "<<i<<endl;
            if(aStar.path[i]->obstacle){

                aStar.m_grid.init();
                pathFound = aStar.run(inix, iniy, goalx, goaly);
                aStar.m_grid.print();
                if(pathFound) aStar.genPath(inix, iniy, goalx, goaly);
                //visited = aStar.visited;
                //path = fastMarching.path;
                break;
            }
            else
                fillCell(aStar.path[i]->i,aStar.path[i]->j);
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
    clickRightDown=!state;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        if(countClicks==0){
            inix = y/(screenHeight/COLUMNS);
            iniy = x/(screenHeight/COLUMNS);
            iniSeted = true;
        }
        if(countClicks==1){
            goalx = y/(screenHeight/COLUMNS);
            goaly = x/(screenHeight/COLUMNS);
            goalSeted = true;
        }
        /*aStar.m_grid.setObstacle(y/(500/COLUMNS),x/(500/COLUMNS));
        obstacles.push_back(aStar.m_grid.grid[y/(500/COLUMNS)][x/(500/COLUMNS)]);*/
        ++countClicks;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        
        clock_t begin = clock();
        pathFound = aStar.run(inix, iniy, goalx, goaly);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout<<"Time: "<<elapsed_secs<<endl<<endl;
        //aStar.m_grid.print();
        if(pathFound) aStar.genPath(inix, iniy, goalx,goaly);
        visited = aStar.visited;
        //path = fastMarching.path;
    }
}

void mouse_motion(int x, int y)
{
    if(countClicks>1 && clickRightDown){
        if((y/(screenHeight/COLUMNS)!=goalx || x/(screenHeight/COLUMNS)!=goaly) && (y/(screenHeight/COLUMNS)!=inix || x/(screenHeight/COLUMNS)!=iniy)) 
            aStar.m_grid.setObstacle(y/(screenHeight/COLUMNS),x/(screenHeight/COLUMNS));
        for(int i=0; i<aStar.m_grid.grid.size(); ++i){
            for(int j=0; j<aStar.m_grid.grid[i].size(); ++j){
                if(aStar.m_grid.grid[i][j].obstacle)
                    obstacles.push_back(aStar.m_grid.grid[i][j]);
            }
        }

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {

    countClicks = 0;
    iniSeted = false;
    goalSeted = false;
    clickRightDown = false;
	/*inix=5;
    iniy=5;
    goalx=15;
    goaly=17;*/
    //cFastMarching fastMarching(COLUMNS, ROWS, inix, iniy);
    aStar = cAstar (COLUMNS, ROWS);
	
	it=0;
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    screenHeight = 900;
    glutInitWindowSize(screenHeight,screenHeight);
    glutCreateWindow("Grid");
    glutMouseFunc(mouseClicks);

    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);

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
