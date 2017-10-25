#include "aStar.hpp"

bool myfunction (cCell *i,cCell *j) { return (i->value<j->value); }
bool myfunction1 (cCell *i,cCell *j) { return (i->h<j->h); }

cAstar::cAstar (){};

cAstar::cAstar (int w, int h){

	m_grid = cGrid (w,h);
    //cout<<m_grid.grid[0][0].neightbours.size()<<endl;
	//FM(ini_i, ini_j);
}

bool cAstar::run(int ini_i, int ini_j, int fin_i, int fin_j){

    open.clear();
	visited.clear();
    //m_grid.reset();

    cCell *actual=&m_grid.grid[ini_i][ini_j];
    cout<<actual->neightbours.size()<<endl;
    actual->state="CLOSED";
    cout<<"Running"<<endl;
    while(actual->i != fin_i || actual->j != fin_j){
        //cout<<"VIVO"<<endl;
        for(int i=0; i<actual->neightbours.size(); ++i){
            
            
            //cout<<"VIVO"<<endl;
            if(actual->neightbours[i]->state!="OPEN" &&  actual->neightbours[i]->state!="CLOSED" && !actual->neightbours[i]->obstacle){
                
                actual->neightbours[i]->h=abs(actual->neightbours[i]->i-fin_i)+abs(actual->neightbours[i]->j-fin_j)+1;
                actual->neightbours[i]->k=actual->k + 1;
                actual->neightbours[i]->value = actual->neightbours[i]->h + actual->neightbours[i]->k;
                actual->neightbours[i]->state="OPEN";
                actual->neightbours[i]->p=actual;
                open.push_back(actual->neightbours[i]);
                sort(open.begin(), open.end(), myfunction);
                
            }
            else if(actual->neightbours[i]->state=="OPEN"){
                
                if(actual->k+1<actual->neightbours[i]->k){
                    actual->neightbours[i]->k=actual->k+1;
                    actual->neightbours[i]->value = actual->neightbours[i]->h + actual->neightbours[i]->k;
                    actual->neightbours[i]->p=actual;
                    sort(open.begin(), open.end(), myfunction);
                }
            }
        }
        
        //cout<<open.size()<<endl;
        int lessValue = 0;
        actual=open[0];
        while(lessValue<open.size() && open[lessValue]->value == actual->value) ++lessValue;
        //cout<<"vivo"<<endl;
        if(lessValue>0) sort(open.begin(), open.begin()+lessValue-1, myfunction1);
        actual=open[0];
        //cout<<"vivo1"<<endl;
        actual->state="CLOSED";
        visited.push_back(*actual);
        open.erase(open.begin());
        if(open.empty())
            return false;
        //m_grid.print();
        //cout<<endl;
    }
    return true;
}

void cAstar::genPath(int ini_i, int ini_j, int fin_i, int fin_j){

    path.clear();
	cCell *actual = &m_grid.grid[fin_i][fin_j];
    cout<<"Generating path"<<endl;

    while(actual->i != ini_i || actual->j != ini_j){

        //cout<<"estoy en "<<"("<<actual->i<<","<<actual->j<<") ";
        //cout<<"mi padre es "<<"("<<actual->p->i<<","<<actual->p->j<<")"<<endl;
        path.push_back(actual->p);
        actual=actual->p;
        //int a;
        //cin>>a;
    }
    reverse(path.begin(), path.end());
    cout<<"Generated"<<endl;
}

