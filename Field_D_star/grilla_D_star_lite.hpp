#ifndef GRILLA_D_STAR_LITE
#define GRILLA_D_STAR_LITE

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct cCell {

	float g;
	float h;
	float rhs;
	float key;
	float secondaryKey;
	int i,j;
	cCell* p;
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
					grid[i][j].g = 100000;
					grid[i][j].h = 0;
					grid[i][j].rhs = 100000;
					grid[i][j].i = i;
					grid[i][j].j = j;
				}
			}

			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					if (!grid[i][j].obstacle) {
						cout<<"filling"<<endl;
						fillNeightbours(&grid[i][j]);
					}
				}
			}	
		}

		void setObstacle(int i, int j){

			grid[i][j].obstacle=true;
		}

		void fillNeightbours (cCell *c){

			//cout<<"Lleno vecinos"<<endl;
			c->neightbours.clear();
			c->neightbours.resize(8);
			
			if(c->i-1>=0) c->neightbours[0] = (&grid[c->i-1][c->j]);

			if(c->i+1<h) c->neightbours[1] = (&grid[c->i+1][c->j]);

			if(c->j-1>=0) c->neightbours[2] = (&grid[c->i][c->j-1]);

			if(c->j+1<w) c->neightbours[3] = (&grid[c->i][c->j+1]);

			if(c->i-1>0 && c->j+1<w) c->neightbours[4] = (&grid[c->i-1][c->j+1]);

            if(c->i-1>0 && c->j-1>=0) c->neightbours[5] = (&grid[c->i-1][c->j-1]);

            if(c->i+1<h && c->j+1<w) c->neightbours[6] = (&grid[c->i+1][c->j+1]);

            if(c->i+1<h && c->j-1>=0) c->neightbours[7] = (&grid[c->i+1][c->j-1]);

		}

		void reset(){
			
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					grid[i][j].g = 100000;
					grid[i][j].h = 0;
					grid[i][j].rhs = 100000;
					grid[i][j].key = 0;
					grid[i][j].secondaryKey = 0;
					grid[i][j].p = NULL;
				}
			}
		}

		void print(){

			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					printf("(%.1f,%.1f)", grid[i][j].g, grid[i][j].rhs);
				}
				printf("\n");
			}
		}
};

#endif
