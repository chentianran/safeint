class SafeIntLong
{
private:

    int _val;

public:

    SafeIntLong (int value) : _val (value) { };
};

SafeIntLong operator + (SafeIntLong&, SafeIntLong&);
SafeIntLong operator - (SafeIntLong&, SafeIntLong&);
SafeIntLong operator * (SafeIntLong&, SafeIntLong&);
SafeIntLong operator / (SafeIntLong&, SafeIntLong&);
SafeIntLong operator % (SafeIntLong&, SafeIntLong&);
    
class SafeIntFloat
{
private:

    int _val;

public:

    SafeIntFloat (int value) : _val (value) { };
};

SafeIntFloat operator + (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator - (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator * (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator / (SafeIntFloat&, SafeIntFloat&);
SafeIntFloat operator % (SafeIntFloat&, SafeIntFloat&);
    
class SafeIntLim
{
private:

    int _val;

public:

    SafeIntLim (int value) : _val (value) { };
};

SafeIntLim operator + (SafeIntLim&, SafeIntLim&);
SafeIntLim operator - (SafeIntLim&, SafeIntLim&);
SafeIntLim operator * (SafeIntLim&, SafeIntLim&);
SafeIntLim operator / (SafeIntLim&, SafeIntLim&);
SafeIntLim operator % (SafeIntLim&, SafeIntLim&);
    
