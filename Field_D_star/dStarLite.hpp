#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <math.h>
#include <algorithm>

#include "grilla_D_star_lite.hpp"

using namespace std;

class cDstarLite {

	public:
		cGrid m_grid;
		
		vector<cCell> visited;
		vector<cCell*> path, open;
		cDstarLite ();
		cDstarLite (int, int);
        bool run(int, int, int, int);
        void update(cCell*, cCell*);
		float calculateCost(cCell s, cCell *sa, cCell *sb, bool diag);
		float calculate(cCell s, cCell *sa, cCell *sb, bool diag);
        void calculateKey(cCell*);
        float myMin(float a, float b);
		void genPath(int, int, int, int);
};

#endif