# include <sstream>
# include <iostream>
# include <fstream>

using namespace std;

// Make sure to create a file.txt
// unget(): Attempts to decrease the current location in the stream by one character
// get(): Extracts a single character from the stream.

bool getNextToken(string &token, fstream &fd, bool &isNumber)
{
    if (getline(fd, token, ' '))
    {
        if(fd.unget().get() == '\n')
            return false;

        if (token.compare("#") == 0)
            isNumber = false;
        else
            isNumber = true;
        return true;
    }
    //return false;
}

int main()
{
    string token;
    fstream file("file.txt");
    bool isNumber = false;

    while(getNextToken(token, file, isNumber))
    {
        if (isNumber)
            cout<<token<<endl;
        else
        {
            cout<<token<<endl;
            cout<<"Not a number"<<endl;
        }
    }

    file.close();
}


/*
file content is 

30 10 50 # # # 20 45 # # 35 # #

Output:
30
10
50
#
Not a number
#
Not a number
#
Not a number
20
45
#
Not a number
#
Not a number
35
#
Not a number


std::string token;
std::ifstream file("file.txt");
while(std::getline(file, token)) {
    std::istringstream line(token);
    while(line >> token) {
        std::cout << "Token :" << token << std::endl;
    }
    if(file.unget().get() == '\n') {
        std::cout << "newline found" << std::endl;
    }
}
*/
