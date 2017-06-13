#include <iostream>

#include "grilla_FM.hpp"
#include "fastMarching.hpp"

using namespace std;

int main (){

	cGrid grid(5,5);
	cFastMarching fastMarching(grid, 2, 2); //cambiar grid por w,h o constructor vacio
	//fastMarching = cFastMarching(grid, 2, 2);
	grid.print();

	return 0;
}
