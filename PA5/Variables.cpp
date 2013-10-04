#include "Rational.h"
#include "Variables.h"
#include <stdlib.h>

class Variable
{
	public:
		char name;
		rational* value;
		Variable(char c, rational* v)
		{
			name = c;
			value = v;
		}
};

class VariableTree
{
	private:
		VariableTree* left;
		VariableTree* right;
		Variable* data;
	public:
		void insert(char c, rational* r)
		{
			if (data == NULL)
			{
				data = new Variable(c, r);
			}
			else if (data->name > c)
			{
				if (right == NULL)
				{
					right = new VariableTree();
				}
				right->insert(c, r);
			}
			else if (data->name < c)
			{
				if (left == NULL)
				{
					left = new VariableTree();
				}
				left->insert(c, r);
			}
			else
			{
				data->value = r;
			}
		}

		rational getValue(char c)
		{
			if (data->name == c)
			{
				if (data == NULL)
				{
					 return *(data->value);
				}
				return *(data->value);
			}
			if (data->name > c)
			{
				if (right == NULL)
				{
					return *(data->value);
				}
				return right->getValue(c);
			}
			if (data->name < c)
			{
				if (left == NULL)
				{
					return *(data->value);
				}
				return left->getValue(c);
			}
		}
};
