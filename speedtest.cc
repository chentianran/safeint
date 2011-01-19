#include <iostream>
#include "safeint.hh"

//#define TYPE SafeIntLong

int main (int argc, char** argv)
{
    int rows = 10000, cols = 1000;
    int max_iter = 5;

    TYPE* x = new TYPE [cols];
    TYPE* y = new TYPE [rows];
    TYPE* A = new TYPE [rows * cols];

    for (int iter = 0; iter < max_iter; ++iter) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                A[i*cols+j] = 1;

        for (int i = 0; i < cols; ++i)
            x[i] = 1;

        for (int i = 0; i < rows; ++i) {
            y[i] = 0.0;
            for (int j = 0; j < cols; ++j)
                y[i] = y[i] + A[i*cols+j] * x[j];
        }
    }

    delete [] x;
    delete [] y;
    delete [] A;
}

