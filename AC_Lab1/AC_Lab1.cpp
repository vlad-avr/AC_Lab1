
#include <iostream>
#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "Strassen.h"
#include "LU_Inverse.h"
#include <time.h>

int main()
{
	srand(time(0));
	/*
	ComplexNum c1(1, 2);
	ComplexNum c2(2, -3);
	std::cout << c1;
	std::cout << c2;
	ComplexNum c3 = c1 + c2;
	std::cout << c3;
	ComplexNum c4 = c1 * c2;
	std::cout << c4;
	/*
	ComplexNum num;
	ComplexNum num1(1, 2);
	num = num1;
	std::cout << num;
	*/
	ComplexNum c1(4, 5);
	ComplexNum c2(3, 2);
	std::cout << c1 << "\n";
	std::cout << c2 << "\n";
	ComplexNum c3 = c1 / c2;
	std::cout << c3 << "\n\n_________________________________________________________________\n\n";


	ComplexMatrix matr(2, 2);
	matr.set(0, 0, 4, 0);
	matr.set(0, 1, 3, 0);
	matr.set(1, 0, 6, 0);
	matr.set(1, 1, 3, 0);

	ComplexMatrix matr1(13,4);
	ComplexMatrix matr2(525, 1);

	if (LU_decomposition(matr, matr1, matr2))
	{
		matr.print();
		matr1.print();
		matr2.print();
	}

	
}

