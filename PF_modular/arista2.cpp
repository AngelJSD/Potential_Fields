#include <iostream>
#include <vector>
#include <math.h>
#include <GL/glut.h>
using namespace std;

float tamanno = 1.0f;
int up, down;
int alto, ancho;
vector<float> x_vec, y_vec;
vector < pair<float,float> > mapa; 
vector < pair<float,float> > puntos; 

void IniciarGLUT() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Campos potenciales");
}

void PintarEscena() {
   glMatrixMode(GL_MODELVIEW);
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   glColor3f(1.0f,1.0f,1.0f); 
   glRectf(-1000,-1000,1000, 1000);
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
    glEnd();in
   //glPointSize(10.5);
   //glBegin(GL_POINTS);
   //glColor3f(1.1f,1.0f,0.0f);
   glLineWidth(2.0); 
   glColor3f(0.00,1.94,4.37);
   glBegin(GL_LINES);
      for(int i =0; i<puntos.size(); i++)
	{
		
		glVertex3f(puntos[i].first,puntos[i].second,0.0f);
                  // sleep(1);
	}
   glEnd();
   //glEnd();
   glutSwapBuffers();
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
     ReProyectar(ancho,alto);
    glutTimerFunc(33,Zoom,1);
    glutPostRedisplay();
    
}

void Flechas(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 1;
   if (key==GLUT_KEY_DOWN) down = 1;
}

void FlechasUp(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 0;
   if (key==GLUT_KEY_DOWN) down = 0;
}

void arista(float x1, float x2, float y1, float y2, float r){

        float x_aux, y_aux;
        float angle=atan2((y2-y1),(x2-x1));
	cout<<"angulito"<<angle<<endl;
        float d = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	float m=(y2-y1)/(x2-x1);
        x_vec.push_back(x1+r*cos(angle));
	cout<<"xini: "<<x1+r*cos(angle)<<endl;
        y_vec.push_back(y1+r*sin(angle));
	cout<<"yini: "<<y1+r*sin(angle)<<endl;
        float acum=r;
        int it=0;
	while(acum<d){
			x_vec.push_back(x_vec[it]+r*2*cos(angle));
			cout<<"x  : "<<x_vec[it]+r*2*cos(angle)<<endl;
			y_vec.push_back(y_vec[it]+r*2*sin(angle));
			cout<<"y  : "<<y_vec[it]+r*2*sin(angle)<<endl;
			it++;
			acum+=r*2;
		}
}

int main(int argc, char **argv)
{

        float x1,y1,x2,y2,r;
        cin>>x1>>y1>>x2>>y2>>r;

        arista(x1,x2,	y1,y2,r);
        puntos.push_back(make_pair(x1,y1));
        puntos.push_back(make_pair(x2,y2));
        for(int i=0; i<x_vec.size(); ++i)
                mapa.push_back(make_pair(x_vec[i],y_vec[i]));
          
        cout<<endl;
        for(int i=0; i<y_vec.size(); ++i)
                cout<<x_vec[i]<<" ; "<<y_vec[i]<<endl;
  	glutInit(&argc,argv); //Solo necesario en Linux
  	IniciarGLUT();
	glutReshapeFunc(ReProyectar);
	glutDisplayFunc(PintarEscena);

	glutTimerFunc(33,Zoom,1);
	//glutTimerFunc(100,Colorear,1);
	glutSpecialFunc(Flechas);
        glutSpecialUpFunc(FlechasUp);
	  
	glutMainLoop();
        return 0;

}
