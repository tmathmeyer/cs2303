#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

int main(int argc, char*argv[])
{
	// check cmdline args
	int height = atoi(argv[2]);
	int width = atoi(argv[1]);
	
	blah(width, height);
	
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
	int grid_a[width*height];
	int grid_b[width*height];
	int grid_c[width*height];
	memset(grid_c, 0, width*height*sizeof(int));
	memset(grid_b, 0, width*height*sizeof(int));
	memset(grid_a, 0, width*height*sizeof(int));

	read_file(grid_a, argv[4], width, height);
	run_iterations(grid_a, grid_b, grid_c,  generations, print, pause);

	return 0;
}


