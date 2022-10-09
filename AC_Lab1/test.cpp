#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "LU_Inverse.h"
#include "GaussJordan.h"

#include "doctest.h"
#include <time.h>

TEST_CASE("Validity test: Strassen algorithm is equal to regular matrix multiplication") {
	ComplexMatrix square_m1(10, 10);
	ComplexMatrix square_m2(10, 10);
	square_m1.auto_gen(1, 5, 1, 5);
	square_m2.auto_gen(1, 5, 1, 5);
	ComplexMatrix* reg_res = &(square_m1 * square_m2);
	ComplexMatrix* strassen_res = Strassen(&square_m1, &square_m2);
	CHECK(*reg_res == *strassen_res);
	ComplexMatrix rand_m1(10, 15);
	ComplexMatrix rand_m2(15, 20);
	rand_m1.auto_gen(1, 5, 1, 5);
	rand_m2.auto_gen(1, 5, 1, 5);
	reg_res = &(rand_m1 * rand_m2);
	strassen_res = Strassen(&rand_m1, &rand_m2);
	CHECK(*reg_res == *strassen_res);
}

TEST_CASE("speedtest for strassen algorithm") {
	int start_size = 20;
	int	end_size = 320;
	std::clock_t start, end;
	for (int i = start_size; i <= end_size; i *= 2) {
		ComplexMatrix m1(i, i);
		ComplexMatrix m2(i, i);
		m1.auto_gen(1, 5, 1, 5);
		m2.auto_gen(1, 5, 1, 5);
		start = clock();
		ComplexMatrix* res = Strassen(&m1, &m2);
		end = clock();
		std::cout << "\n N = " << i;
		std::cout << "\n Start: " << start << " ticks";
		std::cout << "\n End: " << end << " ticks";
		std::cout << "\n Duration: " << end - start << " ticks";
		bool checker = (*res == (m1 * m2));
		CHECK(checker);
		std::cout << "\n";
	}
}

TEST_CASE("testing the LU decomposition")
{
	int matrix_size = 4;
	int tests_amount = 100;
	ComplexMatrix A(matrix_size, matrix_size);
	ComplexMatrix L(matrix_size, matrix_size);
	ComplexMatrix U(matrix_size, matrix_size);
	for (int n = 0; n < tests_amount; n++)
	{
		A.auto_gen(5, 50, 5, 50);
		bool res = true;
		if (LU_decomposition(A, L, U))
			res = (A == L * U);
		CHECK(res);
	}
}

TEST_CASE("testing the inverse matrix by LU decomposition")
{
	int matrix_size = 4;
	int tests_amount = 100;
	ComplexMatrix A(matrix_size, matrix_size);
	ComplexMatrix E(matrix_size, matrix_size);

	for (int i = 0; i < matrix_size; i++)
		E.set(i, i, ComplexNum(1));

	for (int n = 0; n < tests_amount; n++)
	{
		A.auto_gen(5, 50, 5, 50);
		ComplexMatrix Inverse_A = LU_inverse(A);
		bool res = true;
		if (Inverse_A.get_rows() != 0)
			res = (E == A * Inverse_A);
		CHECK(res);
	}
}

TEST_CASE("speedtesting the LU decomposition")
{
	int matrix_size = 50;
	int tests_amount = 20;
	ComplexMatrix A(matrix_size, matrix_size);
	ComplexMatrix L(matrix_size, matrix_size);
	ComplexMatrix U(matrix_size, matrix_size);
	std::clock_t start, end;

	for (int n = 0; n < tests_amount; n++)
	{
		A.auto_gen(2, 50, 2, 50);
		bool res = true;
		start = clock();
		if (LU_decomposition(A, L, U))
			res = (A == L * U);
		end = clock();
		std::cout << "The end: " << end << " ticks" << "\n";
		std::cout << "The start: " << start << " ticks" << "\n";
		std::cout << "Elapsed time: " << end - start << " ticks" << "\n\n";
		CHECK(res);
	}
}

TEST_CASE("speedtesting the inverse matrix by LU decomposition")
{
	int matrix_size = 200;
	int tests_amount = 20;
	ComplexMatrix A(matrix_size, matrix_size);
	ComplexMatrix E(matrix_size, matrix_size);
	std::clock_t start, end;

	for (int i = 0; i < matrix_size; i++)
		E.set(i, i, ComplexNum(1));

	for (int n = 0; n < tests_amount; n++)
	{
		A.auto_gen(2, 50, 6, 49);

		start = clock();
		ComplexMatrix Inverse_A = LU_inverse(A);
		end = clock();
		bool res = true;
		if (Inverse_A.get_rows() != 0)
			res = (E == A * Inverse_A);
		std::cout << "The end: " << end << " ticks" << "\n";
		std::cout << "The start: " << start << " ticks" << "\n";
		std::cout << "Elapsed time: " << end - start << " ticks" << "\n\n";
		CHECK(res);
	}
}

TEST_CASE("testing the equality of GaussJordan and LU inversions")
{
    ComplexMatrix A (10, 10);
    A.auto_gen(-10, 10, -10, 10);

    A.print();

    CHECK(GaussJordanInverse(A) == LU_inverse(A));
}

