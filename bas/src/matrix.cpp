/* Copyright (C) 2020 - Bastiaan Teeuwen <bastiaan@mkcl.nl> */

#include <matrix.h>

#include <exception>
#include <iomanip>
#include <sstream>

#include <math.h>

Matrix::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;

	vec = new double [m * n];
}

Matrix::Matrix(const Matrix &m)
{
	vec = new double [m.m * m.n];
	std::copy(m.vec, m.vec + m.m * m.n, vec);

	this->m = m.m;
	this->n = m.n;
}

Matrix::~Matrix()
{
	delete [] vec;
}

/* visualize matrix to an output stream */
std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
	int i, j, w = 0;

	/* calculate width of the widest double ... kinda inefficient tho */
	for (i = 0; i < m.m * m.n; i++) {
		std::stringstream ss;
		ss << m.vec[i];

		int cw = ss.str().length();
		if (cw > w)
			w = cw;
	}

	/* top */
	os << "\x1b(0\x6c ";
	for (i = 0; i < m.n * w + m.n; i++)
		os << ' ';
	os << '\x6b' << std::endl;

	/* contents */
	for (i = 0; i < m.m; i++) {
		os << "\x78\x1b(B ";
		for (j = 0; j < m.n; j++)
			os << std::setw(w) << m(i, j) << ' ';
		os << "\x1b(0\x78" << std::endl;
	}

	/* bottom */
	os << "\x6d ";
	for (i = 0; i < m.n * w + m.n; i++)
		os << ' ';
	os << "\x6a\x1b(B" << std::endl;

	return os;
}

/* get index */
double Matrix::operator()(int row, int col) const
{
	if (row < 0 || row > m || col < 0 || col > n)
		throw std::out_of_range("index out of matrix range");

	return vec[row * n + col];
}

/* set index */
double &Matrix::operator()(int row, int col)
{
	if (row < 0 || row > m || col < 0 || col > n)
		throw std::out_of_range("index out of matrix range");

	return vec[row * n + col];
}

/* M + M */
Matrix operator+(const Matrix &a, const Matrix &b)
{
	Matrix res(a.m, a.n);
	int i, j;

	/* matrices must have an equal number of rows and columns */
	if (a.m != b.m || a.n != b.n)
		throw std::out_of_range("matrices are varying in size");

	for (i = 0; i < res.m; i++)
		for (j = 0; j < res.n; j++)
			res(i, j) = a(i, j) + b(i, j);

	return res;
}

/* M - M */
Matrix operator-(const Matrix &a, const Matrix &b)
{
	Matrix res(a.m, a.n);
	int i, j;

	/* matrices must have an equal number of rows and columns */
	if (a.m != b.m || a.n != b.n)
		throw std::out_of_range("matrices are varying in size");

	for (i = 0; i < res.m; i++)
		for (j = 0; j < res.n; j++)
			res(i, j) = a(i, j) - b(i, j);

	return res;
}

/* a * M */
Matrix operator*(const double &a, const Matrix &b)
{
	Matrix res(b.m, b.n);
	int i, j;

	for (i = 0; i < res.m; i++)
		for (j = 0; j < res.n; j++)
			res(i, j) = a * b(i, j);

	return res;
}

/* tranpose vector or matrix */
Matrix &Matrix::transpose(void)
{
	Matrix res(n, m);
	int i, j;

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			res(j, i) = (*this)(i, j);

	/* I wonder if there's a way to do this more efficiently */
	std::copy(res.vec, res.vec + m * n, vec);
	this->m = res.m;
	this->n = res.n;

	return *this;
}

/* scalar/dot product */
double operator%(const Matrix &a, const Matrix &b)
{
	Matrix avec = a, bvec = b;
	double res = 0;
	int i;

	/* transpose both vectors to the same (column) orientation */
	if (avec.m != 1)
		avec.transpose();
	if (avec.n != bvec.n)
		bvec.transpose();

	/* both a and b must be vectors */
	if (avec.m != 1 || bvec.m != 1)
		throw std::out_of_range("a or b is not a vector");

	/* vectors must be of the same length */
	if (avec.n != bvec.n)
		throw std::out_of_range("vectors are varying in size");

	for (i = 0; i < avec.n; i++)
		res += avec(0, i) * bvec(0, i);

	return res;
}

/* cross product (only for 3D spaces) */
Matrix operator^(const Matrix &a, const Matrix &b)
{
	Matrix avec = a, bvec = b;
	Matrix res(1, 3);

	/* vectors must be in the same orientation */
	if (a.m != b.m || a.n != b.n)
		throw std::out_of_range("vectors are not of same kind");

	/* transpose both vectors to the same (column) orientation */
	if (avec.m != 1)
		avec.transpose();
	if (avec.n != bvec.n)
		bvec.transpose();

	/* both a and b must be vectors */
	if (avec.m != 1 || bvec.m != 1)
		throw std::out_of_range("a or b is not a vector");

	/* vectors must be of the same length */
	if (avec.n != bvec.n)
		throw std::out_of_range("vectors are varying in size");

	/* vectors may only be 3 in length */
	if (avec.n != 3)
		throw std::out_of_range("vectors are not in 3D space");

	res(0, 0) = avec(0, 1) * bvec(0, 2) - avec(0, 2) * bvec(0, 1);
	res(0, 1) = avec(0, 2) * bvec(0, 0) - avec(0, 0) * bvec(0, 2);
	res(0, 2) = avec(0, 0) * bvec(0, 1) - avec(0, 1) * bvec(0, 0);

	/* transpose to original orientation if needed */
	if (res.n != a.n)
		res.transpose();

	return res;
}

/* M * V and M * M */
Matrix operator*(const Matrix &a, const Matrix &b)
{
	Matrix res(a.m, b.n);
	int i, j, k;

	/*
	 * columns in 'a' must have the same number of rows as 'b'.
	 * vice versa is also allowed (otherwise this doesn't work with row
	 * vectors like as requested in assignment 'n', but I'm not 100% sure)
	 */
	if (a.n != b.m && a.m != b.n)
		throw std::out_of_range("invalid multiplication");

	/*
	 * headaches
	 * https://mathinsight.org/matrix_vector_multiplication
	 */
	for (i = 0; i < a.m; i++) {
		for (j = 0; j < b.n; j++) {
			res(i, j) = 0;

			for (k = 0; k < b.m; k++)
				res(i, j) += a(i, k) * b(k, j);
		}
	}

	return res;
}

/* M * V = Q */
Matrix operator|(const Matrix &a, const Matrix &b)
{
	Matrix m = a, q = b;
	Matrix v(m.m, 1);
	double maxval, tmp;
	int i, j, k;

	/* columns in 'm' must have the same number of rows */
	if (m.n != m.m)
		throw std::out_of_range("matrix is unsuitable for elimination");

	/* 'm' must have the same number of rows as 'q' */
	if (m.m != q.m)
		throw std::out_of_range("vector is incompatible with matrix");

	/*
	 * more headaches
	 * https://en.wikipedia.org/wiki/Gaussian_elimination#Pseudocode
	 */

	/* forwards elimination (reduce to echelon form) */
	for (i = 0; i < m.m; i++) {
		maxval = m(i, i);

		/* swap rows if row j contains a larger value then row i */
		for (j = i + 1; j < m.m; j++) {
			if ((tmp = fabs(m(j, i))) <= maxval)
				continue;

			maxval = tmp;

			for (k = 0; k < m.m; k++) {
				tmp = m(i, k);
				m(i, k) = m(j, k);
				m(j, k) = tmp;
			}

			tmp = q(i, 0);
			q(i, 0) = q(j, 0);
			q(j, 0) = tmp;
		}

		/* add to rows below row i the scalar multiple of row i */
		for (j = i + 1; j < m.m; j++) {
			tmp = m(j, i) / m(i, i);
			for (k = i + 1; k < m.m; k++)
				m(j, k) -= tmp * m(i, k);
			m(j, i) = 0;

			q(j, 0) -= tmp * q(i, 0);
		}
	}

	/* back substitution */
	for (i = m.m - 1; i >= 0; i--) {
		tmp = q(i, 0);

		for (j = m.m - 1; j > i; j--)
			tmp -= v(j, 0) * m(i, j);

		v(i, 0) = tmp / m(i, i);
	}

	return v.transpose();
}
