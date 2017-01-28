#include <iostream>
using namespace std;

// Chaining, Linked List implementation

class LinkedHashEntry{
	int key;
	int val;
	LinkedHashEntry* next;

public:
	// Default constructor required because we
	// can't define parameterized constructor without
  // default constructor
	LinkedHashEntry(){}
	LinkedHashEntry(int k, int v)
	{
		this->key = k;
		this->val = v;
		this->next = NULL;
	}

	int getval()
	{
		return val;
	}

	int getkey()
	{
		return key;
	}

	LinkedHashEntry* getnext()
	{
	  return next;
	}

	// Imp bcz we will acces LinkHashEntry type entry from another class
	void setnext(LinkedHashEntry* entry)
	{
	   this->next = entry;
	}
};

const int TABLE_SIZE = 128;

class Hashmap{
	LinkedHashEntry** table;
	int hsize;
public:
    Hashmap()
	{
	   table = new LinkedHashEntry*[TABLE_SIZE];
	   for(int i=0; i<TABLE_SIZE; i++)
	       table[i] = NULL;
        hsize = 0;
 	}

 	int get(int key)
    {
        int hash = key % TABLE_SIZE;
        if (table[hash] != NULL)
        {
            LinkedHashEntry* entry = table[hash];
            while(entry->getnext() != NULL && entry->getkey() != key)
                entry = entry->getnext();
            if (entry->getkey() == key)
                return entry->getval();
            else
            {
                cout<<"Key not present in hash table"<<endl;
                return -1;
            }
        }
        else
        {
            cout<<"Key not present in hash table"<<endl;
            return -1;
        }
    }

    int put(int key, int v)
    {
        int hash = key % TABLE_SIZE;
        if (table[hash] != NULL)
        {
            LinkedHashEntry* entry = table[hash];
            while(entry->getnext() != NULL && entry->getkey() != key)
                entry = entry->getnext();
            if (entry->getkey() == key)
                cout<<"Key already present in the table"<<endl;
            else
            {
                entry->setnext( new LinkedHashEntry(key,v));
                hsize ++;
            }
        }
        else
        {
            table[hash] = new LinkedHashEntry(key, v);
            hsize ++;
        }
    }
    void hremove(int key)
    {
        int hash = key % TABLE_SIZE;
        if (table[hash] != NULL)
        {
            LinkedHashEntry* entry = table[hash];
            LinkedHashEntry* prev = NULL;
            while(entry->getnext() != NULL && entry->getkey() != key)
            {
                prev = entry;
                entry = entry->getnext();
            }
            if (prev == NULL && entry->getkey() != key)
            {
                cout<<"No such key present"<<endl;
            }
            else if (prev == NULL && entry->getkey() == key)
            {
                table[hash] = entry->getnext();
                delete entry;
                hsize --;
            }
            else
            {
                LinkedHashEntry* next = entry->getnext();
                prev->setnext(next);
                delete entry;
                hsize --;
            }
        }
    }

    int hash_size()
    {
        return hsize;
    }

    ~Hashmap()
    {
        for(int k =0; k<TABLE_SIZE; k++)
        {
            if (table[k] != NULL)
            {
                LinkedHashEntry* entry = table[k];
                while(entry->getnext() != NULL)
                {
                    LinkedHashEntry* tmp = entry;
                    entry = entry->getnext();
                    delete tmp;
                }
            }
        }
        delete table;
    }
};

int main() {
	// No need of = new Hashmap()
  // Only needed when we dynamically initialise an object
  // In that case we need to write
  // Hashmap * hm= new Hashmap();
  // otherwise Hashmap hm will do
  // Remember delete takes a pointer so if we just have
  // Hashmap hm then delete hm will throw an error
  
	Hashmap* hm = new Hashmap();
	hm->put(121, 1);
	hm->put(124, 4);
	hm->put(249, 9);
	hm->put(125, 5);
	hm->put(253, 3);
	cout<<"Size of hashmap= "<<hm->hash_size()<<endl;
	cout<<"hm->get(121) "<<hm->get(121)<<endl;
	cout<<"hm->get(249) "<<hm->get(249)<<endl;
	cout<<"hm->get(253) "<<hm->get(253)<<endl;
	hm->hremove(121);
	cout<<"Size of hashmap= "<<hm->hash_size()<<endl;
	cout<<"hm->get(249) "<<hm->get(249)<<endl;
	hm->hremove(249);
	cout<<"hm->get(249) "<<hm->get(249)<<endl;
	cout<<"Size of hashmap= "<<hm->hash_size()<<endl;
	hm->put(377, 3);
	cout<<"hm->get(377) "<<hm->get(377)<<endl;
	cout<<"Size of hashmap= "<<hm->hash_size()<<endl;
	hm->hremove(125);

	delete hm;
	return 0;
}
