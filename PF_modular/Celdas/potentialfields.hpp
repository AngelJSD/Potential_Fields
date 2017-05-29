#ifndef POTENTIALFIELDS_H
#define POTENTIALFIELDS_H

#include <random>
#include <time.h>
#include <math.h>

#include "robot.hpp"
#include "goal.hpp"
#include "obstacle.hpp"
//#include "lobstacle.hpp"
#include "arista.hpp"
#define PI 3.14159265

using namespace std;

class cPotentialFields{
	public:
		int indice=0;
		vector < vector < pair<float,float> > > poligonos;
		vector < pair<float,float> > puntos;  //camino
		vector < pair<float,float> > mapa;    //obstaculos
		vector < pair<float,float> > lines;
		vector < pair<float,float> > meta;
		vector < pair<float,float> > radios; //de los obstaculos
		vector < pair<float,float> > meta_radios;
		float maxx,minx,maxy,miny;
		float dxt,dyt,dx,dy;
		int m;
		float uno;
		float otro;
		int N_OBS, avance;
		//cRobot curiosity(7,1);
		cRobot curiosity;
		cGoal goal;
		vector<cObstacle> obstacles;

		cPotentialFields();

		float distancia(float, float, float, float);

		void att_fun(float&, float&, cRobot, cGoal);

		void rep_fun(float&, float&, cRobot, cObstacle);

		void ChangeGoal();

		void step();

		int Init();
};

#endif
