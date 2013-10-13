#include <stdlib.h>
#include "grid.h"
#include "organism.h"
#include <list>
#include <time.h>
#include <iostream>
#include <stdio.h>

using namespace std;

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



		//this starves the doodlebug
		if ((*iterator)->get_satiation() == 0)
		{
			g->put_organism(x, y, new GhostBug(x, y));
			cout << "a doodlebug has starved!" << endl;
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
						cout << "the doodle at (" << x << ", " << y << ") ate an ant" << endl;
						cout << " which was at (" << xx << ", " << yy << ") "<<endl;

						(*surrounding_iterator)->set_sat(-2);
						(*iterator)->set_sat(3);

						DoodleBug* eater = new DoodleBug(xx, yy);
						eater->set_breed(g->organism_at(x, y)->get_breed()+1);
						g->put_organism(x, y, new GhostBug(x, y));
						g->put_organism(xx, yy, eater);

						cout << "eater is a: " << eater->get_rep()<<endl;

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

						DoodleBug* eater = new DoodleBug(xx, yy);
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
				cout << "a doodlebug has bred!"<<endl;
				list<Organism*>* surroundings = g->get_unoccupied_surrounding(x, y);
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
		if ((*iterator)->get_satiation() != -2)
		{
			list<Organism*>* empty_spots = g->get_unoccupied_surrounding(x, y);
			list<Organism*>::const_iterator surrounding_iterator;
			int move_to = get_random(0, empty_spots->size()-1);
			int c = 0;
			result->push_back(*iterator);
			for (surrounding_iterator = empty_spots->begin(); surrounding_iterator != empty_spots->end(); ++surrounding_iterator)
			{
				if (c == move_to)
				{
					int xx = (*surrounding_iterator)->get_x();
					int yy = (*surrounding_iterator)->get_y();
					g->put_organism(xx, yy, *iterator); // move the ant
					g->put_organism(x, y, new GhostBug(x, y));
					(*iterator)->set_x(xx);
					(*iterator)->set_y(yy);
				}
				c++;
			}


			if ((*iterator)->get_breed() >= 2)
			{
				(*iterator)->set_breed(-1);
				c = 0;
				x = (*iterator)->get_x();
				y = (*iterator)->get_y();
				list<Organism*>* new_spots = g->get_unoccupied_surrounding(x, y);
				list<Organism*>::const_iterator spawn_locations;
				int spawn_in = get_random(0, new_spots->size());
				for (spawn_locations = new_spots->begin(); spawn_locations != new_spots->end(); ++spawn_locations)
				{
					if (c == spawn_in)
					{
						int xx = (*spawn_locations)->get_x();
						int yy = (*spawn_locations)->get_y();
						Ant* spawn = new Ant(xx, yy);
						g->put_organism(xx, yy, spawn);
						result->push_back(spawn);
					}
					c++;
				}
			}


			(*iterator)->set_breed((*iterator)->get_breed()+1);
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
	srand(7);
	int DEFAULT_SIZE = 5;
	int DOODLE_DEFAULT = 3;
	int ANT_DEFAULT = 10;

	list<Ant*>* a = new list<Ant*>();
	list<DoodleBug*>* d = new list<DoodleBug*>();



	grid g(DEFAULT_SIZE);
	doodle(&g, DOODLE_DEFAULT, d);
	ant(&g, ANT_DEFAULT, a);







	cout << g;
	int c = 0;
	while(c < 30)
	{
		d = iterate_doodles(d, &g);
		cout << g;
		//a = iterate_ants(a, &g);
		getchar();
		cout << g;
		c++;
	}
	return 0;
}
