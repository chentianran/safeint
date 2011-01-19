#include "safeint.hh"
#include <iostream>

using namespace std;



void Try(int o1, int o2, SafeIntLong* L, SafeIntFloat* F, SafeIntLim* M)
{
    L[0]._val = F[0]._val = M[0]._val = o1;
    L[1]._val = F[1]._val = M[1]._val = o2;


    cout << endl;
    cout << "--------------------\n";
    cout << "Operands : " << o1 << ", " << o2 << endl << endl;
    cout << "Addition\n--------\n";
    cout << "int : " << o1 + o2 << endl;
    cout << "SafeIntLong : ";
    try
    {
        SafeIntLong lSum = L[0] + L[1];
    }
    catch(const char* error)
    {
        cout << "Overflow!  Result is ";
    }
    cout << o1 + o2 << endl;
    cout << "SafeIntFloat : ";
    try
    {
        SafeIntFloat fSum = F[0] + F[1];
    }
    catch(const char* error)
    {
        cout << "Overflow!  Result is ";
    }
    cout << o1 + o2 << endl;
    cout << "SafeIntLim : ";
    try
    {
        SafeIntLim mSum = M[0] + M[1];
    }
    catch(const char* error)
    {
        cout << "Overflow!  Result is ";
    }
    cout << o1 + o2 << endl << endl;

    cout << "Multiplication\n--------\n";
    cout << "int : " << o1 * o2 << endl;
    cout << "SafeIntLong : ";
    try
    {
        SafeIntLong lProd = L[0] * L[1];
    }
    catch(const char* error)
    {
        cout << "Overflow!  Result is ";
    }
    cout << o1 * o2 << endl;
    cout << "SafeIntFloat : ";
    try
    {
        SafeIntFloat fProd = F[0] * F[1];
    }
    catch(const char* error)
    {
        cout << "Overflow!  Result is ";
    }
    cout << o1 * o2 << endl;
    cout << "SafeIntLim : ";
    try
    {
        SafeIntLim mProd = M[0] * M[1];
    }
    catch(const char* error)
    {
        cout << "Overflow!  Result is ";
    }
    cout << o1 * o2 << endl << endl;
    cout << "--------------------\n";
}



/*
 * main
 */
int main()
{
    SafeIntLong L[2] = {SafeIntLong(0), SafeIntLong(0)};
    SafeIntFloat F[2] = {SafeIntFloat(0), SafeIntFloat(0)};
    SafeIntLim M[2] = {SafeIntLim(0), SafeIntLim(0)};

    int op1, op2;

    //
    // Cases involving zero...(shouldn't overflow anyways)
    //
    op1 = -30000;
    op2 = 0;
    Try(op1, op2, L, F, M);

    op1 = 0;
    op2 = 50000;
    Try(op1, op2, L, F, M);

    op1 = 10;
    op2 = 35;
    Try(op1, op2, L, F, M);

    op1 = 789;
    op2 = -38;
    Try (op1, op2, L, F, M);

    op1 = -572;
    op2 = 34;
    Try(op1, op2, L, F, M);


    //
    // Should cause addition overflow (and so also multiplication overflow)
    //

    // Positive
    op1 = 2000000000;
    op2 = 1000000000;
    Try(op1, op2, L, F, M);

    // Negative
    op1 = -2000000000;
    op2 = -1000000000;
    Try(op1, op2, L, F, M);

    //
    // Should cause multiplication overflow
    //

    // Negative overflow
    op1 = -450000;
    op2 = 6872;
    Try(op1, op2, L, F, M);

    // Positive overflow
    op1 = 2;
    op2 = 1080000000;
    Try(op1, op2, L, F, M);

    // Positive overflow
    op1 = -3;
    op2 = -716000000;
    Try(op1, op2, L, F, M);

    
}
