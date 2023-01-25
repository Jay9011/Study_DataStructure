#include <iostream>
using namespace std;

typedef unsigned long long BLONG;

struct Matrix
{
    BLONG Data[2][2];

    static Matrix Multiply(const Matrix& a, const Matrix& b)
    {
        Matrix r;

        r.Data[0][0] = a.Data[0][0] * b.Data[0][0] + a.Data[0][1] * b.Data[1][0];
        r.Data[0][1] = a.Data[0][0] * b.Data[0][1] + a.Data[0][1] * b.Data[1][1];
        r.Data[1][0] = a.Data[1][0] * b.Data[0][0] + a.Data[1][1] * b.Data[1][0];
        r.Data[1][1] = a.Data[1][0] * b.Data[0][1] + a.Data[1][1] * b.Data[1][1];

        return r;
    }
};

Matrix Power(const Matrix& m, int n)
{
    if (n <= 1)
        return m;

    Matrix newM = Power(m, n / 2);
    newM = Matrix::Multiply(newM, newM);

    if (n & 1)
    {
        Matrix b;
        b.Data[0][0] = 1; b.Data[0][1] = 1;
        b.Data[1][0] = 1; b.Data[1][1] = 0;

        newM = Matrix::Multiply(newM, b);
    }

    return newM;
}

BLONG Fibonacci(int n)
{
    Matrix m;
    m.Data[0][0] = 1; m.Data[0][1] = 1;
    m.Data[1][0] = 1; m.Data[1][1] = 0;

    m = Power(m, n);

    return m.Data[0][1];
}

int main()
{
    BLONG temp = Fibonacci(10);

    cout << temp << endl;

    return 0;
}