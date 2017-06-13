#include "fastMarching.hpp"

cFastMarching::cFastMarching (cGrid grid, int ini_i, int ini_j){

	this->m_grid = grid;
	FM(ini_i, ini_j);
}

void cFastMarching::solveEikonal(cCell c){

}

void cFastMarching::FM(int ini_i, int ini_j){

	m_grid[ini_i][ini_j].t = 0;
	m_grid[ini_i][ini_j].state = "FROZEN";

	for(int i=0; i<m_grid[ini_i][ini_j].neightbours.size(); ++i){

		cCell n = m_grid[ini_i][ini_j].neightbours[i];
		if( n.state!="FROZEN" ){
			//n.t = solveEikonal(n);
			if(n.state == "UNKNOWN"){
				n.state = "NARROW BAND";
				mNarrowBand.push_back(n);
			}
		}
	}
}
