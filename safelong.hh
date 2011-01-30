#include <limits.h>
#include <math.h>
#include <string>





//------------------------------------------------------------------
// SafeLong class
//
class SafeLong
{
public:
    long long int _val;

    SafeLong () { };
    SafeLong (long long int value) : _val (value) { }
    SafeLong (int value) : _val ( (long long int) value ) { }
    SafeLong (char value) : _val( (long long int) value ) { }
    SafeLong& operator= (long long int);
    SafeLong& operator= (const SafeLong&);

    static const unsigned long long int SIGN_BIT = (1uLL << (sizeof(long long int) * 8 - 1));
    static const int LONGBITS = sizeof(long long int) * 8;
    static const long long int THRESHOLD = 2000000000l;


};
//
//--------------------------------------------------------------------




//--------------------------------------------------------------------
//
// SafeLong operators
//
SafeLong operator + (SafeLong, SafeLong);
SafeLong operator - (SafeLong, SafeLong);
SafeLong operator * (SafeLong, SafeLong);
SafeLong operator / (SafeLong, SafeLong);
SafeLong operator % (SafeLong, SafeLong);

bool operator== (SafeLong, SafeLong);
bool operator < (SafeLong, SafeLong);
bool operator <= (SafeLong, SafeLong);
bool operator > (SafeLong, SafeLong);
bool operator >= (SafeLong, SafeLong);
bool operator ! (SafeLong);

SafeLong& operator ++ (SafeLong&);
SafeLong operator ++ (SafeLong&, int);
SafeLong& operator -- (SafeLong&);
SafeLong operator -- (SafeLong&, int);
SafeLong& operator += (SafeLong&, SafeLong);
SafeLong& operator += (SafeLong&, long long int i);
SafeLong& operator -= (SafeLong&, SafeLong);
SafeLong& operator -= (SafeLong&, long long int);
SafeLong& operator *= (SafeLong&, SafeLong);
SafeLong& operator *= (SafeLong&, long long int);
SafeLong& operator /= (SafeLong&, SafeLong);
SafeLong& operator /= (SafeLong&, long long int);
SafeLong& operator %= (SafeLong&, SafeLong);
SafeLong& operator %= (SafeLong&, long long int);
SafeLong operator - (SafeLong);
SafeLong abs(SafeLong);

std::ostream& operator << (std::ostream&, SafeLong);


inline SafeLong& SafeLong::operator=(long long int val)
{
    _val = val;
    return *this;
}

inline SafeLong& SafeLong::operator=(const SafeLong& arg)
{
    _val = arg._val;
    return *this;
}


inline SafeLong operator + (SafeLong lhs, SafeLong rhs)
{
    long long int sum = lhs._val + rhs._val;
    
    unsigned long long int lhsBits = (unsigned long long int) lhs._val;
    unsigned long long int rhsBits = (unsigned long long int) rhs._val;
    unsigned long long int sumBits = (unsigned long long int) sum;

    //  Test if the sign bits are the same
    //    and if they are, test if that sign bit
    //    is the same as that of the operands
    if( ~(lhsBits ^ rhsBits) &  SafeLong::SIGN_BIT )
        if( (lhsBits ^ sumBits) & SafeLong::SIGN_BIT )
            throw "overflow";

    return SafeLong(sum);
}


inline SafeLong operator - (SafeLong lhs, SafeLong rhs)
{
    SafeLong rhsNew(-rhs._val);
    return lhs + rhsNew;
}


inline SafeLong operator * (SafeLong lhs, SafeLong rhs)
{
    
    // bit patterns (of the absolute values)
    unsigned long long int leftBits = (unsigned long long int) 
                           lhs._val & SafeLong::SIGN_BIT ? -lhs._val : lhs._val;
    unsigned long long int rightBits = (unsigned long long int) 
                           rhs._val & SafeLong::SIGN_BIT ? -rhs._val : rhs._val;
 

    
    // check for the threshold
    if( lhs._val > -SafeLong::THRESHOLD && lhs._val < SafeLong::THRESHOLD &&
        rhs._val > -SafeLong::THRESHOLD && rhs._val < SafeLong::THRESHOLD )
        return SafeLong( lhs._val * rhs._val );
    else
    {
        // Count the place values :
        //   overflow can only occur if the place values of the most
        //   significant bits add to 63 or more
        int leftSigBit = 0;
        int rightSigBit = 0;

        for(int i=0; i<SafeLong::LONGBITS; i++)
          if(leftBits & 1uLL << (SafeLong::LONGBITS - i - 1))
          { leftSigBit = SafeLong::LONGBITS - i; break;}

        for(int i=0; i<SafeLong::LONGBITS; i++)
          if(rightBits & 1uLL << (SafeLong::LONGBITS - i - 1))
          { rightSigBit = SafeLong::LONGBITS - i; break;}
 

        // If the place values add to more than 64(for pos), then overflow
        if(leftSigBit + rightSigBit - 1 > SafeLong::LONGBITS - 2)
            throw "overflow";

     }


    return SafeLong( lhs._val * rhs._val );
}


inline SafeLong operator / (SafeLong lhs, SafeLong rhs)
{
    long long int quotient = lhs._val / rhs._val;

    return SafeLong(quotient);
}


inline SafeLong operator % (SafeLong lhs, SafeLong rhs)
{
    long long int mod = lhs._val % rhs._val;

    return SafeLong(mod);
}


inline bool operator == (SafeLong lhs, SafeLong rhs)
{
    return lhs._val == rhs._val;
}


inline bool operator < (SafeLong lhs, SafeLong rhs)
{
    return lhs._val < rhs._val;
}


inline bool operator <= (SafeLong lhs, SafeLong rhs)
{
    return lhs._val <= rhs._val;
}


inline bool operator > (SafeLong lhs, SafeLong rhs)
{
    return lhs._val > rhs._val;
}


inline bool operator >= (SafeLong lhs, SafeLong rhs)
{
    return lhs._val >= rhs._val;
}


inline bool operator ! (SafeLong arg)
{
    return !arg._val;
}


inline SafeLong& operator ++ (SafeLong& arg)
{
    SafeLong one(1);
    arg = arg + one;
    return arg;
}


inline SafeLong operator ++ (SafeLong& arg, int i)
{
    long long int val = arg._val;
    SafeLong one(1);
    arg = arg + 1;
    return SafeLong(val); 
}


inline SafeLong& operator += (SafeLong& lhs, SafeLong rhs)
{
    lhs = lhs + rhs;
    return lhs;
}


inline SafeLong& operator += (SafeLong& lhs, long long int rhs)
{
    lhs = lhs + SafeLong(rhs);
    return lhs;
}


inline SafeLong& operator -- (SafeLong& arg)
{
    SafeLong one(1);
    arg = arg - one;
    return arg;
}


inline SafeLong operator -- (SafeLong& arg, int i)
{
    long long int val = arg._val;
    SafeLong one(1);
    arg = arg - one;
    return SafeLong(val);
}


inline SafeLong& operator -= (SafeLong& lhs, SafeLong rhs)
{
    return lhs += -rhs;
}


inline SafeLong& operator -= (SafeLong& lhs, long long int rhs)
{
    return lhs += -rhs;
}


inline SafeLong& operator *= (SafeLong& lhs, SafeLong rhs)
{
    lhs = lhs * rhs;
    return lhs;
}


inline SafeLong& operator *= (SafeLong& lhs, long long int rhs)
{
    return lhs *= SafeLong(rhs);
}


inline SafeLong& operator /= (SafeLong& lhs, SafeLong rhs)
{
    lhs = lhs / rhs;
    return lhs;
}


inline SafeLong& operator /= (SafeLong& lhs, long long int rhs)
{
    return lhs /= SafeLong(rhs);
}


inline SafeLong& operator %= (SafeLong& lhs, SafeLong rhs)
{
    lhs = lhs % rhs;
    return lhs;
}


inline SafeLong& operator %= (SafeLong& lhs, long long int rhs)
{
    return lhs %= SafeLong(rhs);
}


inline SafeLong operator - (SafeLong arg)
{
    return SafeLong( -arg._val );
}

inline SafeLong abs(SafeLong arg)
{
    unsigned long long int argBits = (unsigned long long int) arg._val;
    if(argBits & SafeLong::SIGN_BIT)
        return -arg;
    else
        return arg;
}


inline std::ostream& operator << (std::ostream& out, SafeLong si)
{
    out << si._val;
    return out;
}
//
// End SafeLong operators
//------------------------------------------------------------------------

