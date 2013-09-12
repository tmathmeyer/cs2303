#include <stdio.h>
#include <stdlib.h>
#include "life.h"

int main(int argc, char*argv[])
{

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

	int test[width*height];
	int test2[width*height];

	read_file(argv[4], width, height, test, test2);
	run_iterations(test, test2, generations, print, pause);

	return 0;
}


