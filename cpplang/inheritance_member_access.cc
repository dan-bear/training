/**
 * Private members of the base class cannot be acccessed by
 * the deriving class.
 */
class Base{
public:
    int m_accessibleMember{1};
private:
    int m_inaccessibleMember{-1};
};

class Derived : public Base{
public:
    ///Does not compile, the derived class tries to access
    ///a private member of the base class.
    //Derived() : m_val(m_inaccessibleMember) {} 

    ///Works:
    Derived() : m_val(m_accessibleMember) {}
    
private:
    int m_val;
};
