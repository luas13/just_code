// Soln 1: Iterative soln, with better time complexity
// Prints only unique combinations

#include <iostream>
#include <vector>
#include<string>
#include<algorithm>

using namespace std;

vector<string> permuteUnique(string& str) {
        vector<string> vv;
        vv.push_back(str);
        
        int l = str.length();
        if (l<2)
            return vv;
        
        for(int pos=0; pos<l-1; pos++)
        {
            int s = vv.size();
            for(int i=0; i<s; i++)
            {
                sort(vv[i].begin()+pos, vv[i].end());
                for(int j=pos+1; j<l; j++)
                {
                    // reset to old vector
                    string v = vv[i];
                    
                    // perform swap on this vector
                    if (j-1 >= 0 && v[j] == v[j-1])
                        continue;
                    
                    swap(v[j], v[pos]);
                    vv.push_back(v);
                }
            }
        }
        
        cout<<"Orignal string is: "<<str<<endl;
        cout<<"Total permuations formed: "<<vv.size()<<endl<<endl;
        for(int i=0; i<vv.size(); i++)
            cout<<vv[i]<<endl;
            
        return vv;
}

int main()
{
    string s = "geek";
    permuteUnique(s);

    return 0;
}


//-------------------------------------------------------------------
// Soln 2
Input: "abc"
// Output
abc
acb
bac
bca
cab
cba

  " " + 'a'           "a" + 'b'       "ab" + 'c' = "abc"
    |                    |                |
    v                    v                v
    a b c --> (b c) -->  b c --> (c) -->  c
    
  " " + 'a'           "a" + 'c'       "ac" + 'b' = "acb"
    |                      |              |
    v                      v              v
    a b c --> (b c) -->  b c --> (b) -->  b
                        
 ------------------------------------------------------------   
  " " + 'b'           "b" + 'a'       "ba" + 'c' = "bac"
      |                  |                |
      v                  v                v
    a b c --> (a c) -->  a c --> (c) -->  c
  
  " " + 'b'           "b" + 'c'       "bc" + 'a' = "bca"
      |                    |              |
      v                    v              v
    a b c --> (a c) -->  a c --> (a) -->  a
 -------------------------------------------------------------
 
 " " + 'c'           "c" + 'a'       "ca" + 'b' = "cab"
        |                |                |
        v                v                v
    a b c --> (a b) -->  a b --> (b) -->  b
  
" " + 'c'           "c" + 'b'       "cb" + 'a' = "cba"
        |                  |              |
        v                  v              v
    a b c --> (a b) -->  a b --> (a) -->  a
 -------------------------------------------------------------
 
// 1. One method is using C strings and swap function(Not in Order)
// 2. print n! permutation of the characters of the string s (in order)

#include <iostream>
#include <vector>

using namespace std;

void permuteutil(vector<string>& res, string prefix, string s)
{
	int n = s.length();
	if (!n)
	{
		cout<<prefix<<endl;
		res.push_back(prefix);
	}
	else
	{
		for(int i=0; i<n; i++)
			permuteutil(res, prefix + s[i], s.substr(0,i) + s.substr(i+1, n-i-1));
	}
}

void permute(vector<string>& res, string s)
{
	permuteutil(res, "", s);
}


int main() {
	// your code goes here
	string s = "abc";
	vector<string> res;
	permute(res, s);
	return 0;
}

//-----------------------------------------------------------------
// Soln: 3 Pure recursive

#include <iostream>
#include <string>
using namespace std;

/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
void permute(string a, int l, int r)
{
int i;
if (l == r)
	cout<<a<<endl;
else
{
	for (i = l; i <= r; i++)
	{
		swap(a[l], a[i]);
		permute(a, l+1, r);
		swap(a[l], a[i]); //backtrack
	}
}
}

/* Driver program to test above functions */
int main()
{
	string str = "ABC";
	int n = str.length();
	permute(str, 0, n-1);
	return 0;
}


// In case you want to print all the variants of a string
// meaning all the permutations of different combinations
// ABC=> A, B, C, AB, AC, BC, ABC, BA, CA, CB, BAC, BCA

// Algo: I think
/* Generate all the combinations.
For each combination, call permuteUnique() as above for each combination

// For generating different combinations in increasing manner:

Simplest way of calculating the possible combinations of strings is here ...

Mathematically to find R combinations in a given lot of N = NcR

So what we are finding here is, all possible combinations = Nc0 + Nc1 .... + Ncn = 2 Pow N

So you get 2 Pow N combinations for given word of length N characters.

If you represent 1 to (2 Pow N) integers in binary, and place your char in the place where 1 is present, finally you would get the solution.

Example:
Input : ABC

Solution :

ABC length is 3. So possible combinations 2 Pow 3 = 8

If 0 - 8 represented in binary

000 =

001 = C

010 = B

011 = BC

100 = A

101 = AC

110 = AB

111 = ABC

all possible combinations are shown above.

*/
