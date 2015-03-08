#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#define a_size 27

//char buffer[1000];
char *buffer= new char[1000] ;

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


//**********************************************************************************************
//Insert

void insert(mytrie *t, string key)
{
    int l= key.length();
    t->count ++;
    tnode* temp = t->root;

    for(int i=0; i<l; i++)
    {
        int index;
        if(key[i] == ' ')
            index=26;
        else
            index = (int) key[i] - (int)'a';
        if( !temp->child[index] )
            temp->child[index] = getnode();
        temp= temp->child[index];
    }
    temp->val= t->count;

}

//****************************************************************************************************
//Search

int search(mytrie* t, string key)
{
    int l= key.length();
    if( l == 0 ) return 0;
    tnode* temp = t->root;

    for(int i=0; i<l; i++)
    {
        int index;
        if(key[i] == ' ')
            index=26;
        else
            index = (int) key[i] - (int)'a';

        if( !temp->child[index] )
            return 0;
        temp= temp->child[index];
    }
    return (temp && temp->val);
}



//************************************************************************
// Autocomplete and Print
//Simple DFS

void printTrieUtil (tnode* tn, char buffer[], int len)
{
    for(int i=0; i<27; i++)
    {
        if(tn->child[i])
        {
            if(i==26)
                buffer[len] =' ';
            else
                buffer[len] = i + 'a' ;

            if(tn->child[i]->val != 0)
            {
                buffer[len+1] = '\0' ;
                cout<<buffer<<endl;
            }

            printTrieUtil(tn->child[i], buffer ,len+1 );

        }
    }
}

void autocomplete_word (mytrie *t, char str[])
{
    //str.clear();
    //buffer[0]= '\0';
    tnode* tn= t->root;
    //int l= str.length();
    int l= strlen(str);

    if(l == 0)
    {
        cout<<"\nThe input is empty.Type something...\n";
        return;
    }

    cout<<"The input string is \n"<<str<<endl;

    strcpy(buffer, str);
    //str.copy(buffer, 0, l);

    for( int i=0; tn && i<l; i++)
    {
        int index= (int)str[i] - (int)'a';
        if(tn->child[index] != 0)
        {
            tn= tn->child[index];
        }
        else
        {
            cout<<"\n The word is not present in the dictionary\n";
            return;
        }
    }

    //cout<<"\n\nAutocomplete Selected strings are : \n";
    printTrieUtil (tn, buffer ,l);
    cout<<endl;

}

void printTrie (mytrie* pTrie) {
    tnode *pCrawl = pTrie->root ;
    printf ( "\nThe whole trie contains :\n") ;
    printTrieUtil (pCrawl, buffer, 0) ;
}


//********************************************************************************************


int main()
{
    vector< string > keys = {"the", "the mask", "a", "there", "answer", "any", "by", "bye", "their", "them",
    "the spiderman", "the batman returns" , "the life", "theme song plays always", "abhi", "abp news", "aircraft men",
    "how i met your mother ", "happy womens day", "how to use strlen in c", "hotmail", "hindi news"};

    vector< string > output = {"Not present in trie", "Present in trie" };

    mytrie t;      //ADT so no pointer

    initialise(&t);

    // Construct trie
    for(int i = 0; i < keys.size() ; i++)
    {
        insert(&t, keys[i]);
    }

    //printTrie (&t) ;
    //autocomplete_word (&t, "th") ;
    autocomplete_word (&t, "a") ;
    autocomplete_word (&t, "h") ;
    autocomplete_word (&t, "ho") ;
    autocomplete_word (&t, "") ;


    delete(buffer);

    return 0;
}
