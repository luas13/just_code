/*
http://www.cnblogs.com/grandyang/p/6944331.html

Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, return a list that only contains this file's name. 
If it is a directory path, return the list of file and directory names in this directory. Your output 
(file and directory names together) should in lexicographic order.

mkdir: Given a directory path that does not exist, you should make a new directory according to the path. 
If the middle directories in the path don't exist either, you should create them as well. 
This function has void return type.

addContentToFile: Given a file path and file content in string format. If the file doesn't exist, 
you need to create that file containing given content. If the file already exists, you need to 
append given content to original content. This function has void return type.

readContentFromFile: Given a file path, return its content in string format.

Example:

Input: 
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]
Output:
[null,[],null,null,["a"],"hello"]
Explanation:
filesystem

 

Note:

You can assume all file or directory paths are absolute paths which begin with / 
and do not end with /except that the path is just "/".

You can assume that all operations will be passed valid parameters and users 
will not attempt to retrieve file content or list a directory or file that does not exist.

You can assume that all directory names and file names only contain lower-case letters, 
and same names won't exist in the same directory.



Soln:
This problem allows us to design a memory file system, 
1. to achieve the display of the current file,
2. create a file, 
3. add content to a file, 
4. read the contents of the file and other functions,

I feel like simulating a terminal command. This trick is more tricky for ls command, 
the example in the title can not actually show the ls requirements, the files and folders 
are handled differently. Because there is no suffix in the file, the last string may be a 
file or a folder. Such as a / b / c, then the last c may be a folder, it may well be a file, 
if c is a folder, ls command to output all files and folders in the folder c, and when c is 
a file Then only need to output the file c can be. 

Also note that when creating a folder, 
there is no folder on the path to be created. There is also a folder in the path that is 
created when you add content to the file. Forum on the issue of high votes solution have 
a new custom class, but bloggers generally do not like to use custom classes to solve problems, 
and feel that those who use a custom class solution is not more concise and easy, so here 
The blogger does not create a custom class, but rather uses two hashes to do, where dirs 
creates a mapping of paths and their corresponding collections of all files and folders, 
files creates the path to the file, The mapping between its contents.

The beginning of the root directory "/" into the dirs, and then see ls implementation, 
if the path exists in files, the last string is a file, then we will take out the 
file name to return, if it does not exist , That the last string is a folder, then we 
dirs to remove all the things in the folder can be returned. Let's look at the mkdir function, 
our approach is based on the "/" to separate the delimited string, if it is Java, then use 
String's own split function just fine, but C ++ does not have Java so much comes with 
functions, so only With string stream class to deal with the method is to separate the 
path of each layer, and then add the layer files or folders to the corresponding collection, 
pay attention to the place is to deal with the root directory, you must first add "/ ", 
Other situations are added. The following addContentToFile function, first of all separate 
the path and file name, if the path is empty, indicating that the root directory, you need 
to add "/" and then see if this path already exists in the dirs, if not exist, call mkdir 
to create The path, and then add the file to the path corresponding to the collection, and 
then add the contents of the file path mapping. The final read the contents of the file is 
quite simple, you can return directly in the file, see the code below:
*/


# include <iostream>
# include <vector>
# include <string>
# include <unordered_map>
# include <set>
# include <sstream>

using namespace std;

class FileSystem {
public:
    FileSystem() {
        // Effect of this statement is that dirs map 
        // just contain an entry of key: "/" with
        // no value
        dirs["/"];
    }
    
    // check if the path is a folder or file
    // if it's a file just output filename
    // if it's folder, output all files & folder inside it
    
    vector<string> ls(string path) {
        // count no of files with this path as entry in
        // files unordered_map
        if (files.count(path)) {
            // gives the last index of character '/' in the path
            int idx = path.find_last_of('/');
            return {path.substr(idx + 1)};
        }
        auto t = dirs[path];
        return vector<string>(t.begin(), t.end());
    }
    
    void mkdir(string path) {
        // istringstream is(path);
        // stringstream will also work
        stringstream is(path);
        string t = "", dir = "";
        // keys of dirs are like /, /a, or /a/b
        while (getline(is, t, '/')) {
            if (t.empty()) continue;
            if (dir.empty()) dir += "/";
            dirs[dir].insert(t);
            // checking if there is any more character 
            // in string dir, apart from "/"
            if (dir.size() > 1) dir += "/";
            dir += t;
        }
    }
    
    void addContentToFile(string filePath, string content) {
        int idx = filePath.find_last_of('/');
        string dir = filePath.substr(0, idx);
        string file = filePath.substr(idx + 1);
        if (dir.empty()) dir = "/";
        // create a directory, if it doesn't exist
        if (!dirs.count(dir)) mkdir(dir);
        
        // So here we are also adding a file in 
        // a directory
        dirs[dir].insert(file);
        files[filePath].append(content);
    }
    
    string readContentFromFile(string filePath) {
        return files[filePath];
    }
    
private:
    unordered_map<string, set<string>> dirs;
    unordered_map<string, string> files;
};

void printContent(vector<string> &r)
{
    // cout<<"r.size() "<<r.size()<<endl;
    for(auto it = r.begin(); it != r.end(); it++)
        cout<<*it<<" ";
    cout<<endl;
}
int main()
{
    vector<string> res = fs->ls("/");
    printContent(res);
    
    fs->mkdir("/a/b/c");
    res = fs->ls("/");
    cout<<"ls: / content is"<<endl;
    printContent(res);
    
    fs->addContentToFile("/a/b/c/d", "hello");
    cout<<"Read contents from file a/b/c/d is"<<endl;
    cout<<fs->readContentFromFile("/a/b/c/d")<<endl;
    
    fs->mkdir("/a/b/c/e");
    res = fs->ls("/a/b/c");
    cout<<"ls: /a/b/c content is"<<endl;
    printContent(res);
}


/*
Output:
ls: / content is
a 
Read contents from file a/b/c/d is
hello
ls: /a/b/c content is
d e  
** check we have a dir with the name 'e' & 
a file with the name 'd' on the path /a/b/c
*/
