#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

using namespace std;

class Matrix {
private:
	vector<vector<double>> m;
public:
	~Matrix() {}
	Matrix();
	Matrix(size_t rows, size_t cols);
	Matrix(size_t n);
	static Matrix unit_matrix(size_t n);
	static Matrix row_matrix(size_t n);
	static Matrix col_matrix(size_t n);
	Matrix(const vector<double>& diag);
	Matrix(const Matrix& obj);
	Matrix(Matrix&& obj);
	Matrix(const vector<vector<double>>& src);
	Matrix(vector<vector<double>>&& src);

	size_t rowsize() const;
	size_t colsize() const;
	size_t size() const;
	vector<double>& operator[](size_t row);
	const vector<double>& operator[](size_t row) const;
	Matrix& operator=(const Matrix& src);
	Matrix& operator=(Matrix&& src);
	Matrix operator+(const Matrix& rhs) const;
	Matrix operator-(const Matrix& rhs) const;
	Matrix operator*(const Matrix& rhs) const;

	Matrix operator*(double multiplier) const;
	Matrix operator/(double divider) const;
	friend Matrix operator*(double multiplier, const Matrix& obj);

	Matrix transpose() const;
	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);

	Matrix& operator*=(double multiplier);
	Matrix& operator/=(double divider);

	Matrix operator^(int power) const;
};
#include "Matrix_impl.h"
#endif // !MATRIX_H
