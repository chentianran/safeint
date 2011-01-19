#include <limits.h>
#include <math.h>
#include <string>

using namespace std;


const unsigned int SIGN_BIT = (1u << (sizeof(int) * 8 - 1));



//------------------------------------------------------------------
// SafeInt class
//
class SafeInt
{
public:
    int _val;

    SafeInt () { };
    SafeInt (int value) : _val (value) { }
    SafeInt (short int value) : _val ( (int) value ) { }
    SafeInt (char value) : _val( (int) value ) { }
    SafeInt& operator= (int);
    SafeInt& operator= (const SafeInt&);
};
//
//--------------------------------------------------------------------




//--------------------------------------------------------------------
//
// SafeInt operators
//
SafeInt operator + (SafeInt, SafeInt);
SafeInt operator - (SafeInt, SafeInt);
SafeInt operator * (SafeInt, SafeInt);
SafeInt operator / (SafeInt, SafeInt);
SafeInt operator % (SafeInt, SafeInt);
bool operator== (SafeInt, SafeInt);
bool operator < (SafeInt, SafeInt);
bool operator <= (SafeInt, SafeInt);
bool operator > (SafeInt, SafeInt);
bool operator >= (SafeInt, SafeInt);
bool operator ! (SafeInt);
SafeInt operator - (SafeInt);
SafeInt abs(SafeInt);
ostream& operator << (ostream&, SafeInt);


inline SafeInt& SafeInt::operator=(int val)
{
    _val = val;
    return *this;
}

inline SafeInt& SafeInt::operator=(const SafeInt& arg)
{
    _val = arg._val;
    return *this;
}


inline SafeInt operator + (SafeInt lhs, SafeInt rhs)
{
    int sum = lhs._val + rhs._val;
    
    unsigned int lhsBits = (unsigned int) lhs._val;
    unsigned int rhsBits = (unsigned int) rhs._val;
    unsigned int sumBits = (unsigned int) sum;

    //  Test if the sign bits are the same
    //    and if they are, test if that sign bit
    //    is the same as that of the operands
    if( ~(lhsBits ^ rhsBits) &  SIGN_BIT )
        if( (lhsBits ^ sumBits) & SIGN_BIT )
            throw "overflow";

    return SafeInt(sum);
}


inline SafeInt operator - (SafeInt lhs, SafeInt rhs)
{
    SafeInt rhsNew(-rhs._val);
    return lhs + rhsNew;
}


inline SafeInt operator * (SafeInt lhs, SafeInt rhs)
{
    long long int longLeft = (long long int) lhs._val;
    long long int longRight = (long long int) rhs._val;

    // bit patterns
    unsigned int leftBits = (unsigned int) lhs._val;
    unsigned int rightBits = (unsigned int) rhs._val;

    long long product = longLeft * longRight;
    
    // If the signs are the same, test product against max,
    //   otherwise, test against min integer value
    if( ~(leftBits ^ rightBits) & SIGN_BIT )
    {
        if(product > (long long int) INT_MAX)
            throw "overflow";
    }
    else
        if(product < (long long int) INT_MIN)
            throw "overflow";

    return SafeInt( lhs._val * rhs._val );
}


inline SafeInt operator / (SafeInt lhs, SafeInt rhs)
{
    int quotient = lhs._val / rhs._val;

    return SafeInt(quotient);
}


inline SafeInt operator % (SafeInt lhs, SafeInt rhs)
{
    int mod = lhs._val % rhs._val;

    return SafeInt(mod);
}


inline bool operator == (SafeInt lhs, SafeInt rhs)
{
    return lhs._val == rhs._val;
}


inline bool operator < (SafeInt lhs, SafeInt rhs)
{
    return lhs._val < rhs._val;
}


inline bool operator <= (SafeInt lhs, SafeInt rhs)
{
    return lhs._val <= rhs._val;
}


inline bool operator > (SafeInt lhs, SafeInt rhs)
{
    return lhs._val > rhs._val;
}


inline bool operator >= (SafeInt lhs, SafeInt rhs)
{
    return lhs._val >= rhs._val;
}


inline bool operator ! (SafeInt arg)
{
    return !arg._val;
}


inline SafeInt operator - (SafeInt arg)
{
    return SafeInt( -arg._val );
}

inline SafeInt abs(SafeInt arg)
{
    unsigned int argBits = (unsigned int) arg._val;
    if(argBits & SIGN_BIT)
        return -arg;
    else
        return arg;
}


inline ostream& operator << (ostream& out, SafeInt si)
{
    out << si._val;
    return out;
}
//
// End SafeInt operators
//------------------------------------------------------------------------

