#include <stdlib.h>

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
						return left->eval() + right->eval();
						break;
					case 2: //-
						return left->eval() - right->eval();
						break;
					case 3: //*
						return left->eval() * right->eval();
						break;
					case 4: // '/'
						return left->eval() / right->eval();
						break;
				}
			}
			return *r;
		}

		ParseTree(rational* ra)
		{
			left = NULL;
			right = NULL;
			operation = 0;
			r = ra;
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
			}
		}
};
