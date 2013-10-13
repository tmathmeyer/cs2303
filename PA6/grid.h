#include "organism.h"
#include <list>

#ifndef GRID_H_
#define GRID_H_

class grid {
	private:
		Organism** organisms; //2D arrays are for noobs... this is an array of pointers to individual Organisms
		int size;
	public:
		Organism* organism_at(int x, int y);
		void put_organism(int x, int y, Organism* o);
		int get_size();	
		std::list<Organism*>* get_occupied_surrounding(int x, int y);
		std::list<Organism*>* get_unoccupied_surrounding(int x, int y);
		grid(int size);
		grid();
};





#endif
