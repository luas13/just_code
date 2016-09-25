/* KMP Search Algo : 
a. Preprocessing Algo :Compute LPS array aka longest proper Suffix array. 
   **** Resource: https://www.youtube.com/watch?v=tWDUjkMv6Lc
b. Searching algorithm : Search pattern in given text. 
    https://www.youtube.com/watch?v=GTJr8OvyEVQ

The core of KMP algorithm needs to build a partial match table for pattern, 
which can determin how many chars need to skip if mismatch happens.

 Preprocessing Step
lps[i] = longest proper prefix of pattern[0 to i] which is also a suffix
of pattern[0 to i]
eg  for AABAACAABAA     lps[]= {0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5}
    for ABCD            lps[]= {0, 0, 0, 0}
    for AAAAA           lps[]= {0, 1, 2, 3, 4}
*/

void computeLPSArray(char* pat, int m, int *lps)
{
    int i = 1;
    int len = 0;
    lps[0] = 0;

    while(i < m)
    {
        //match means go on traversing furthers
        if (pat[i] == pat[len])
        {
            lps[i] = len + 1;
            len ++;
            i++;
        }

        //Stop at i and check until len becomes 0.
            //Find the next largest substring which is also both a proper prefix and suffix
            //lets consider length of proper prefix and suffix = 8 for substring text[0 to i-1]
            //  0   prefix1      len         suffix1       i
            //[(- - - - - - - -)  -  - - (- - - - - - - -) - - - - ]
            //  <-------8------>         <-------8------>

            //Match i.e. pat[len] == pat[i] then update lps[i] by len+1
            //  0   prefix1       len         suffix1      i
            //[(- - - - - - - -  -)  - - (- - - - - - - - -) - - - ]
            //  <-------9------>-->       <-------9------>->

            //MisMatch i.e. pat[len] != pat[i] then find next largest suffix which is also prefix
            //of sustring text[0 to i-1]. In this case lets say its p2 & s2 & length is 4
            //  0   p2             len                    s2     i
            //[{(- - - -) - - - -}  -  - - - {- - - - (- - - -)} - - - ]
            //  <--4--->                              <---4--->
            //  <------8--------->           <------8--------->  
            //Equivalently its as below since p1 = s1. new position of len is basically lps[len-1]
            //  0   p2  len  s2                            
            //[{(- - - -)(- - - -)}  -  - - - {- - - - (- - - -)} - - - ]
            //  <--4---> <---4--->                            
            //  <------8--------->            <-------8-------->       
            
            //try to go as much "left" as possible on pattern array, i.e go on decreasing len 
            //so that pat[len] matches pat[i] otherwise make lps[i] = 0 when we cant decrease len
        else
        {           
            if (len != 0)
                len = lps[len-1];        // ****vvi remember, it's not lps[i-1]
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


//In the process, "i" never decreases and only j changes. 
//This without looking back, this algorithm can move forward and thus will be of
// time complexity O(n) where n is the length of the text.
void KMP(char* text, int n, char* pat, int m)
{
    int i= 0;
    int j= 0;
    int* lps = (int*) malloc(sizeof(int) * m);
    computeLPSArray(pat, m, lps);

    while(i < n)
    {
        if (text[i] == pat[j])
        {
            i++;
            j++;
        }
        //2 cases
        //a. len != 0, means there is no need to search for 1st lps[len-1] no of characters
        // as we already know them and we have just already compared that many no of 
        // characters before hitting a mismatch now. So don't make l=0 rather update it
        // uptil we know, i.e. the length of prefix/suffix. 

        //b. len == 0, means we have reached a point where even the 1st character of pattern
        //does not match so we update the lps for that particular i as 0 and scan for next
        //characters
        if (text[i] != pat[j])
        {           
            if (j != 0)
                j = lps[j-1];
            else
                i++;
        }
        if(j == m)
        {
            printf("pattern found at %d\n", i-j);
            j = lps[j-1];
        }
    }
}
