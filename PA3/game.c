#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

int main(int argc, char*argv[])
{
	// check cmdline args
	int height = atoi(argv[2]);
	int width = atoi(argv[1]);
	int generations = atoi(argv[3]);
	int print = 0;
	int pause = 0;
	if (argc >= 6){
		print = argv[5][0]=='y';
	}
	if (argc >= 7){
		pause = argv[6][0]=='y';
	}

	// init the arrays
	int* grid_a;
	int* grid_b;
	int* grid_c;
	memset(grid_c, 0, width*height);
	memset(grid_b, 0, width*height);
	memset(grid_a, 0, width*height);

	grid_a = read_file(argv[4], width, height);
	run_iterations(test, test2, generations, print, pause);

	return 0;
}


