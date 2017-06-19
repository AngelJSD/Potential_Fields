#include "fastMarching.hpp"

bool myfunction (cCell i,cCell j) { return (i.t<j.t); }
float myMin(float a, float b){

	if(a<b) return a;
	return b;
}

cFastMarching::cFastMarching (){};

cFastMarching::cFastMarching (int w, int h, int ini_i, int ini_j){

	m_grid = cGrid (w,h);
	FM(ini_i, ini_j);
}

float cFastMarching::solveEikonal(cCell c){

	float t1,t2, T;

	if(c.i-1<0) t1=m_grid.grid[c.i+1][c.j].t;

	else if(c.i+1>=m_grid.h) t1=m_grid.grid[c.i-1][c.j].t;

	else t1=myMin(m_grid.grid[c.i+1][c.j].t, m_grid.grid[c.i-1][c.j].t);

	if(c.j-1<0) t2=m_grid.grid[c.i][c.j+1].t;

	else if(c.j+1>=m_grid.w) t2=m_grid.grid[c.i][c.j-1].t;

	else t2=myMin(m_grid.grid[c.i][c.j+1].t,m_grid.grid[c.i][c.j-1].t);

	if(abs(t1-t2)<1/c.vel){
		T = (t1+t2 + pow((2/c.vel-pow((t1-t2),2)),0.5))/2;
	}
	else{
		T = min(t1,t2);
	}

	//cout<<"T: "<<T<<endl;
	return T;
}

void cFastMarching::FM(int ini_i, int ini_j){

	m_grid.grid[ini_i][ini_j].t = 0;
	m_grid.grid[ini_i][ini_j].state = "FROZEN";

	cout<<"VIVO"<<endl;
	//chequear aqui!!
	for(int i=0; i<m_grid.grid[ini_i][ini_j].neightbours.size(); ++i){

		cCell *n = m_grid.grid[ini_i][ini_j].neightbours[i];
		cout<<"state: "<<n->state<<endl;
		if( n->state!="FROZEN" ){
			n->t = solveEikonal(*n);
			if(n->state == "UNKNOWN"){
				n->state = "NARROW BAND";
				mNarrowBand.push_back(*n);
				sort(mNarrowBand.begin(), mNarrowBand.end(), myfunction);
			}
		}
	}
	while(!mNarrowBand.empty()){

		cCell actual = mNarrowBand[0];
		mNarrowBand.erase(mNarrowBand.begin());
		for(int i=0; i<actual.neightbours.size(); ++i){

			cCell *n = actual.neightbours[i];
			if( n->state!="FROZEN" ){
				n->t = solveEikonal(*n);
				if(n->state == "UNKNOWN"){
					n->state = "NARROW BAND";
					mNarrowBand.push_back(*n);
					sort(mNarrowBand.begin(), mNarrowBand.end(), myfunction);
				}
			}
		}
	}
}
