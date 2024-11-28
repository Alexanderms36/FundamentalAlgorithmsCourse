#pragma once
#ifndef MATRIX_IMPL_H
#define MATRIX_IMPL_H
#include <iostream>
#include <stdexcept>

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

Matrix& Matrix::operator*=(double multiplier) {
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

void Matrix::swap_rows(size_t i, size_t j) {
	if (i != j) swap(m[i], m[j]);
}

void Matrix::swap_cols(size_t i, size_t j) {
	if (i != j) {
		for (size_t k = 0; k < rowsize(); k++)
			swap(m[k][i], m[k][j]);
	}
}

pair<double, bool> Matrix::getF(size_t i, size_t j) {
	if (m[i][i] != 0) {
		return { m[j][i] / m[i][i], true };
	}

	double mii = 0;

	for (size_t k = i; k < colsize(); k++) {
		mii = max(abs(m[k][i]), mii);
	}
	swap_rows(i, j);
	if (m[i][i] != 0) {
		return { m[j][i] / m[i][i], true };
	}
	swap_rows(j, i);

	mii = 0;
	for (size_t k = i; k < rowsize(); k++) {
		mii = max(abs(m[i][k]), mii);
	}
	swap_cols(i, j);
	if (m[i][i] != 0) {
		return { m[j][i] / m[i][i], true };
	}
	swap_cols(j, i);
	

	if (i + 1 < rowsize() && i - 1 > -1) {
		if (m[i][i + 1] != 0 && m[i][i - 1] != 0) {
			swap_rows(i, i + 1);
			swap_cols(i, i - 1);
			return { m[j][i] / max(abs(m[i][i + 1]), abs(m[i][i - 1])), true };
		}
	}
	if (i + 1 < rowsize()) {
		if (m[i][i + 1] != 0) {
			swap_rows(i, i + 1);
			swap_cols(i, i + 1);
			return { m[j][i] / abs(m[i][i + 1]), true };
		}
	}
	if (i - 1 > -1) {
		if (m[i][i - 1] != 0) {
			swap_rows(i, i - 1);
			swap_cols(i, i - 1);
			return { m[j][i] / abs(m[i][i - 1]), true };
		}
	}

	return { 0, false };
}


double Matrix::det() const {
	size_t rows = rowsize();
	size_t cols = colsize();
	if (rows != cols)
		throw invalid_argument("matrix should be square");
	Matrix tmp = *this;
	double det = 1.0;
	int sign = 1;

	for (size_t i = 0; i < rows; i++) {
		size_t max_row = i;
		for (size_t j = i + 1; j < rows; j++) {
			if (abs(tmp[j][i]) > abs(tmp[max_row][i]))
				max_row = j;
		}
		
		if (tmp[max_row][i] == 0)
			return 0;

		if (i != max_row) {
			tmp.swap_rows(i, max_row);
			sign *= -1;
		}

		for (size_t j = i + 1; j < rows; j++) {
			auto f = tmp.getF(i, j);
			if (!f.second) {
				return 0;
			}
			double fixed = f.first;
			for (size_t k = 0; k < cols; k++) {
				tmp[j][k] -= tmp[i][k] * fixed;
			}
		}
		det *= tmp[i][i];
		cout << "det = " << det << endl;
	}

	return sign * det;
}

Matrix Matrix::invertMatrix() const {
	size_t rows = rowsize();
	size_t cols = colsize();
	if (rows != cols)
		throw invalid_argument("matrix should be square");
	Matrix tmp = *this;
	Matrix E = unit_matrix(rows);

	for (size_t i = 0; i < rows; i++) {
		size_t max_row = i;
		for (size_t j = i + 1; j < rows; j++) {
			if (abs(tmp[j][i]) > abs(tmp[max_row][i]))
				max_row = j;
		}

		if (tmp[max_row][i] == 0)
			throw invalid_argument("matrix cannot be inverted");

		tmp.swap_rows(i, max_row);
		E.swap_rows(i, max_row);

		double diag = tmp[i][i];
		for (size_t j = 0; j < rows; j++) {
			tmp[i][j] /= diag;
			E[i][j] /= diag;
		}

		for (size_t j = i + 1; j < rows; j++) {
			auto f = tmp.getF(i, j);
			if (!f.second) {
				throw invalid_argument("matrix cannot be inverted");
			}
			double fixed = f.first;
			for (size_t k = 0; k < cols; k++) {
				tmp[j][k] -= fixed * tmp[i][k];
				E.m[j][k] -= fixed * E.m[i][k];
			}
		}
	}
	int i = rows - 1;
	while (i >= 0) {
		for (size_t j = 0; j < i; j++) {
			auto f = tmp.getF(i, j);
			if (!f.second) {
				throw invalid_argument("matrix cannot be inverted");
			}
			double fixed = f.first;
			for (size_t k = 0; k < rows; k++) {
				tmp[j][k] -= fixed * tmp[i][k];
				E[j][k] -= fixed * E[i][k];
			}
		}
		i--;
	}
	return E;
}

#endif // !MATRIX_IMPL_H