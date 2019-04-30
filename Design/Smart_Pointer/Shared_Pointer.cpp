// C++ libraries provide implementations of smart pointers 
// in the form of auto_ptr, unique_ptr, shared_ptr and weak_ptr

// Below is Smart pointer in the form of Shared pointer

#include <iostream>

using namespace std;

class RC
{
    private:
    int count; // Reference count

    public:
    void AddRef()
    {
        // Increment the reference count
        count++;
    }

    int Release()
    {
        // Decrement the reference count and
        // return the reference count.
        return --count;
    }
    
    int getCount()
    {
        return count;
    }
    
    // Overloading << operator 
    friend ostream& operator<<(ostream& os, const RC& counter)
    {
        os << "Counter Value : " << counter.count << endl; 
    }
};



template < typename T > class SP
{
private:
    T*    pData;        // pointer
    RC* reference;      // Reference count

public:
    SP() : pData(0), reference(0) 
    {
        // Create a new reference 
        reference = new RC();
        // Increment the reference count
        reference->AddRef();
    }

    SP(T* pValue) : pData(pValue), reference(0)
    {
        // Create a new reference 
        reference = new RC();
        // Increment the reference count
        reference->AddRef();
    }

    SP(const SP<T>& sp) : pData(sp.pData), reference(sp.reference)
    {
        // Copy constructor
        // Copy the data and reference pointer
        // and increment the reference count
        reference->AddRef();
    }

    ~SP()
    {
        cout<<"Destructor called !"<<endl;
        
        // Destructor
        // Decrement the reference count
        // if reference become zero delete the data
        if(reference->Release() == 0)
        {
            cout<<"Updated "<<*reference;
            
            delete pData;
            delete reference;
            
            cout<<"Memory allocated now deleted !!!";
        }
        else
           cout<<*reference; 
    }

    T& operator* ()
    {
        return *pData;
    }

    T* operator-> ()
    {
        return pData;
    }
    
    SP<T>& operator = (const SP<T>& sp)
    {
        // Assignment operator
        if (this != &sp) // Avoid self assignment
        {
            // Decrement the old reference count
            // if reference become zero delete the old data
            if(reference->Release() == 0)
            {
                delete pData;
                delete reference;
            }

            // Copy the data and reference pointer
            // and increment the reference count
            pData = sp.pData;
            reference = sp.reference;
            reference->AddRef();
        }
        return *this;
    }
    
    T* getPointer()
    {
        return pData;
    }
    
    friend ostream& operator<<(ostream& os, SP<T>& sp) 
	  { 
		    os << "Address pointed : " << sp.getPointer() << endl; 
		    cout << *(sp.reference) << endl; 
	  } 
};

class Person
{
    int age;
    string pName;

    public:
        Person(): pName(0),age(0) {}
        Person(string pName, int age): pName(pName), age(age) {}
        ~Person() {}

        void Display()
        {
            cout<<"Name = "<<pName<<" Age = "<<age<<endl;
        }
        void Shout()
        {
            cout<<"Ooooooooooooooooo";
        } 
};

int main()
{
    SP<Person> p(new Person("Scott", 25));
    
    // Print the address and present reference count
    // To achieve this, overload "<<" operator
    cout<<p;
    p->Display();
    cout<<endl;
    
    {
        SP<Person> q = p;
        cout << "--- Shared pointers p, q ---\n";
        cout<<p;
        cout<<q;
        q->Display();
        cout<<endl;
        

        SP<Person> r;
        r = p;
        cout << "--- Shared pointers p, q, r ---\n";
        cout<<p;
        cout<<q;
        cout<<r;
        r->Display();
        cout<<endl;
    }
    // Destructor of q and r will be called here..
    
    cout<<endl;
    cout << "--- Shared pointers p ---\n";
    cout<<p;
    p->Display();
    // Destructor of p will be called here 
    // and person pointer will be deleted
    
    return 0;
}


/*
Address pointed : 0x1ed0e70
Counter Value : 1

Name = Scott Age = 25

--- Shared pointers p, q ---
Address pointed : 0x1ed0e70
Counter Value : 2

Address pointed : 0x1ed0e70
Counter Value : 2

Name = Scott Age = 25

--- Shared pointers p, q, r ---
Address pointed : 0x1ed0e70
Counter Value : 3

Address pointed : 0x1ed0e70
Counter Value : 3

Address pointed : 0x1ed0e70
Counter Value : 3

Name = Scott Age = 25

Destructor called !
Counter Value : 2
Destructor called !
Counter Value : 1

--- Shared pointers p ---
Address pointed : 0x1ed0e70
Counter Value : 1

Name = Scott Age = 25
Destructor called !
Updated Counter Value : 0
Memory allocated now deleted !!!
*/
