/*

Simple insertion ,searching and deletion of words without space.
Searching an empty string will return Not present in trie

*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define a_size 27

typedef struct node
{
    int val;
    struct node* child[a_size];
}tnode;


// trie ADT
typedef struct trie
{
    tnode* root;
    int count;
}mytrie;


tnode* getnode()
{
    tnode* temp = new tnode();
    temp->val = 0;
    for(int i=0; i<27; i++)
        temp->child[i] = NULL;

    return temp;
}


void initialise(mytrie *t)
{
    t->root = getnode();
    t->count = 0;
}


void insert(mytrie *t, string key)
{
    int l= key.length();
    t->count ++;
    tnode* temp = t->root;

    for(int i=0; i<l; i++)
    {
        int index = (int) key[i] - (int)'a';
        if( !temp->child[index] )
            temp->child[index] = getnode();
        temp= temp->child[index];
    }
    temp->val= t->count;

}

int search(mytrie* t, string key)
{
    int l= key.length();
    if( l == 0 ) return 0;
    tnode* temp = t->root;

    for(int i=0; i<l; i++)
    {
        int index = (int) key[i] - (int)'a';
        if( !temp->child[index] )
            return 0;
        temp= temp->child[index];
    }
    return (temp && temp->val);
}

int isfree( tnode* tn)
{
    for(int i=0; i<27; i++)
        if(tn->child[i])
            return 0;
    return 1;
}

int delete_util(tnode* tn, string key, int level, int l)
{
    if(tn)
    {
        if(level == l)
        {
            if( tn->val )
            {
                tn->val = 0;
                if(isfree(tn))
                    return 1;
                else
                    return 0;
            }
        }

        else
        {
            int index= (int) key[level] - (int) 'a';
            if( delete_util( tn->child[index], key, level+1, l ) )
            {
                delete( tn->child[index] );
                return ( !tn->val && isfree(tn));
            }
        }
    }
    return 0;
}

void delete_t(mytrie* t, string key)
{
    int l= key.length();
    if( l>0 )
    {
        delete_util(t->root,key,0,l);
    }
}

int main()
{
    vector< string > keys = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    vector< string > output = {"Not present in trie", "Present in trie"};

    mytrie t;      //ADT so no pointer

    initialise(&t);

    // Construct trie
    for(int i = 0; i < keys.size() ; i++)
    {
        insert(&t, keys[i]);
    }

    // Search for different keys
    cout<<"the => "<<output[ search(&t, "the")] <<endl;
    cout<<"these => "<<output[ search(&t, "these")] <<endl;
    cout<<"their => "<<output[ search(&t, "their")] <<endl;
    cout<<"thaw => "<<output[ search(&t, "thaw")] <<endl;
    cout<<" => "<<output[ search(&t, "")] <<endl;


    cout<<"deletion operation \n";
    delete_t(&t, keys[0]);
    cout<<"the => "<<output[ search(&t, "the")] <<endl;

    return 0;
}
