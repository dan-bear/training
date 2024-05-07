///-----------------------------------------------------------------------------
/**
 * Class D is derived from a base class B. If creating an object of
 * type D, what order will the constructors of these classes get
 * called?
 *
 * Answer:
 * The order of ctors calls is done with correspondence to the classes'
 * heirarchy. In this specific question, B's ctor is called before D's ctor.
 * This is pretty intuitive since in many cases the derived class needs the
 * data of the base class (data members and functions) in order to be
 * constructed.
 */

///In the next example, if Base's ctor is not called before
///Derived's ctor the Derived class cannot be instantiated.
class Base{
public:
    Base(int val) : m_baseMember(val) {}
    
    int m_baseMember;
private:
    int m_inaccessibleMember{0};
};

class Derived : public Base{
public:
    Derived() {
      m_derivedMember = m_baseMember > 0 ? m_baseMember : 0;
    }

private:
    int m_derivedMember;
};
