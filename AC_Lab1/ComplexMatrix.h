#pragma once
#include<iostream>
#include"ComplexNum.h"
#include <cassert>
class ComplexMatrix
{
private:
	ComplexNum** matrix;
	int columns;
	int rows;
public:
	ComplexMatrix(unsigned int columns, unsigned int rows) {
		matrix = new ComplexNum * [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new ComplexNum[columns];
		}
		this->columns = columns;
		this->rows = rows;
	}

	/*~ComplexMatrix() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}*/

	void auto_gen(int min_real, int max_real, int min_imag, int max_imag) {
		int span_real = abs(max_real - min_real) + 1;
		int span_imag = abs(max_imag - min_imag) + 1;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = ComplexNum(rand() % span_real + min_real, rand() % span_imag + min_imag);
			}
		}
	}

	int get_columns() {
		return columns;
	}

	int get_rows() {
		return rows;
	}

	void set(unsigned int i, unsigned int j, double real, double imag) {
		assert(i < rows);
		assert(j < columns);
		matrix[i][j] = ComplexNum(real, imag);
	}

	void set(unsigned int i, unsigned int j, ComplexNum num) {
		assert(i < columns);
		assert(j < rows);
		matrix[i][j] = num;
	}

	void set_column(int j, ComplexNum* num)
	{
		for (int i = 0; i < this->rows; i++)
			this->set(i, j, num[i]);
	}

	void set_row(int i, ComplexNum* num)
	{
		for (int j = 0; j < this->columns; j++)
			this->set(i, j, num[j]);
	}

	ComplexNum get(unsigned int i, unsigned int j) {
		assert(i < columns);
		assert(j < rows);
		return matrix[i][j];
	}

	void print() {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				std::cout << matrix[i][j] << "  ";
			}
			std::cout << '\n';
		}
	}

	ComplexMatrix operator +(const ComplexMatrix& other)const  //add 2 matrix
	{
		ComplexMatrix temp(this->rows, this->columns);
		if (rows != other.rows || columns != other.columns)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					temp.matrix[i][j] = this->matrix[i][j];
			return temp;
		}
		else
		{
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					temp.matrix[i][j] = other.matrix[i][j] + matrix[i][j];

				}
			}
		}
		return temp;
	}

	bool operator ==(const ComplexMatrix& other)const
	{
		if (this->columns != other.columns || this->rows != other.rows)
			return false;

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				if (this->matrix[i][j] != other.matrix[i][j])
					return false;
			}
		}

		return true;
	}

	/*ComplexMatrix* add(ComplexMatrix* m1, ComplexMatrix* m2) {
		ComplexMatrix* res = new ComplexMatrix(m1->columns, m1->rows);
		for (int i = 0; i < m1->columns; i++) {
			for (int j = 0; j < m1->rows; j++) {
				ComplexNum temp = *(m1->matrix[i][j]) + *(m2->matrix[i][j]);
				res->matrix[i][j] = &temp;
			}
		}
		return res;
	}*/
	/*
	ComplexMatrix operator-(const ComplexMatrix& cm1) {
		assert(this->width == cm1.width);
		assert(this->height == cm1.height);
		ComplexMatrix new_matr(this->width, this->height);
		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < this->width; j++) {
				*(new_matr.matrix[i][j]) = *(matrix[i][j]) - *(cm1.matrix[i][j]);
			}
		}
	}*/

};

