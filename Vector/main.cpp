#include <iostream>
#include <stdio.h>
#include<random>
#include <vector>
#include <time.h>
#include <math.h>

#include "robot.hpp"
#include "goal.hpp"
#include "obstacle.hpp"

#define PI 3.14159265

using namespace std;

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
    cout << "angle " << angle << endl;

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

int main()
{
    cRobot curiosity(5,5);
    cGoal goal(60,60,2,2,1);
    vector<cObstacle> obstacles;

    for(int i=0; i<5; ++i){
        float auxx=rand()%50;
        while (auxx==curiosity.m_x || auxx==goal.m_x) auxx=rand()%50;
        float auxy=rand()%50;
        while (auxy==curiosity.m_y || auxy==goal.m_y) auxy=rand()%50;
        cObstacle auxobs(auxx,auxy,2,2,1);
        obstacles.push_back(auxobs);
    }

    /*
     *cObstacle auxobs1(50,44,2,2,1);
    obstacles.push_back(auxobs1);
    cObstacle auxobs2(54,56,2,2,1);
    obstacles.push_back(auxobs2);
    cObstacle auxobs3(45,59,2,2,1);
    obstacles.push_back(auxobs3);*/

    float dxt,dyt,dx,dy;
int m;
float uno=distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
float otro=goal.m_r;
    do{
    //while(m!=0){
        dx=0; dy=0;

        //cout<<distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y)<<" "<<goal.m_r<<endl;
        att_fun(dxt,dyt,curiosity,goal);
        cout << "goal " << dxt << " " << dyt << endl;
        dx+=dxt; dy+=dyt;
        for(int i=0; i<5; ++i){
            rep_fun(dxt,dyt,curiosity,obstacles[i]);
            cout << "obstacle " << dxt << " " << dyt << endl;
            dx+=dxt; dy+=dyt;
        }
        curiosity.m_x+=dx;
        curiosity.m_y+=dy;
        cout << curiosity.m_x << " " << curiosity.m_y << endl;
        uno=(float)distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
        otro=goal.m_r;
        //int m;
        //cin>>m;
        printf("uno%f",uno);
        printf("   otro%f",otro);

    }
    while(uno-otro>0.000009);

    return 0;
}
