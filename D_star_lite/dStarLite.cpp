#include "dStarLite.hpp"

bool myfunction1 (cCell *i,cCell *j) { return (i->key<j->key); }
bool myfunction2 (cCell *i,cCell *j) { return (i->g<j->g); }
float cDstarLite::myMin(float a, float b){

	if(a<b) return a;
	return b;
}

cDstarLite::cDstarLite (){};

cDstarLite::cDstarLite (int w, int h){

	m_grid = cGrid (w,h);
    //cout<<m_grid.grid[0][0].neightbours.size()<<endl;
	//FM(ini_i, ini_j);
}

void cDstarLite::calculateKey(cCell *u){

    u->key= myMin(u->g, u->rhs) + u->h;
}

void cDstarLite::update(cCell* u, cCell* goal){

    vector<cCell*>::iterator it;
    if(u->i != goal->i || u->j != goal->j){
        float minrhs;
        minrhs = u->neightbours[0]->g +1;
        for(int i=0; i<u->neightbours.size(); ++i){
            if(u->neightbours[i]->g +1 <minrhs)
                minrhs = u->neightbours[i]->g +1;
        }
        u->rhs=minrhs;
    }
    it = find(open.begin(), open.end(), u);
    if(it != open.end()){
        open.erase(it);
    }
    if(u->g != u->rhs){
        calculateKey(u);
        open.push_back(u);
        visited.push_back(*u);
        sort(open.begin(), open.end(), myfunction1);
    }
}

bool cDstarLite::run(int ini_i, int ini_j, int fin_i, int fin_j){

    open.clear();
    m_grid.grid[fin_i][fin_j].rhs=0;
    calculateKey(&m_grid.grid[fin_i][fin_j]);
    calculateKey(&m_grid.grid[ini_i][ini_j]);

    open.push_back(&m_grid.grid[fin_i][fin_j]);
    visited.push_back(m_grid.grid[fin_i][fin_j]);
    
    while(open[0]->key<m_grid.grid[ini_i][ini_j].key || 
            m_grid.grid[ini_i][ini_j].rhs!=m_grid.grid[ini_i][ini_j].g)
    {
        cCell *u = open[0];
        open.erase(open.begin());
        if(u->g>u->rhs){
            u->g=u->rhs;
        }
        else{
            u->g=100000;
            update(u, &m_grid.grid[fin_i][fin_j]);
        }
        for(int i=0; i<u->neightbours.size(); ++i){
            if(!u->neightbours[i]->obstacle){
                update(u->neightbours[i], &m_grid.grid[fin_i][fin_j]);
            }
        }
    }

    return true;
}

void cDstarLite::genPath(int x, int y, int xf, int yf){

    cCell *actual, *fin;
    actual=&m_grid.grid[x][y];
    fin=&m_grid.grid[xf][yf];
    path.push_back(actual);
    while(actual->i!=fin->i || actual->j!=fin->j){

        sort(actual->neightbours.begin(), actual->neightbours.end(), myfunction2);
        path.push_back(actual->neightbours[0]);
        actual=actual->neightbours[0];
    }
}