
#include <iostream>
#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "Strassen.h"
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

	ComplexMatrix matr(10, 10);
	matr.auto_gen(-2, 2, 0, 0);
	/*matr.set(0, 0, 1, 2);
	matr.set(0, 1, 0, -3);
	matr.set(1, 0, 8, -2);
	matr.set(1, 1, 0, 0);*/
	matr.print();
	std::cout << "A" << std::endl;
	ComplexMatrix matr1(10, 10);
	matr1.auto_gen(-4, 4, 0, 0);
	/*matr1.set(0, 0, 2, 2);
	matr1.set(0, 1, 4, -5);
	matr1.set(1, 0, 1, -1);
	matr1.set(1, 1, 5, 0);*/
	matr1.print();
	std::cout << "B" << std::endl;
	ComplexMatrix* m = regular_mult(&matr, &matr1);
	m->print();
	std::cout << "C" << std::endl;
	m = Strassen(&matr, &matr1);
	m->print();
}

