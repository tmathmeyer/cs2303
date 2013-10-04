#include "rational.h"
#include "Variable.h"

class Variable
{
	char name;
	rational* value;
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
					return NULL;
				}
				return *(data->value);
			}
			if (data->name > c)
			{
				if (right == NULL)
				{
					return NULL;
				}
				return right->getValue(c);
			}
			if (data->name < c)
			{
				if (left == NULL)
				{
					return NULL;
				}
				return left->getValue(c);
			}
		}
};
