#ifndef GRILLA_FM_H
#define GRILLA_FM_H

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct cCell {

	float h;
	float k;
	float value;
	float vel;
	float t;
	int i,j;
	cCell* p;
	string state;
	vector <cCell*> neightbours;
	bool obstacle = false;
};

class cGrid {

	public:
		vector< vector<cCell> > grid;
		int h, w;
		cGrid (){};
		cGrid (int h, int w){
			
			this->h = h;
			this->w = w;
			cout<<"init"<<endl;
			init();
		}

		void init(){

			//cout<<"GrillaA"<<endl;
			grid.resize(h);

			for (int i = 0; i < h; i++) {

				grid[i].resize(w);
				for (int j = 0; j < w; j++) {
					grid[i][j].h = 0;
					grid[i][j].k = 0;
					grid[i][j].vel = 1;
					grid[i][j].t = 100000;
					grid[i][j].i = i;
					grid[i][j].j = j;
					grid[i][j].state = "UNKNOWN";
				}
			}

			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					if (!grid[i][j].obstacle) 
						fillNeightbours(&grid[i][j]);
				}
			}	
		}

		void setObstacle(int i, int j){

			grid[i][j].obstacle=true;
		}

		void fillNeightbours (cCell *c){

			//cout<<"Lleno vecinos"<<endl;
			c->neightbours.clear();
			
			if(c->i-1>=0) c->neightbours.push_back(&grid[c->i-1][c->j]);

			if(c->i+1<h) c->neightbours.push_back(&grid[c->i+1][c->j]);

			if(c->j-1>=0) c->neightbours.push_back(&grid[c->i][c->j-1]);

			if(c->j+1<w) c->neightbours.push_back(&grid[c->i][c->j+1]);

		}

		void reset(){
			
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					grid[i][j].h = 0;
					grid[i][j].k = 0;
					grid[i][j].value = 0;
					grid[i][j].p = NULL;
					grid[i][j].state = "UNKNOWN";
				}
			}
		}

		void print(){

			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					printf("(%.1f,%.1f)", grid[i][j].h, grid[i][j].k);
				}
				printf("\n");
			}
		}
};

#endif