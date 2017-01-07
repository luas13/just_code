// Sometimes one needs to create a priority queue to contain
// user defined objects. In this case, the priority queue
// needs to know the comparison criterion used to determine
// which objects have the highest priority. This is done by
// means of a function object beloging to a class that
// overloads the operator (). The overloaded () acts as < for
//  the purpose of determining priorities. For example, suppose
// we want to create a priority queue to store Time objects.
// A Time object has three fields: hours, minutes, seconds:

// By default a priority queue implements a max heap

#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Time {
    int h; // >= 0
    int m; // 0-59
    int s; // 0-59
};

/*
If we wanted earliest times to have the highest priority, we would redefine CompareTime like this:

class CompareTime {
public:
    bool operator()(Time& t1, Time& t2) // t2 has highest prio than t1 if t2 is earlier than t1
    {
       if (t2.h < t1.h) return true;
       if (t2.h == t1.h && t2.m < t1.m) return true;
       if (t2.h == t1.h && t2.m == t1.m && t2.s < t1.s) return true;
       return false;
    }
};
*/

class CompareTime {
public:
    bool operator()(Time& t1, Time& t2)
    {
       if (t1.h < t2.h) return true;
       if (t1.h == t2.h && t1.m < t2.m) return true;
       if (t1.h == t2.h && t1.m == t2.m && t1.s < t2.s) return true;
       return false;
    }
};

int main()
{
    priority_queue<Time, vector<Time>, CompareTime> pq;

    // Array of 4 time objects:

    Time t[4] = { {3, 2, 40}, {3, 2, 26}, {5, 16, 13}, {5, 14, 20}};

    for (int i = 0; i < 4; ++i)
       pq.push(t[i]);

    while (! pq.empty()) {
       Time t2 = pq.top();
       cout << setw(3) << t2.h << " " << setw(3) << t2.m << " " <<
       setw(3) << t2.s << endl;
       pq.pop();
    }

    return 0;
}
