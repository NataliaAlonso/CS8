#include <iostream>
#include "myqueue.h"

using namespace std;

int main()
{

    queue<int> start;
    queue<int> temp;
    queue<int> end;

    start.push(1);
    start.push(2);
    start.push(3);

    end.push(start.top());
    start.pop();
    cout << "Disk " << end.top() << " -> Peg C" <<endl;
    temp.push(start.top());
    start.pop();
    cout << "Disk " << temp.top() << " -> Peg B" <<endl;
    temp.push(end.top());
    end.pop();
    cout << "Disk " << temp.top() << " -> Peg B" <<endl;
    end.push(start.top());
    start.pop();
    cout << "Disk " <<end.top() << " -> Peg C" <<endl;
    start.push(temp.top());
    temp.pop();
    cout << "Disk " << start.top() << " -> Peg A" <<endl;
    end.push(temp.top());
    temp.pop();
    cout << "Disk " << end.top() << " -> Peg C" <<endl;
    cout << start.top() <<endl;
    end.push(start.top());

    start.pop();

    cout << "Emptied start" <<endl;
    cout << "Disk " << end.top() << " -> Peg C" <<endl;



    return 0;
}

