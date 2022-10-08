#include "ComplexMatrix.h"

ComplexMatrix GaussJordanInverse(ComplexMatrix A)
{
    int rank = A.get_rows(); //rows
    int columns = A.get_columns(); //columns

    assert(rank == columns);
    assert(rank == A.getRank());

    ComplexMatrix resMatrix(rank, rank);

    for(int i = 0; i < rank; i++)
    {
        for(int j = 0; j < rank; j++)
        {
            resMatrix.set(i,j,((i==j) ? 1 : 0), 0);
        }
    }

    for(int i = 0; i < rank; i++)
    {
        assert(A.get(i, i) != ComplexNum(0,0)); // checking nulls on a principal diagonal

        for(int j = 0; j < rank; j++)
        {
            if(i != j)
            {
                ComplexNum ratio = A.get(j, i) / A.get(i, i);

                for(int k = 0; k < rank; k++)
                {
                    A.set(j, k, A.get(j, k) - ratio * A.get(i, k));
                    resMatrix.set(j, k, resMatrix.get(j, k) - ratio * resMatrix.get(i, k));
                }
            }
        }
    }

    for(int i = 0; i < rank; i++)
    {
        for(int j = 0; j < rank; j++)
        {
            resMatrix.set(i, j, resMatrix.get(i,j) / A.get(i, i));
        }
    }

    return resMatrix;
}