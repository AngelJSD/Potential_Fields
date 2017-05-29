#include <iostream>
#include <stdio.h>
#include<random>
#include <vector>
#include <time.h>
#include <math.h>

#include "robot.hpp"
#include "goal.hpp"
#include "obstacle.hpp"
#include "lobstacle.hpp"
#include "arista.cpp"

//////////////////////////////////////////////////GRAFICO////////////////////////
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
using namespace std;
float tamanno = 1.0f;
int up, down,left1,right1;
int alto, ancho;
int indice=0;
vector < vector < pair<float,float> > > poligonos;
vector < pair<float,float> > puntos;
vector < pair<float,float> > lines;
vector < pair<float,float> > mapa;
vector < pair<float,float> > meta;
vector < pair<float,float> > radios; //de los obstaculos
vector < pair<float,float> > meta_radios;
float maxx,minx,maxy,miny;
float R, G, B;

float dxt,dyt,dx,dy;
int m;
float uno;
float otro;
int N_OBS, avance;
//cRobot curiosity(7,1);
cRobot curiosity(-50,-50);
cGoal goal(25,50,2,2,1);
vector<cObstacle> obstacles;

float distancia(float x1, float x2, float y1, float y2){

    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

void att_fun(float &d_x, float &d_y, cRobot r, cGoal g){

    float d;
    float angle;

    d = sqrt(pow(g.m_x-r.m_x,2)+pow(g.m_y-r.m_y,2));
    angle = atan2((g.m_y-r.m_y),(g.m_x-r.m_x));

    if(d<g.m_r){

        d_x=0;
        d_y=0;
    }
    else if(g.m_r<=d && d<=g.m_s+g.m_r){

        d_x=g.m_alpha*(d-g.m_r)*cos(angle);
        d_y=g.m_alpha*(d-g.m_r)*sin(angle);
    }
    else{

        d_x=g.m_alpha*g.m_s*cos(angle);
        d_y=g.m_alpha*g.m_s*sin(angle);
    }
}

void rep_fun(float &d_x, float &d_y, cRobot r, cObstacle o){

    float d;
    float angle;

    d = sqrt(pow(o.m_x-r.m_x,2)+pow(o.m_y-r.m_y,2));
    angle = atan2((o.m_y-r.m_y),(o.m_x-r.m_x));
    //cout << "angle " << angle << endl;

    if(d<o.m_r){

        d_x=cos(angle) > 0 ? -1 : 1;
        d_y=sin(angle) > 0 ? -1 : 1;
        d_x*=1000000;
        d_y*=1000000;
    }
    else if(o.m_r<=d && d<=o.m_s+o.m_r){

        d_x=-o.m_beta*(o.m_r+o.m_s-d)*cos(angle);
        d_y=-o.m_beta*(o.m_r+o.m_s-d)*sin(angle);
    }
    else{

        d_x=0;
        d_y=0;
    }
}

void IniciarGLUT() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Campos potenciales");
}

void printtext(int x, int y, string String)
{
//(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, ancho, 0, alto, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void drawFilledSun(){
    //static float angle;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -10);
    int i, x, y;
    double radius = 0.30;
    //glColor3ub(253, 184, 19);
    glColor3ub(255, 0, 0);
    double twicePi = 2.0 * 3.142;
    x = 0, y = 0;
    glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= 20; i++)   {
        glVertex2f (
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
            );
    }
    glEnd(); //END
}

void PintarEscena() {
   glMatrixMode(GL_MODELVIEW);
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   //glColor3f(R++,G++,B++);
   //glRectf(minx,miny,maxx, maxy);


   ///////////////////////////////////////////////ESPACIO//////////////////////////////////////////////////////
          maxx=meta[0].first+meta_radios[0].first+meta_radios[0].second+1;
          minx=meta[0].first-meta_radios[0].first-meta_radios[0].second-1;
          maxy=meta[0].second+meta_radios[0].first+meta_radios[0].second+1;
          miny=meta[0].second-meta_radios[0].first-meta_radios[0].second-1;

	  for(int i =0; i<puntos.size(); i++)
	  {
		if(puntos[i].first>maxx)maxx=puntos[i].first+1;////x
		if(puntos[i].first<minx)minx=puntos[i].first-1;////x
		if(puntos[i].second>maxy)maxy=puntos[i].second+1;///y
		if(puntos[i].second<miny)miny=puntos[i].second-1;///y
	  }
          for(int i =0; i<mapa.size(); i++)
	  {
		if(mapa[i].first+radios[i].first+radios[i].second>maxx)maxx=mapa[i].first+radios[i].first+radios[i].second+1;////x
		if(mapa[i].first-radios[i].first-radios[i].second<minx)minx=mapa[i].first-radios[i].first-radios[i].second-1;////x
		if(mapa[i].second+radios[i].first+radios[i].second>maxy)maxy=mapa[i].second+radios[i].first+radios[i].second+1;///y
		if(mapa[i].second-radios[i].first-radios[i].second<miny)miny=mapa[i].second-radios[i].first-radios[i].second-1;///y
	  }
   glColor3f(1.0f,1.0f,1.0f);
   //cout<<"painting "<<minx<<" ,  "<<miny <<" maximos "<<maxx<<"  ,  "<<maxy<<endl;
   glRectf(minx,miny,maxx, maxy);
      ///////////////////////////////////////////////EJES//////////////////////////////////////////////////////
   glLineWidth(2.0);
   glColor3f(2.47,0.94,0.37);
   glBegin(GL_LINES);
   glVertex3f(-1000, 0.0, 0.0);
   glVertex3f(1000, 0, 0);
   glVertex3f(0, -1000.0, 0.0);
   glVertex3f(0, 1000, 0);
   glEnd();
   ///////////////////////////////////////////////OBSTACULOS//////////////////////////////////////////////////////
   glPointSize(10.5);
   glBegin(GL_POINTS);
   glColor3f(1.1f,0.0f,0.0f);

      for(int i =0; i<mapa.size(); i++)
	{
		glVertex3f(mapa[i].first,mapa[i].second,0.0f);
                  // sleep(1);
	}
    glEnd();

   glColor3f(1.1f,0.0f,0.0f);

      for(int j =0; j<poligonos.size(); j++)
	{  glBegin(GL_POLYGON);
                for(int i =0; i<poligonos[j].size(); i++)
		glVertex3f(poligonos[j][i].first,poligonos[j][i].second,0.0f);

            glEnd();       // sleep(1);
	}


   glColor3f(1.0f,0.0f,0.0f);///RADIO
   glPointSize(2.5);
   glBegin(GL_POINTS);
   for(int i =0; i<mapa.size(); i++)
   {
	for (double ii = 0.0; ii < 10; ii+=0.01)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = radios[i].first * cosf(ii)+mapa[i].first;//calculate the x component
        float y = radios[i].first * sinf(ii)+mapa[i].second;//calculate the y component
        glVertex2f(x , y);//output vertex
    }
    }
   glEnd();
   glColor3f(0.0f,1.0f,1.0f);///RADIO DE ACCION
   glPointSize(1.5);
   glBegin(GL_POINTS);
   for(int i =0; i<mapa.size(); i++)
   {
	for (double ii = 0.0; ii < 10; ii+=0.01)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = (radios[i].first+radios[i].second) * cosf(ii)+mapa[i].first;//calculate the x component
        float y = (radios[i].first+radios[i].second)  * sinf(ii)+mapa[i].second;//calculate the y component
        glVertex2f(x , y);//output vertex
    }
    }
   glEnd();
   ///////////////////////////////////////////////META//////////////////////////////////////////////////////
   glPointSize(7.5);
   glBegin(GL_POINTS);
   glColor3f(0.1f,1.0f,0.0f);
   glVertex3f(meta[0].first,meta[0].second,0.0f);
   glEnd();
   glColor3f(0.1f,1.0f,0.0f);///RADIO
   glPointSize(2.5);
   glBegin(GL_POINTS);
   for(int i =0; i<1; i++)
   {
	for (double ii = 0.0; ii < 10; ii+=0.01)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = meta_radios[0].first * cosf(ii)+meta[0].first;//calculate the x component
        float y = meta_radios[0].first * sinf(ii)+meta[0].second;//calculate the y component
        glVertex2f(x , y);//output vertex
    }
    }
   glEnd();
   glColor3f(0.0f,1.0f,1.0f);///RADIO DE ACCION
   glPointSize(1.5);
   glBegin(GL_POINTS);
   for(int i =0; i<1; i++)
   {
	for (double ii = 0.0; ii < 10; ii+=0.01)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = (meta_radios[0].first+meta_radios[0].second) * cosf(ii)+meta[0].first;//calculate the x component
        float y = (meta_radios[0].first+meta_radios[0].second)  * sinf(ii)+meta[0].second;//calculate the y component
        glVertex2f(x , y);//output vertex
    }
    }
   glEnd();
   ///////////////////////////////////////////////CAMINO//////////////////////////////////////////////////////
   glPointSize(3.5);
   glBegin(GL_POINTS);
   glColor3f(0.1f,0.0f,1.0f);

      for(int i =0; i<puntos.size(); i++)
	{
		glVertex3f(puntos[i].first,puntos[i].second,0.0f);


        }

   glEnd();

   glPointSize(10.5);
   glBegin(GL_POINTS);
   glColor3f(0.0f,0.0f,0.0f);
   glVertex3f(puntos[0].first,puntos[0].second,0.0f);
   glEnd();

   /*glLineWidth(2.0);
   glColor3f(0.00,1.0,0.0);

      for(int i =0; i<lines.size(); i+=2)
	{
		glBegin(GL_LINES);
		glVertex3f(lines[i].first,lines[i].second,0.0f);
                glVertex3f(lines[i+1].first,lines[i+1].second,0.0f);
	        glEnd();
	}*/

   glutSwapBuffers();
}



void Colorear(int value)
{

 glColor3f(0.0f,1.0f,1.0f);
   glBegin(GL_POINTS);
   int i=0;
   for(int i =0; i<puntos.size(); i++)
	{
	    char string[64];
	    sprintf(string, "a");
            glVertex3f(puntos[i].first,puntos[i].second,0.0f);
	    printtext(puntos[i].first,puntos[i].second,string);
	    //cout<<"here"<<i++<<endl;
        }
   glEnd(); //
   glutTimerFunc(100,Colorear,1);
   glutPostRedisplay();
}
void ReProyectar(int w, int h) {
   ancho = w;
   alto = h;

   GLfloat formato;

   if(h == 0) h = 1;

    glViewport(-10, -10, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   formato = (GLfloat)w / (GLfloat)h;
    if (w <= h) glOrtho (-10.0f*tamanno, 10.0f*tamanno, -10.0f*tamanno / formato, 10.0f*tamanno / formato, 1.0f, -1.0f);
    else glOrtho (-10.0f*tamanno * formato, 10.0f*tamanno * formato, -10.0f*tamanno, 10.0f*tamanno, 1.0f, -1.0f);
    glutDisplayFunc(PintarEscena);
}

void Zoom(int value) {
   if (up) tamanno = tamanno * 1.2;//1.01f;
   if (down) tamanno = tamanno / 1.2;//1.01f;
   if (left1){

	   curiosity.m_x=puntos[0].first;
	   curiosity.m_y=puntos[0].second;
	   puntos.clear();
        float uno=1 ;
	for(int j =0; j<=indice;j++)
	{
	   for(int i=0; i<obstacles.size(); ++i){

	   	if (obstacles[i].m_id==j)
               /* {
		obstacles[i].m_x+=pow(-1,j);
                obstacles[i].m_y+=pow(-1,j);
		}*/

		{if(i>obstacles.size()/2){
			if(obstacles[i].m_x+1>60)
			    avance=-1;
			if(obstacles[i].m_x-1<-60)
			    avance=1;
		       obstacles[i].m_x+=avance;
		}
		else{
			if(obstacles[i].m_y+1>60)
			    avance=-1;
			if(obstacles[i].m_y-1<-60)
			    avance=1;
		       obstacles[i].m_y+=avance;
		}
		}


		//obstacles[i].m_x+=rand()%(i+1)-rand()%N_OBS;
                //obstacles[i].m_y+=rand()%(i+1)-rand()%N_OBS;
		//obstacles[i].m_x+=pow(rand()%2,rand());
                //obstacles[i].m_y+=pow(rand()%2,rand());
	   }
	uno=uno*-1;
	}
	   uno=distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
	   otro=goal.m_r;
	   while(uno-otro>0.000009){
	   	dx=0; dy=0;

		//cout<<distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y)<<" "<<goal.m_r<<endl;
		att_fun(dxt,dyt,curiosity,goal);
		cout << "goal " << dxt << " " << dyt << endl;
		dx+=dxt; dy+=dyt;
		mapa.clear();
   		radios.clear();
		for(int i=0; i<obstacles.size(); ++i){

		    rep_fun(dxt,dyt,curiosity,obstacles[i]);
		    //cout << "obstacle " << dxt << " " << dyt << endl;
		    mapa.push_back(make_pair(obstacles[i].m_x,obstacles[i].m_y));
		    radios.push_back(make_pair(obstacles[i].m_r,obstacles[i].m_s));
		    dx+=dxt; dy+=dyt;
		}
		if(distancia(curiosity.m_x,curiosity.m_x+dx,curiosity.m_y,curiosity.m_y+dy)>curiosity.m_max_step) break;

		curiosity.m_x+=dx;
		curiosity.m_y+=dy;
		cout <<endl<< "Robot"<<curiosity.m_x << " " << curiosity.m_y << endl;

		puntos.push_back(make_pair(curiosity.m_x,curiosity.m_y));

		uno=(float)distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
		otro=goal.m_r;

		printf("uno%f",uno);
		printf("   otro%f",otro);
		cout<<endl;
		//glutReshapeFunc(ReProyectar);


	    }


   }
   if(right1)
   {
    left1=0;
    int i = int(goal.m_x+rand()-rand());
    int j = int(goal.m_y+rand()-rand());
    if(i<minx or i>maxx) i=i%int(maxx+1);
    if(j<miny or j>maxy) j=j%int(maxy+1);

    meta.clear();
    goal.m_x=i;
    goal.m_y=j;
    meta.push_back(make_pair(goal.m_x,goal.m_y));
left1=1;
   }
    ReProyectar(ancho,alto);
    glutTimerFunc(33,Zoom,1);
    glutPostRedisplay();

}

void Flechas(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 1;
   if (key==GLUT_KEY_DOWN) down = 1;
   if (key==GLUT_KEY_LEFT) left1 = 1;
   if (key==GLUT_KEY_RIGHT) right1 = 1;
}

void FlechasUp(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 0;
   if (key==GLUT_KEY_DOWN) down = 0;
   if (key==GLUT_KEY_LEFT) left1 = 0;
   if (key==GLUT_KEY_RIGHT) right1 = 0;
}

//////////////////////////////////////////////////////////////////////////////////

#define PI 3.14159265

using namespace std;


int main(int argc, char **argv)
{
    N_OBS=12;
    avance=1;

    srand(time(NULL));

    for(int i=0; i<N_OBS/2; ++i){
        float auxx=rand()%50-rand()%40;
        while (auxx==curiosity.m_x || auxx==goal.m_x) auxx=rand()%50;
        float auxy=rand()%50-rand()%40;
        while (auxy==curiosity.m_y || auxy==goal.m_y) auxy=rand()%50;
        cObstacle auxobs(auxx,auxy,2,4,1.5);
	auxobs.m_id=indice;
        indice++;
	obstacles.push_back(auxobs);
    }

    for(int i=0; i<2; ++i){
	float auxxi=rand()%50-rand()%40;
	while (auxxi==curiosity.m_x || auxxi==goal.m_x) auxxi=rand()%50;
	float auxyi=rand()%50-rand()%40;
	while (auxyi==curiosity.m_y || auxyi==goal.m_y) auxyi=rand()%50;
        float auxxf=auxxi+(rand()%50-rand()%40)%20;
	while (auxxf==curiosity.m_x || auxxf==goal.m_x) auxxf=rand()%50;
	float auxyf=auxyi+(rand()%50-rand()%40)%20;
	while (auxyf==curiosity.m_y || auxyf==goal.m_y) auxyf=rand()%50;
	arista(auxxi,auxxf,auxyi,auxyf,2);
        lines.push_back(make_pair(auxxi,auxyi));
        lines.push_back(make_pair(auxxf,auxyf));
        for(int i=0; i<x_vec.size(); ++i)
        {      cObstacle auxob(x_vec[i],y_vec[i],2,4,1.5);
	       auxob.m_id=indice;
               obstacles.push_back(auxob);
	}
        x_vec.clear();
	y_vec.clear();
	indice++;
    }


    uno=distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
    otro=goal.m_r;

    while(uno-otro>0.000009){
   	dx=0; dy=0;

	//cout<<distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y)<<" "<<goal.m_r<<endl;
	att_fun(dxt,dyt,curiosity,goal);
	cout << "goal " << dxt << " " << dyt << endl;
	meta.push_back(make_pair(goal.m_x,goal.m_y));
        meta_radios.push_back(make_pair(goal.m_r,goal.m_s));
	dx+=dxt; dy+=dyt;
	for(int i=0; i<obstacles.size(); ++i){
	    rep_fun(dxt,dyt,curiosity,obstacles[i]);
	    //cout << "obstacle " << dxt << " " << dyt << endl;
	    mapa.push_back(make_pair(obstacles[i].m_x,obstacles[i].m_y));
	    radios.push_back(make_pair(obstacles[i].m_r,obstacles[i].m_s));
	    dx+=dxt; dy+=dyt;
	}
	if(distancia(curiosity.m_x,curiosity.m_x+dx,curiosity.m_y,curiosity.m_y+dy)>curiosity.m_max_step) break;
	curiosity.m_x+=dx;
	curiosity.m_y+=dy;
	cout <<endl<< "Robot"<<curiosity.m_x << " " << curiosity.m_y << endl;

	puntos.push_back(make_pair(curiosity.m_x,curiosity.m_y));

	uno=(float)distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
	otro=goal.m_r;

	printf("uno%f",uno);
	printf("   otro%f",otro);
	cout<<endl;
    /* vector< pair<float,float> > auxiliar;
    	    auxiliar.push_back(make_pair(78,10));
    	    auxiliar.push_back(make_pair(11,74));
    	    auxiliar.push_back(make_pair(7,78));
    	    auxiliar.push_back(make_pair(78,0));
    	    auxiliar.push_back(make_pair(20,45));
     poligonos.push_back(auxiliar);
 arista(1,0,	5,8,2);*/

    }



	  glutInit(&argc,argv); //Solo necesario en Linux
  	IniciarGLUT();
	  glutReshapeFunc(ReProyectar);
	  glutDisplayFunc(PintarEscena);

	    glutTimerFunc(33,Zoom,1);
	    glutTimerFunc(100,Colorear,1);
	  glutSpecialFunc(Flechas);
	  glutSpecialUpFunc(FlechasUp);

	  glutMainLoop();


//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

    return 0;
}
