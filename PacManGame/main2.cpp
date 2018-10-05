#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "BFS.h"
using namespace std;
int main()
{
    fstream f("maze2.txt");
    BFS w(f);
    stack<Cell> s = w.FindPath();
    /*cout << w << endl;
    while(s.size()){
        cout<<s.top()<<endl;
        s.pop();
    }
   //w.~BFS();*/
    return 0;
}
