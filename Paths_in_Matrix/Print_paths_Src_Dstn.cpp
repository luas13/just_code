#include<iostream>
#include<string>
using namespace std;

/* print all the paths robot can take to reach cell(n-1,n-1)
   from cell(0), given a maze in the form of a matrix of size nxn
   and the robot can move only 'Right' and 'Down'
   (r_idx,c_idx) -> starting point of robot      
*/
void printRobotPaths(string path,int row,int col,int r_idx,int c_idx) {
   if ((r_idx == row-1) && (c_idx == col-1)) {
      cout<<path<<endl;
      return;
   }
   if (r_idx == row-1) {
      printRobotPaths(path+'D',row,col,r_idx,c_idx+1);
      return;
   }
   if (c_idx == col-1) {
      printRobotPaths(path+'R',row,col,r_idx+1,c_idx);
      return;
   }
   printRobotPaths(path+'D',row,col,r_idx,c_idx+1);
   printRobotPaths(path+'R',row,col,r_idx+1,c_idx);
}

// main
int main() {
   // dimensions of the maze is row x col
   int row = 3, col = 3;
   string path;
   cout<<"\nAll possible paths :-\n";
   printRobotPaths(path,row,col,0,0);
   cout<<endl;
   return 0;
}
