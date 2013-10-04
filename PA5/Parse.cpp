#include "Rational.h"
#include "Parse.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;
int end_of_file = 0;
int is_math(char c);

void ParseTree::print()
{
	if (r != NULL)
	{
		cout << r->getNumerator() << "/" << r->getDenominator();
	}
	else if (left != NULL && right != NULL)
	{
		cout << "(";
		left->print();
		cout << " &" << operation << "& ";
		right->print();
		cout << ")";
	}
}



istream& operator >> (istream& is, rational& r)
{
	int a,b;
	is >> a;
	is.ignore(1);
	is >> b;
	cout << a << "/" << b << "    : ";
	r.setNumerator(a);
	r.setDenominator(b);
	return is;
}

istream& operator >> (istream& is, ParseTree& t)
{
	char c;
	int num = 0;
	int denom = 0;

	//0->not reading anything
	//1->reading numerator
	//2->reading denominator
	int pos_control = 0;

	ParseStack* s = new ParseStack();
	int something = 0;

	while (is.get(c))
	{
		something = 1;
		if (c!='\n')
		{
			cout << c;
		}

		if (isdigit(c))
		{
			if (pos_control == 1 || pos_control == 0)
			{
				num*=10;
				num+=(c-'0');
				pos_control = 1;
			}
			else
			{
				denom*=10;
				denom+=(c-'0');
				pos_control = 2;
			}
		}
		else if (c == '/' && pos_control == 1)
		{
			pos_control = 2;
		}
		else if (c == ' ')
		{
			if (pos_control == 2)
			{
				rational* r = new rational(num, denom);
				ParseTree* pt = new ParseTree(r);
				s->insert(pt);
				num = 0;
				denom = 0;
			}

			pos_control = 0;
		}
		else if (is_math(c))
		{
			ParseTree* a = s->pop();
			ParseTree* b = s->pop();

			ParseTree* n = new ParseTree(a, b, &c);
			s->insert(n);
		}
		else if (c == '\n')
		{
			t = *(s->pop());
			cout << "\t: ";
			return is;
		}
	}


	if (something)
	{
		t = *(s->pop());
		cout << "\t: ";
		return is;
	}
	end_of_file = 1;
	return is;
}


int is_math(char c)
{
	return (c=='+') || (c=='*') || (c=='/') || (c=='-');
}

int main()
{
	ifstream myfile;
	myfile.open ("in.txt");

	do
	{
		ParseTree t;
		myfile >> t;
		if (!end_of_file)
		{
			rational r = t.eval();
			cout << r.getNumerator() << "/" << r.getDenominator() << " (double " << r.toDouble() << ")" << endl;
		}
	} while(!end_of_file);
}
