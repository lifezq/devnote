#include <iostream>
#include <vector>

using namespace std;

class Obj
{
    static int i, j;

public:
    void f() const { cout << "i:" << i++ << endl; }
    void g() const { cout << "j:" << j++ << endl; }
    static int geti()
    {
        return i;
    }
    static int getj()
    {
        return j;
    }
};

int Obj::i = 7;
int Obj::j = 10;

class ObjContainer
{
public:
    static int cnt;
    vector<Obj *> oc;

    ObjContainer()
    {
        cnt++;
    }

    void add(Obj *o)
    {
        oc.push_back(o);
    }

    friend class smartPointer;
    static int count()
    {
        cout << "cnt:" << cnt << endl;
        return cnt;
    }
};

int ObjContainer::cnt = 0;

class smartPointer
{
    ObjContainer objc;
    int index;

public:
    smartPointer(ObjContainer *oc)
    {
        objc = *oc;
        index = 0;
    }

    Obj *operator++()
    {
        index++;
        if (index > objc.oc.size() - 1)
        {
            return (Obj *)0;
        }
        else if (objc.oc[index] == 0)
        {
            return (Obj *)0;
        }

        return objc.oc[index];
    }

    Obj *operator--()
    {
        index--;
        if (index < 0)
        {
            return (Obj *)0;
        }
        else if (index > objc.oc.size() - 1)
        {
            return (Obj *)0;
        }
        else if (objc.oc[index] == 0)
        {
            return (Obj *)0;
        }

        return objc.oc[index];
    }

    Obj *operator[](int i)
    {
        if (i < 0)
        {
            return (Obj *)0;
        }
        else if (i > objc.oc.size() - 1)
        {
            return (Obj *)0;
        }
        else if (objc.oc[i] == 0)
        {
            return (Obj *)0;
        }

        return objc.oc[i];
    }

    Obj *operator->() const
    {
        cout << "->operator index:" << index << endl;

        if (index > objc.oc.size() - 1 || !objc.oc[index])
        {
            cout << "Zero value";
            return (Obj *)0;
        }

        return objc.oc[index];
    }
};

int main()
{
    Obj o;

    cout << "obj i:" << o.geti() << " j:" << o.getj() << endl;

    ObjContainer::count();

    ObjContainer oc;
    int vc = 10;
    for (int i = 0; i < vc; i++)
    {
        oc.add(new Obj);
    }

    smartPointer sp(&oc);
    for (int i = 0; i < vc; i++)
    {
        cout << "sp[i].i:" << (*sp[i]).geti() << " sp[i].j:" << (*sp[i]).getj() << endl;
    }

    do
    {
        sp->f(); // call smart pointer
        sp->g();
    } while (++sp);

    cout << "(Obj *)0:" << (Obj *)0 << " (Obj *)0==NULL: " << ((Obj *)0 == NULL) << endl;

    return 0;
}
