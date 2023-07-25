// <https://en.cppreference.com/w/cpp/container/deque>
#include <iostream>
#include <deque>
#include "utils.h"

int main()
{
    /*
    class deque {
        ...
    protected:
        iterator start;
        iterator finish;
        map_pointer map; // T**
        size_type map_size;
    }

    struct __deque_iterator {
        ...
        T* cur;
        T* first;
        T* last;
        map_pointer node;
    }
    */
    std::deque<int> dq = {1, 2, 3};
    std::deque<int>::iterator it = dq.begin();

    std::cout << sizeof(it) << std::endl;
    std::cout << sizeof(dq) << std::endl;


    std::cout << "dq.size() : " << dq.size();
    std::cout << "\ndq.max_size() : " << dq.max_size();
 
    std::cout << "\ndq.front() : " << dq.front();
    std::cout << "\ndq.back() : " << dq.back() << std::endl;

    dq.push_back(4);
    print("deque", dq);

    dq.pop_front();
    print("deque", dq);


    return 0;
}