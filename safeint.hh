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

    long long product = longLeft * longRight;
    if(product > (long long) INT_MAX)
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


SafeIntFloat& SafeIntFloat::operator=(SafeIntFloat& arg)
{
    _val = arg._val;

    return *this;
}


// SafeIntFloat operator + (SafeIntFloat
//
// End SafeIntFloat operators
//--------------------------------------------------------------------------    

class SafeIntLim
{
private:

    int _val;

public:

    SafeIntLim (int value) : _val (value) { };
    SafeIntLim& operator = (SafeIntLim&);
};

SafeIntLim operator + (SafeIntLim&, SafeIntLim&);
SafeIntLim operator - (SafeIntLim&, SafeIntLim&);
SafeIntLim operator * (SafeIntLim&, SafeIntLim&);
SafeIntLim operator / (SafeIntLim&, SafeIntLim&);
SafeIntLim operator % (SafeIntLim&, SafeIntLim&);
SafeIntLim operator== (SafeIntLim&, SafeIntLim&);    
