#include "grid.h"
#include <stdlib.h>
#include <list>

using namespace std;

Organism* grid::organism_at(int x, int y)
{
	if (x < 0 || y < 0 || x >= size || y >= size)
	{
		throw -1;
	}
	return organisms[y*size + x];
}

void grid::put_organism(int x, int y, Organism* o)
{
	organisms[y*size+x] = o;
}

int grid::get_size()
{
	return size;
}


list<Organism*>* grid::get_occupied_surrounding(int x, int y)
{
	list<Organism*>* result = new list<Organism*>();
	for(int i = -1; i < 2; i++)
	{
		for(int j = -1; j < 2; j++)
		{
			if (!(j==0 && i==0))
			{
				try
				{
					Organism* q = organism_at(x+i, y+j);
					if (q->get_satiation() == -1)
					{ // get ze ants
						result->push_back(q);
					}
				}
				catch(int i)
				{
					//off the board with ye
				}
			}
		}
	}
	return result;
}

list<Organism*>* grid::get_unoccupied_surrounding(int x, int y)
{
	list<Organism*>* result = new list<Organism*>();
	for(int i = -1; i < 2; i++)
	{
		for(int j = -1; j < 2; j++)
		{
			if (!(j==0 && i==0))
			{
				try
				{
					Organism* q = organism_at(x+i, y+j);
					if (q->get_satiation() == -9001)
					{ // a ghost bug
						result->push_back(q);
					}
				}
				catch(int i)
				{
					//off the board with ye
				}
			}
		}
	}
	return result;
}

grid::grid(int size)
{
	this->size = size;
	organisms = new Organism*[size*size];
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			organisms[j*size+i] = new GhostBug(i, j);
		}
	}
}

grid::grid()
{
	this->size = 20;
	organisms = new Organism*[400];
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			organisms[j*size+i] = new GhostBug(i, j);
		}
	}
}
