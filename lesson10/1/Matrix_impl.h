#pragma once
#ifndef MATRIX_IMPL_H
#define MATRIX_IMPL_H
#include <iostream>
#include <stdexcept>

//Matrix::~Matrix() {}

Matrix::Matrix() {
	m = {};
}

Matrix::Matrix(size_t rows, size_t cols) {
	m = vector<vector<double>>(rows, vector<double>(cols, 0.0));
}

Matrix::Matrix(size_t n) {
	m = vector<vector<double>>(n, vector<double>(n, 0.0));
}

Matrix Matrix::unit_matrix(size_t n) {
	Matrix matrix(n);
	for (size_t i = 0; i < n; i++) {
		matrix.m[i][i] = 1;
	}
	return matrix;
}

Matrix Matrix::row_matrix(size_t n) {
	Matrix row_m(1, n);
	return row_m;
}

Matrix Matrix::col_matrix(size_t n) {
	Matrix col_m(n, 1);
	return col_m;
}

Matrix::Matrix(const vector<double>& diag) {
	size_t n = diag.size();
	m = vector<vector<double>>(n, vector<double>(n, 0.0));
	for (size_t i = 0; i < n; i++) {
		m[i][i] = diag[i];
	}
}

Matrix::Matrix(const Matrix& obj) {
	m = obj.m;
}

Matrix::Matrix(Matrix&& obj) {
	m = obj.m;
	obj.m.clear();
}

Matrix::Matrix(const vector<vector<double>>& src) {
	m = src;
}

Matrix::Matrix(vector<vector<double>>&& src) {
	m = src;
}

size_t Matrix::rowsize() const {
	return m.size();
}

size_t Matrix::colsize() const {
	return (m.empty()) ? 0 : m[0].size();
}

size_t Matrix::size() const {
	return m.size();
}

//size_t Matrix::size() const {
//	if (m.size() != (m.empty() ? 0 : m[0].size())) {
//		throw invalid_argument("matrix is not square");
//	}
//	return m.size() * (m.empty() ? 0 : m[0].size());
//}

vector<double>& Matrix::operator[](size_t row) {
	return m[row];
}

const vector<double>& Matrix::operator[](size_t row) const {
	return m[row];
}

Matrix& Matrix::operator=(const Matrix& src) {
	if (this != &src) 
		m = src.m;
	return *this;
}

Matrix& Matrix::operator=(Matrix&& src) {
	if (this != &src) {
		m = src.m;
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const {
	if (colsize() != rhs.colsize() || rowsize() != rhs.rowsize())
		throw invalid_argument("matrix are not equal");

	size_t rows = rowsize();
	size_t cols = colsize();
	Matrix res(rows, cols);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			res[i][j] = m[i][j] + rhs[i][j];
		}
	}

	return res;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
	if (colsize() != rhs.colsize() || rowsize() != rhs.rowsize())
		throw invalid_argument("matrix are not equal");

	size_t rows = rowsize();
	size_t cols = colsize();
	Matrix res(rows, cols);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			res[i][j] = m[i][j] - rhs[i][j];
		}
	}

	return res;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	if (colsize() != rhs.rowsize())
		throw invalid_argument("matrix dims are not right for multiplication");
	
	size_t rows = rowsize();
	size_t cols = rhs.colsize();
	size_t inner_dim = colsize();
	Matrix res(rows, cols);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			for (size_t k = 0; k < inner_dim; k++) {
				res[i][j] += m[i][k] * rhs[k][j];
			}
		}
	}
	return res;
}

Matrix Matrix::operator+(double num) const {
	size_t rows = rowsize();
	size_t cols = colsize();
	Matrix res(rows, cols);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			res[i][j] = m[i][j] + num;
		}
	}
	return res;
}

Matrix Matrix::operator-(double num) const {
	size_t rows = rowsize();
	size_t cols = colsize();
	Matrix res(rows, cols);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			res[i][j] = m[i][j] - num;
		}
	}

	return res;
}

Matrix Matrix::operator*(double multiplier) const {
	size_t rows = rowsize();
	size_t cols = colsize();
	Matrix res(rows, cols);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			res[i][j] = m[i][j] * multiplier;
		}
	}

	return res;
}

Matrix Matrix::operator/(double divider) const {
	if (divider == 0)
		throw invalid_argument("invalid divider");

	size_t rows = rowsize();
	size_t cols = colsize();
	Matrix res(rows, cols);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			res[i][j] = m[i][j] / divider;
		}
	}

	return res;
}

Matrix operator*(double multiplier, const Matrix& obj) {
	return obj * multiplier;
}

Matrix Matrix::transpose() const {
	size_t rows = rowsize();
	size_t cols = colsize();
	Matrix res(cols, rows);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			res[j][i] = m[i][j];
		}
	}

	return res;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	if (colsize() != rhs.colsize() || rowsize() != rhs.rowsize())
		throw invalid_argument("matrix are not equal");

	size_t rows = rowsize();
	size_t cols = colsize();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			m[i][j] += rhs[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	if (colsize() != rhs.colsize() || rowsize() != rhs.rowsize())
		throw invalid_argument("matrix are not equal");

	size_t rows = rowsize();
	size_t cols = colsize();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			m[i][j] -= rhs[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	if (colsize() != rhs.rowsize())
		throw invalid_argument("matrix dims are not right for multiplication");

	size_t rows = rowsize();
	size_t cols = rhs.colsize();
	size_t inner_dim = colsize();
	vector<double> tmp(inner_dim, 0.0);

	for (size_t i = 0; i < rows; i++) {
		fill(tmp.begin(), tmp.end(), 0.0);
		for (size_t j = 0; j < cols; j++) {
			for (size_t k = 0; k < inner_dim; k++) {
				tmp[j] += m[i][k] * rhs.m[k][j];
			}
		}
		for (size_t j = 0; j < cols; j++) {
			m[i][j] = tmp[j];
		}
	}
	return *this;
}

Matrix& Matrix::operator+=(double num) {
	size_t rows = rowsize();
	size_t cols = colsize();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			m[i][j] += num;
		}
	}

	return *this;
}

Matrix& Matrix::operator-=(double num) {
	size_t rows = rowsize();
	size_t cols = colsize();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			m[i][j] -= num;
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(double multiplier){
	size_t rows = rowsize();
	size_t cols = colsize();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			m[i][j] *= multiplier;
		}
	}

	return *this;
}

Matrix& Matrix::operator/=(double divider) {
	if (divider == 0)
		throw invalid_argument("invalid divider");
	size_t rows = rowsize();
	size_t cols = colsize();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			m[i][j] /= divider;
		}
	}

	return *this;
}

Matrix Matrix::operator^(int power) const {
	if (power <= 0)
		throw invalid_argument("power should be > 0");

	size_t rows = rowsize();
	size_t cols = colsize();
	if (rows != cols)
		throw invalid_argument("matrix should be square");
	Matrix res = *this;
	Matrix base = *this;

	for (size_t i = 1; i < power; i++) 
		res = res * base;
	
	return res;
}


#endif // !MATRIX_IMPL_H
