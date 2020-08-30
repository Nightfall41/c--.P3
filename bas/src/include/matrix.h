/* Copyright (C) 2020 - Bastiaan Teeuwen <bastiaan@mkcl.nl> */

#include <iostream>

class Matrix {
private:
	double *vec;
	int m, n;

public:
	Matrix(int m, int n);
	Matrix(const Matrix &m);
	~Matrix();

	/* visualize matrix to an output stream */
	friend std::ostream &operator<<(std::ostream &os, const Matrix &m);

	double operator()(int row, int col) const; /* get index */
	double &operator()(int row, int col); /* set index */

	friend Matrix operator+(const Matrix &a, const Matrix &b); /* M + M */
	friend Matrix operator-(const Matrix &a, const Matrix &b); /* M - M */
	friend Matrix operator*(const double &a, const Matrix &b); /* a * M */

	Matrix &transpose(void); /* transpose this matrix */

	friend double operator%(const Matrix &a, const Matrix &b); /* . prod. */
	friend Matrix operator^(const Matrix &a, const Matrix &b); /* x prod. */

	friend Matrix operator*(const Matrix &a, const Matrix &b); /* M * M */

	friend Matrix operator|(const Matrix &a, const Matrix &b); /* M * V = Q */
};
