class rational
{
	private:
		int num;
		int denom;
		int gcd(int a, int b);
		void normalize();

	public:
		rational operator +  (const rational);
		rational operator *  (const rational);
		rational operator /  (const rational);
		rational operator -  (const rational);
		int operator >  (const rational);
		int operator <  (const rational);
		int operator == (const rational);
		int operator >= (const rational);
		int operator <= (const rational);
		int operator != (const rational);
		void operator =  (const rational);
		void operator += (const rational);
		void operator -= (const rational);
		void operator *= (const rational);
		void operator /= (const rational);
		double toDouble();
		rational();
		rational(int a, int b);
		void setNumerator(int a);
		void setDenominator(int b);
};
