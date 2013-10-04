#include "Rational.h"
#include <iostream>

using namespace std;


void rational::setNumerator(int a)
{
	num = a;
	normalize();
}

void rational::setDenominator(int b)
{
	denom = b;
	normalize();
}

rational::rational()
{
	num = 0;
	denom = 1;
}

rational::rational(int a, int b)
{
	num = a;
	denom = b;
	normalize();
}

void rational::normalize()
{
	int g = gcd(num, denom);
	num = num/g;
	denom = denom/g;
}

int rational::gcd(int a, int b)
{
	if (a==0 || b==0) return 1;
	if (a<0) return gcd(a*-1, b);
	if (b<0) return gcd(a, b*-1);
	if (a < b) return gcd(b, a);
	if (a%b == 0) return b;
	return gcd(b, a%b);
}

double rational::toDouble()
{
	return ((double)num) / ((double) denom);
}

rational rational::operator +  (const rational r)
{
	rational temp(num*r.denom + r.num*denom, denom*r.denom);
	return temp;
}

rational rational::operator *  (const rational r)
{
	rational temp(num*r.num, denom*r.denom);
	return temp;
}

rational rational::operator /  (const rational r)
{
	rational temp(num*r.denom, denom*r.num);
	return temp;
}

rational rational::operator -  (const rational r)
{
	rational temp(num*r.denom - r.num*denom, denom*r.denom);
	return temp;
}

int rational::operator >  (const rational r)
{
	return num*r.denom > r.num*denom;
}

int rational::operator <  (const rational r)
{
	return num*r.denom < r.num*denom;
}

int rational::operator == (const rational r)
{
	return r.num*denom == num*r.denom;
}

int rational::operator >= (const rational r)
{
	return r.num*denom >= num*r.denom;
}

int rational::operator <= (const rational r)
{
	return r.num*denom <= num*r.denom;
}

int rational::operator != (const rational r)
{
 	return r.num*denom != num*r.denom;
}

int rational::getNumerator()
{
	return num;
}

int rational::getDenominator()
{
	return denom;
}

void rational::operator =  (const rational r)
{
	this->num = r.num;
	this->denom = r.denom;
	normalize();
}

void rational::operator += (const rational r)
{
	int t_num = num*r.denom + r.num*denom;
	int t_denom = denom*r.denom;
	num = t_num;
	denom = t_denom;
	normalize();
}

void rational::operator -= (const rational r)
{
	int t_num = num*r.denom - r.num*denom;
	int t_denom = denom*r.denom;
	num = t_num;
	denom = t_denom;
	normalize();
}

void rational::operator *= (const rational r)
{
	num *= r.num;
	denom *= r.denom;
	normalize();
}

void rational::operator /= (const rational r)
{
	num *= r.denom;
	denom *= r.num;
	normalize();
}
