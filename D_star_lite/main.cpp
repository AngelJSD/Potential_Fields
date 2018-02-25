#include <cstdlib>
#include <iostream>
#include <random>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "grilla_D_star_lite.hpp"
#include "dStarLite.hpp"

#define COLUMNS 40
#define ROWS 40
#define FPS 60

using namespace std;

cDstarLite dStarLite;

int it, inix, iniy, goalx, goaly, countClicks, screenHeight;
bool iniSeted, goalSeted, clickRightDown, pathFound;

vector<cCell> visited, path, obstacles;

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
    /*if(it<visited.size()){
		 fillCell(visited[it].i,visited[it].j);
		 ++it;
	}
	else{*/
        //cout<<dStarLite.path.size()<<endl;
		for(int i=0; i<dStarLite.path.size(); ++i){
			//cout<<dStarLite.path.size()<<" "<<i<<endl;
            if(dStarLite.path[i]->obstacle){

                dStarLite.m_grid.init();
                pathFound = dStarLite.run(inix, iniy, goalx, goaly);
                dStarLite.m_grid.print();
                if(pathFound) dStarLite.genPath(inix, iniy, goalx, goaly);
                //visited = dStarLite.visited;
                //path = fastMarching.path;
                break;
            }
            else{
                //fillCell(dStarLite.path[i]->i,dStarLite.path[i]->j);
                GLfloat point[2];
                glPointSize(5.0);
                glLineWidth(2.5);
                glColor3f(1.0, 1.0, 0.0);

                glBegin(GL_POINTS);
                    for (int i = 0; i < dStarLite.path.size(); i++){ 
                        point[0]=dStarLite.path[i]->j+0.5;
                        point[1]=(COLUMNS-1)-dStarLite.path[i]->i+0.5;
                        glVertex2fv(&point[0]);
                    }
                glEnd();
                glBegin(GL_LINE_STRIP);
                    for (int i = 0; i < dStarLite.path.size(); i++){ 
                        point[0]=dStarLite.path[i]->j+0.5;
                        point[1]=(COLUMNS-1)-dStarLite.path[i]->i+0.5;
                        glVertex2fv(&point[0]);
                    }
                glEnd();
            }
		}
	//}
    
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
        /*dStarLite.m_grid.setObstacle(y/(500/COLUMNS),x/(500/COLUMNS));
        obstacles.push_back(dStarLite.m_grid.grid[y/(500/COLUMNS)][x/(500/COLUMNS)]);*/
        ++countClicks;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        
        cout<<inix<<endl;
        clock_t begin = clock();
        pathFound = dStarLite.run(inix, iniy, goalx, goaly);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout<<"Time: "<<elapsed_secs<<endl<<endl;
        dStarLite.m_grid.print();
        if(pathFound) dStarLite.genPath(inix, iniy, goalx,goaly);
        visited = dStarLite.visited;
        //path = fastMarching.path;
    }
}

void mouse_motion(int x, int y)
{
    if(countClicks>1 && clickRightDown){
        if((y/(screenHeight/COLUMNS)!=goalx || x/(screenHeight/COLUMNS)!=goaly) && (y/(screenHeight/COLUMNS)!=inix || x/(screenHeight/COLUMNS)!=iniy)) 
            dStarLite.m_grid.setObstacle(y/(screenHeight/COLUMNS),x/(screenHeight/COLUMNS));
        for(int i=0; i<dStarLite.m_grid.grid.size(); ++i){
            for(int j=0; j<dStarLite.m_grid.grid[i].size(); ++j){
                if(dStarLite.m_grid.grid[i][j].obstacle)
                    obstacles.push_back(dStarLite.m_grid.grid[i][j]);
            }
        }

        glutPostRedisplay();
    }
}

int main(int argc, char** argv){

    countClicks = 0;
    iniSeted = false;
    goalSeted = false;
    clickRightDown = false;
    
    dStarLite = cDstarLite (COLUMNS, ROWS);
    /*dStarLite.run(1, 1, 15, 15);
    dStarLite.genPath(1,1,15,15);

    cout<<dStarLite.path.size()<<endl;

    for (int i=0; i<dStarLite.path.size(); ++i){

        cout<<dStarLite.path[i]->i<<","<<dStarLite.path[i]->j<<endl;
    }*/

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