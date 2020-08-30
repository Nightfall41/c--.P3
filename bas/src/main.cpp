/* Copyright (C) 2020 - Bastiaan Teeuwen <bastiaan@mkcl.nl> */

#include <matrix.h>

#include <iostream>

using namespace std;

int main()
{
	Matrix a(2, 3);
	a(0, 0) = 0;
	a(0, 1) = 4;
	a(0, 2) = -2;
	a(1, 0) = -4;
	a(1, 1) = -3;
	a(1, 2) = 0;
	cout << "Matrix A" << endl << a << endl;

	Matrix b(2, 3);
	b(0, 0) = 0;
	b(0, 1) = 1;
	b(0, 2) = 2;
	b(1, 0) = 1;
	b(1, 1) = -1;
	b(1, 2) = 3;
	cout << "Matrix B" << endl << b << endl;

	Matrix add = a + b;
	cout << "Addition: A + B" << endl << add << endl;

	Matrix sub = a - b;
	cout << "Subtraction: A - B" << endl << sub << endl;

	Matrix mulx = 1.5 * a;
	cout << "Scalar multiplication: 1.5 * A" << endl << mulx << endl;

	cout << "Transpose: A′" << endl << a.transpose() << endl;

	Matrix c(1, 3);
	c(0, 0) = 1;
	c(0, 1) = 3;
	c(0, 2) = -5;
	cout << "Vector c" << endl << c << endl;

	Matrix d(3, 1);
	d(0, 0) = 4;
	d(1, 0) = -2;
	d(2, 0) = -1;
	cout << "Vector d" << endl << d << endl;

	double dot = c % d;
	cout << "Dot product: c · d = " << dot << endl;

	cout << "Transpose: c′" << endl << c.transpose() << endl;

	Matrix cross = c ^ d;
	cout << "Cross product: c × d" << endl << cross << endl;

	Matrix mulc = b * d;
	cout << "Column vector multiplication: B * d" << endl << mulc << endl;

	Matrix mulm = a * b;
	cout << "Matrix multiplication: A′ * B" << endl << mulm << endl;

	Matrix mulr = c.transpose() * a;
	cout << "Row vector multiplication: c * A" << endl << mulr << endl;

	/* Gaussian elimination */
	Matrix m(3, 3);
	m(0, 0) = 9;
	m(0, 1) = 3;
	m(0, 2) = 4;
	m(1, 0) = 4;
	m(1, 1) = 3;
	m(1, 2) = 4;
	m(2, 0) = 1;
	m(2, 1) = 1;
	m(2, 2) = 1;
	cout << "Matrix M" << endl << m << endl;

	Matrix q(3, 1);
	q(0, 0) = 7;
	q(1, 0) = 8;
	q(2, 0) = 3;
	cout << "Vector q" << endl << q << endl;

	Matrix x = m | q;
	cout << "Gaussian elimination: M * v = q" << endl << "v =" << endl << x
			<< endl;

	cout << "Performing gaussian elimination on a singular matrix is not "
		"possible as it will lead to division by zero during the "
		"elementary operations and back substitution." << endl;

	cout << endl << "I didn't do assignments 'q' and 'r'" << endl;

	return 0;
}
