// Soln 1: Iterative soln, with better time complexity

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> permuteUnique(string& nums) {
        vector<string> vv;
        int l = nums.size();
        if (l<2)
            return vv;
        
        vv.push_back(nums);
        
        for(int pos=0; pos<l-1; pos++)
        {
            int s = vv.size();
            for(int i=0; i<s; i++)
            {
                sort(vv[i].begin()+ pos, vv[i].end());
                
                for(int j=pos+1; j<l; j++)
                {
                    string v = vv[i];
                    
                    if (j>0 && v[j] == v[j-1])
                        continue;
                    
                    swap(v[pos], v[j]);
                    vv.push_back(v);
                }
            }
        }
        return vv;
    }
};


// Driver code
int main()
{
	// Creating object of the class
	Solution object;
    	string s = "abac";

	vector<string> res = object.permuteUnique(s);

	for(int i=0; i<res.size(); i++)
	    cout<<res[i]<<endl;
	
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

