#ifndef FASTMARCHING_H
#define FASTMARCHING_H

#include <iostream>

#include "grilla_FM.hpp"

using namespace std;

class cFastMarching {

	public:
		cGrid m_grid;
		vector<cCell> mNarrowBand;

		cFastMarching (cGrid, int, int);
		float solveEikonal(cCell);
		//void init();
		void FM(int, int);
};

#endif
