#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <math.h>
#include <algorithm>

#include "grilla_A_star.hpp"

using namespace std;

class cAstar {

	public:
		cGrid m_grid;
		
		vector<cCell> visited;
		vector<cCell*> path, open;
		cAstar ();
		cAstar (int, int);
        bool run(int, int, int, int);
		//float solveEikonal(cCell);
		//void init();
		//void FM(int, int);
		void genPath(int, int, int, int);
};

#endif
