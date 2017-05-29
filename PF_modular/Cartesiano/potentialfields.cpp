#include "potentialfields.hpp"

cPotentialFields::cPotentialFields(){
	curiosity = cRobot(-50,-50);
	cout<<curiosity.m_x<<" "<<curiosity.m_y<<endl;
	goal = cGoal(25,50,2,2,1);
}

float cPotentialFields::distancia(float x1, float x2, float y1, float y2){

	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

void cPotentialFields::att_fun(float &d_x, float &d_y, cRobot r, cGoal g){

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

void cPotentialFields::rep_fun(float &d_x, float &d_y, cRobot r, cObstacle o){

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

void cPotentialFields::ChangeGoal()
{

	int i = int(goal.m_x+rand()-rand());
	int j = int(goal.m_y+rand()-rand());
	if(i<minx or i>maxx) i=i%int(maxx+1);
	if(j<miny or j>maxy) j=j%int(maxy+1);

	meta.clear();
	goal.m_x=i;
	goal.m_y=j;
	meta.push_back(make_pair(goal.m_x,goal.m_y));
}

void cPotentialFields::step(){

	curiosity.m_x=puntos[0].first;
	curiosity.m_y=puntos[0].second;
	puntos.clear();
	float uno=1 ;
	for(int j =0; j<=indice;j++){

		for(int i=0; i<obstacles.size(); ++i){

			if (obstacles[i].m_id==j){

				if(i>obstacles.size()/2){
					if(obstacles[i].m_x+1>60)
						avance=-1;
					if(obstacles[i].m_x-1<-60)
						avance=1;
					if(distancia(obstacles[i].m_x+avance,goal.m_x,obstacles[i].m_y,goal.m_y)>obstacles[i].m_r+obstacles[i].m_s+goal.m_r)
						obstacles[i].m_x+=avance;
				}
				else{
					if(obstacles[i].m_y+1>60)
						avance=-1;
					if(obstacles[i].m_y-1<-60)
						avance=1;
					if(distancia(obstacles[i].m_x,goal.m_x,obstacles[i].m_y+avance,goal.m_y)>obstacles[i].m_r+obstacles[i].m_s+goal.m_r)
						obstacles[i].m_y+=avance;
				}
			}
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
	}
}

int cPotentialFields::Init()
{
	N_OBS=12;
	avance=1;

	srand(time(NULL));

	for(int i=0; i<N_OBS/2; ++i){
		float auxx=rand()%50-rand()%40;
		float auxy=rand()%50-rand()%40;
		while ( distancia(auxx,goal.m_x,auxy,goal.m_y)<6 || distancia(auxx,curiosity.m_x,auxy,curiosity.m_y)<6 ){
			auxx=rand()%50;
			auxy=rand()%50;
		}
		cObstacle auxobs(auxx,auxy,2,4,1.5);
		auxobs.m_id=indice;
		indice++;
		obstacles.push_back(auxobs);
	}

	//Aristas
	for(int i=0; i<2; ++i){

		float auxxi=rand()%50-rand()%40;
		while (auxxi==curiosity.m_x || auxxi==goal.m_x) auxxi=rand()%50;
		float auxyi=rand()%50-rand()%40;
		while (auxyi==curiosity.m_y || auxyi==goal.m_y) auxyi=rand()%50;
		float auxxf=auxxi+(rand()%50-rand()%40)%20;
		while (auxxf==curiosity.m_x || auxxf==goal.m_x) auxxf=rand()%50;
		float auxyf=auxyi+(rand()%50-rand()%40)%20;
		while (auxyf==curiosity.m_y || auxyf==goal.m_y) auxyf=rand()%50;

		cArista arista(auxxi,auxxf,auxyi,auxyf,2);
		lines.push_back(make_pair(auxxi,auxyi));
		lines.push_back(make_pair(auxxf,auxyf));
		for(int i=0; i<arista.x_vec.size(); ++i){

			cObstacle auxob(arista.x_vec[i],arista.y_vec[i],2,4,1.5);
			auxob.m_id=indice;
			obstacles.push_back(auxob);
		}

		arista.x_vec.clear();
		arista.y_vec.clear();
		indice++;
	}

	//Fin Aristas

	uno=distancia(curiosity.m_x,goal.m_x,curiosity.m_y,goal.m_y);
	otro=goal.m_r;

	while(uno-otro>0.000009){
		dx=0; dy=0;
		att_fun(dxt,dyt,curiosity,goal);
		cout << "goal " << dxt << " " << dyt << endl;
		meta.push_back(make_pair(goal.m_x,goal.m_y));
			meta_radios.push_back(make_pair(goal.m_r,goal.m_s));
		dx+=dxt; dy+=dyt;
		for(int i=0; i<obstacles.size(); ++i){
			rep_fun(dxt,dyt,curiosity,obstacles[i]);
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
	}

	return 0;
}
