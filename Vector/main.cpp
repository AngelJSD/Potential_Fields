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

//Funcion que calcula la distancia
float distancia(float x1, float x2, float y1, float y2){

    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

//Funcion de atraccion
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

//Función de repulsion
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
    
    //Robot
    cRobot curiosity(7,1);
    //Objetivo
    cGoal goal(7,20,2,2,1);
    //Vector de obstaculos
    vector<cObstacle> obstacles;
    
    //Lleno vector obstaculos
    //Aleatorio
    /*for(int i=0; i<5; ++i){
        float auxx=rand()%50;
        while (auxx==curiosity.m_x || auxx==goal.m_x) auxx=rand()%50;
        float auxy=rand()%50;
        while (auxy==curiosity.m_y || auxy==goal.m_y) auxy=rand()%50;
        cObstacle auxobs(auxx,auxy,2,2,1);
        obstacles.push_back(auxobs);
    }*/
    
    //Por coordenadas especificas
    /*cObstacle auxobs1(3,5,1,2,1);
    obstacles.push_back(auxobs1);
    cObstacle auxobs2(3,7,1,2,1);
    obstacles.push_back(auxobs2);
    cObstacle auxobs3(3,9,1,2,1);
    obstacles.push_back(auxobs3);
    cObstacle auxobs4(3,11,1,2,1);
    obstacles.push_back(auxobs4);
    cObstacle auxobs5(5,11,1,2,1);
    obstacles.push_back(auxobs5);*/
    cObstacle auxobs6(7,11,1,2,1);
    obstacles.push_back(auxobs6);
    /*cObstacle auxobs7(9,11,1,2,1);
    obstacles.push_back(auxobs7);
    cObstacle auxobs8(11,11,1,2,1);
    obstacles.push_back(auxobs8);
    cObstacle auxobs9(11,9,1,2,1);
    obstacles.push_back(auxobs9);
    cObstacle auxobs10(11,7,1,2,1);
    obstacles.push_back(auxobs10);
    cObstacle auxobs11(11,5,1,2,1);
    obstacles.push_back(auxobs11);*/

    float dxt,dyt,dx,dy;
int m;
float uno=distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
float otro=goal.m_r;
    do{
        dx=0; dy=0;

        //cout<<distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y)<<" "<<goal.m_r<<endl;
	
	//Calculo funcion de atraccion en dxt y dyt
        att_fun(dxt,dyt,curiosity,goal);
        cout << "goal " << dxt << " " << dyt << endl;
        dx+=dxt; dy+=dyt;
	
	//Calculo la repulsion de cada obstaculo
        for(int i=0; i<1; ++i){
            rep_fun(dxt,dyt,curiosity,obstacles[i]);
            cout << "obstacle " << dxt << " " << dyt << endl;
	    //Actualizo dx y dy
            dx+=dxt; dy+=dyt;
        }
	
	//Muevo el robot
        curiosity.m_x+=dx;
        curiosity.m_y+=dy;

        cout << curiosity.m_x << " " << curiosity.m_y << endl;
        uno=(float)distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
        otro=goal.m_r;
        int m;
        cin>>m;
        printf("uno%f",uno);
        printf("   otro%f",otro);

    }
    //Mientras no llegue al goal
    while(uno-otro>0.000009);

    return 0;
}
