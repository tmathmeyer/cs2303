#include "organism.h"
#include "grid.h"

int DoodleBug::get_x()
{
	return x;
}
int DoodleBug::get_y()
{
	return y;
}
int DoodleBug::set_x(int a)
{
	return x = a;
}

int DoodleBug::set_y(int a)
{
	return y = a;
}
void DoodleBug::move()
{

}
int DoodleBug::get_breed()
{
	return breed;
}
int DoodleBug::get_satiation()
{
	return satiation;
}
char DoodleBug::get_rep()
{
	return 'D';
}
int DoodleBug::set_breed(int a)
{
	return breed = a;
}
void DoodleBug::set_sat(int s)
{
	satiation = s;
}
DoodleBug::DoodleBug(int a, int b)
{
	x = a;
	y = b;
	satiation = 3;
	breed = 0;
}



int Ant::get_x()
{
	return x;
}

int Ant::get_y()
{
	return y;
}
int Ant::set_x(int a)
{
	return x = a;
}

int Ant::set_y(int a)
{
	return y = a;
}
void Ant::move()
{

}
int Ant::get_breed()
{
	return breed;
}
int Ant::get_satiation()
{
	return -1;
}
char Ant::get_rep()
{
	return 'A';
}
int Ant::set_breed(int a)
{
	return breed = a;
}
void Ant::set_sat(int s)
{}
Ant::Ant(int a, int b)
{
	x = a;
	y = b;
	breed = 0;
}


int GhostBug::get_x()
{
	return x;
}

int GhostBug::get_y()
{
	return y;
}
int GhostBug::set_x(int a)
{
	return x = a;
}

int GhostBug::set_y(int a)
{
	return y = a;
}
void GhostBug::move()
{}
int GhostBug::get_breed()
{
	return 0;
}
int GhostBug::get_satiation()
{
	return -9001;
}
char GhostBug::get_rep()
{
	return ' ';
}
int GhostBug::set_breed(int a)
{
	return breed = a;
}
void GhostBug::set_sat(int s)
{}
GhostBug::GhostBug(int a, int b)
{
	x = a;
	y = b;
	breed = 0;
}
