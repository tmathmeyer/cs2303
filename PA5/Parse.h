#include <stdlib.h>

class ParseStack;

class ParseTree
{
	private:
		ParseTree* left;
		ParseTree* right;
		rational* r;
		int operation;
	public:
		rational eval()
		{
			if (left != NULL   &&   right != NULL   &&   operation > 0   && operation < 5)
			{
				switch(operation)
				{
					case 1: //+
						return right->eval() + left->eval();
						break;
					case 2: //-
						return right->eval() - left->eval();
						break;
					case 3: //*
						return right->eval() * left->eval();
						break;
					case 4: // '/'
						return right->eval() / left->eval();
						break;
				}
			}
			return *r;
		}

		void print();

		ParseTree(rational* ra)
		{
			left = NULL;
			right = NULL;
			operation = 0;
			r = ra;
		}

		ParseTree()
		{
			left = NULL;
			right = NULL;
			operation = 0;
			r = NULL;
		}

		ParseTree(ParseTree* le, ParseTree* ri, int op)
		{
			r = NULL;
			left = le;
			right = ri;
			operation = op;
		}
		
		ParseTree(ParseTree* le, ParseTree* ri, char* op)
		{
			r = NULL;
			left = le;
			right = ri;
			switch(*op)
			{
				case '+' :
					operation = 1;
					break;
				case '-' :
					operation = 2;
					break;
				case '*' :
					operation = 3;
					break;
				case '/' :
					operation = 4;
					break;
				default:
					operation = 0;
					break;
			}
		}
};

class StackElement
{
	public:
		StackElement* rest;
		ParseTree* elem;
		StackElement(ParseTree* pt)
		{
			elem = pt;
			rest = NULL;
		}
};

class ParseStack
{
	private:
		StackElement* head;

	public:
		void insert(ParseTree* elem)
		{
			StackElement* se = new StackElement(elem);
			se->rest = head;
			head = se;
		}
		ParseTree* pop()
		{
			if (head == NULL)
			{
				return NULL;
			}
			ParseTree* result = head->elem;
			StackElement* temp = head->rest;
			head->rest = NULL;
			head->elem = NULL;
			head = NULL;
			head = temp;

			return result;
		}
		ParseStack()
		{
			head = NULL;
		}

};
