/*
Ternary Search Tree implementation of Autocomplete is good when the words being stored is sparsely/unevenly distributed
but if it is evenly distributed then trie is better.

Tries and ternary search trees represent a time/space trade off. If your alphabet has k symbols in it, then each node 
in a trie holds k pointers plus one extra bit for whether or not the node encodes a word. Looking up a word of length
L always takes time O(L). A ternary search tree stores three pointers per node, plus one character and one bit for 
whether or not the node encodes a word. Looking up a word of length L takes time O(L log k). (If you have a static 
ternary search tree, you can build the TST using weight-balanced trees, which improves the lookup time to O(L + log k)
but makes insertions prohibitively expensive.)

For cases where each node in the trie has most of its children used, the Trie is substantially more space efficient 
and time efficient than th ternary search tree. If each node stores comparatively few child nodes, the ternary search 
tree is much more space efficient. Typically speaking, tries are much, much faster than ternary search trees because 
fewer pointer indirections are required.

So in sort, neither structure is strictly better than the other. It depends on what words are being stored.

*/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;
#define MAX 50
char *buffer1= new char[1000] ;

// ternary search tree
typedef struct ternary_search_node
{
    char splitchar;
    int endofstring;
    struct ternary_search_node *left, *eq, *right;
}mytst;


mytst* getnode(char data)
{
    mytst* temp= new mytst();
    temp->splitchar = data;
    temp->endofstring = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}


//*******************************************Insertion****************************************************

void insert_tst(mytst** tst, const char* word, const char* insert_word)
{
    if( !(*tst) )
        *tst= getnode(*word);

    if( *word < (*tst)->splitchar )
        insert_tst( &( (*tst)->left ), word, insert_word);

    else if( *word > (*tst)->splitchar )
        insert_tst(&( (*tst)->right ), word, insert_word);

    else
    {
        if( !(*(word+1) ) )
        {
            (*tst)->endofstring =1;
            //(*tst)->eq = (mytst*) insert_word;
        }
        else
            insert_tst(& ( (*tst)->eq ), ++word, insert_word);
    }

}


//**************************************Search***************************************************

int search_tst(mytst* tst, const char* word)
{
    if(!tst)
        return 0;

    if(*word < tst->splitchar )
        return search_tst( tst->left , word);

    else if(*word > tst->splitchar )
        return search_tst( tst->right , word);

    else
    {
        if( (*(word+1) ) == '\0' )
            return tst->endofstring;
        return search_tst(tst->eq , ++word);
    }

}


//**************************************Traversal******************************************************

void traverseTSTUtil(mytst* root, char* buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        traverseTSTUtil(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->splitchar;
        if (root->endofstring)
        {
            buffer[depth+1] = '\0';
            cout<<buffer<<endl;
        }

        traverseTSTUtil(root->eq, buffer, depth + 1);

        traverseTSTUtil(root->right, buffer, depth);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void traverse(mytst* root)
{
    char buffer[MAX];
    traverseTSTUtil(root, buffer, 0);
}



//****************************************Autocomplete*********************************************************

int autocomplete_word (mytst *tst, char word[], int k)
{
    if(!tst)
    {
        cout<<"The word is not present in the dictionary\n";
        return 0;
    }


    if(*word < tst->splitchar )
        return autocomplete_word( tst->left , word, k);

    else if(*word > tst->splitchar )
        return autocomplete_word( tst->right , word, k);

    else
    {
        buffer1[k] = *word;
        if( (*(word+1) ) == '\0' )
        {
            traverseTSTUtil(tst->eq, buffer1, ++k);
            return tst->endofstring;
        }
        else
        {
            return autocomplete_word(tst->eq , ++word, ++k);
        }

    }
}




int main()
{
    //vector< string > keys = {"the", "the mask", "a", "there", "answer", "any", "by", "bye", "their", "them",
    //"the spiderman", "the batman returns" , "the life", "theme song plays always", "abhi", "abp news", "aircraft men",
    //"how i met your mother ", "happy womens day", "how to use strlen in c", "hotmail", "hindi news"};

    mytst* t= NULL;

    insert_tst(&t, "the", "the");
    insert_tst(&t, "the mask", "the mask");
    insert_tst(&t, "hello", "hello");
    insert_tst(&t, "helsinki", "helsinki");
    insert_tst(&t, "a", "a");
    insert_tst(&t, "there", "there");
    insert_tst(&t, "answer", "answer");
    insert_tst(&t, "any", "any");
    insert_tst(&t, "by", "by");
    insert_tst(&t, "bye Adams", "bye Adams");
    insert_tst(&t, "ball", "ball");
    insert_tst(&t, "rest", "rest");
    insert_tst(&t, "son", "son");
    insert_tst(&t, "help", "help");
    insert_tst(&t, "abp news", "abp news");
    insert_tst(&t, "how i met your mother", "how i met your mother");
    insert_tst(&t, "happy womens day", "happy womens day");
    insert_tst(&t, "how to use strlen in c", "how to use strlen in c");
    insert_tst(&t, "hindi news", "hindi news");


    traverse(t);
    cout<<endl;



    search_tst(t, "any") ? cout<< "Match Found" :cout<< "Match Not Found";
    cout<<" any"<<endl;
    search_tst(t, "answer") ? cout<< "Match Found" :cout<< "Match Not Found";
    cout<<" answer"<<endl;
    search_tst(t, "a") ? cout<< "Match Found" :cout<< "Match Not Found";
    cout<<" a"<<endl;
    search_tst(t, "dog") ? cout<< "Match Found" :cout<< "Match Not Found";
    cout<<" dog"<<endl;
    search_tst(t, "happy womens day") ? cout<< "Match Found" :cout<< "Match Not Found";
    cout<<" happy womens day"<<endl;
    search_tst(t, "") ? cout<< "Match Found" :cout<< "Match Not Found";
    cout<<" "<<endl<<endl;



    cout<<"Autocomplete with (a) \n";
    autocomplete_word (t, "a", 0) ;
    cout<<endl;

    cout<<"Autocomplete with (h) \n";
    autocomplete_word (t, "h", 0) ;
    cout<<endl;

    cout<<"Autocomplete with (b) \n";
    autocomplete_word (t, "b", 0) ;
    cout<<endl;

    cout<<"Autocomplete with (th) \n";
    autocomplete_word (t, "th", 0) ;
    cout<<endl;

    cout<<"Autocomplete with (hindi news) \n";
    autocomplete_word (t, "hindi news", 0) ;
    cout<<endl;

    cout<<"Autocomplete with (happy wo) \n";
    autocomplete_word (t, "happy wo", 0) ;
    cout<<endl;

    cout<<"Autocomplete with ("") \n";
    autocomplete_word (t, "", 0) ;
    cout<<endl;


    delete buffer1;
    return 0;
}


/* ************************************OUTPUT***************************************
a
abp news
answer
any
ball
by
bye Adams
happy womens day
hello
help
helsinki
hindi news
how i met your mother
how to use strlen in c
rest
son
the
the mask
there

Match Found any
Match Found answer
Match Found a
Match Not Found dog
Match Found happy womens day
Match Not Found 

Autocomplete with (a) 
abp news
answer
any

Autocomplete with (h) 
happy womens day
hello
help
helsinki
hindi news
how i met your mother
how to use strlen in c

Autocomplete with (b) 
ball
by
bye Adams

Autocomplete with (th) 
the
the mask
there

Autocomplete with (hindi news) 

Autocomplete with (happy wo) 
happy womens day

Autocomplete with () 
The word is not present in the dictionary

*/
