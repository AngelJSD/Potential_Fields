#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

#include "robot.hpp"
#include "goal.hpp"
#include "obstacle.hpp"

using namespace std;

void att_fun(float d_x, float d_y, cRobot r, cGoal g){

	float d;
	float angle;

	d = sqrt(pow(g.m_x-r.m_x,2)+pow(g.m_y-r.m_y,2));
	angle = atan((g.m_y-r.m_y)/(g.m_x-r.m_x));

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


int main()
{
    cRobot curiosity(10,10);
	cGoal goal(23,30,2,2,1);
	vector<cObstacle> obstacles;

	for(int i=0; i<5; ++i){

		float auxx=rand()%50;
		while (auxx==curiosity.m_x || auxx==goal.m_x) auxx=rand()%50;
		float auxy=rand()%50;
		while (auxy==curiosity.m_y || auxy==goal.m_y) auxy=rand()%50;
		cObstacle auxobs(auxx,auxy,2,2,1);
		obstacles.push_back(auxobs);
	}

	return 0;
}
