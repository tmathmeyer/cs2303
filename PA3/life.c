#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

int height;
int width;

// which board is current
int current_state = 0;

void read_file(char *filename, int w, int h, int* a, int* b)
{
	memset(a,0,w*h);
	memset(b,0,w*h);

	width = w;
	height = h;
	//init variables
	FILE *f = fopen(filename, "rt");
	char temp;
	int h_t = 0, w_t = 0;
	int delta_x, delta_y;

	while((temp = fgetc(f)) != EOF)
	{
		if (h_t >= height)
		{
			fclose(f);
			break;
		}
		else if (temp == '\n' || w_t >= width)
		{
			h_t++;
			delta_x = (w - w_t) / 2;
			w_t = 0;
		}
		else
		{
			print_array(a);
			printf("test\n");
			put(b, w_t, h_t, temp=='x'?1:0);
			w_t++;
		}
	}

	delta_y = (h - h_t) / 2;

	//close the file and exit
	fclose(f);

	printf("wewoooo");

	//now we need to center the data
	int i,j;
	for(i = 0; i < h - 2*delta_y; i++)
	{
		for(j = 0; j < w - 2*delta_x; i++)
		{
			put(a, delta_x+j, delta_y+i, get(b, delta_x+j, delta_y+i));
		}
	}

	memset(b,0,w*h);
	
}

void run_iterations(int* a, int* b, int itr, int print, int pause)
{	
	
	int i;
	for(i = 0; i < itr; i++)
	{
		if (current_state == 0)
		{
			if (print) {
				print_array(a);
			}
			iterate(a, b);
			current_state = 1;
		}
		else
		{
			if (print) {
				print_array(b);
			}
			iterate(b, a);
			current_state = 0;
		}

		if (are_equal(a, b))
		{
			printf("the game has stabilized on iteration %i of %i\n", i, itr);
			i = itr;
		}
		else if (pause){
			printf("please press the anykey to continue");
			getchar();
			printf("\f");
		}
	}
	if (!are_equal(a, b))
	{
		printf("the game has finished all %i iterations\n", itr);
	}
}

void iterate(int* B, int* D)
{
	int i, j;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			int s = get_surrounding(B, j, i);
			if (get(B, j, i) == 1)
			{
				if (s > 3 || s < 2)
				{
					put(D, j, i, 0);
				}
				else
				{
					put(D, j, i, 1);
				}
			}
			if (get(B, j, i) == 0)
			{
				if (s == 3)
				{
					put(D, j, i, 1);
				}
				else
				{
					put(D, j, i, 0);
				}
			}
		}
	}
}

int get_surrounding(int* test, int x, int y)
{
	int total = 0;
	if (x > 0)
	{
		total+=get(test, x-1, y);
		if (y > 0)
		{
			total+=get(test, x-1, y-1);
		}
		if (y < height-1)
		{
			total+=get(test, x-1, y+1);
		}
	}
	if (x < width-1)
	{
		total+=get(test, x+1, y);
		if (y > 0)
		{
			total+=get(test, x+1, y-1);
		}
		if (y < height-1)
		{
			total+=get(test, x+1, y+1);
		}
	}
	if (y > 0)
	{
		total+=get(test, x, y-1);
	}
	if (y < height-1)
	{
		total+=get(test, x, y+1);
	}
	return total;
}




void print_array(int* test)
{
	int i, j;
	printf("+");
	for(i = 0; i < width; i++)
	{
		printf("==");
	}
	printf("+\n");
	for(i = 0; i < height; i++)
	{
		printf("|");
		for(j = 0; j < width; j++)
		{
			//char c = get(test, j, i);
			printf("%c ", get(test, j, i)==1?'X':' ');
		}
		printf("|\n");
	}
	printf("+");
	for(i = 0; i < width; i++)
	{
		printf("==");
	}
	printf("+\n");
	printf("\n");
}




int get(int* test, int x, int y)
{
	return test[y*height+x];
}




void put(int* test, int x, int y, int value)
{
	test[y*height+x] = value;
}




int are_equal(int* a, int* b)
{
	int i, j;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			if ((get(a, j, i) - get(b, j, i)) != 0)
			{
				return 0;
			}
		}
	}

	return 1;
}
