#pragma once
#include <iostream>
#include "ComplexMatrix.h"



ComplexMatrix* regular_mult(ComplexMatrix* a, ComplexMatrix* b) {
    ComplexMatrix* res = new ComplexMatrix(a->get_rows(), b->get_columns());
    for (int i = 0; i < a->get_rows(); i++)
    {
        for (int j = 0; j < b->get_columns(); j++)
        {
            for (int k = 0; k < b->get_rows(); k++)
            {
                res->set(i, j,res->get(i, j) + a->get(i,k) * b->get(k,j));
            }
        }
    }
    return res;
}
/*
ComplexMatrix* matr_mult(ComplexMatrix* a, ComplexMatrix* b) {
    int c_num = a->get_columns();
    int r_num = b->get_rows();
    int adj_num = b->get_columns();
    ComplexMatrix* res = new ComplexMatrix(c_num, r_num);

    for (int i = 0; i < c_num; i++) {
        for (int j = 0; j < r_num; j++) {
            for (int k = 0; k < adj_num; k++) {
                res->set(i, j, a->get(i, k) * b->get(k, j));
            }
        }
    }
    return res;
}

ComplexMatrix* Strassen(ComplexMatrix* a, ComplexMatrix* b) {
    int n = a->get_columns();
    int m = b->get_rows();
    int l = b->get_columns();
    if (n == 1 || m == 1 || l == 1)
        return matr_mult(a, b);

    ComplexMatrix* c_matr = new ComplexMatrix(n, m);
    int adj_n = (n >> 1) + (n & 1);
    int adj_l = (l >> 1) + (l & 1);
    int adj_m = (m >> 1) + (m & 1);

    ComplexMatrix*** a_matr = new ComplexMatrix * *[2];
    a_matr[0] = new ComplexMatrix * [2];
    a_matr[1] = new ComplexMatrix * [2];
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            a_matr[i][j] = new ComplexMatrix(adj_n, adj_l);
            for (int k = 0; k < adj_n; k++) {
                for (int x = 0; x < adj_l; x++) {
                    int K = k + (i & 1) * adj_n;
                    int L = x + (j & 1) * adj_l;
                    a_matr[i][j]->set(k, x, ((K < n&& L < l) ? a->get(K, L) : ComplexNum(0, 0)));
                }
            }
        }
    }

    ComplexMatrix*** b_matr = new ComplexMatrix * *[2];
    b_matr[0] = new ComplexMatrix * [2];
    b_matr[1] = new ComplexMatrix * [2];
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            b_matr[i][j] = new ComplexMatrix(adj_l, adj_m);
            for (int k = 0; k < adj_l; k++) {
                for (int x = 0; x < adj_m; x++) {
                    int K = k + (i & 1) * adj_l;
                    int L = x + (j & 1) * adj_m;
                    b_matr[i][j]->set(k, x, ((K < l&& L < m) ? b->get(K, L) : ComplexNum(0, 0)));
                }
            }
        }
    }
    ComplexMatrix** s_arr = new ComplexMatrix * [10];
    for (int i = 0; i < 10; i++) {
        switch (i)
        {
        case 0:
            s_arr[i] = new ComplexMatrix(adj_l, adj_m);
            for (int j = 0; j < adj_l; j++) {
                for (int k = 0; k < adj_m; k++) {
                    s_arr[i]->set(j, k, b_matr[0][1]->get(j, k) - b_matr[1][1]->get(j, k));

                }
            }
            break;
        case 1:
            s_arr[i] = new ComplexMatrix(adj_n, adj_l);
            for (int j = 0; j < adj_n; j++) {
                for (int k = 0; k < adj_l; k++) {
                    s_arr[i]->set(j, k, a_matr[0][0]->get(j, k) + a_matr[0][1]->get(j, k));
                }
            }
            break;
        case 2:
            s_arr[i] = new ComplexMatrix(adj_n, adj_l);
            for (int j = 0; j < adj_n; j++) {
                for (int k = 0; k < adj_l; k++) {
                    s_arr[i]->set(j, k, a_matr[1][0]->get(j, k) + a_matr[1][1]->get(j, k));

                }
            }
            break;
        case 3:
            s_arr[i] = new ComplexMatrix(adj_l, adj_m);
            for (int j = 0; j < adj_l; j++) {
                for (int k = 0; k < adj_m; k++) {
                    s_arr[i]->set(j, k, b_matr[1][0]->get(j, k) - b_matr[0][0]->get(j, k));

                }
            }
            break;
        case 4:
            s_arr[i] = new ComplexMatrix(adj_n, adj_l);
            for (int j = 0; j < adj_n; j++) {
                for (int k = 0; k < adj_l; k++) {
                    s_arr[i]->set(j, k, a_matr[0][0]->get(j, k) + a_matr[1][1]->get(j, k));
                }
            }
            break;
        case 5:
            s_arr[i] = new ComplexMatrix(adj_l, adj_m);
            for (int j = 0; j < adj_l; j++) {
                for (int k = 0; k < adj_m; k++) {
                    s_arr[i]->set(j, k, b_matr[0][0]->get(j, k) + b_matr[1][1]->get(j, k));
                }
            }
            break;
        case 6:
            s_arr[i] = new ComplexMatrix(adj_n, adj_l);
            for (int j = 0; j < adj_n; j++) {
                for (int k = 0; k < adj_l; k++) {
                    s_arr[i]->set(j, k, a_matr[0][1]->get(j, k) - a_matr[1][1]->get(j, k));
                }
            }
            break;
        case 7:
            s_arr[i] = new ComplexMatrix(adj_l, adj_m);
            for (int j = 0; j < adj_l; j++) {
                for (int k = 0; k < adj_m; k++) {
                    s_arr[i]->set(j, k, b_matr[1][0]->get(j, k) + b_matr[1][1]->get(j, k));
                }
            }
            break;
        case 8:
            s_arr[i] = new ComplexMatrix(adj_n, adj_l);
            for (int j = 0; j < adj_n; j++) {
                for (int k = 0; k < adj_l; k++) {
                    s_arr[i]->set(j, k, a_matr[0][0]->get(j, k) - a_matr[1][0]->get(j, k));
                }
            }
            break;
        case 9:
            s_arr[i] = new ComplexMatrix(adj_l, adj_m);
            for (int j = 0; j < adj_l; j++) {
                for (int k = 0; k < adj_m; k++) {
                    s_arr[i]->set(j, k, b_matr[0][0]->get(j, k) + b_matr[0][1]->get(j, k));
                }
            }
            break;
        }


    }


    ComplexMatrix** res_arr = new ComplexMatrix * [7];
    res_arr[0] = Strassen(a_matr[0][0], s_arr[0]);
    res_arr[1] = Strassen(s_arr[1], b_matr[1][1]);
    res_arr[2] = Strassen(s_arr[2], b_matr[0][0]);
    res_arr[3] = Strassen(a_matr[1][1], s_arr[3]);
    res_arr[4] = Strassen(s_arr[4], s_arr[5]);
    res_arr[5] = Strassen(s_arr[6], s_arr[7]);
    res_arr[6] = Strassen(s_arr[8], s_arr[9]);
    for (int i = 0; i < adj_n; i++) {
        for (int j = 0; j < adj_m; j++) {
            c_matr->set(i, j, res_arr[4]->get(i, j) + res_arr[3]->get(i, j) - res_arr[1]->get(i, j) + res_arr[5]->get(i, j));
            if (j + adj_m < m) {
                c_matr->set(i, j + adj_m, res_arr[0]->get(i, j) + res_arr[1]->get(i, j));
            }
            if (i + adj_n < n) {
                c_matr->set(i + adj_n, j, res_arr[2]->get(i, j) + res_arr[3]->get(i, j));
            }
            if (i + adj_n < n && j + adj_m < m) {
                c_matr->set(i + adj_n, j + adj_m, res_arr[4]->get(i, j) + res_arr[0]->get(i, j) - res_arr[2]->get(i, j) - res_arr[6]->get(i, j));
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            delete[] a_matr[i][j];
        }
        delete[] a_matr[i];
    }
    delete[] a_matr;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            delete[] b_matr[i][j];
        }
        delete[] b_matr[i];
    }
    delete[] b_matr;

    for (int i = 0; i < 10; i++) {
        delete s_arr[i];
    }
    delete[] s_arr;

    for (int i = 0; i < 7; i++) {
        delete res_arr[i];
    }
    delete[] res_arr;

    return c_matr;

}*/

ComplexMatrix* Strassen_rec(ComplexMatrix* a, ComplexMatrix* b) {
    // matrices sizes are M x N and N x Q
    int N = a->get_columns();
    int M = a->get_rows();
    int Q = b->get_columns();
    if (N <= 8 || M <= 8 || Q <= 8) {
        return regular_mult(a, b);
    }
    int new_N = N / 2 + N % 2;
    int new_M = M / 2 + M % 2;
    int new_Q = Q / 2 + Q % 2;
    ComplexMatrix a11(new_M, new_N);
    ComplexMatrix a12(new_M, new_N);
    ComplexMatrix a21(new_M, new_N);
    ComplexMatrix a22(new_M, new_N);
    
    for (int i = 0; i < new_M; i++) {
        for (int j = 0; j < new_N; j++) {
            a11.set(i, j, a->get(i, j));
            a12.set(i, j, ((j + new_N) < N) ? a->get(i, j + new_N) : ComplexNum(0, 0));
            a21.set(i, j, ((i + new_M) < M) ? a->get(i + new_M, j) : ComplexNum(0, 0));
            a22.set(i, j, ((i + new_M) < M && (j + new_N) < N) ? a->get(i + new_M, j + new_N) : ComplexNum(0, 0));
        }
    }


    ComplexMatrix b11(new_N, new_Q);
    ComplexMatrix b12(new_N, new_Q);
    ComplexMatrix b21(new_N, new_Q);
    ComplexMatrix b22(new_N, new_Q);

    for (int i = 0; i < new_N; i++) {
        for (int j = 0; j < new_Q; j++) {
            b11.set(i, j, b->get(i, j));
            b12.set(i, j, ((j + new_Q) < Q) ? b->get(i, j + new_Q) : ComplexNum(0, 0));
            b21.set(i, j, ((i + new_N) < N) ? b->get(i + new_N, j) : ComplexNum(0, 0));
            b22.set(i, j, ((i + new_N) < N && (j + new_Q) < Q) ? b->get(i + new_N, j + new_Q) : ComplexNum(0, 0));
        }
    }

    ComplexMatrix* M1;// = new ComplexMatrix(new_M, new_Q);
    M1 = Strassen_rec(&(a11 + a22), &(b11 + b22));
    ComplexMatrix* M2;// = new ComplexMatrix(new_N, new_N);
    M2 = Strassen_rec(&(a21 + a22), &b11);
    ComplexMatrix* M3;// = new ComplexMatrix(new_N, new_N);
    M3 = Strassen_rec(&a11, &(b12 - b22));
    ComplexMatrix* M4;// = new ComplexMatrix(new_N, new_N);
    M4 = Strassen_rec(&a22, &(b21 - b11));
    ComplexMatrix* M5;// = new ComplexMatrix(new_N, new_N);
    M5 = Strassen_rec(&(a11 + a12), &(b22));
    ComplexMatrix* M6;// = new ComplexMatrix(new_N, new_N);
    M6 = Strassen_rec(&(a21 - a11), &(b11 + b12));
    ComplexMatrix* M7;// = new ComplexMatrix(new_N, new_N);
    M7 = Strassen_rec(&(a12 - a22), &(b21 + b22));

    ComplexMatrix* R1;
    ComplexMatrix *R2;
    ComplexMatrix *R3;
    ComplexMatrix *R4;
    R1 = &(*M1 + *M4 - *M5 + *M7);
    R2 = &(*M3 + *M5);
    R3 = &(*M2 + *M4);
    R4 = &(*M1 - *M2 + *M3 + *M6);
    ComplexMatrix* Res = new ComplexMatrix(M, Q);
    for (int i = 0; i < new_M; i++) {
        for (int j = 0; j < new_Q; j++) {
            Res->set(i, j, R1->get(i, j));
            if ((j + new_Q) < Q) {
                Res->set(i, j + new_Q, R2->get(i, j));
            }
            if ((i + new_M) < M) {
                Res->set(i + new_M, j, R3->get(i, j));
            }
            if ((i + new_M) < M && (j + new_Q) < Q) {
                Res->set(i + new_M, j + new_Q, R4->get(i, j));
            }
        }
    }
    delete M1; delete M2; delete M3; delete M4; delete M5; delete M6; delete M7; 
   // delete R1; delete R2; delete R3; delete R4;
    return Res;
}

ComplexMatrix* Strassen(ComplexMatrix* a, ComplexMatrix* b) {
    assert(a->get_columns() == b->get_rows());
    if (a->get_columns() <= 8 || a->get_rows() <= 8 || b->get_columns() <= 8) {
        return regular_mult(a,b);
    }
    
    return Strassen_rec(a,b);

}


