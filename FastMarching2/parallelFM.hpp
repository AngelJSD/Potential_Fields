#ifndef FASTMARCHING_H
#define FASTMARCHING_H

#include <iostream>
#include <math.h>
#include <algorithm>
#include <thread>

#include "grilla_FM.hpp"
//#include "../A_star/grilla_A_star.hpp"

using namespace std;

class cFastMarching {

	public:
		cGrid m_grid;
		
		vector<cCell> mNarrowBand, visited;
		vector<cCell*> path;
        vector<vector<cCell> > nb;
		cFastMarching ();
		cFastMarching (int, int);
		float solveEikonal(cCell);
		//void init();
		bool FM(int, int, int, int);
		void genPath(int, int);
		static bool myfunction (cCell i,cCell j);
		static bool myfunction1 (cCell* i,cCell* j);
		float myMin(float a, float b);

        void parallelFM(int id, cCell actual);

};

#endif
