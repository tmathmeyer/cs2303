#include <stdlib.h>
#include "grid.h"
#include "organism.h"
#include <list>
#include <time.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int antc = 0;
int dbs = 0;

int get_random(int min, int max)
{
	return ((double) rand() / (RAND_MAX)) * (max-min+1) + min;
}


list<DoodleBug*>* iterate_doodles(list<DoodleBug*>* bugs, grid* g)
{
	list<DoodleBug*>* result = new list<DoodleBug*>();
	list<DoodleBug*>::const_iterator iterator;
	for (iterator = bugs->begin(); iterator != bugs->end(); ++iterator)
	{
		int x = (*iterator)->get_x();
		int y = (*iterator)->get_y();

		try
		{
			if (g->organism_at(x, y)->get_ID() != (*iterator)->get_ID())
			{
				throw -1;
			}
			//this starves the doodlebug
			if ((*iterator)->get_satiation() == 0)
			{
				g->put_organism(x, y, new GhostBug(x, y));
			}
			else
			{
				list<Organism*>* empty_spots = g->get_occupied_surrounding(x, y);
				list<Organism*>* non_empty_spots = g->get_unoccupied_surrounding(x, y);

				if (empty_spots->size() != 0)
				{
					list<Organism*>::const_iterator surrounding_iterator;
					int move_to = get_random(0, empty_spots->size()-1);
					int c = 0;
					for (surrounding_iterator = empty_spots->begin(); surrounding_iterator != empty_spots->end(); ++surrounding_iterator)
					{
						if (c == move_to)
						{
							int xx = (*surrounding_iterator)->get_x();
							int yy = (*surrounding_iterator)->get_y();
							(*surrounding_iterator)->set_sat(-2);
							(*iterator)->set_sat(3);

							DoodleBug* eater = new DoodleBug(xx, yy, ++antc);
							eater->set_breed(g->organism_at(x, y)->get_breed()+1);
							g->put_organism(x, y, new GhostBug(x, y));
							g->put_organism(xx, yy, eater);

							c+=9;
							result->push_back(eater);
						}
						c++;
					}
				}
				else
				{
					list<Organism*>::const_iterator surrounding_iterator;
					int move_to = get_random(0, non_empty_spots->size()-1);
					int c = 0;
					for (surrounding_iterator = non_empty_spots->begin(); surrounding_iterator != non_empty_spots->end(); ++surrounding_iterator)
					{
						if (c == move_to)
						{
							int xx = (*surrounding_iterator)->get_x();
							int yy = (*surrounding_iterator)->get_y();

							DoodleBug* eater = new DoodleBug(xx, yy, ++antc);
							eater->set_breed(g->organism_at(x, y)->get_breed()+1);
							eater->set_sat(g->organism_at(x, y)->get_satiation()-1);

							g->put_organism(x, y, new GhostBug(x, y));
							g->put_organism(xx, yy, eater);
							c+=9;
							result->push_back(eater);
						}
						c++;
					}
				}



				// this breeds the doodlebug
				if ((*iterator)->get_breed() == 7)
				{
					list<Organism*>* surroundings = g->get_unoccupied_surrounding(x, y);
					list<Organism*>::const_iterator surrounding_iterator;
					for (surrounding_iterator = surroundings->begin(); surrounding_iterator != surroundings->end(); ++surrounding_iterator)
					{
						if ((*iterator)->get_breed() == 7)
						{
							int xx = (*surrounding_iterator)->get_x();
							int yy = (*surrounding_iterator)->get_y();
							DoodleBug* db = new DoodleBug(xx, yy, ++antc);
							dbs++;
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
			}
		}
		catch(int i)
		{
			//DIE
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

		try
		{
			if (g->organism_at(x, y)->get_ID() != (*iterator)->get_ID())
			{
				throw -1;
			}
			//this starves the ant
			if ((*iterator)->get_satiation() == 0)
			{
				g->put_organism(x, y, new GhostBug(x, y));
			}
			else
			{
				list<Organism*>* empty_spots = g->get_unoccupied_surrounding(x, y);

				if (empty_spots->size() != 0)
				{
					list<Organism*>::const_iterator surrounding_iterator;
					int move_to = get_random(0, empty_spots->size()-1);
					int c = 0;
					for (surrounding_iterator = empty_spots->begin(); surrounding_iterator != empty_spots->end(); ++surrounding_iterator)
					{
						if (c == move_to)
						{
							int xx = (*surrounding_iterator)->get_x();
							int yy = (*surrounding_iterator)->get_y();

							Ant* eater = new Ant(xx, yy, ++antc);
							eater->set_breed(g->organism_at(x, y)->get_breed()+1);

							g->put_organism(x, y, new GhostBug(x, y));
							g->put_organism(xx, yy, eater);
							c+=9;
							result->push_back(eater);
						}
						c++;
					}
				}



				// this breeds the ant
				if ((*iterator)->get_breed() == 2)
				{
					list<Organism*>* surroundings = g->get_unoccupied_surrounding(x, y);
					list<Organism*>::const_iterator surrounding_iterator;
					for (surrounding_iterator = surroundings->begin(); surrounding_iterator != surroundings->end(); ++surrounding_iterator)
					{
						if ((*iterator)->get_breed() == 2)
						{
							int xx = (*surrounding_iterator)->get_x();
							int yy = (*surrounding_iterator)->get_y();
							Ant* db = new Ant(xx, yy, ++antc);
							antc++;
							g->put_organism(xx, yy, db);
							result->push_back(db);
							(*iterator)->set_breed(0);
						}
					}

					if ((*iterator)->get_breed() == 2)
					{ // it never bred, so decrement it so it can be incremented later.
						(*iterator)->set_breed(1);
					}
				}


			}
		}
		catch(int i)
		{
			//DIE
		}
	}



	return result;
}


void doodle(grid* g, int count, list<DoodleBug*>* db)
{
	int c = 0;
	int size = g->get_size()-1;
	while(c < count)
	{
		int x = get_random(0, size);
		int y = get_random(0, size);
		DoodleBug* d = new DoodleBug(x, y, ++dbs);
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
	int c = 0;
	int size = g->get_size()-1;
	while(c < count)
	{
		int x = get_random(0, size);
		int y = get_random(0, size);
		Ant* d = new Ant(x, y, ++antc);
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

int main(int argc, char*argv[])
{
	srand(1);
	int DEFAULT_SIZE = 20;
	int DOODLE_DEFAULT = 5;
	int ANT_DEFAULT = 100;
	int ITERATION_DEFAULT = 1000;
	int PAUSE = 1;

	if (argc > 1)
	{
		DEFAULT_SIZE = atoi(argv[1]);
	}
	if (argc > 2)
	{
		DOODLE_DEFAULT = atoi(argv[2]);
	}
	if (argc > 3)
	{
		ANT_DEFAULT = atoi(argv[3]);
	}
	if (argc > 4)
	{
		ITERATION_DEFAULT = atoi(argv[4]);
	}
	if (argc > 5)
	{
		int seed = atoi(argv[5]);
		if(seed == 0)
		{
			srand(time(NULL));
		}
		else
		{
			srand(seed);
		}
	}
	if (argc > 6)
	{
		PAUSE = atoi(argv[6]);
	}





	list<Ant*>* a = new list<Ant*>();
	list<DoodleBug*>* d = new list<DoodleBug*>();



	grid g(DEFAULT_SIZE);
	doodle(&g, DOODLE_DEFAULT, d);
	ant(&g, ANT_DEFAULT, a);







	int c = 0;
	while(c < ITERATION_DEFAULT && d->size()>0 && a->size()>0)
	{
		if(PAUSE > 0)getchar();
		d = iterate_doodles(d, &g);
		if(PAUSE > 0)
		{
			cout << g << "ants: " << a->size() << endl << "doodles: " << d->size() << endl;
		}
		a = iterate_ants(a, &g);
		c++;
	}
	//d = iterate_doodles(d, &g);

	cout << "there were " << c << " steps completed" << endl;
	cout << "there were " << antc << " ants total, and " << a->size() << " remaining." << endl;
	cout << "there were " << dbs << " Doodlebugs total, and " << d->size() << " remaining." << endl;
	cout << g;


	return 0;
}
