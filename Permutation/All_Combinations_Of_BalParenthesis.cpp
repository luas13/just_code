// Program to Print all combinations
// of balanced parentheses
# include <iostream>
# include <string>
# include <vector>

using namespace std;

class Solution{
public:
    void helper(vector<string>& res, int n, int open, int close, string str)
    {
    	if(close == n) 
    	{
    		res.push_back(str);
    		return;
    	}
    	else
    	{
    		if(open > close) 
    			helper(res, n, open, close+1, str+"}");
    		
    		if(open < n)
    		    helper(res, n, open+1, close, str+"{");
    	}
    } 
    
    void printParenthesis(vector<string>& res, int n)
    {
        string str= "";
    	if(n > 0)
    		helper(res, n, 0, 0, str);
    	return;
    }
};

// Driver program to test above functions
int main()
{
	Solution obj;
	int n = 3;
	vector<string> res;
	obj.printParenthesis(res, n);
	
	for(auto bstr: res)
	    cout<<bstr<<endl;
	return 0;
}
