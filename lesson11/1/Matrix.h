#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

using namespace std;

//1️) Класс матрицы. Обращение и определитель
//Реализовать в классе матриц операцию обращения и нахождения определителя методом Гаусса(для каждой из техник выбора опорного элемента).
//Напоминаю, что метод Гаусса заключается в последовательном занулении поддиагональных элементов с помощью вычитания
//текущей строки матрицы с подходящим коэффициентом из нижестоящих строк.
//Однако, в некоторый момент времени может оказаться, что текущий диагональный элемент m[i][i], называемый опорным, равен 0,
//поэтому его невозможно использовать для зануления.В таком случае применяют одну из техник выбора опорного элемента :
//
//среди всех элементов, стоящих под m[i][i] выбирают максимальный по модулю m[i][j] и переставляют местами строки i и j
//среди всех элементов, стоящих после m[i][i] выбирают максимальный по модулю m[j][i] и переставляют местами столбцы i и j
//среди всех элементов, стоящих левее или правее m[i][i] выбирают максимальный по модулю m[x][y] и переставляют местами строки i и x,
//а затем столбцы i и y
//
//Если опорный элемент оказывается всё равно нулевым, то значит матрица необратима и определитель равен 0;
//в противном случае алгоритм продолжается с новым опорным элементом.
//Замечание.При вычислении обратной матрицы все операции со строками и столбцами нужно дублировать в присоединенной матрице.
//При нахождении определителя перестановка строк меняет знак.

class Matrix {
private:
	vector<vector<double>> m;

	void swap_rows(size_t i, size_t j);
	void swap_cols(size_t i, size_t j);
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

	pair<double, bool> getF(size_t i, size_t j);
	double det() const;
	Matrix invertMatrix() const;

};
#include "Matrix_impl.h"
#endif // !MATRIX_H