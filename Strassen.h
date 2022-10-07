#pragma once
#include <iostream>
#include "ComplexMatrix.h"



ComplexMatrix* regular_mult(ComplexMatrix* a, ComplexMatrix* b) {
    int c_num = a->get_columns();
    int r_num = b->get_rows();
    int adj_num = b->get_columns();
    ComplexMatrix* res = new ComplexMatrix(c_num, r_num);

    for (int i = 0; i < c_num; i++) {
        for (int j = 0; j < r_num; j++) {
            for (int k = 0; k < adj_num; k++) {
                res->set(i, j, res->get(i, j) + a->get(i, k) * b->get(k, j));
            }
        }
    }
    return res;
}

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

}


