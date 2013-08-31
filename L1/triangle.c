/*
 * super duper easy lab triangle.c
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
	double a1;
	double a2;
	double b1;
	double b2;
	double c1;
	double c2;

	double ab;
	double ac;
	double bc;

	double circ;
	double area;
	
	printf("Enter the x- and y-coordinates of point A:- ");
	scanf("%lf %lf", &a1, &a2);

	printf("Enter the x- and y-coordinates of point B:- ");
	scanf("%lf %lf", &b1, &b2);

	printf("Enter the x- and y-coordinates of point C:- ");
	scanf("%lf %lf", &c1, &c2);

	ab = sqrt( (a1-b1)*(a1-b1)  +  (a2-b2)*(a2-b2) );
	ac = sqrt( (a1-c1)*(a1-c1)  +  (a2-c2)*(a2-c2) );
	bc = sqrt( (b1-c1)*(b1-c1)  +  (b2-c2)*(b2-c2) );
	
	circ = ab+ac+bc;

	double s = circ / 2;
	area = sqrt( s * (s-ab) * (s-ac) * (s-bc) );

	printf("Length of AB is %f\nLength of BC is %f\nLength of CA is %f\nCircumference is %f\n\nArea is %f\n", ab, bc, ac, circ, area);

	return 0;
}