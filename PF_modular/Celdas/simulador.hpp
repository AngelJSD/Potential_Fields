#include <GL/glut.h>
#include <unistd.h>
#include <cstring>

#include "potentialfields.hpp"

using namespace std;

cPotentialFields PF;

float R, G, B;
int alto, ancho;
float tamanno = 1.0f;
bool up, down,left1,right1;

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
          PF.maxx=PF.meta[0].first+PF.meta_radios[0].first+PF.meta_radios[0].second+1;
          PF.minx=PF.meta[0].first-PF.meta_radios[0].first-PF.meta_radios[0].second-1;
          PF.maxy=PF.meta[0].second+PF.meta_radios[0].first+PF.meta_radios[0].second+1;
          PF.miny=PF.meta[0].second-PF.meta_radios[0].first-PF.meta_radios[0].second-1;

	  for(int i =0; i<PF.puntos.size(); i++)
	  {
		if(PF.puntos[i].first>PF.maxx)PF.maxx=PF.puntos[i].first+1;////x
		if(PF.puntos[i].first<PF.minx)PF.minx=PF.puntos[i].first-1;////x
		if(PF.puntos[i].second>PF.maxy)PF.maxy=PF.puntos[i].second+1;///y
		if(PF.puntos[i].second<PF.miny)PF.miny=PF.puntos[i].second-1;///y
	  }
          for(int i =0; i<PF.mapa.size(); i++)
	  {
		if(PF.mapa[i].first+PF.radios[i].first+PF.radios[i].second>PF.maxx)PF.maxx=PF.mapa[i].first+PF.radios[i].first+PF.radios[i].second+1;////x
		if(PF.mapa[i].first-PF.radios[i].first-PF.radios[i].second<PF.minx)PF.minx=PF.mapa[i].first-PF.radios[i].first-PF.radios[i].second-1;////x
		if(PF.mapa[i].second+PF.radios[i].first+PF.radios[i].second>PF.maxy)PF.maxy=PF.mapa[i].second+PF.radios[i].first+PF.radios[i].second+1;///y
		if(PF.mapa[i].second-PF.radios[i].first-PF.radios[i].second<PF.miny)PF.miny=PF.mapa[i].second-PF.radios[i].first-PF.radios[i].second-1;///y
	  }
   glColor3f(1.0f,1.0f,1.0f);
   //cout<<"painting "<<minx<<" ,  "<<miny <<" maximos "<<maxx<<"  ,  "<<maxy<<endl;
   glRectf(PF.minx,PF.miny,PF.maxx,PF.maxy);
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

      for(int i =0; i<PF.mapa.size(); i++)
	{
		glVertex3f(PF.mapa[i].first,PF.mapa[i].second,0.0f);
                  // sleep(1);
	}
    glEnd();

   glColor3f(1.1f,0.0f,0.0f);

      for(int j =0; j<PF.poligonos.size(); j++)
	{  glBegin(GL_POLYGON);
                for(int i =0; i<PF.poligonos[j].size(); i++)
		glVertex3f(PF.poligonos[j][i].first,PF.poligonos[j][i].second,0.0f);

            glEnd();       // sleep(1);
	}


   glColor3f(1.0f,0.0f,0.0f);///RADIO
   glPointSize(2.5);
   glBegin(GL_POINTS);
   for(int i =0; i<PF.mapa.size(); i++)
   {
	for (double ii = 0.0; ii < 10; ii+=0.01)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = PF.radios[i].first * cosf(ii)+PF.mapa[i].first;//calculate the x component
        float y = PF.radios[i].first * sinf(ii)+PF.mapa[i].second;//calculate the y component
        glVertex2f(x , y);//output vertex
    }
    }
   glEnd();
   glColor3f(0.0f,1.0f,1.0f);///RADIO DE ACCION
   glPointSize(1.5);
   glBegin(GL_POINTS);
   for(int i =0; i<PF.mapa.size(); i++)
   {
	for (double ii = 0.0; ii < 10; ii+=0.01)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = (PF.radios[i].first+PF.radios[i].second) * cosf(ii)+PF.mapa[i].first;//calculate the x component
        float y = (PF.radios[i].first+PF.radios[i].second)  * sinf(ii)+PF.mapa[i].second;//calculate the y component
        glVertex2f(x , y);//output vertex
    }
    }
   glEnd();
   ///////////////////////////////////////////////META//////////////////////////////////////////////////////
   glPointSize(7.5);
   glBegin(GL_POINTS);
   glColor3f(0.1f,1.0f,0.0f);
   glVertex3f(PF.meta[0].first,PF.meta[0].second,0.0f);
   glEnd();
   glColor3f(0.1f,1.0f,0.0f);///RADIO
   glPointSize(2.5);
   glBegin(GL_POINTS);
   for(int i =0; i<1; i++)
   {
	for (double ii = 0.0; ii < 10; ii+=0.01)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = PF.meta_radios[0].first * cosf(ii)+PF.meta[0].first;//calculate the x component
        float y = PF.meta_radios[0].first * sinf(ii)+PF.meta[0].second;//calculate the y component
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
        float x = (PF.meta_radios[0].first+PF.meta_radios[0].second) * cosf(ii)+PF.meta[0].first;//calculate the x component
        float y = (PF.meta_radios[0].first+PF.meta_radios[0].second)  * sinf(ii)+PF.meta[0].second;//calculate the y component
        glVertex2f(x , y);//output vertex
    }
    }
   glEnd();
   ///////////////////////////////////////////////CAMINO//////////////////////////////////////////////////////
   glPointSize(3.5);
   glBegin(GL_POINTS);
   glColor3f(0.1f,0.0f,1.0f);

      for(int i =0; i<PF.puntos.size(); i++)
	{
		glVertex3f(PF.puntos[i].first,PF.puntos[i].second,0.0f);


        }

   glEnd();

   glPointSize(10.5);
   glBegin(GL_POINTS);
   glColor3f(0.0f,0.0f,0.0f);
   glVertex3f(PF.puntos[0].first,PF.puntos[0].second,0.0f);
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
   for(int i =0; i<PF.puntos.size(); i++)
	{
	    char string[64];
	    sprintf(string, "a");
            glVertex3f(PF.puntos[i].first,PF.puntos[i].second,0.0f);
	    printtext(PF.puntos[i].first,PF.puntos[i].second,string);
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

	   PF.step();
   }
   if(right1)
   {
	   //left1=0;
	   PF.ChangeGoal();
	   //left1=1;
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

void Run_sim(int argc, char **argv){

	up = 0;
	down = 0;
	left1 = 0;
	right1 = 0;
	PF = cPotentialFields();
	PF.Init();

	glutInit(&argc,argv); //Solo necesario en Linux
  	IniciarGLUT();
	glutReshapeFunc(ReProyectar);
	//glutDisplayFunc(PintarEscena);

	glutTimerFunc(33,Zoom,1);
	glutTimerFunc(100,Colorear,1);
	glutSpecialFunc(Flechas);
	glutSpecialUpFunc(FlechasUp);

	glutMainLoop();
}
