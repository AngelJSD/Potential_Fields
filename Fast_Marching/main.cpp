#include <iostream>

#include "grilla_FM.hpp"
#include "fastMarching.hpp"

using namespace std;

int main (){

	cGrid grid(5,5);
	cFastMarching fastMarching(10, 10, 2, 2); //cambiar grid por w,h o constructor vacio
	//fastMarching = cFastMarching(grid, 2, 2);
	fastMarching.m_grid.print();

	return 0;
}
