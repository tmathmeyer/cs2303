#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

int height;
int width;

// which board is current
int current_state = 0;

int* read_file(int* array, char *filename, int w, int h)
{
	//stores these for use in other functions
	width = w;
	height = h;

	//open the file
	FILE *f = fopen(filename, "rt");

	//create some temp variables
	char temp;
	int h_t = 0, w_t = 0;
	int w_r;

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
			w_r = w_t;
			w_t = 0;
		}
		else
		{
			put(array, w_t, h_t, temp=='x'?1:0);
			w_t++;
		}
	}

	//close the file
	fclose(f);
	
	//time to center the arrays
	int m_b_a = ((h-h_t)/2)*w + (w-w_r)/2;
	int i = w*h;
	for(; i >= 0; i--)
	{
		if ((i-m_b_a) >=0)
		{
			array[i] = array[i-m_b_a];
		}
		else {
			array[i] = 0;
		}
	}
	



	return array;
}

void run_iterations(int* a, int* b, int* c, int itr, int print, int pause)
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
		else if (current_state == 1)
		{
			if (print) {
				print_array(b);
			}
			iterate(b, c);
			current_state = 2;
		}
		else
		{
			if (print) {
				print_array(c);
			}
			iterate(c, a);
			current_state = 0;
		}

		if (are_equal(a, b) || are_equal(b, c) || are_equal(c, a))
		{
			printf("the game has stabilized on iteration %i of %i\nwith final configuration:\n", i, itr+1);
			print_array(current_state==1 ? a : (current_state==2 ? b : c));
			i = itr;
		}
		else if (pause){
			printf("please press the anykey to continue");
			getchar();
			printf("\f");
		}
	}
	if (!(are_equal(a, b) || are_equal(b, c) || are_equal(c, a)))
	{
		printf("the game has finished all %i iterations\nwith final configuration:\n", itr);
		print_array(current_state==1 ? a : (current_state==2 ? b : c));
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
			int c = get(test, j, i);
			printf("%c ", c==1?'X':' ');
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