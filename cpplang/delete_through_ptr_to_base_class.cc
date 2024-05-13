/**
 * Abstract class must delare a virtual dtor
 * in order to call delete of a derived class
 * while holdig a pointer to the base class.
 */
class Base{
public:
    virtual void vFunc();
};

class Derive : public Base{
public:
};

int main(){
  Base* pB = new Derive();
  ///The static type of pB is Base*
  ///The dynamic type of pB is Derive*.
  delete pB;
  ///once delete is called, Derive' dtor is called
  ///and then Base' dtor is called. Also base has
  ///a virtual function, its default dtor is not
  ///virtual.
  ///The result of delete pB is undefined behaviour
  ///since base does not have virtual dtor.
  ///To solve it, add the next line to the Base class.
  ///"virtual ~base() = defualt".
}
