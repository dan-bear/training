/**
 * @note remember that private members of the base class cannot
 *       be accessed (what so ever) by the derived class
 * @note remember that protected members can be accessed only
 *       from the derived class.
 *
 * There are three type of access specifier when a class
 * derives from another:
 * public specifier - 1: All the public members of the base class
 *                       becomes public in the derived class.
 *                    2: All the protected members of the base class
 *                       becomes protected members in the derived class.
 * protect specifier - Makes both the public and protected members of
 *                     the base class, protected in the derived class.
 * private specifier - Makes both the public and protected members of
 *                     the base class, private in the derived class.
 */

class Base{
public:
    int m_accessibleToAllInstanceHolder{1};
protected:
    int m_accessibleToDerivingInstances{2};
private:
    int m_baseInaccessible{3};
};

///public access specifier
class DerivedPub : public Base{
public:
    ///Holds m_accessibleToAllInstanceHolder as public member.

protected:
    ///Holds m_accessibleToDerivingInstances as protected member.\

private:
    ///Nothing here.  
};

///protected access specifier
class DerivedProt : protected Base{
public:
    ///Nothing here.

protected:
    ///Holds m_accessibleToAllInstanceHolder as protected member.
    ///Holds m_accessibleToDerivingInstances as protected member.
private:

    ///Nothing here.
};

///private access specifier
class DerivedProt : private Base{
public:
    ///Nothing here.

protected:
    ///Nothing here.

private:
    ///Holds m_accessibleToAllInstanceHolder as private member.
    ///Holds m_accessibleToDerivingInstances as private member.
    
};
