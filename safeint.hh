#include <limits.h>
#include <math.h>



//------------------------------------------------------------------
// SafeIntLong class
//
class SafeIntLong
{
public:
    int _val;

    SafeIntLong (int value) : _val (value) { };
    SafeIntLong& operator = (SafeIntLong&);
};
//
//--------------------------------------------------------------------




//--------------------------------------------------------------------
//
// SafeIntLong operators
//
SafeIntLong operator + (SafeIntLong&, SafeIntLong&);
SafeIntLong operator - (SafeIntLong&, SafeIntLong&);
SafeIntLong operator * (SafeIntLong&, SafeIntLong&);
SafeIntLong operator / (SafeIntLong&, SafeIntLong&);
SafeIntLong operator % (SafeIntLong&, SafeIntLong&);
bool operator== (SafeIntLong&, SafeIntLong&);



inline SafeIntLong& SafeIntLong::operator=(SafeLongInt& arg)
{
    _val = arg._val;

    return *this;
}


inline SafeIntLong operator + (SafeIntLong& lhs, SafeIntLong& rhs)
{
    int sum = lhs._val + rhs._val;
    
    lhsBits = (unsigned) lhs._val;
    rhsBits = (unsigned) rhs._val;
    sumBits = (unsigned) sum;

    //  Test if the sign bits are the same
    //    and if they are, test if that sign bit
    //    is the same as that of the operands
    if( ~(lhsBits ^ rhsBits) &  0x80000000u )
        if( (lhsBits ^ sumBits) & 0x80000000u )
            throw "overflow";

    return SafeIntLong(sum);
}


inline SafeIntLong operator - (SafeIntLong& lhs, SafeIntLong& rhs)
{
    SafeIntLong rhsNew(-rhs._val);
    return lhs + rhsNew;
}


inline SafeIntLong operator * (SafeIntLong& lhs, SafeIntLong& rhs)
{
    long long longLeft = (long long) lhs._val;
    long long longRight = (long long) rhs._val;

    // bit patterns
    unsigned leftBits = (unsigned) lhs._val;
    unsigned rightBits = (unsigned) rhs._val;

    long long product = longLeft * longRight;
    
    // If the signs are the same, test product against max,
    //   otherwise, test against min integer value
    if( ~(leftBits ^ rightBits) & 0x80000000u )
        if(product > (long long) INT_MAX)
            throw "overflow";
    else
        if(product < (long long) INT_MIN)
            throw "overflow";

    return SafeIntLong(product);
}


inline SafeIntLong operator / (SafeIntLong& lhs, SafeIntLong& rhs)
{
    int quotient = lhs._val / rhs._val;

    return SafeIntLong(quotient);
}


inline SafeIntLong operator % (SafeIntLong& lhs, SafeIntLong& rhs)
{
    int mod = lhs._val % rhs._val;

    return SafeIntLong(mod);
}


inline bool operator == (SafeIntLong& lhs, SafeIntLong& rhs)
{
    return lhs._val == rhs._val;
}
//
// End SafeIntLong operators
//------------------------------------------------------------------------



//------------------------------------------------------------------------
// SafeIntFloat class
//    
class SafeIntFloat
{
public:
    int _val;

    SafeIntFloat (int value) : _val (value) { };
    SafeIntFloat& operator = (SafeIntFloat&);
};
//
//--------------------------------------------------------------------------



//--------------------------------------------------------------------------
// SafeIntFloat operators
//
SafeIntFloat operator + (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator - (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator * (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator / (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator % (SafeIntFloat&, SafeIntFloat&);
bool operator== (SafeIntFloat&, SafeIntFloat&);


inline SafeIntFloat& SafeIntFloat::operator=(SafeIntFloat& arg)
{
    _val = arg._val;

    return *this;
}


inline SafeIntFloat operator + (SafeIntFloat& lhs, SafeIntFloat& rhs)
{
    // Bit patterns
    unsigned leftBits = (unsigned) lhs._val;
    unsigned rightBits = (unsigned) rhs._val;

    float leftFloat = (float) lhs._val;
    float rightFloat = (float) rhs._val;

    
    // If the signs are the same, just test the sum of the absolute values against the max
    // If the signs are different, there can be no overflow
    float sum = fabs(leftFloat) + fabs(rightFloat);
    if( ~(leftBits ^ rightBits) & 0x80000000u  && sum > (float) INT_MAX)
        throw "overflow";
        return SafeIntFloat(0);


    return SafeInt( lhs._val + rhs._val );
}


inline SafeIntFloat operator - (SafeIntFloat& lhs, SafeIntFloat& rhs)
{
    SafeIntFloat negRhs( -(rhs._val) );

    return lhs + negRhs;
}


inline SafeIntFloat operator * (SafeIntFloat& lhs, SafeIntFloat& rhs)
{
    float leftFloat = (float) lhs._val;
    float rightFloat = (float) rhs._val;

    float product = leftFloat * rightFloat;
    if(product > (float) INT_MAX || product < (float) INT_MIN)
        throw "overflow";


    return SafeIntFloat( lhs._val * rhs._val );
}


inline SafeIntFloat operator / (SafeIntFloat& lhs, SafeIntFloat& rhs)
{
    return SafeIntFloat( lhs._val / rhs._val );
}


inline SafeIntFloat operator % (SafeIntFloat& lhs, SafeIntFloat& rhs)
{
    return SafeIntFloat( lhs._val % rhs._val );
}


inline bool operator == (SafeIntFloat& lhs, SafeIntFloat& rhs)
{
    return lhs._val == rhs._val;
}
//
// End SafeIntFloat operators
//--------------------------------------------------------------------------    



//--------------------------------------------------------------------------
// SafeIntLim class
//
class SafeIntLim
{
public:
    int _val;

    SafeIntLim (int value) : _val (value) { };
    SafeIntLim& operator = (SafeIntLim&);
};
//
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// SafeIntLim operators
//
SafeIntLim operator + (SafeIntLim&, SafeIntLim&);
SafeIntLim operator - (SafeIntLim&, SafeIntLim&);
SafeIntLim operator * (SafeIntLim&, SafeIntLim&);
SafeIntLim operator / (SafeIntLim&, SafeIntLim&);
SafeIntLim operator % (SafeIntLim&, SafeIntLim&);
SafeIntLim operator== (SafeIntLim&, SafeIntLim&);


inline SafeIntLim& SafeIntLim::operator=(SafeIntLim& arg)
{
    _val = arg._val;
    
    return *this;
}


inline SafeIntLim operator + (SafeIntLim& lhs, SafeIntLim& rhs)
{
    unsigned leftBits = (unsigned) lhs._val;
    unsigned rightBits = (unsigned) rhs._val;

    // Only same-sign additions can overflow
    if( ~(leftBits ^ rightBits) & 0x80000000u )
    {
        // Test negative sum against min value
        if(leftBits & 0x80000000u && lhs._val < INT_MIN - rhs._val)
            throw "overflow";

        // Test positive sum against max value
        else if( !(leftBits & 0x80000000u) && lhs._val > INT_MAX - rhs._val)
            throw "overflow";
    }

    return SafeIntLim( lhs._val + rhs._val );
}


inline SafeIntLim operator - (SafeIntLim& lhs, SafeIntLim& rhs)
{
    SafeIntLim negRhs(-rhs._val);

    return lhs + negRhs;
}


inline SafeIntLim operator * (SafeIntLim& lhs, SafeIntLim& rhs)
{
    // Bit patterns
    unsigned leftBits = (unsigned) lhs._val;
    unsigned rightBits = (unsigned) rhs._val;

    // Operands have same sign...
    //    overflow will happen in the positive direction
    if( ~(leftBits ^ rightBits) & 0x80000000u )
    {
        // positive
        if( !(leftBits & 0x80000000u) && lhs._val > INT_MAX / rhs._val )
            throw "overflow";

        // negative
        else if(leftBits & 0x80000000u && lhs._val < INT_MAX / rhs._val)
            throw "overflow";

    }

    // Operands have opposite sign...
    //    overflow will happen in the negative direction
    else
    {
        // second operand is positive
        if( !(leftBits & 0x80000000u) && lhs._val < INT_MIN / rhs._val )
            throw "overflow";

        // second operand is negative
        if(leftBits & 0x80000000u && lhs._val > INT_MIN / rhs._val)
            throw "overflow";
    }


    return SafeIntLim( lhs._val * rhs._val );
}


inline SafeIntLim operator / (SafeInt& lhs, SafeIntLim& rhs)
{
    return SafeIntLim( lhs._val / rhs._val );
}


inline SafeIntLim operator % (SafeIntLim& lhs, SafeIntLim& rhs)
{
    return SafeIntLim( lhs._val % rhs._val );
}


inline bool operator == (SafeIntLim& lhs, SafeIntLim& rhs)
{
    return lhs._val == rhs._val;
}
