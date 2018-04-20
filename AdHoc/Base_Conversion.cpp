/*
Problem 1.1, pg. 2: Write a function that performs base conversion. Specifically, the input
is an integer base b1, a string s, representing an integer x in base b1, and another integer base
b2; the output is the string representing the integer x in base b2. Assume 2 ≤ b1, b2 ≤ 16.
Use “A” to represent 10, “B” for 11, . . . , and “F” for 15.

Solution 1.1: We can convert the base-b1 string s to a variable x of integer type, and
then convert x to a base-b2 string a. For example, if the string is “615”, b1 = 7 and
b2 = 13, then in decimal x is 306, and the final result is “1A7”.


The time complexity is O(n(1 + logb2b1)), where n is the length of s. The reasoning is
as follows. First, we perform n multiply-and-adds to get x from s. Then we perform
logb2 x multiply and adds to get the result. The value x is upper-bounded by b1^n, and
logb2(b1n) = n logb2b1.

*/

string ConvertBase (const string& s, int b1 , int b2) {
    bool is_negative = s.front () == ’-’;
    int x = 0;
    for (size_t i = ( is_negative == true ? 1 : 0); i < s.size (); ++i) {
        x *= b1;
        x += isdigit(s[i]) ? s[i] - ’0’ : s[i] - ’A’ + 10;
    }

    string result;
    do {
        int remainder = x % b2;
        result.push_back(remainder >= 10 ? ’A’ + remainder - 10 : ’0’ + remainder);
        x /= b2;
    } while (x);

    if ( is_negative ) { // s is a negative number.
       result.push_back (’-’);
    }

    reverse(result.begin(), result.end());

    return result;
 }
