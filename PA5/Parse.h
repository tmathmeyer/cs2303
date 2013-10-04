#include <stdlib.h>
#include <exception>

class ParseStack;

class ParseTree
{
	private:
		ParseTree* left;
		ParseTree* right;
		rational* r;
		int operation;
		int type; // 1-> rational
		  		  // 2-> bool
				  // 3-> error
				  // 4-> rational w/assignment
		int boolean;


	public:
		int getType()
		{
			return type;
		}

		void setType(int t)
		{
			type = t;
		}

		rational* getRational()
		{
			return r;
		}

		rational eval()
		{
			try
			{
				if (left != NULL   &&   right != NULL   &&   operation > 0   && operation < 5)
				{
					switch(operation)
					{
						case 1: //+
							type = 1;
							return (right->eval() + left->eval());
							break;
						case 2: //-
							type = 1;
							return (right->eval() - left->eval());
							break;
						case 3: //*
							type = 1;
							return (right->eval() * left->eval());
							break;
						case 4: // '/'
							type = 1;
							return (right->eval() / left->eval());
							break;
						case 5: // >
							type = 2;
							return *r;
							break;

						case 6: // <
						case 7: // >=
						case 8: // <=
						case 9: // !=
						case 10: // ==
						case 11: // =
						default:
							type = 3;
							break;
					}
				}
				if (r == NULL)
				{
					rational* err = new rational(1,0);
					return *err;
				}
				return *r;
			}
			catch (std::exception& e)
			{
				rational* err = new rational(1,0);
				return *err;
			}
			
		}

		void setEval()
		{
			rational k = eval();
			if (k.getDenominator() == 0)
			{
				type = 3;
			}
			r = new rational(k.getNumerator(), k.getDenominator());
		}

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

			if (result == NULL)
			{
				throw 1;
			}
			return result;
		}
		ParseStack()
		{
			head = NULL;
		}

};
