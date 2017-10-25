#include <iostream>
#include <random>
#include <time.h>

#include "../A_star/grilla_A_star.hpp"
#include "../A_star/aStar.hpp"
#include "../Fast_Marching/grilla_FM.hpp"
#include "../Fast_Marching/fastMarching.hpp"


#define GRID_SIZE 500

using namespace std;

int main(){

    srand(time(NULL));

    cFastMarching fastMarching(GRID_SIZE,GRID_SIZE);
    cAstar aStar(GRID_SIZE,GRID_SIZE);
    
    for(int i=0; i<GRID_SIZE*3/4; ++i){

        int x,y;
        x=rand() % GRID_SIZE;
        y=rand() % GRID_SIZE;
        fastMarching.m_grid.setObstacle(x,y);
        aStar.m_grid.setObstacle(x,y);
    }

    int inix,iniy,goalx,goaly;
    inix=rand() % GRID_SIZE;
    iniy=rand() % GRID_SIZE;
    while(fastMarching.m_grid.grid[inix][iniy].obstacle){
        inix=rand() % GRID_SIZE;
        iniy=rand() % GRID_SIZE;
    }
    goalx=rand() % GRID_SIZE;
    goaly=rand() % GRID_SIZE;
    while(fastMarching.m_grid.grid[inix][iniy].obstacle){
        goalx=rand() % GRID_SIZE;
        goaly=rand() % GRID_SIZE;
    }

    cout<<"A STAR"<<endl;
    clock_t begin = clock();
    bool pathFound2 = aStar.run(inix, iniy, goalx, goaly);
    if(pathFound2) aStar.genPath(inix, iniy, goalx,goaly);
    else cout<<"PATH NOT FOUND ASTAR";
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time: "<<elapsed_secs<<endl<<endl;

    cout<<"FAST MARCHING"<<endl;
    begin = clock();
    bool pathFound1 = fastMarching.FM(goalx,goaly, inix, iniy);
    if(pathFound1) fastMarching.genPath(inix,iniy);
    else cout<<"PATH NOT FOUND"<<endl;
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time: "<<elapsed_secs<<endl<<endl;

    

    return 0;
}