#include <stdlib.h>
#include "grid.h"
#include "organism.h"
#include <list>
#include <time.h>
#include <iostream>

using namespace std;




list<DoodleBug*>* iterate_doodles(list<DoodleBug*>* bugs, grid* g)
{
	list<DoodleBug*>* result = new list<DoodleBug*>();
	list<DoodleBug*>::const_iterator iterator;
	for (iterator = bugs->begin(); iterator != bugs->end(); ++iterator)
	{
		int x = (*iterator)->get_x();
		int y = (*iterator)->get_y();


		// LALALALA this moves the doodle bug
		for(int i = -1; i < 2; i++)
		{
			for(int j = -1; j < 2; j++)
			{
				if (j != 0 || i != 0)
				{
					try
					{
						int ant = g->organism_at(x+i, y+j)->get_satiation();
						if (ant < 0 && ant > -9000)
						{
							g->organism_at(x+i, y+j)->set_sat(-2); // mark the ant for deletion
							g->put_organism(x+i, y+j, *iterator); // move the doodle
							g->put_organism(x, y, new GhostBug(x, y)); // replace the doodle with a ghost
							(*iterator)->set_x(x+i); // update doodle's position
							(*iterator)->set_y(y+j); // update doodle's position
							(*iterator)->set_sat(3); // feeeeeeeeeed me
							i=3;
							j=3;
						}
					}
					catch(int err)
					{}
				}
			}
		}

		//this starves the doodlebug
		if ((*iterator)->get_satiation() == 0)
		{
			g->put_organism(x, y, new GhostBug(x, y));
		}
		else
		{
			result->push_back(*iterator);

			// this breeds the doodlebug
			if ((*iterator)->get_breed() == 7)
			{
				list<Organism*>* surroundings = g->get_surrounding(x, y);
				list<Organism*>::const_iterator surrounding_iterator;
				for (surrounding_iterator = surroundings->begin(); surrounding_iterator != surroundings->end(); ++surrounding_iterator)
				{
					if ((*surrounding_iterator)->get_satiation() == -9001 && (*iterator)->get_breed() == 7)
					{
						int xx = (*surrounding_iterator)->get_x();
						int yy = (*surrounding_iterator)->get_y();
						DoodleBug* db = new DoodleBug(xx, yy);
						g->put_organism(xx, yy, db);
						result->push_back(db);
						(*iterator)->set_breed(0);
					}
				}

				if ((*iterator)->get_breed() == 7)
				{ // it never bred, so decrement it so it can be incremented later.
					(*iterator)->set_breed(6);
				}
			}

			cout << x << " " << y << endl;
			cout << "  b:" << (*iterator)->get_breed() << endl;
			cout << "  s:" << (*iterator)->get_satiation() << endl;
			(*iterator)->set_breed((*iterator)->get_breed()+1);
			(*iterator)->set_sat((*iterator)->get_satiation()-1);
		}
	}



	return result;
}


list<Ant*>* iterate_ants(list<Ant*>* ants, grid* g)
{
	list<Ant*>* result = new list<Ant*>();
		list<Ant*>::const_iterator iterator;

		for (iterator = ants->begin(); iterator != ants->end(); ++iterator)
		{
			int x = (*iterator)->get_x();
			int y = (*iterator)->get_y();

			list<Organism*>* empty_spots = g->get_unoccupied_surrounding(x, y);
			list<Organism*>::const_iterator e_i;
			int to_move = get_random(0, empty_spots->size());
			e_i+=to_move;
			int xx = (*e_i)->get_x();
			int yy = (*e_i)->get_y();
			g->put_organism(xx, yy, *iterator); // move the and
			g->put_organism(x, y, new GhostBug(x, y));
			(*iterator)->set_x(xx);
			(*iterator)->set_y(yy);

	return result;
}



int get_random(int min, int max)
{
	return ((double) rand() / (RAND_MAX)) * (max-min+1) + min;
}

void doodle(grid* g, int count, list<DoodleBug*>* db)
{
	srand(time(NULL));
	int c = 0;
	int size = g->get_size()-1;
	while(c < count)
	{
		int x = get_random(0, size);
		int y = get_random(0, size);
		DoodleBug* d = new DoodleBug(x, y);
		try
		{
			if (g->organism_at(x, y)->get_satiation() == -9001)
			{
				g->put_organism(x, y, d);
				db->push_back(d);
			}
		}
		catch(int i)
		{
			c--;
		}
		c++;
	}
}

void ant(grid* g, int count, list<Ant*>* ants)
{
	srand(time(NULL));
	int c = 0;
	int size = g->get_size()-1;
	while(c < count)
	{
		int x = get_random(0, size);
		int y = get_random(0, size);
		Ant* d = new Ant(x, y);
		try
		{
			if (g->organism_at(x, y)->get_satiation() == -9001)
			{
				g->put_organism(x, y, d);
				ants->push_back(d);
			}
		}
		catch(int i)
		{
			c--;
		}
		c++;
	}
}

ostream& operator << (ostream& os, Organism& o)
{
	os << o.get_rep();
	return os;
}

ostream& operator << (ostream& os, grid& g)
{
	os << "+";
	int s = g.get_size();
	for(int i = 0; i < s; i++)
	{
		os << "=";
	}
	os << "+";
	os << endl;
	for(int i = 0; i < s; i++)
	{
		os << "|";
		for(int j = 0; j < s; j++)
		{
			if (g.organism_at(j, i) != NULL)
			{
				os << *(g.organism_at(j, i)) << "";
			}
			else
			{
				os << "  ";
			}
		}
		os << "|" << endl;
	}
	os << "+";
	for(int i = 0; i < s; i++)
	{
		os << "=";
	}
	os << "+";
	os << endl;
	return os;
}

int main()
{
	int DEFAULT_SIZE = 20;
	int DOODLE_DEFAULT = 5;
	int ANT_DEFAULT = 200;

	list<Ant*>* a = new list<Ant*>();
	list<DoodleBug*>* d = new list<DoodleBug*>();



	grid g(DEFAULT_SIZE);
	doodle(&g, DOODLE_DEFAULT, d);
	ant(&g, ANT_DEFAULT, a);







	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
	d = iterate_doodles(d, &g);
	cout << g;
}
