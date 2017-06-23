#ifndef GRILLA_FM_H
#define GRILLA_FM_H

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct cCell {

	float vel;
	float t;
	int i,j;
	string state;
	vector <cCell*> neightbours;
};

class cGrid {

	public:
		vector< vector<cCell> > grid;
		int h, w;
		cGrid (){};
		cGrid (int h, int w){

			this->h = h;
			this->w = w;

			init();
		}

		void init(){

			grid.resize(h);

			for (int i = 0; i < h; i++) {

				grid[i].resize(w);
				for (int j = 0; j < w; j++) {
					grid[i][j].vel = 1;
					grid[i][j].t = 100000;
					grid[i][j].i = i;
					grid[i][j].j = j;
					grid[i][j].state = "UNKNOWN";
				}
			}

			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					fillNeightbours(&grid[i][j]);
				}
			}
		}

		void fillNeightbours (cCell *c){

			if(c->i-1>=0) c->neightbours.push_back(&grid[c->i-1][c->j]);

			if(c->i+1<h) c->neightbours.push_back(&grid[c->i+1][c->j]);

			if(c->j-1>=0) c->neightbours.push_back(&grid[c->i][c->j-1]);

			if(c->j+1<w) c->neightbours.push_back(&grid[c->i][c->j+1]);

		}

		void print(){

			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					printf("(%.1f,%.4f)", grid[i][j].vel, grid[i][j].t);
				}
				printf("\n");
			}
		}
};

#endif
