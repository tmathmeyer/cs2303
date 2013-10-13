#ifndef ORGANISM_H_
#define ORGANISM_H_

class Organism{
	public:
		virtual void move()           = 0;
		virtual int  get_x()          = 0;
		virtual int  get_y()          = 0;
		virtual int  set_x(int a)     = 0;
		virtual int  set_y(int a)     = 0;
		virtual int  get_breed()      = 0;
		virtual int  set_breed(int a) = 0;
		virtual int  get_satiation()  = 0;
		virtual void set_sat(int s)   = 0;
		virtual char get_rep()        = 0;
};

class DoodleBug : public Organism {
	private:
		int x;
		int y;
		int breed;
		int satiation; //dictionary time!
	public:
		int get_x();
		int get_y();
		int set_x(int a);
		int set_y(int a);
		void move();
		void set_sat(int s);
		int get_breed();
		int get_satiation();
		char get_rep();
		int  set_breed(int a);
		DoodleBug(int x, int y);
};

class Ant : public Organism {
	private:
		int x;
		int y;
		int breed;
	public:
		int get_x();
		int get_y();
		int set_x(int a);
		int set_y(int a);
		void move();
		void set_sat(int s);
		int get_breed();
		int get_satiation();
		char get_rep();
		int  set_breed(int a);
		Ant(int x, int y);
};

class GhostBug : public Organism {
	private:
		int x;
		int y;
		int breed;
	public:
		int get_x();
		int get_y();
		int set_x(int a);
		int set_y(int a);
		void move();
		void set_sat(int s);
		int get_breed();
		int get_satiation();
		char get_rep();
		int  set_breed(int a);
		GhostBug(int x, int y);
};


#endif

