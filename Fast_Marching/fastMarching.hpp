#ifndef FASTMARCHING_H
#define FASTMARCHING_H

#include <iostream>
#include <math.h>
#include <algorithm>

#include "grilla_FM.hpp"

using namespace std;

class cFastMarching {

	public:
		cGrid m_grid;
		
		vector<cCell> mNarrowBand, visited;
		vector<cCell*> path;
		cFastMarching ();
		cFastMarching (int, int);
		float solveEikonal(cCell);
		//void init();
		void FM(int, int);
		void genPath(int, int);
};

#endif
