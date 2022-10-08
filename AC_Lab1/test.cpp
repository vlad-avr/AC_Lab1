#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "LU_Inverse.h"

#include "doctest.h"

TEST_CASE("testing the LU decomposition")
{
	int matrix_size = 4;
	int tests_amount = 100;
	ComplexMatrix A(0, 0);
	ComplexMatrix L(0, 0);
	ComplexMatrix U(0, 0);
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
	ComplexMatrix A(0, 0);
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

