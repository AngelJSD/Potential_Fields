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

float cDstarLite::calculateCost(cCell s, cCell *sa, cCell *sb, bool diag){

    if(!sa || !sb)
        return 1000000;
    cCell s1, s2;
    if(diag){
        s1=*sb;
        s2=*sa;
    }
    else{
        s1=*sa;
        s2=*sb;
    }
    if(s1.g<=s2.g){
        return s1.g+1;
    }
    else{
        float f = s1.g-s2.g;
        if(f<=1){
            if(1<=f)
                return s2.g+1.4;
            else{
                
                float y=myMin(f/sqrt(pow(1,2)-pow(f,2)),1);
                cout<<"OJO "<<y<<endl;
                return 1*sqrt(1 + pow(y,2))+f*(1-y)+s2.g;
            }
        }
        else{
            return s2.g+1.4;
        }
    }

}

float cDstarLite::calculate(cCell s, cCell *sa, cCell *sb, bool diag){

    if(!sa || !sb)
        return 1000000;
    cCell s1, s2;
    if(diag){
        s1=*sb;
        s2=*sa;
    }
    else{
        s1=*sa;
        s2=*sb;
    }
    if(s1.g<=s2.g){
        return 0;
    }
    else{
        float f = s1.g-s2.g;
        if(f<=1){
            if(1<=f)
                return 0;
            else{
                
                return myMin(f/sqrt(pow(1,2)-pow(f,2)),1);
            }
        }
        else{
            return 0;
        }
    }

}


/*void cDstarLite::update(cCell* u, cCell* goal){

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
}*/

void cDstarLite::update(cCell* u, cCell* goal){

    vector<cCell*>::iterator it;
    
    if(u->i != goal->i || u->j != goal->j){
        float minrhs=10000000;
        float minrhs1;
        
        minrhs1 = calculateCost(*u, u->neightbours[0], u->neightbours[4], false);
        
        if(minrhs1<minrhs)
            minrhs=minrhs1;
        minrhs1 = calculateCost(*u, u->neightbours[0], u->neightbours[5], false);
        if(minrhs1<minrhs)
            minrhs=minrhs1;
        minrhs1 = calculateCost(*u, u->neightbours[1], u->neightbours[6], false);
        if(minrhs1<minrhs)
            minrhs=minrhs1;
        minrhs1 = calculateCost(*u, u->neightbours[1], u->neightbours[7], false);
        if(minrhs1<minrhs)
            minrhs=minrhs1;
        minrhs1 = calculateCost(*u, u->neightbours[2], u->neightbours[5], false);
        if(minrhs1<minrhs)
            minrhs=minrhs1;
        minrhs1 = calculateCost(*u, u->neightbours[2], u->neightbours[7], false);
        if(minrhs1<minrhs)
            minrhs=minrhs1;
        minrhs1 = calculateCost(*u, u->neightbours[3], u->neightbours[4], false);
        if(minrhs1<minrhs)
            minrhs=minrhs1;
        minrhs1 = calculateCost(*u, u->neightbours[3], u->neightbours[6], false);
        if(minrhs1<minrhs)
            minrhs=minrhs1;

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
    cout<<"vivo "<<m_grid.grid[0][1].neightbours.size()<<endl;
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
            
            if(u->neightbours[i] && !u->neightbours[i]->obstacle){
                
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
    cout<<"PATH:"<<endl;
    while(actual->i!=fin->i || actual->j!=fin->j){

        sort(actual->neightbours.begin(), actual->neightbours.end(), myfunction2);
        path.push_back(actual->neightbours[0]);
        float y;
        y = calculate(*actual, actual->neightbours[0], actual->neightbours[1], true);
        if(y){
            cout<<"1:"<<y<<endl;
            actual->neightbours[0]->j+=y;
        }
        path.push_back(actual->neightbours[0]);
        /*y = calculate(*actual, actual->neightbours[0], actual->neightbours[5], false);
        if(y)
            cout<<"2:"<<y<<endl;
        y = calculate(*actual, actual->neightbours[1], actual->neightbours[6], false);
        if(y)
            cout<<"3:"<<y<<endl;
        y = calculate(*actual, actual->neightbours[1], actual->neightbours[7], false);
        if(y)
            cout<<"4:"<<y<<endl;
        y = calculate(*actual, actual->neightbours[2], actual->neightbours[5], false);
        if(y)
            cout<<"5:"<<y<<endl;
        y = calculate(*actual, actual->neightbours[2], actual->neightbours[7], false);
        if(y)
            cout<<"6:"<<y<<endl;
        y = calculate(*actual, actual->neightbours[3], actual->neightbours[4], false);
        if(y)
            cout<<"7:"<<y<<endl;
        y = calculate(*actual, actual->neightbours[3], actual->neightbours[6], false);
        if(y)
            cout<<"8:"<<y<<endl;*/
        
        actual=actual->neightbours[0];
    }
}